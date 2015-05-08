#ifndef LetterClustering_H
#define LetterClustering_H

#include <QtCore/QObject>
#include <QImage>

class LetterClustering {
public:
	typedef QVector<QPoint> ImgData;

	LetterClustering();
	virtual ~LetterClustering();

private:
	ImgData loadImage(const QString &path);
	void insertData(const QImage &image);

	QVector<ImgData> tra;
};

#endif // LetterClustering_H
