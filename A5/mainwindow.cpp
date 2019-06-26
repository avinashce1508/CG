#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"


int x_arr[100] ; int y_arr[100];
int colourval;
int i = 0;
int flag = 0;
QImage image(400 , 400 , QImage::Format_RGB888);
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
    if(val < 0 )
      return -1;
    else if (val > 0)
      return 1;
    else
      return 0;
}

void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    int dx , dy , s1 , s2 , Exchange , decision_parameter , i;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    s1 = sign(x2- x1);
    s2 = sign(y2 - y1);

     int x  = x1;
     int y = y1;

    if(dy > dx)
    {
        int temp = dx;
        dx = dy;
        dy = temp;
        Exchange = 1;
    }
    else
    {
        Exchange = 0;
    }

    i = 1;
    decision_parameter = 2*dy - dx;

    while(i <= dx)
    {
       img.setPixel(x , y+50 , colourval);
       while(decision_parameter >= 0)
       {
           if(Exchange == 1)
           {
               x += s1;
           }
           else
           {
               y += s2;
           }
           decision_parameter -= 2*dx;

       }
       if(Exchange == 1)
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

void MainWindow::ddaAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    float dx , dy , len;
    if(abs(x2 - x1) > abs(y2-y1))
    {
        len = abs(x2 - x1);
    }
    else
    {
        len = abs(y2 - y1);
    }

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);

    dx = abs(x2 - x1)/len ;
    dy = abs(y2 - y1)/len;

    int x = x1 + 0.5*s1;
    int y = y1 + 0.5*s2;
    int i = 1;
    while(i <= len)
    {
        img.setPixel(x , y ,qRgb(0 , 255 , 0) );
        x += dx;
        y += dy;
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
    {
        return ;
    }
    if(i > 0 &&event->button()== Qt::LeftButton)
    {
        BresenhamLineDrawingAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[i] , y_arr[i] , image );
      //  ddaAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[i] , y_arr[i] , image );
    }
    i++;
    emit(clicked());
    ui->label->setPixmap(QPixmap::fromImage(image));
    if(event->button() == Qt::RightButton)
    {
        flag = 1;
        BresenhamLineDrawingAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[0] , y_arr[0] , image );
       // ddaAlgo(x_arr[i-1] , y_arr[i-1] , x_arr[0] , y_arr[0] , image );

    }
    emit(rightclicked());

     ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::SeedfillAlgo(int x , int y)
{
    QColor currentcol(image.pixel(x , y));
    image.setPixel(x , y , colourval);
    if(currentcol == qRgb( 0 , 0 , 0))
    {
        SeedfillAlgo(x+1 , y);
         SeedfillAlgo(x-1 , y);
          SeedfillAlgo(x , y+1);
           SeedfillAlgo(x , y-1);
    }
}
void MainWindow::on_radioButton_clicked()
{
    colourval = qRgb(0 , 255 , 0);
}

void MainWindow::on_radioButton_2_clicked()
{
    colourval = qRgb(255 , 255 , 255);
}

void MainWindow::on_radioButton_3_clicked()
{
   colourval = qRgb(255, 255 , 0);
}
