/*
 * Write C++ program to draw inscribed and Circumscribed circles in the triangle as shown in
 * an example below. Use Bresenham’s Circle drawing algorithm for outer circle and DDA circle
 * for inner circle. Use any Line drawing algorithm for drawing triangle
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
void MainWindow::display(int x ,int y , int x1 , int y1 , QImage &img)
{
    img.setPixel(x1+x , y1+y , qRgb(0 , 255 , 0));
    img.setPixel(x1+x , y-y1 , qRgb(0 , 255 , 0));
    img.setPixel(x-x1 , y1+y , qRgb(0 , 255 , 0));
    img.setPixel(x-x1 , y-y1 , qRgb(0 , 255 , 0));
    img.setPixel(x+y1 , x1+y , qRgb(0 , 255 , 0));
    img.setPixel(x+y1 , y-x1 , qRgb(0 , 255 , 0));
    img.setPixel(x-y1 , y+x1 , qRgb(0 , 255 , 0));
    img.setPixel(x-y1 , y-x1 , qRgb(0 , 255 , 0));
}
void MainWindow::BresenhamCircleDrawingAlgo( int x , int y ,  int radius , QImage &img)
{
 float decision_parameter;

 int x1 = 0;
 int y1 = radius;

 decision_parameter = 3 - 2*radius;

 while(x1 <= y1)
 {
     if(decision_parameter <= 0)
     {
         decision_parameter += (4*x1 + 6);
     }
     else
     {
         decision_parameter += 4*(x1 - y1) + 10;
         y1--;
     }
     x1++;
     display(x , y , x1 , y1 , img);
 }

}
void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
  int x , y , i , decision_factor , dx , dy , s1 , s2;
  int Interchange;
  dx = abs( x2 - x1 );
  dy = abs( y2 - y1 );

  x = x1;
  y = y1;

  s1 = sign(x2-x1);
  s2 = sign(y2-y1);

 if(dy > dx)
  {
      int temp = dx;
      dx = dy;
      dy = temp;
      Interchange = 1;
  }
  else
  {
      Interchange = 0;
  }

 i = 1;
 decision_factor = 2*dy -dx;

 while(i <=dx )
 {
     img.setPixel(x , y , qRgb(0 , 255, 0));
     while(decision_factor >=0)
     {
         if(Interchange == 1)
         {
             x+= s1;
         }
         else
         {
             y+= s2;
         }
         decision_factor -= 2*dx;
     }
     if(Interchange == 1)
     {
         y += s2;
     }
     else
     {
         x += s1;
     }
     decision_factor += 2*dy;
     i++;
 }

}
void MainWindow::DDACircleDrawingAlgo(int x ,int y , int radius , QImage &img)
{
  int i =0 ;

  float val;
  float x1= radius;
  float y1 = 0;
  float start_x = x1;
  float start_y = y1;
  do
  {
      val = pow(2 ,i);
      i++;
  }while(val < radius);

  float epsilon = 1/pow(2 , i-1);

  do
  {
      float x2 = x1 + y1*epsilon;
      float y2 = y1 - x2*epsilon;

      img.setPixel(x+x2 , y+y2 , qRgb(0 , 255 , 0));

      x1 = x2;
      y1 = y2;
  }while((y1-start_y) < epsilon || (start_x - x1) >epsilon );

}

void MainWindow::on_pushButton_clicked()
{
    QImage image(400 , 400 , QImage::Format_RGB888);

    int x = ui->textEdit->toPlainText().toInt();
    int y = ui->textEdit_2->toPlainText().toInt();
    int radius = ui->textEdit_3->toPlainText().toInt();
    BresenhamCircleDrawingAlgo(x , y , radius , image);
    BresenhamLineDrawingAlgo(x , y-radius , x - 0.866*radius , y+radius/2 , image);
    BresenhamLineDrawingAlgo(x - 0.866*radius , y+radius/2, x + 0.866*radius , y+radius/2 , image);
    BresenhamLineDrawingAlgo(x , y-radius , x + 0.866*radius , y+radius/2 , image);
    DDACircleDrawingAlgo(x , y , radius/2 , image);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
