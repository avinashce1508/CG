#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMouseEvent"
#include"QDebug"
#include "math.h"

int C_Array[20][2];

int i = 0;
int flag = 0;
int count = 0;
QImage image(600 , 600 , QImage::Format_RGB888);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    DDALineDrawingAlgo(300 , 0 , 300 , 600 , image );
    DDALineDrawingAlgo(0 , 300 , 600 , 300 , image );
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::sign(int val)
{
    if(val < 0)
        return -1;
    else if(val > 0)
        return 1;
    else
        return 0;
}
void MainWindow::DDALineDrawingAlgo(int x1 , int y1 , int x2 , int y2, QImage &img)
{
    float dx , dy , length;

    if(abs(x2 - x1) > abs(y2 -y1))
    {
        length = abs(x2 - x1);
    }
    else
    {
        length = abs(y2 - y1);
    }

    dx = (x2 - x1)/length;
    dy = (y2 - y1)/length;

    float x = x1 + 0.5*sign(x2 - x1);
    float y = y1 + 0.5*sign(y2 - y1);
    int i = 0;
    while(i <= length)
    {
        img.setPixel(x , y , qRgb(0 , 255 , 0));

        x += dx;
        y += dy;
        i++;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(flag == 1)
    {
        return;
    }

    int x1 = QString::number(event->x()).toInt();
    int y1 = QString::number(event->y()).toInt();

   C_Array[i][0] = x1;
   C_Array[i][1] = y1;
    qDebug()<<C_Array[i][0]<<C_Array[i][1];
   if(i > 0 && event->button() == Qt::LeftButton)
   {
       DDALineDrawingAlgo(C_Array[i-1][0] , C_Array[i-1][1] , C_Array[i][0] , C_Array[i][1] , image );
   }
   if(event->button() == Qt::RightButton)
   {
       flag = 1;
       DDALineDrawingAlgo(C_Array[i-1][0] , C_Array[i-1][1] , C_Array[0][0] , C_Array[0][1] , image );
   }
   i++;

   count++;

   emit(clicked());
   ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::ScalingOfFigure()
{
   float sx = ui->textEdit->toPlainText().toFloat();
   float sy = ui->textEdit_2->toPlainText().toFloat();
   int i = 0;
   int Array[20][2];
   while( i < count-1)
   {
      Array[i][0] = (C_Array[i][0]-300)*sx;
      Array[i][1] = (C_Array[i][1]-300)*sy;
      i++;
   }
   i = 1;
   while(i < count-1)
   {
       DDALineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[i][0]+300 , Array[i][1]+300 , image );
       i++;
   }
    DDALineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[0][0]+300 , Array[0][1]+300 , image );
  ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::TranslationOfFigure()
{
    int tx = ui->textEdit_3->toPlainText().toUInt();
    int ty = ui->textEdit_4->toPlainText().toUInt();

    int i = 0;
    int Array[20][2];
    while( i < count-1)
    {
       Array[i][0] = (C_Array[i][0]) + tx;
       Array[i][1] = (C_Array[i][1]) + ty;
       i++;
    }
    i = 1;
    while(i < count-1)
    {
        DDALineDrawingAlgo(Array[i-1][0] , Array[i-1][1] , Array[i][0] , Array[i][1] , image );
        i++;
    }
     DDALineDrawingAlgo(Array[i-1][0] , Array[i-1][1] , Array[0][0] , Array[0][1] , image );
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::RotationOfFigure()
{
    int angle = ui->textEdit_5->toPlainText().toUInt();

    int i = 0;
    int Array[20][2];
    while( i < count-1)
    {
       Array[i][0] = ((C_Array[i][0]-300)*cos(angle*3.14/180) - (C_Array[i][1]-300)*sin(angle*3.14/180));
       Array[i][1] = ((C_Array[i][0]-300)*sin(angle*3.14/180) + (C_Array[i][1]-300)*cos(angle*3.14/180));
       i++;
    }
    i = 1;
    while(i < count-1)
    {
        DDALineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[i][0]+300 , Array[i][1]+300 , image );
        i++;
    }
   DDALineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[0][0]+300 , Array[0][1]+300 , image );
   ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::seedfillAlgo(int x , int y)
{
    QColor current(image.pixel(x , y));
    image.setPixel(x , y , qRgb(255 , 255 , 0));
    if(current == qRgb(0 , 0 , 0))
    {
        seedfillAlgo(x+1 , y);
        seedfillAlgo(x-1 , y);
        seedfillAlgo(x , y+1);
        seedfillAlgo(x , y-1);
    }
}
void MainWindow::on_pushButton_clicked()  // scaling
{
  ScalingOfFigure();
}

void MainWindow::on_pushButton_2_clicked()  // translation
{
  TranslationOfFigure();
}

void MainWindow::on_pushButton_3_clicked() // rotation
{
  RotationOfFigure();
}

void MainWindow::on_pushButton_4_clicked()
{

    int x1 = C_Array[0][0] + 10 ;
    int y1 = C_Array[0][1];
    seedfillAlgo(x1 , y1);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
