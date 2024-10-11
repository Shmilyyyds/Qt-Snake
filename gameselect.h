#ifndef GAMESELECT_H
#define GAMESELECT_H

#include <QWidget>

class GameSelect : public QWidget
{
    Q_OBJECT
public:
    explicit GameSelect(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:
};

#endif // GAMESELECT_H
