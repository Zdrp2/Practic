#ifndef ORGANISM_H
#define ORGANISM_H

#include <QGraphicsEllipseItem>

class Organism : public QGraphicsEllipseItem
{

protected:
    qreal X;
    qreal Y;
public:
    Organism(qreal x, qreal y);

    // QGraphicsItem interface
public:
    void advance(int phase);
};

#endif // ORGANISM_H
