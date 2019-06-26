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
      void rightclicked();
private slots:

    void mousePressEvent(QMouseEvent *event);
    void on_pushButton_clicked();
    void BresenhamLineDrawingAlgo(int , int , int , int , QImage &);
    int sign(int );
    void seedfillAlgo(int , int );
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
