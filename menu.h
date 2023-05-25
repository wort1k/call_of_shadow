#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "QKeyEvent"
#include "controller.h"
#include "QTimerEvent"
#include "QTimer"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT
public slots:
   // void timerEvent(QTimerEvent*);
    void tick();
public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void keyPressEvent(QKeyEvent *event);
private:
    QTimer* timer;
    Ui::Menu *ui;
    Controller* controller;
    int timerClock = 0;
protected:
   // void keyPressEvent(QKeyEvent *event);
};

#endif // MENU_H
