#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"

// declaration of global variables

int cArray[2][2];
int cArray1[20][2];
static int k = 0;
int j = 0;
QImage image(400 , 400 , QImage::Format_RGB888);
QImage image1(400 , 400 , QImage::Format_RGB888);

 int Inside = 0;
 int Top = 8;
 int Bottom = 4;
 int Left = 1;
 int Right = 2;

int x_min = 100;
int y_min = 100;
int x_max = 200;
int y_max = 200;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
void MainWindow::BresenhamLineDrawingAlgo1(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    int dx , dy , interchange , s1 , s2 , x , y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    s1 = sign(x2 - x1);
    s2 = sign(y2 - y1);

    x = x1;
    y = y1;

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

    int decision_parameter = 2*dy -dx ;

    while( i <= dx )
    {
        img.setPixel(x ,y+30 , qRgb(255 , 255 , 0));
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

void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    int dx , dy , interchange , s1 , s2 , x , y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    s1 = sign(x2 - x1);
    s2 = sign(y2 - y1);

    x = x1;
    y = y1;

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

    int decision_parameter = 2*dy -dx ;

    while( i <= dx )
    {
        img.setPixel(x ,y+30 , qRgb(255 , 255 , 0));
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

int MainWindow::ComputeCode(double x , double y)
{
   int code = Inside;

   if(x < x_min)
   {
       code |= Left;
   }
   else if( x > x_max)
   {
       code |= Right;
   }
   if(y < y_min)
   {
       code |= Bottom;
   }
   else if( y > y_max)
   {
       code |= Top;
   }
   return code;

}
void MainWindow::CohenSutherlandLineClippingAlgo(double x1 , double y1 , double x2 , double y2 )
{
   double x , y;
   int code1 = ComputeCode(x1 , y1);
   int code2 = ComputeCode(x2 , y2);

   bool accept = false;

   while(true)
   {
       if( code1 == 0 && code2 == 0)   // completely inside
       {
           accept = true;
           break;
       }
       else if(code1 & code2)   // completely outside
       {
           break;
       }
       else     // partial inside
       {
           int outcode;

           if( code1 != 0)
           {
               outcode = code1;
           }
           else
           {
               outcode = code2;
           }

           if(outcode & Top)
           {
               x = x1 + (x2 - x1)*(y_max - y1)/(y2 - y1);
               y = y_max;
           }
           else if( outcode & Bottom)
           {
               x = x1 + (x2 - x1)*(y_min - y1)/(y2 - y1);;
               y = y_min;
           }
           else if(outcode & Right)
           {
               x = x_max ;
               y = y1 + (y2 - y1)*(x_max - x1)/(x2 - x1);
           }
           else if( outcode & Left)
           {
               x = x_min;
               y = y1 + (y2 - y1)*(x_max - x1)/(x2 - x1);
           }

           if(outcode == code1)
           {
               x1 = x;
               y1 = y;
               code1 = ComputeCode(x1 , y1);
           }
           else
           {
               x2 = x;
               y2 = y;
               code2 = ComputeCode(x2 , y2);

           }
       }
   }

   if(accept == true)
   {
       BresenhamLineDrawingAlgo1(x2 , y2 , x1 , y1 , image1);
      ui->label_2->setPixmap(QPixmap::fromImage(image1));
   }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{

    cArray[j][0] = QString::number(event->x()).toUInt();
    cArray[j][1] = QString::number(event->y()).toUInt();

    if(j > 0 && event->button() == Qt::LeftButton)
    {
        BresenhamLineDrawingAlgo(cArray[j-1][0] ,  cArray[j-1][1] , cArray[j][0] , cArray[j][1] , image );

         cArray1[k][0] = cArray[0][0];
         cArray1[k][1] = cArray[0][1];
         cArray1[k+1][0] = cArray[1][0];
         cArray1[k+1][1] = cArray[1][1];
         k += 2;
         j = -1;

     }
   j++;
   emit(clicked());

ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::on_pushButton_clicked()
{
    BresenhamLineDrawingAlgo(x_min , y_min , x_min+200,y_min , image1);
    BresenhamLineDrawingAlgo(x_min , y_min+200,x_min+200,y_min+200,image1);
    BresenhamLineDrawingAlgo(x_min , y_min ,x_min,y_min+200,image1);
    BresenhamLineDrawingAlgo(x_min+200,y_min,x_min+200,y_min+200,image1);


  for(int i = 0 ; i < k ; i +=2)
  {
      CohenSutherlandLineClippingAlgo(cArray1[i][0] , cArray1[i][1] , cArray1[i+1][0] , cArray1[i+1][1]);
   }


}

void MainWindow::on_pushButton_2_clicked()
{
    BresenhamLineDrawingAlgo(x_min,y_min,x_min+200,y_min , image);
    BresenhamLineDrawingAlgo(x_min,y_min+200,x_min+200,y_min+200,image);
    BresenhamLineDrawingAlgo(x_min,y_min,x_min,y_min+200,image);
    BresenhamLineDrawingAlgo(x_min+200,y_min,x_min+200,y_min+200,image);

    ui->label->setPixmap(QPixmap::fromImage(image));
}
