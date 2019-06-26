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
    void BresenhamsLineDrawingAlgo(int , int , int , int , QImage &img);
    void DDALineDrawingAlgo(int , int , int , int , QImage &img);
    int sign(int);
    void DrawFigure(int , int , int , int , QImage &img);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
