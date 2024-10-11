#include "gamehall.h"
#include "ui_gamehall.h"
#include "gameselect.h"
#include <QPushButton>


GameHall::GameHall(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameHall)
{
    ui->setupUi(this);
    this->setFixedSize(1000,650);
    this->setWindowTitle("贪吃蛇游戏");

    QPushButton *startBtn=new QPushButton(this);
    startBtn->setText("开始游戏");
    startBtn->move(this->width()*0.44,this->height()*0.7);
    startBtn->setStyleSheet("QPushButton{border : 0px;}");
    QFont font("华文行楷",23,QFont::ExtraLight,false);
    startBtn->setFont(font);

    GameSelect* gameselect = new GameSelect();
    connect(startBtn,&QPushButton::clicked,[=](){
        gameselect->setGeometry(this->geometry());
        this->close();
        gameselect->show();
    });

}

GameHall::~GameHall()
{
    delete ui;
}

void GameHall::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load("D:/Qt_project/Snake/resource/startGame.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
