#include <gameover.h>
#include "gameroom.h"
#include <QPen>
#include <QPushButton>
GameRoom::GameRoom(QWidget *parent)
    : QWidget(parent)

{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFixedSize(wholeLength,wholeWidth);

    QRectF head(windowLength/2,windowWidth/2,nodeWidth,nodeHeight);
    snake.append(head);
    addTop();
    addTop();

    addNewFood();


    timer=new QTimer(this);

    connect(timer , &QTimer::timeout, this,[=](){
        int count = 1;
        if(snake[0].intersects(food)){
            count++;
            addNewFood();
        }
        while(count--){
            switch (moveFlag) {
            case DIR_UP:
                addTop();
                break;
            case DIR_DOWN:
                addDown();
                break;
            case DIR_LEFT:
                addLeft();
                break;
            case DIR_RIGHT:
                addRight();
                break;
            default:
                break;
            }
        }

        deleteLast();
        update();
    });


    QPushButton *startbtn = new QPushButton(this);
    QPushButton *stopbtn = new QPushButton(this);
    QFont font("华文行楷",23,QFont::ExtraLight,false);

    startbtn->move(windowLength+60,150);
    stopbtn->move(windowLength+60,200);

    startbtn->setText("开始");
    stopbtn->setText("暂停");

    startbtn->setFont(font);
    stopbtn->setFont(font);

    connect(startbtn,&QPushButton::clicked,[=](){
        gameStart = true;
        timer->start(time);
        this->setFocus();
    });


    connect(stopbtn,&QPushButton::clicked,[=](){
        gameStart = false;
        timer->stop();
        this->setFocus();
    });

    gameOverShown = false;

}



void GameRoom::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Up:
        if(moveFlag != DIR_DOWN)
            moveFlag=DIR_UP;
        break;
    case Qt::Key_Down:
        if(moveFlag != DIR_UP)
            moveFlag=DIR_DOWN;
        break;
    case Qt::Key_Left:
        if(moveFlag != DIR_RIGHT)
            moveFlag=DIR_LEFT;
        break;
    case Qt::Key_Right:
        if(moveFlag != DIR_LEFT)
            moveFlag=DIR_RIGHT;
        break;
    case Qt::Key_Space:
        if(!gameStart) {
            gameStart = true;
            timer->start(time);
        }else{
            gameStart = false;
            timer->stop();
        }

        break;
    default:
        break;
    }
}



void GameRoom::addTop(){
    QPointF leftTop;
    QPointF rightBottom;

    if(snake[0].y() - nodeHeight < 0){
        leftTop = QPointF(snake[0].x(),this->height()-nodeHeight);
        rightBottom = QPointF(snake[0].x()+nodeWidth, this->height());
    }else{
        leftTop = QPointF(snake[0].x(),snake[0].y()-nodeHeight);
        rightBottom = QPointF(snake[0].topRight());
    }

    snake.insert(0,QRectF(leftTop,rightBottom));
}

void GameRoom::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QPixmap pix;
    pix.load("D:/Qt_project/Snake/resource/background.png");
    painter.drawPixmap(0,0,windowLength,windowWidth,pix);
    painter.setRenderHint(QPainter::Antialiasing);

    if(difficultMode){
        pix.load("D:/Qt_project/Snake/resource/wall.png");
        for(int i=0;i<obstacle.size();i++){
            auto node = obstacle[i];
            painter.drawPixmap(node.x(),node.y(),nodeWidth,nodeHeight,pix);
        }
    }

    if(moveFlag==DIR_UP){
        pix.load("D:/Qt_project/Snake/resource/up.png");
    }else if(moveFlag==DIR_DOWN){
        pix.load("D:/Qt_project/Snake/resource/down.png");
    }else if(moveFlag==DIR_LEFT){
        pix.load("D:/Qt_project/Snake/resource/left.png");
    }else if(moveFlag==DIR_RIGHT){
        pix.load("D:/Qt_project/Snake/resource/right.png");
    }

    auto snakeHead = snake.front();
    painter.drawPixmap(snakeHead.x(),snakeHead.y(),nodeWidth,nodeHeight,pix);



    pix.load("D:/Qt_project/Snake/resource/snakeTail.png");
    for(int i=1;i<snake.size();i++){
        auto node = snake[i];
        painter.drawPixmap(node.x(),node.y(),nodeWidth,nodeHeight,pix);
    }

    pix.load("D:/Qt_project/Snake/resource/china.png");
    painter.drawPixmap(food.x(),food.y(),nodeWidth,nodeHeight,pix);

    pix.load("D:/Qt_project/Snake/resource/right_area.png");
    painter.drawPixmap(windowLength,0,wholeLength-windowLength,windowWidth,pix);

    //雪之下
    pix.load("D:/Qt_project/Snake/resource/snow.jpg");
    painter.drawPixmap(windowLength+10,355,180,270,pix);

    pix.load("D:/Qt_project/Snake/resource/dialoge.jpg");
    painter.drawPixmap(windowLength+10,255,180,100,pix);

    //雪乃

    pix.load("D:/Qt_project/Snake/resource/score.jpg");
    painter.drawPixmap(windowLength,0,90,70,pix);

    //score

    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QFont penfont("方正舒体", 30, QFont::ExtraLight,false);
    painter.setFont(penfont);
    painter.drawText(windowLength+120,45,QString("%1").arg(snake.size()-3));

    //干巴爹
    painter.drawText(windowLength+35,305,"加油哟");

    if(checkMeet()&&!gameOverShown){
        gameOverShown = true;
        timer->stop();
        GameOver *gameover =new GameOver();
        gameover->setScore(this);
        gameover->show();
        this->close();



    }
}

