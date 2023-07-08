#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class Food : public QObject
{
    Q_OBJECT
public:
    explicit Food(QGraphicsScene* scene, QObject* parent = nullptr);

public slots:
    void createCircle();

private:
    QGraphicsScene* scene;
};

#endif // FOOD_H
