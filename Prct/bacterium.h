#ifndef BACTERIUM_H
#define BACTERIUM_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

#include "organism.h"
#include "predator.h"

class Bacterium : public Organism
{
public:
    Bacterium(int chance, int speed, bool check);
    void reproduction();

    // QGraphicsItem interface
    void advance(int phase);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal speed = 0;
    int chance;
    bool check;
    QColor color;

};

#endif // BACTERIUM_H
