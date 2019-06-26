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

private slots:
    void on_pushButton_clicked();
    int sign(int);
    void BresenhamCircleDrawingAlgo(int , int , int , QImage &);
    void BresenhamLineDrawingAlgo(int , int , int , int , QImage &);
    void DDACircleDrawingAlgo(int , int ,int , QImage&);
    void display(int , int, int , int , QImage &);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
