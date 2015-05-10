#pragma once

#include <QtCore/QObject>
#include <QImage>

class LetterClustering {
public:
	typedef QList<int> ImgData;

	LetterClustering(const QString &input, const QString &output);
	virtual ~LetterClustering();

private:
	ImgData loadImage(const QString &path);
	void printLetter(const QList<QPoint> &data);

	QVector<QString> fileNames;
	QVector<ImgData> tra;
};
