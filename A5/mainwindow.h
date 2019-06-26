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

    void SeedfillAlgo(int x , int y);
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void BresenhamLineDrawingAlgo(int , int , int, int , QImage & );

    int sign(int );

    void ddaAlgo(int , int , int, int , QImage &);

    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
