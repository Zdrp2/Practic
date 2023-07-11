#ifndef BACTERIUM_H
#define BACTERIUM_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

#include "predator.h"

class Bacterium : public QGraphicsEllipseItem
{
public:
    Bacterium(int chance, int speed);

    // QGraphicsItem interface
public:
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle = 0;
    qreal speed = 0;
    int foodCount = 0;
    int chance;
    QColor color;

};

#endif // BACTERIUM_H
