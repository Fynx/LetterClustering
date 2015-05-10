#pragma once

#include <QtCore/QList>
#include <QtCore/QString>

struct Point {
	static const int Noise = -1;
	static const int Unclassified = 0;
	int x, y, clusterId;

	Point(int x, int y)
		: x(x), y(y), clusterId(Unclassified)
	{}

	inline bool operator==(const Point &p)
	{
		return x == p.x && y == p.y;
	}

	inline operator QString() const
	{
		return QString("(%1, %2)").arg(x).arg(y);
	}

	inline static int distanceSquared(const Point &p1, const Point &p2)
	{
		int diffX = p2.x - p1.x;
		int diffY = p2.x - p1.x;
		return diffX * diffX + diffY * diffY;
	}
};

class DBScan {
public:
	DBScan(const QList<Point> &points, qreal eps, int minPts);

	void run();
	void setClusters();
	void setRegion(int index);
	bool expandCluster(int index, int clusterId);

	void printPoints() const;
	void printClusters() const;
	void printNoise() const;

private:
	QList<Point> points;
	QList<QList<int> > clusters;
	QList<int> region;
	qreal eps;
	int minPts;
};
