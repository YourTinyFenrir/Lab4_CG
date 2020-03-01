#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "setofls.h"
#include "rectangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawCoordAxes();

private slots:
    void on_generateButton_clicked();

    void on_cutButton_clicked();

private:
    Ui::MainWindow *ui;
    SetOfLS slc;
    Rectangle rct;
};
#endif // MAINWINDOW_H
