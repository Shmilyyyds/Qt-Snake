#include "gameselect.h"
#include "gameroom.h"
#include <QPainter>
#include <QFont>
#include <QPushButton>
GameSelect::GameSelect(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(1000,650);
    this->setWindowTitle("关卡选择");

    QFont font("华文行楷",20,QFont::ExtraLight,false);

    GameRoom *gameroom = new GameRoom();

    QPushButton *simpleBtn = new QPushButton(this);
    simpleBtn->setStyleSheet("QPushButton { background-color:#0072C6; color:white;"
                             "border:2px groove gray; border-radius:10px; padding:6px; }");
    simpleBtn->setFont(font);
    simpleBtn->setText("简单模式");
    simpleBtn->move(435,300);

    connect(simpleBtn,&QPushButton::clicked,[=](){
        gameroom->setTime(100);
        gameroom->setGeometry(this->geometry());
        this->close();
        gameroom->show();
    });

    QPushButton *difficBtn = new QPushButton(this);
    difficBtn->setStyleSheet("QPushButton { background-color:#0072C6; color:white;"
                             "border:2px groove gray; border-radius:10px; padding:6px; }");
    difficBtn->setFont(font);
    difficBtn->setText("困难模式");
    difficBtn->move(435,370);

    connect(difficBtn,&QPushButton::clicked,[=](){
        gameroom->setTime(75);
        gameroom->setDifficult();
        gameroom->addObstacle();
        gameroom->setGeometry(this->geometry());
        this->close();
        gameroom->show();
    });
}

void GameSelect::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix("D:/Qt_project/Snake/resource/select.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
