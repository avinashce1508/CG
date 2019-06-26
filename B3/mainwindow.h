#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void clicked();
private slots:

    void on_pushButton_clicked();

    void BresenhamLineDrawingAlgo(int , int , int , int , QImage &img);

    void BresenhamLineDrawingAlgo1(int , int , int , int , QImage &img);

    int sign(int );

    void CohenSutherlandLineClippingAlgo(double ,double, double ,double);

    int ComputeCode(double , double);

    void mousePressEvent(QMouseEvent *event);
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
