#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(250, 235, 215));
    setPalette(palette);

    setFixedSize(size());

    ui->graphicsView->setFrameStyle(QFrame::Box);
    ui->graphicsView->setLineWidth(1);
    ui->graphicsView->setMidLineWidth(1);

    scene = new QGraphicsScene(0, 0, 645, 495,this);
    ui->graphicsView->setScene(scene);

    connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);


    ui->pushButton->setStyleSheet("QPushButton {"
                          "background-color: #4CAF50;"
                          "border-style: outset;"
                          "border-width: 2px;"
                          "border-color: beige;"
                          "font: bold 14px;"
                          "color: white;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #45a049;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #2d703e;"
                          "}");

    ui->pushButton_2->setStyleSheet("QPushButton {"
                          "background-color: red;"
                          "border-style: outset;"
                          "border-width: 2px;"
                          "border-color: beige;"
                          "font: bold 14px;"
                          "color: white;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: darkred;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: maroon;"
                          "}");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    scene->clear();

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);

    bool check = ui->checkBox->isChecked();

    QRectF sceneRect = scene->sceneRect();

    for (int i = 0; i < ui->spinBox->value(); ++i) {
        bacterium = new Bacterium(ui->horizontalSlider_2->value(), 5, check);
        qreal x = QRandomGenerator::global()->bounded(sceneRect.width());
        qreal y = QRandomGenerator::global()->bounded(sceneRect.height());
        bacterium->setPos(sceneRect.x() + x, sceneRect.y() + y);
        scene->addItem(bacterium);
    }
    for (int i = 0; i < ui->spinBox_2->value(); ++i) {
        predator = new Predator(check);
        qreal x = QRandomGenerator::global()->bounded(sceneRect.width());
        qreal y = QRandomGenerator::global()->bounded(sceneRect.height());
        predator->setPos(sceneRect.x() + x, sceneRect.y() + y);
        scene->addItem(predator);
    }
    food = new Food(scene);
    connect(&timerFood, &QTimer::timeout, food, &Food::createCircle);
    timer.start(1000 / 33);
    timerFood.start(2000/(ui->horizontalSlider->value())); // Создание кружка каждые 2 секунды
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    timer.stop();
    timerFood.stop();
    disconnect(&timerFood, &QTimer::timeout, food, &Food::createCircle);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    QString labelText = QString::number(value) + "%";
    ui->label_5->setText(labelText);
}

