#include "predator.h"

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

Predator::Predator(bool ch)
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    reprod = ch;
}

QRectF Predator::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Predator::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Predator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Кисть с градиентом в качестве фона
    QLinearGradient gradient(-5, -10, 5, 10);
    gradient.setColorAt(0, Qt::darkGray);
    gradient.setColorAt(1, Qt::red);
    painter->setBrush(gradient);

    // Эллипс с градиентным фоном
    painter->drawEllipse(-5, -10, 10, 20);

    // Глаза
    painter->setBrush(Qt::white);
    painter->drawEllipse(-3, -8, 2, 4);
    painter->drawEllipse(1, -8, 2, 4);

    // Зубы
    painter->setBrush(Qt::white);
    painter->drawPolygon(QPolygonF() << QPointF(-2, 0) << QPointF(2, 0) << QPointF(0, -5));

    // Рога
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-8, -18, 3, 8);
    painter->drawEllipse(5, -18, 3, 8);

    // Усики
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawLine(0, -10, -5, -15);
    painter->drawLine(0, -10, 5, -15);
}

void Predator::advance(int phase)
{
    if (!phase)
        return;

    controlCenter();

    const QList<QGraphicsItem *> othersIt = scene()->items(QPolygonF()
                                                             << mapToScene(0, 0)
                                                             << mapToScene(-30, -50)
                                                             << mapToScene(30, -50));

    for (QGraphicsItem *item : othersIt) {
        if (!dynamic_cast<Predator*>(item) && !dynamic_cast<Bacterium*>(item))
        {
            hunt(item);

            if (collidesWithItem(item)) {
                // Удалить съеденный объект со сцены
                scene()->removeItem(item);

                foodCount++;
            }
            if (reprod) {
                if (foodCount == 5) {
                    // Создаем нового хищника
                    Predator *newPredator = new Predator(reprod);
                    newPredator->setPos(pos());
                    scene()->addItem(newPredator);

                    foodCount = 0;
                }
            }
        }
        else if (!dynamic_cast<Predator*>(item))
        {
            hunt(item);
        }
        else {
            escape(item);
        }
    }

    if (othersIt.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }

    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));

    // Ограничение перемещения
    controlBorder(pos().x(),pos().y());
}
