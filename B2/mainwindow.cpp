#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include<QDebug>
int x_arr[100];
int y_arr[100];
QImage image(491 , 371 , QImage::Format_RGB888);
QRgb colourval = qRgb(0 , 255 , 0);
QRgb inputColour;
QRgb targetColour = qRgb(0 , 0 , 0 );
int i = 0;
int flag = 0;

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
    else if (val > 0)
        return 1;
    else
        return 0;
}
void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
  int dx = abs(x2-x1);
  int dy = abs(y2 - y1);

  int s1 = sign(x2-x1);
  int s2 = sign(y2-y1);

  int x = x1;
  int y = y1;

  int exchange;

  if(dy > dx)
  {
      int temp = dx;
      dx = dy;
      dy = temp;
      exchange = 1;
  }
  else
  {
      exchange = 0;
  }

  int i = 0;
  int decision_parameter = 2*dy - dx;
  while(i <= dx)
  {
      if(inputColour)
      img.setPixel(x , y-30 , inputColour);
      else
        img.setPixel(x , y-30 , colourval);
      while(decision_parameter >=0)
      {
          if(exchange == 1)
          {
              x += s1;
          }
          else
          {
              y += s2;
          }
          decision_parameter -= 2*dx;
      }
      if(exchange == 1)
      {
          y += s2;
      }
      else
      {
          x += s1;
      }
      decision_parameter += 2*dy;
      i++;
  }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{

   int x1 = QString::number(event->x()).toUInt();
   int y1 = QString::number(event->y()).toUInt();


   x_arr[i] = x1;
   y_arr[i] = y1;
   if(flag == 1)
       return;
   if(i > 0 && event->button() == Qt::LeftButton)
   {
      BresenhamLineDrawingAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[i] , y_arr[i] , image);

   }
  // emit(clicked());

//   ui->label->setPixmap(QPixmap::fromImage(image));

   if(event->button() == Qt::RightButton)
   {
       flag = 1;
       BresenhamLineDrawingAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[0] , y_arr[0] , image);
   }
  // emit(rightclicked());
   ui->label->setPixmap(QPixmap::fromImage(image));
    i++;
 emit(clicked());


}
void MainWindow::seedfillAlgo(int x , int y )
{
  QColor currentColour(image.pixel(x , y));

   if(currentColour == targetColour)
   {
       if(inputColour)
        image.setPixel(x , y , inputColour);
       else
        image.setPixel(x , y , colourval);

       seedfillAlgo(x + 1 , y);
       seedfillAlgo(x - 1 , y);
       seedfillAlgo(x , y - 1);
       seedfillAlgo(x , y + 1);
   }

}
void MainWindow::on_pushButton_clicked()
{
   int x1 = x_arr[i];
   int y1 = y_arr[i];
   //image.setPixel(x1 , y1 , qRgb(255 , 255 , 255));
   qDebug()<<x1<<y1;
   seedfillAlgo(x1 , y1);
   ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
  int r = ui->textEdit->toPlainText().toInt();
  int g = ui->textEdit_2->toPlainText().toInt();
  int b = ui->textEdit_3->toPlainText().toInt();

  inputColour = qRgb(r , g , b);
}
