#include "food.h"
#include <QTimer>
#include <QRandomGenerator>

Food::Food(QGraphicsScene* scene, QObject* parent)
    : QObject(parent), scene(scene)
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Food::createCircle);
    timer->start(2000); // Создание кружка каждые 2 секунды
}

void Food::createCircle()
{
    if (scene == nullptr)
        return;

    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(-5, -5, 10, 10);
    circle->setPos(QRandomGenerator::global()->bounded(scene->width()), QRandomGenerator::global()->bounded(scene->height()));
    circle->setBrush(Qt::yellow);
    scene->addItem(circle);
}
