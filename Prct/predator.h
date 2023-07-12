#ifndef PREDATOR_H
#define PREDATOR_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

#include "organism.h"
#include "food.h"
#include "bacterium.h"

class Predator : public Organism
{
public:
    Predator(bool ch);

    // QGraphicsItem interface
public:
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal speed = 0;
    bool reprod;
};

#endif // BACTERIUM_H
