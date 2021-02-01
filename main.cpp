#include <QtCore/QtGlobal>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QApplication>
#include <QLabel>
#include <QWSServer>
#endif
#include "mainwidget.h"

int main(int argc, char **argv) {
	QApplication app (argc, argv);

	TMainWidget w(0);

	w.setWindowFlags(Qt::FramelessWindowHint);
	w.showFullScreen();
	return app.exec();
}
