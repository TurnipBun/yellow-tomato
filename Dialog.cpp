#include <QtWidgets>
#include <QtWidgets/QDesktopWidget>
#include <QTextStream>

#include "TomatoState.h"
#include "Dialog.h"
#include "analogclock.h"

Dialog::Dialog(QDialog* parent):
    QDialog(parent),ui(new Ui::Dialog),request(NULL),manager(NULL),status(0),count(0),_state(NULL)
{
    //初始化UI
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //初始化通知图标
    iconQuitAction = new QAction(tr("退出"),this);
    iconMenu = new QMenu((QWidget*)QApplication::desktop());
    iconMenu->addAction(iconQuitAction);//关联动作
    systemTray = new QSystemTrayIcon(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/favicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
    systemTray->setIcon(icon);//关联图标
    systemTray->setContextMenu(iconMenu);//关联菜单
    systemTray->show();
    
    _state = new StartState(this);
    updateUi();

    connect(iconQuitAction, SIGNAL(triggered()), this, SLOT(quit()));
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayShow(QSystemTrayIcon::ActivationReason)));

    //初始化定时器
    timer = new QTimer(this);
    timer->start(30000);//30s
    connect(timer, SIGNAL(timeout()), ui->analogClock, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateUi()));

    //初始化按钮事件
    connect(ui->pushDone, SIGNAL(clicked()), this, SLOT(myCliked()));
    connect(ui->pushDone, SIGNAL(clicked()), this, SLOT(hide()));
}

void Dialog::replyFinished(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();
    QTextStream qout(stdout);
    //qout << data;

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data,&jsonErr);
    if (jsonErr.error != QJsonParseError::NoError) return; 
    if (jsonDoc.isNull()) return;
    QJsonObject jsonObj = jsonDoc.object();
    QJsonValue value = jsonObj.value("data");
    if (value == QJsonValue::Undefined) return;
    jsonObj = value.toObject();
    value = jsonObj.value("f43");
    ui->lcdStockNow->display(value.toInt());
    value = jsonObj.value("f60");
    ui->lcdStockLast->display(value.toInt());
    reply->deleteLater();
}
    
Dialog::~Dialog()
{
    delete ui;
    systemTray->hide();
    delete systemTray;
    delete timer;
    delete request;
    delete manager;
    delete iconMenu;
    delete iconQuitAction;
}


void Dialog::closeEvent(QCloseEvent *event)
{
    QDialog::hide();
    event->ignore();
}


void Dialog::show()
{
    //QDesktopWidget* deskTop = QApplication::desktop();
    //QRect deskRect = deskTop->availableGeometry();
    QRect deskRect = QGuiApplication::primaryScreen()->availableGeometry();
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
    //番茄进度条
    int pos = time.minute() % 30;
    ui->progress30->setValue(pos);
    
    //一天进度条
    pos = 60 * time.hour() + time.minute();
    ui->progress1440->setValue(pos);

    //超时
    if (pos == 5 || pos == 25 || pos == 29)
    {
        handleState(static_cast<Event>(pos));
    }
    
    //http通信
    if (manager == NULL) manager = new QNetworkAccessManager(this);
    if (request == NULL) connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    if (request == NULL) request = new QNetworkRequest();
    
    request->setUrl(QUrl("http://push2.eastmoney.com/api/qt/stock/get?secid=1.000001&ut=bd1d9ddb04089700cf9c27f6f7426281&fields=f43,f60"));
    manager->get(*request);
}

void Dialog::myCliked()
{
    handleState(BUTTON);
}

void Dialog::quit()
{
    //exit(0);
    QApplication::quit();
}

void Dialog::setState(TomatoState* state)
{
  if (_state != NULL) delete _state;
  _state = state;
}

void Dialog::handleState(Event event)
{
  if (_state != NULL) 
  {
    _state->handle(event);
  }
}


void Dialog::changeUiStart()
{
  ui->pushDone->setText(QString::fromUtf8("开始"));
  ui->pushDone->setEnabled(true);
}

void Dialog::changeUiEnd()
{
  ui->pushDone->setText(QString::fromUtf8("休息"));
  ui->pushDone->setEnabled(false);
}

void Dialog::changeUiProcess()
{
  ui->pushDone->setText(QString::fromUtf8("进行中"));
  ui->pushDone->setEnabled(false);
}

void Dialog::changeUiCancle()
{
  ui->pushDone->setText(QString::fromUtf8("已取消"));
  ui->pushDone->setEnabled(false);
}


