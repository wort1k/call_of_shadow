#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "QKeyEvent"
#include "controller.h"
#include "QTimer"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT
public slots:
    void TimerEvent();
public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::Menu *ui;
    Controller* controller;
    QTimer* timer;
protected:
   // void keyPressEvent(QKeyEvent *event);
};

#endif // MENU_H
