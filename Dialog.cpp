#include <QtWidgets>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QSystemTrayIcon>
#include "Dialog.h"
#include "analogclock.h"

Dialog::Dialog(QDialog* parent):
    QDialog(parent),ui(new Ui::Dialog),status(0),isStarted(false),count(0)
{
    //初始化UI
    ui->setupUi(this);
    updateUi();
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //初始化通知图标
    systemTray = new QSystemTrayIcon(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/favicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
    systemTray->setIcon(icon);
    systemTray->show();
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayShow(QSystemTrayIcon::ActivationReason)));

    //初始化定时器
    timer = new QTimer(this);
    timer->start(10000);//10s
    connect(timer, SIGNAL(timeout()), ui->analogClock, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUi()));

    //初始化按钮事件
    connect(ui->pushDone, SIGNAL(clicked()), this, SLOT(myCliked()));
    connect(ui->pushDone, SIGNAL(clicked()), this, SLOT(hide()));
}
    
Dialog::~Dialog()
{
    delete ui;
    systemTray->hide();
    delete systemTray;
    delete timer;
}


void Dialog::closeEvent(QCloseEvent *event)
 {
     QDialog::hide();
     event->ignore();
 }


void Dialog::show()
{
    QDesktopWidget* deskTop = QApplication::desktop();
    QRect deskRect = deskTop->availableGeometry();
    QPoint point(deskRect.width()-rect().width()-1,deskRect.height()-rect().height()-30);
    move(point);
    QDialog::show();
}

void Dialog::trayShow(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        QDialog::show();
    }
}

void Dialog::updateUi()
{
    QTime time = QTime::currentTime();
    //一个番茄时间
    int pos = time.minute() % 30;
    if (pos < 5 && isStarted == false)
    {
        ui->pushDone->setText(QString::fromUtf8("开始"));
        ui->pushDone->setEnabled(true);
        QDialog::show();
    }
    else if (pos < 5 && isStarted == true)
    {
        ui->pushDone->setText(QString::fromUtf8("进行中"));
        ui->pushDone->setEnabled(false);
    }
    else if (pos < 25 && isStarted == false)
    {
        ui->pushDone->setText(QString::fromUtf8("未进行"));
        ui->pushDone->setEnabled(false);
    }
    else if (pos < 25 && isStarted == true)
    {
        ui->pushDone->setText(QString::fromUtf8("进行中"));
        ui->pushDone->setEnabled(false);
    }
    else if (isStarted == true)
    {
        ui->pushDone->setText(QString::fromUtf8("完成"));
        ui->pushDone->setEnabled(true);
        QDialog::show();
    }
    else
    {
        ui->pushDone->setText(QString::fromUtf8("未开始"));
        ui->pushDone->setEnabled(false);
    }
    ui->progress30->setValue(pos);

    //一天
    pos = 60 * time.hour() + time.minute();
    ui->progress1440->setValue(pos);
    if (pos == 0) 
    {
        count = 0;
        ui->lcdCount->display(count);
    }
}

void Dialog::myCliked()
{
    if (isStarted == false)
    {
        isStarted = true;
    }
    else
    {
        ++count;
        ui->lcdCount->display(count);
        isStarted = false;
    }
    updateUi();
}

