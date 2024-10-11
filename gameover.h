#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include "gameroom.h"



class GameOver : public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setScore(GameRoom *gameroom);
    void closeRoom(GameRoom *gameroom);
private:
    int score;
};

#endif // GAMEOVER_H
