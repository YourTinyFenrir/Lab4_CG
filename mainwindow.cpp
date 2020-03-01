#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawCoordAxes() {

    ui->graphicsView->items().clear();
    ui->graphicsView->scene()->clear();

    ui->graphicsView->scene()->addLine(0, 200, 0, -200, QPen(Qt::black));
    ui->graphicsView->scene()->addLine(-200, 0, 200, 0, QPen(Qt::black));

}

void MainWindow::on_generateButton_clicked() {

    drawCoordAxes();

    SetOfLS generateSet(ui->num->value());
    slc = generateSet;
    slc.draw(ui->graphicsView->scene(), QPen(Qt::blue));

    Rectangle generateRct(ui->length->value(), ui->width->value());
    rct = generateRct;
    rct.draw(ui->graphicsView->scene(), QPen(Qt::black));

}

void MainWindow::on_cutButton_clicked() {

    drawCoordAxes();

    SetOfLS cutSet = slc.algorithmOfCohenSutherland(rct);

    rct.draw(ui->graphicsView->scene(), QPen(Qt::black));
    slc.draw(ui->graphicsView->scene(), QPen(Qt::blue));
    cutSet.draw(ui->graphicsView->scene(), QPen(Qt::red));

}
