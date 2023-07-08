#include "bacterium.h"

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Bacterium::Bacterium() : color(QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256))
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
}

QRectF Bacterium::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Bacterium::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Bacterium::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(Qt::black);
    painter->setBrush(color);
    painter->drawEllipse(-5, -10, 10, 20);

    // Рисуем усики
    painter->drawLine(0, -10, -5, -15);
    painter->drawLine(0, -10, 5, -15);
}

void Bacterium::advance(int phase)
{
    if (!phase)
        return;
    //! [4]
    // Don't move too far away
    //! [5]
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(322, 247));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
        //! [5] //! [6]
    }
    //! [6]

    // Try not to crash with any other mice
    //! [7]
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                                                             << mapToScene(0, 0)
                                                             << mapToScene(-30, -50)
                                                             << mapToScene(30, -50));

    for (QGraphicsItem *item : dangerMice) {
        if (item != this && !dynamic_cast<Bacterium*>(item))
        {
            QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
            qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
            angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

            if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
                // Rotate right
                angle -= 0.5;
            } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
                // Rotate left
                angle += 0.5;
            }
            if (collidesWithItem(item)) {
                // Remove the item from the scene
                delete item;
                foodCount++;
            }

            if (foodCount == 3) {
                // Создаем новую бактерию
                Bacterium *newBacterium = new Bacterium();
                scene()->addItem(newBacterium);
                newBacterium->setPos(pos());

                // Сбрасываем счетчик съеденной еды
                foodCount = 0;
            }
        }
        else {
            QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
            qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
            angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

            if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
                // Rotate right
                angle += 0.5;
            } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
                // Rotate left
                angle -= 0.5;
            }
        }
    }
    //! [9]

    // Add some random movement
    //! [10]
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }
    //! [10]

    //! [11]
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));

    // Ограничение перемещения по горизонтали
    qreal xPos = pos().x();
    qreal yPos = pos().y();

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
