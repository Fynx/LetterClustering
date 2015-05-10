#pragma once

#include <QtCore/QList>
#include <QtCore/QString>

struct Point {
	static const int Noise = -1;
	static const int Unclassified = 0;
	int clusterId;

	Point(const QList<int> &points)
		: clusterId(Unclassified), points(points)
	{}

	inline bool operator==(const Point &p);
	inline operator QString() const;
	inline int operator[](int i) const;
	inline static int distanceSquared(const Point &p1, const Point &p2);
	inline int dim() const;

private:
	QList<int> points;
};

class DBScan {
public:
	DBScan(const QList<Point> &points, qreal eps, int minPts);

	const QList<Point> &getPoints() const;

	void run();

	void printPoints() const;
	void printClusters() const;
	void printNoise() const;

private:
	void setClusters();
	void setRegion(int index);
	bool expandCluster(int index, int clusterId);

	QList<Point> points;
	QList<QList<int> > clusters;
	QList<int> region;
	qreal eps;
	int minPts;
};


inline bool Point::operator==(const Point &p)
{
	for (int i = 0; i < points.size(); ++i)
		if (points[i] != p[i])
			return false;
	return true;
}

inline Point::operator QString() const
{
	QString str("(");
	for (int x : points)
		str += QString::number(x) + " ";
	str += ")";
	return str;
}

inline int Point::operator[](int i) const
{
	return points[i];
}

inline int Point::distanceSquared(const Point &p1, const Point &p2)
{
	int result = 0;
	for (int i = 0; i < p1.points.size(); ++i)
		result += (p2[i] - p1[i]) * (p2[i] - p1[i]);
	return result;
}

int Point::dim() const
{
	return points.size();
}
