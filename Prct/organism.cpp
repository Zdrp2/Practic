#include "organism.h"

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

Organism::Organism()
{
}

qreal Organism::normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

void Organism::controlCenter() {

    QLineF lineToCenter(QPointF(0, 0), mapFromScene(322, 247));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Лево
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Право
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
    }
}

void Organism::controlBorder(qreal xPos, qreal yPos) {

    if (xPos < 0) {
        setPos(0, pos().y());
        angle = Pi;
    } else if (xPos > scene()->width()) {
        setPos(scene()->width(), pos().y());
        angle = Pi;
    }

    if (yPos < 0) {
        setPos(pos().x(), 0);
        angle = Pi;
    } else if (yPos > scene()->height()) {
        setPos(pos().x(), scene()->height());
        angle = Pi;
    }
}

void Organism::hunt(QGraphicsItem *item) {

    QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
    qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
    angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

    // Движение к цели
    if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
        angle -= 0.5;
    } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
        angle += 0.5;
    }
}

void Organism::escape(QGraphicsItem *item) {

    QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
    qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
    angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

    // Попытки избежать столкновения
    if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
        angle += 0.5;
    } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
        angle -= 0.5;
    }
}

