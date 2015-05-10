#include "LetterClustering.hpp"
#include "DBScan.hpp"

#include <QDebug>
#include <QDir>
#include <QTextStream>

LetterClustering::LetterClustering()
{
// 	QTextStream in(stdin);
// 	QString dirPath("data/data/");
// 	QDir dir(dirPath);
// 	for (const QString &path : dir.entryList()) {
// 		LetterClustering::ImgData imgData = loadImage(dirPath + "/" + path);
// 		if (!imgData.isEmpty())
// 			tra.append(imgData);
// 	}

	QList<Point> pts = {
		{{0,   100}},
		{{0,   200}},
		{{0,   275}},
		{{100, 150}},
		{{200, 100}},
		{{250, 200}},
		{{0,   300}},
		{{100, 200}},
		{{600, 700}},
		{{650, 700}},
		{{675, 700}},
		{{675, 710}},
		{{675, 720}},
		{{50,  400}}
	};

        double eps = 100.0;
        int minPts = 3;

	DBScan dbscan(pts, eps, minPts);
	dbscan.run();

	exit(0);
}

LetterClustering::~LetterClustering()
{}

LetterClustering::ImgData LetterClustering::loadImage(const QString &path)
{
	QImage image(path);
	ImgData data;

	if (image.isNull())
		return {};

	int minY = image.height();
	int minX = image.width();

	for (int i = 0; i < image.height(); ++i) {
		for (int j = 0; j < image.width(); ++j) {
			if (qGray(image.pixel(j, i)) < 100) {
				data.append(QPoint(i, j));
				minX = qMin(minX, j);
				minY = qMin(minY, i);
			}
		}
	}

	for (QPoint &point : data)
		point -= QPoint(minX, minY);

	return data;
}

void LetterClustering::normaliseData()
{
}
