#include "bacterium.h"

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

// Конструктор
Bacterium::Bacterium(int c, int s, bool ch) : color(QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256))
{
    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    chance = c;
    check = ch;
}

void Bacterium::reproduction() {

    if (foodCount == 3) {
        int randomNumber = QRandomGenerator::global()->bounded(100);
        if (randomNumber < chance) {
            // Создаем новую бактерию
            Predator *newPredator = new Predator(check);
            newPredator->setPos(pos());
            scene()->addItem(newPredator);
        }
        else {
            Bacterium *newBacterium = new Bacterium(chance, speed, check);
            newBacterium->setPos(pos());
            scene()->addItem(newBacterium);
        }

        // Сбрасываем счетчик съеденной еды
        foodCount = 0;
    }
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

    // Не отходите слишком далеко
    controlCenter();

    // Список объектов

    const QList<QGraphicsItem *> otherItems = scene()->items(QPolygonF()
                                                             << mapToScene(0, 0)
                                                             << mapToScene(-30, -50)
                                                             << mapToScene(30, -50));

    for (QGraphicsItem *item : otherItems) {
        if (!dynamic_cast<Bacterium*>(item) && !dynamic_cast<Predator*>(item))
        {
            hunt(item);

            if (collidesWithItem(item)) {
                scene()->removeItem(item);
                foodCount++;
            }

            reproduction();
        }
        else if (!dynamic_cast<Bacterium*>(item) && !dynamic_cast<Food*>(item))
        {
            escape(item);

            if (collidesWithItem(item)) {
                // Remove the item from the scene
                this->removeFromIndex();
            }
        }
        else {
            escape(item);
        }
    }

    //Рандомное движение
    if (otherItems.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }

    //Смена скорости и перемещение
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));

    // Ограничение перемещения
    controlBorder(pos().x(),pos().y());
}
