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
    timer.start(1000 / 33);
}

