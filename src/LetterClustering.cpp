#include "LetterClustering.h"

#include <QDebug>
#include <QDir>
#include <QTextStream>

LetterClustering::LetterClustering()
{
	QTextStream in(stdin);
	QString dirPath("data/data/");
	QDir dir(dirPath);
	for (const QString &path : dir.entryList()) {
		LetterClustering::ImgData imgData = loadImage(dirPath + "/" + path);
		if (!imgData.isEmpty())
			tra.append(imgData);
	}

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
