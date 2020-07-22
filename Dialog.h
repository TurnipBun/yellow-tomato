#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QSystemTrayIcon>
#include <QtNetwork>
#include <QtWidgets/QDialog>

#include "TomatoState.h"
#include "ui_tomato.h"

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QDialog* parent = 0);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void show();
    void trayShow(QSystemTrayIcon::ActivationReason reason);
    void updateUi();
    void myCliked();
    void quit();
    void replyFinished(QNetworkReply* reply);
    void setState(TomatoState* state);
    void handleState(Event event);
    void changeUiStart();
    void changeUiEnd();
    void changeUiProcess();
    void changeUiCancle();
private:
    Ui::Dialog* ui;
    QNetworkRequest* request;
    QNetworkAccessManager *manager;
    QSystemTrayIcon* systemTray;
    QMenu *iconMenu;
    QAction *iconQuitAction;
    QTimer* timer;
    int status;
    int count;
    TomatoState* _state;
    
};

#endif
