#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "QKeyEvent"
#include "controller.h"
#include "QTimerEvent"
#include "QTimer"
#include <QtMultimedia/QAudioOutput>

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT
public slots:
   // void timerEvent(QTimerEvent*);
    void tick();
    void nothing() { controller->player->wait = true; }
    void newLevel();
public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void keyPressEvent(QKeyEvent *event);
private:
    QTimer* timer;
    QTimer* wait;
    Ui::Menu *ui;
    Controller* controller;
    int timerClock = 0;
    QGraphicsScene *scene_;
    QGraphicsView *view_;
    void paint();
    void update();
protected:
   // void keyPressEvent(QKeyEvent *event);
};

#endif // MENU_H
