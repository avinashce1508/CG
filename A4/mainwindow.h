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
    void DDALineDrawingAlgo(int , int , int , int , QImage &img);

    void mousePressEvent(QMouseEvent *event);

    void seedfillAlgo(int ,int);

    void ScalingOfFigure();

    void TranslationOfFigure();

    void RotationOfFigure();

   // void DrawXYAxis();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
