#include "TestViewerWidget.h"



TTestViewerWidget::TTestViewerWidget(QWidget *parent) :
    QWidget(parent)
{
    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);

}



void TTestViewerWidget::onKeepAlive() {
    update();
}


void TTestViewerWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

}
