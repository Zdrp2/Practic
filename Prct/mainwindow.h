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

private:
    QGraphicsScene *scene;
    Bacterium *bacterium;
    Food* food;
    QTimer timer; // Объект таймера объявлен как член класса
    QTimer timerFood;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
