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
    int sign(int);

   void BresenhamLineDrawingAlgo(int , int , int , int , QImage &img);

    void mousePressEvent(QMouseEvent *event);

    void MultiplicationOfTwoMatrices();

    void ReflectionAboutXAxis();

    void ReflectionAboutYAxis();

    void ReflectionAboutXYLine();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
