
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

    int ButtonA_pin = GPIO_PIN(7); 
    int ButtonB_pin = GPIO_PIN(11); 
    int ButtonC_pin = GPIO_PIN(13); 
    int ButtonD_pin = GPIO_PIN(15); 

};

#endif // WIDGET_H
