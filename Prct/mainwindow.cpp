#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 645, 495,this);
    ui->graphicsView->setScene(scene);

    connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    int BactCount = ui->spinBox->value();
    QRectF sceneRect = scene->sceneRect();

    for (int i = 0; i < BactCount; ++i) {
        bacterium = new Bacterium;
        qreal x = QRandomGenerator::global()->bounded(sceneRect.width());
        qreal y = QRandomGenerator::global()->bounded(sceneRect.height());
        bacterium->setPos(sceneRect.x() + x, sceneRect.y() + y);
        scene->addItem(bacterium);
    }
    food = new Food(scene);
    connect(&timerFood, &QTimer::timeout, food, &Food::createCircle);
    timer.start(1000 / 33);
    timerFood.start(2000/(ui->horizontalSlider->value())); // Создание кружка каждые 2 секунды
}


void MainWindow::on_pushButton_2_clicked()
{
    scene->clear();
    timer.stop();
    timerFood.stop();
    disconnect(&timerFood, &QTimer::timeout, food, &Food::createCircle);
    ui->pushButton->setEnabled(true);
}
