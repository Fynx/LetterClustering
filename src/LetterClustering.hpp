#pragma once

#include <QtCore/QObject>
#include <QImage>

class LetterClustering {
public:
	typedef QVector<QPoint> ImgData;

	LetterClustering();
	virtual ~LetterClustering();

private:
	ImgData loadImage(const QString &path);
	void normaliseData();

	QVector<ImgData> tra;
};
