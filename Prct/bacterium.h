#ifndef BACTERIUM_H
#define BACTERIUM_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

#include "food.h"

class Bacterium : public QGraphicsEllipseItem
{
public:
    Bacterium();

    // QGraphicsItem interface
public:
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle = 0;
    qreal speed = 0;
    QColor color;
};

#endif // BACTERIUM_H
