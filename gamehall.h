#ifndef GAMEHALL_H
#define GAMEHALL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui {
class GameHall;
}
QT_END_NAMESPACE

class GameHall : public QWidget
{
    Q_OBJECT

public:
    GameHall(QWidget *parent = nullptr);
    ~GameHall();
    void paintEvent(QPaintEvent *event);
private:
    Ui::GameHall *ui;
};
#endif // GAMEHALL_H
