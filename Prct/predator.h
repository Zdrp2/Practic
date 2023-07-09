#ifndef PREDATOR_H
#define PREDATOR_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

#include "food.h"

class Predator : public QGraphicsEllipseItem
{
public:
    Predator();

    // QGraphicsItem interface
public:
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setChance(int c);

private:
    qreal angle = 0;
    qreal speed = 0;
    int chance = 0;
};

#endif // BACTERIUM_H
