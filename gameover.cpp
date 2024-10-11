#include "gameover.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include "gameroom.h"
#include "gameselect.h"



GameOver::GameOver(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(500,400);
    QPushButton *rePlay = new QPushButton(this);
    QPushButton *cancel = new QPushButton(this);
    QFont font("华文行楷",20,QFont::ExtraLight,false);

    rePlay->setStyleSheet("QPushButton { background-color:#0072C6; color:white;"
                             "border:2px groove gray; border-radius:10px; padding:6px; }");
    cancel->setStyleSheet("QPushButton { background-color:#0072C6; color:white;"
                             "border:2px groove gray; border-radius:10px; padding:6px; }");

    rePlay->setFont(font);
    cancel->setFont(font);

    rePlay->setText("再玩一次");
    cancel->setText("退出");
    rePlay->move(100,300);
    cancel->move(320,300);


    connect(rePlay,&QPushButton::clicked,[=](){
        GameRoom *gameroom = new GameRoom();
        if(gameroom->isDifficult()){
            gameroom->setTime(75);
            gameroom->addObstacle();
        }
        gameroom->show();
        this->close();
    });

    connect(cancel,&QPushButton::clicked,[=](){
        GameSelect *gameselect = new GameSelect();
        gameselect->show();
        this->close();
    });

}

void GameOver::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/Qt_project/Snake/resource/gameover.jpg");
    painter.drawPixmap(50,40,180,240,pix);

    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QFont penfont("方正舒体", 30, QFont::ExtraLight,false);
    painter.setFont(penfont);
    painter.drawText(265,150,"你的分数是");
    painter.drawText(350,200,QString("%1").arg(score));


}

void GameOver::setScore(GameRoom *gameroom)
{
    this->score = gameroom->getScore();
}

void GameOver::closeRoom(GameRoom *gameroom)
{
    gameroom->close();
}
