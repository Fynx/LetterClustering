#include <QCoreApplication>
#include <QDebug>
#include "LetterClustering.hpp"

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);

	if (argc < 3)
		qDebug() << "Invalid number of parameters.";

	QString input(argv[1]);
	QString output(argv[2]);

	LetterClustering w(input, output);

	return app.exec();
}
