#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "bacterium.h"
#include "food.h"
#include "predator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

private:
    QGraphicsScene *scene;
    Bacterium *bacterium;
    Predator *predator;
    Food* food;
    QTimer timer; // Объект таймера объявлен как член класса
    QTimer timerFood;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
