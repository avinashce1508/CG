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
    void displaysmily();
    void displayCircletouchingCircle();
    void displayFigure();
    void displayLogoOfLG();
     void BresenhamCircleDrawingAlgoForSbiLogo(int ,int , int , QImage &);

    void displaySbiLogo();
    void SeedfillAlgo(int ,int );
    int sign(int);
    void BresenhamLineDrawingAlgo(int , int , int ,int ,QImage &);
    void DDALineDrawingAlgo(float , float , float , float , QImage &);
    void BresenhamCircleDrawingAlgo(int ,int , int , QImage &);

    void DDACircleDrawingAlgo(float , float , float , QImage &);
    void displayCircle(int , int , int ,int ,QImage & );
    void displayTriangleinsideTriangle();
    void displayCircleInsideHexagon();
    void semicircleAroundSquare();
    void displayCircle1(int, int, int, int, QImage &);
    void displaySquareAroundSquare();
    void displayTriangleinscribedCircle();
    void displaySemicircleAroundCircle();
    void figure();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
