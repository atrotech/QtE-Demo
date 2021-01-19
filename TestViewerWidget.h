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


private slots:
    void onKeepAlive();
private:
    void paintEvent(QPaintEvent *);

private:
    QTimer* mpKeepAliveTimer;

    QPixmap testTableImg = QPixmap(":/img/testTable.png");


};
