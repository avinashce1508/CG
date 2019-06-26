
/*Write C++/Java program to implement reflection of 2-D object about X axis, Y axis and about
 * X=Y axis. Also rotate object about arbitrary point given by user.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QDebug"
#include "math.h"

int C_Array[20][2];
int ReflectionMat[2][2] = { {1 , 0 }, {0 , 1}};
int Array[20][2]= { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
int i = 0;
int flag = 0;
static int count = 0;
QImage image(600 , 600 , QImage::Format_RGB888);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BresenhamLineDrawingAlgo(0 , 300 , 600 , 300 , image);
    BresenhamLineDrawingAlgo(300 , 0 , 300 , 600 , image);
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
    else if( val > 0)
        return 1;
    else
        return 0;
}
void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    int dx , dy , s1 , s2 , interchange , decision_parameter , x , y;

    dx = abs(x2-x1);
    dy = abs(y2-y1);

    x = x1;
    y = y1;

    s1 = sign(x2-x1);
    s2 = sign(y2 -y1);

    if(dy > dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }
    else
    {
        interchange = 0;
    }
    int i = 1;
    decision_parameter = 2*dy - dx;
    while(i <= dx)
    {
        img.setPixel(x , y-15 , qRgb(0 , 255 , 0));

        while(decision_parameter >= 0)
        {
            if(interchange == 1)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
            decision_parameter -= 2*dx;
        }
        if(interchange == 1)
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
   if(flag == 1)
   {
       return;
   }
   C_Array[i][0] = QString::number(event->x()).toInt();
   C_Array[i][1] = QString::number(event->y()).toInt();

   if(i > 0  && event->button() == Qt::LeftButton)
   {
       BresenhamLineDrawingAlgo(C_Array[i-1][0] , C_Array[i-1][1] , C_Array[i][0] ,C_Array[i][1] ,image);
   }
   else if( event->button() == Qt::RightButton)
   {
       flag = 1;
       BresenhamLineDrawingAlgo( C_Array[i][0] ,C_Array[i][1] , C_Array[0][0] , C_Array[0][1],image);
   }
   i++;
   count++;
   ui->label->setPixmap(QPixmap::fromImage(image));
   emit(clicked());
}
void MainWindow::MultiplicationOfTwoMatrices()
{
  for(int i = 0 ; i < count-1 ; i++)
  {
      for(int j = 0 ; j < 2 ; j++)
      {
          for( int k = 0 ; k < 2 ; k++)
          {
              Array[i][j] += (C_Array[i][k]-300)*ReflectionMat[k][j];
          }
      }
  }

}
void MainWindow::ReflectionAboutXAxis()
{
  //  ReflectionMat[2][2] = {{1 , 0} , {0 , -1}};

    ReflectionMat[1][1] = -1;
    MultiplicationOfTwoMatrices();
    i = 1;
    while(i < count - 1)
    {
       BresenhamLineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[i][0]+300 ,Array[i][1]+300 ,image);
       i++;
    }
       BresenhamLineDrawingAlgo(Array[i-1][0]+300 , Array[i-1][1]+300 , Array[0][0]+300 ,Array[0][1]+300 ,image);
   ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::ReflectionAboutYAxis()
{
    ReflectionMat[0][0] = -1;
    ReflectionMat[1][1] = 1;
    MultiplicationOfTwoMatrices();
    i = 1;
    while(i < count - 1)
    {
       BresenhamLineDrawingAlgo(300 + Array[i-1][0] , Array[i-1][1]+300 , 300 + Array[i][0] , Array[i][1]+300 ,image);
       i++;
    }
       BresenhamLineDrawingAlgo(300 + Array[i-1][0] , Array[i-1][1]+300 , 300 + Array[0][0] , Array[0][1]+300 ,image);
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::ReflectionAboutXYLine()
{
    ReflectionMat[0][1] = -1;
    ReflectionMat[1][0] = -1;
    ReflectionMat[0][0] = 0;
    ReflectionMat[1][1] = 0;
    MultiplicationOfTwoMatrices();
    i = 1;
    while(i < count - 1)
    {
       BresenhamLineDrawingAlgo(Array[i-1][0]+300 , 300 + Array[i-1][1] , Array[i][0]+300 ,300+Array[i][1] ,image);
       i++;
    }
       BresenhamLineDrawingAlgo(Array[i-1][0]+300 , 300 + Array[i-1][1] , Array[0][0]+300 ,300+Array[0][1],image);
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::on_pushButton_clicked()   // reflection about about x-axis
{
   ReflectionAboutXAxis();
}

void MainWindow::on_pushButton_2_clicked() // reflection about y-axis
{
   ReflectionAboutYAxis();
}

void MainWindow::on_pushButton_3_clicked() // reflection about x = y line
{
  ReflectionAboutXYLine();
}
