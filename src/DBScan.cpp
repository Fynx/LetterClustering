#include "DBScan.hpp"
#include <QDebug>

DBScan::DBScan(const QList<Point> &points, qreal eps, int minPts)
	: points(points), eps(eps), minPts(minPts)
{}

void DBScan::run()
{
	setClusters();

	printPoints();
	printClusters();
	printNoise();
}

void DBScan::setClusters()
{
	if (points.isEmpty())
		return;

	eps *= eps; /** square eps */
	int clusterId = 1;
	for (int i = 0; i < points.size(); ++i) {
		Point p = points[i];
		qDebug() << "point" << p;
		if (p.clusterId == Point::Unclassified)
			if (expandCluster(i, clusterId))
				++clusterId;
	}

	/** sort out points into their clusters, if any */
	int maxClusterId = 0;
	for (const Point &p : points)
		maxClusterId = qMax(maxClusterId, p.clusterId);
	if (maxClusterId < 1)
		return; /** no clusters, so list is empty */

	for (int i = 0; i < maxClusterId; i++)
		clusters.append(QList<int>());
	for (int i = 0; i < points.size(); ++i) {
		Point p = points[i];
		if (p.clusterId > 0)
			clusters[p.clusterId - 1].append(i);
	}
	return;
}

void DBScan::setRegion(int index)
{
	Point p = points[index];
	region.clear();
	for (int i = 0; i < points.size(); ++i) {
		Point cp = points[i];
		int distSquared = Point::distanceSquared(p, cp);
		if (distSquared <= eps)
			region.append(i);
	}
}

bool DBScan::expandCluster(int index, int clusterId)
{
	qDebug() << "expandCluster:" << points[index] << "clusterId:" << clusterId;

	setRegion(index);
	QList<int> seeds = region;

	qDebug() << "seeds:" << seeds;
	if (seeds.size() < minPts) { /** no core point */
		points[index].clusterId = Point::Noise;
		qDebug() << "NO CORE POINT.";
		return false;
	}
	/** all points in seeds are density reachable from point 'p' */
	for (int i : seeds)
		points[i].clusterId = clusterId;
	seeds.removeOne(index);
	while (seeds.size() > 0) {
// 		qDebug() << "seeds now:" << seeds;
		int currentIndex = seeds[0];
		setRegion(currentIndex);
// 		qDebug() << "result:" << region;
		if (region.size() >= minPts) {
			for (int i : region) {
				Point &resultP = points[i];
				if (resultP.clusterId == Point::Unclassified || resultP.clusterId == Point::Noise) {
					if (resultP.clusterId == Point::Unclassified)
						seeds.append(i);
					resultP.clusterId = clusterId;
				}
			}
		}
		seeds.removeOne(currentIndex);
	}
	return true;
}

void DBScan::printPoints() const
{
	/** print points to console */
	QString str;
	for (const Point &p : points)
		str += p + " ";
	qDebug() << "The" << points.size() << "points are:" << str;
}

void DBScan::printClusters() const
{
	for (int i = 0; i < clusters.size(); i++) {
		QString str;
		int count = clusters[i].size();
		QString plural = (count != 1) ? "s" : "";
		qDebug("\nCluster %d consists of the following %d point%s:",
		       i + 1, count, plural.toStdString().c_str());
		for (int j : clusters[i])
			str += " " + points[j] + " ";
		qDebug() << str;
	}
}

void DBScan::printNoise() const
{
	int total = 0;
	for (const QList<int> &list : clusters)
		total += list.size();

	/** print any points which are Noise */
	total = points.size() - total;
	if (total > 0) {
		QString plural = (total != 1) ? "s" : "";
		QString verb = (total != 1) ? "are" : "is";
		qDebug("\nThe following %d point%s %s NOISE :\n",
		       total, plural.toStdString().c_str(), verb.toStdString().c_str());
		QString str;
		for (const Point &p : points)
			if (p.clusterId == Point::Noise)
				str += " " + p + " ";
		qDebug() << str;
	} else {
		qDebug() << "\nNo points are NOISE";
	}
}
