
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
    explicit TMainWidget(QWidget *parent, bool transparency, const QString& surl);
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

};

#endif // WIDGET_H