void GameRoom::deleteLast(){
    snake.removeLast();
}

void GameRoom::addDown(){
    QPointF lefttop;
    QPointF rightBottom;

    if(snake[0].y()+nodeHeight*2>windowWidth){
        lefttop = QPointF(snake[0].x(),0);
        rightBottom = QPointF(snake[0].x()+nodeWidth,nodeHeight);
    }else{
        lefttop = snake[0].bottomLeft();
        rightBottom = snake[0].bottomRight() + QPointF(0,nodeHeight);
    }

    snake.insert(0,QRectF(lefttop,rightBottom));
}

void GameRoom::addLeft(){
    QPointF leftTop;
    QPointF rightBottom;
    if(snake[0].x()-nodeWidth < 0){
        leftTop = QPointF(windowLength-nodeWidth,snake[0].y());
        rightBottom = QPointF(windowLength,snake[0].y()+nodeWidth);
    }else{
        leftTop = snake[0].topLeft() - QPointF(nodeWidth,0);
        rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
    }

    snake.insert(0,QRectF(leftTop,rightBottom));
}

void GameRoom::addRight(){
    QPointF leftTop;
    QPointF rightBottom;
    if(snake[0].x()+nodeWidth * 2 > windowLength){
        leftTop = QPointF(0,snake[0].y());
    }else{
        leftTop = snake[0].topRight();
    }

    rightBottom = leftTop + QPointF(nodeWidth, nodeHeight);

    snake.insert(0,QRectF(leftTop,rightBottom));
}

void GameRoom::addNewFood(){
    QRectF newfood;
    bool illegal;
    do{

    newfood = QRectF(
        rand()%(windowLength/20)*20,
        rand()%(windowWidth/20)*20,
        nodeWidth,
        nodeHeight
        );

        illegal = false;
    for(int i=0;i<obstacle.length();i++){
        if(newfood.intersects(obstacle[i])){
            illegal = true;
            break;
        }
    }
    }while(illegal);

    food = newfood;
}

bool GameRoom::checkMeet(){
    for(int i=0;i<snake.length();i++){
        for(int j=i+1;j<snake.length();j++){
            if(snake[i] == snake[j]) return true;
        }
    }
    for(int i=0;i<obstacle.length();i++){
        if(snake[0].intersects(obstacle[i])) return true;
    }
    return false;
}

void GameRoom::addObstacle()
{
    for(int i=0;i<windowLength*0.6/nodeWidth;i++){
        QPointF leftTop(nodeWidth*i,windowWidth*0.7);
        QPointF rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
        obstacle.append(QRectF(leftTop,rightBottom));
    }

    for(int i=0;i<windowWidth*0.3/nodeWidth;i++){
        QPointF leftTop(windowLength*0.6,windowWidth*0.7+nodeHeight*i);
        QPointF rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
        obstacle.append(QRectF(leftTop,rightBottom));
    }

    for(int i=0;i<windowLength*0.6/nodeWidth;i++){
        QPointF leftTop(windowLength-nodeWidth*i,windowWidth*0.3);
        QPointF rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
        obstacle.append(QRectF(leftTop,rightBottom));
    }

    for(int i=0;i<windowWidth*0.3/nodeWidth;i++){
        QPointF leftTop(windowLength*0.4,nodeHeight*i);
        QPointF rightBottom = leftTop + QPointF(nodeWidth,nodeHeight);
        obstacle.append(QRectF(leftTop,rightBottom));
    }

    QPainter painter(this);

    QPixmap pix;
    pix.load("D:/Qt_project/Snake/resource/wall.png");
    for(int i=0;i<obstacle.size();i++){
        auto node = obstacle[i];
        painter.drawPixmap(node.x(),node.y(),nodeWidth,nodeHeight,pix);
    }

}

int GameRoom::getScore()
{
    return snake.length()-3;
}

void GameRoom::setDifficult()
{
    difficultMode = true;
}

void GameRoom::setSimple()
{
    difficultMode = false;
}

bool GameRoom::isDifficult()
{
    return difficultMode;
}

void GameRoom::setTime(int t)
{
    this->time=t;
}


