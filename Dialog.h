#ifndef DIALOG_H
#define DIALOG_H
#include <QtWidgets/QSystemTrayIcon>
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
private:
    Ui::Dialog* ui;
    QSystemTrayIcon* systemTray;
    QTimer* timer;
    int status;
    bool isStarted;
    int count;
    
};

#endif
