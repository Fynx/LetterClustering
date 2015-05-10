#include "LetterClustering.hpp"
#include "DBScan.hpp"

#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include <qmath.h>
#include <iostream>

LetterClustering::LetterClustering()
{
	QString dirPath("data/data/");
	QDir dir(dirPath);
	for (const QString &path : dir.entryList()) {
		LetterClustering::ImgData imgData = loadImage(dirPath + "/" + path);
		if (!imgData.isEmpty()) {
			tra.append(imgData);
			fileNames.append(path);
		}
	}

        double eps = 1.038;
        int minPts = 3;

	if (tra.isEmpty()) {
		qDebug() << "No images.";
		exit(0);
	}

	QList<Point> imgs;
	for (const ImgData &data : tra)
		imgs.append(Point(data));

	DBScan dbscan(imgs, eps, minPts);
	dbscan.run();

	QMap<int, QList<QString> > clusters;

	int i = 0;
	int huge = 10000;
	for (const Point &point : dbscan.getPoints()) {
		if (point.clusterId == Point::Noise)
			clusters[huge++].append(fileNames[i++]);
		else
			clusters[point.clusterId].append(fileNames[i++]);
	}

// 	qDebug() << dbscan.getPoints();

	i = 1;
	for (const QList<QString> &c : clusters) {
		qDebug() << i++;
		QString str;
		for (const QString &s : c)
			str += s + " ";
		std::cout << str.toStdString() << "\n";
	}

	exit(0);
}

LetterClustering::~LetterClustering()
{}

LetterClustering::ImgData LetterClustering::loadImage(const QString &path)
{
	QImage image(path);
	QList<QPair<int, QPoint> > data;

	if (image.isNull())
		return {};

	int minY = image.height();
	int minX = image.width();

	auto isBlack = [](QRgb rgb) -> int {
		return (int) qGray(rgb) < 100;
	};

	for (int i = 1; i < image.height(); ++i) {
		for (int j = 1; j < image.width(); ++j) {
			data.append({isBlack(image.pixel(j, i)), QPoint(j, i)});
			minX = qMin(minX, j);
			minY = qMin(minY, i);
		}
	}

	for (auto &p : data)
		p.second -= QPoint(minX, minY);


	static const int Width  = 10;
	static const int Height = 10;

	int wMult = qCeil((qreal) image.width()  / (qreal) Width);
	int hMult = qCeil((qreal) image.height() / (qreal) Height);

	ImgData newData;
	newData.reserve(Width * Height);
	for (int i = 0; i < Height; ++i)
		for (int j = 0; j < Width; ++j)
			newData.append(0);

	for (auto &p : data) {
		int w = p.second.x() / wMult;
		int h = p.second.y() / hMult;

		newData[h * Width + w] += p.first;
	}

	return newData;
}

void LetterClustering::printLetter(const QList<QPoint> &data)
{
	int width  = 0;
	int height = 0;
	for (QPoint point : data) {
		width = qMax(width, point.x());
		height = qMax(height, point.y());
	}

	int index = 0;
	for (int i = 0; i <= height; ++i) {
		QString line;
		for (int j = 0; j <= width; ++j) {
			if (index < data.size() && data[index].x() == j && data[index].y() == i)
				line += "*";
			else
				line += " ";
			while (index < data.size() && (data[index].y() < i || (data[index].y() == i && data[index].x() <= j)))
				++index;
		}
		qDebug() << line;
	}
}
