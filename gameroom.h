#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QRectF>


typedef enum Direct{
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
}dir_t;


class GameRoom : public QWidget
{
    Q_OBJECT

public:
    explicit GameRoom(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void addTop();
    void addDown();
    void addRight();
    void addLeft();
    void deleteLast();
    void addNewFood();
    bool checkMeet();
    void addObstacle();
    int getScore();
    void setDifficult();
    void setSimple();
    bool isDifficult();
    void setTime(int t);
private:


    int moveFlag = DIR_UP;
    bool gameStart = false;
    QTimer *timer;
    int time = 100;
    int score;
    QList<QRectF> snake;
    QList<QRectF> obstacle;
    int nodeWidth = 20;
    int nodeHeight = 20;
    int windowLength = 600;
    int windowWidth = 688;
    int wholeLength = 800;
    int wholeWidth = 688;
    bool gameOverShown;
    QRectF food;
    bool difficultMode;

};


#endif // GAMEROOM_H
