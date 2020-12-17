
#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore/QtGlobal>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include <sys/time.h>

class TMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TMainWidget(QWidget *parent);
    ~TMainWidget() {}
private slots:
    void onKeepAlive();
 
private:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent *);
    void customEvent(QEvent*);
private:
    QTimer* mpKeepAliveTimer;
    QPixmap FrameMap;
    bool transparent;
    QString sourceCodeUrl;

    int progresses[3];
    struct timeval startTime;

    int ButtonA_pin = 104; 
    int ButtonB_pin = 61; 
    int ButtonC_pin = 62; 
    int ButtonD_pin = 63; 

};

#endif // WIDGET_H
