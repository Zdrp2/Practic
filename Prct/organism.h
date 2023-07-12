#ifndef ORGANISM_H
#define ORGANISM_H

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>
#include <QPainter>
#include <QGraphicsScene>

class Organism : public QGraphicsItem
{
public:
    Organism();
    void hunt(QGraphicsItem *item);
    void escape(QGraphicsItem *item);
    static qreal normalizeAngle(qreal angle);
    void controlCenter();
    void controlBorder(qreal x, qreal y);
protected:
    qreal angle = 0;
    int foodCount = 0;
};

#endif // ORGANISM_H
