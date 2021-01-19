#include <QtCore/QtGlobal>
#include <QtWidgets>
#include <sys/time.h>
#include <signal.h>


class TTestViewerWidget : public QWidget
{

  Q_OBJECT

public:
    explicit TTestViewerWidget(QWidget *parent);
    ~TTestViewerWidget() {}
    int Button = 0;


private slots:
    void onKeepAlive();
private:
    void paintEvent(QPaintEvent *);

private:
    QTimer* mpKeepAliveTimer;

    QPixmap btnNormal = QPixmap(":/img/Btn.png");
    QPixmap btnPush = QPixmap(":/img/BtnFocus.png");
    QPixmap BatteryImg = QPixmap(":/img/battery.png");
    QPixmap printerImg = QPixmap(":/img/printer.png");
    QPixmap flashImg = QPixmap(":/img/flash-disk.png");
    QPixmap deleteImg = QPixmap(":/img/remove.png");
    QPixmap returnImg = QPixmap(":/img/return.png");
    QPixmap tableImg = QPixmap(":/img/table.png");


};
