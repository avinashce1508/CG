#include "mainwindow.h"
#include "ui_mainwindow.h"

 QImage image( 300 , 300 , QImage::Format_RGB888);

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
void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1, int x2 , int y2, QImage & img)
{
    int x , y , i , Interchange , dx , dy , Decision_Parameter , s1 , s2 ;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    x = x1;
    y = y1;
    s1 = sign(x2 - x1);
    s2 = sign(y2 - y1);
    i = 0;

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
   Decision_Parameter = 2*dy - dx;
   i = 0;
    while( i <= dx)
      {
        img.setPixel(x , y , qRgb(0 , 0 , 255));
        while(Decision_Parameter >= 0)
        {
            if(Interchange == 1)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
              Decision_Parameter -= 2*dx;

        }
        if(Interchange == 1)
        {
            y += s2;
        }
        else
        {
            x += s1;
        }
         Decision_Parameter += 2*dy;
        i++;
      }


}
void MainWindow::DDALineDrawingAlgo(float x1 , float y1 , float x2 , float y2 , QImage & img)
{
  float dx , dy , len;
  if(abs(x2 - x1 ) > abs( y2 - y1))
    len = abs( x2 - x1);
  else
     len = abs(y2 - y1);

  dx = abs( x2 - x1)/ len;
  dy = abs( y2 - y1)/ len;

  float x = x1 + 0.5*sign(x2 -x1);
  float y = y1 + 0.5*sign(y2 -y1);
  int i = 0;
  while(i <= len)
  {
      img.setPixel(x , y , qRgb( 0 , 255 , 0));

      x+= dx;
      y+= dy;
      i++;
  }
}
void MainWindow::BresenhamCircleDrawingAlgo(int x , int y , int radius, QImage & img)
{
  float decision_factor = 3 - 2*radius;

  int x1 = 0;
  int y1 = radius;

  while( x1 < y1)
  {
      if(decision_factor <= 0)
      {
          decision_factor += 4*x1 + 6;
          x1++;
      }
      else
      {
          decision_factor += 4*(x1 - y1) + 10;

          x1++;
          y1--;
      }
      displayCircle( x , y , x1 , y1 , img);
     // displayCircle1( x , y , x1 , y1 , image);
  }

}
void MainWindow::DDACircleDrawingAlgo(float x , float y , float radius, QImage & img)
{
  float x1 = radius;
  float y1 = 0;
  int i = 0;
  float start_x = x1;
  float start_y = y1;
  float val;
  do
  {
     val = pow( 2, i);
              i++;
  }while(val < radius);

  float epsilon = 1/pow(2 , i-1);

  do
  {
      float x2 = x1 + y1*epsilon;
      float y2 = y1 - x2*epsilon;

      img.setPixel(x + x2 , y+ y2 , qRgb(0 , 255 , 0));

      x1 = x2;
      y1 = y2;
  }while((y1 - start_y) < epsilon || (start_x - x1) >epsilon);

}
void MainWindow::displayCircle(int x , int y , int x1 , int y1 , QImage &img)
{

    img.setPixel(x + x1 , y + y1  , qRgb(255 , 255 , 0));
    img.setPixel(x + x1 , y - y1 , qRgb(255 , 255 , 0));
    img.setPixel(x + y1 , y + x1 , qRgb(255 , 255 , 0));
    img.setPixel(x + y1 , y - x1 , qRgb(255 , 255 , 0));

    img.setPixel(x - x1 , y + y1 , qRgb(255 , 255 , 0));
    img.setPixel(x - x1 , y - y1 , qRgb(255 , 255 , 0));
    img.setPixel(x - y1 , y + x1 , qRgb(255 , 255 , 0));
    img.setPixel(x - y1 , y - x1 , qRgb(255 , 255 , 0));


}
void MainWindow::displayCircle1(int x , int y, int x1 , int y1 , QImage & img)
{
    img.setPixel(x + x1 , y + y1- 30  , qRgb(255 , 255 , 0));
    img.setPixel(x - x1 , y + y1 -30 , qRgb(255 , 255 , 0));
    ui->label->setPixmap(QPixmap::fromImage(image));
}
/*void MainWindow::displayCircle(int x , int y , int x1 , int y1 , QImage &img)
{

    img.setPixel(x + x1+50 , y + y1  , qRgb(255 , 255 , 0));
    img.setPixel(x + x1+50 , y - y1 , qRgb(255 , 255 , 0));
    img.setPixel(x + y1+50 , y + x1 , qRgb(255 , 255 , 0));
    img.setPixel(x + y1+50 , y - x1 , qRgb(255 , 255 , 0));

    img.setPixel(x - x1-50 , y + y1 , qRgb(255 , 255 , 0));
    img.setPixel(x - x1-50 , y - y1 , qRgb(255 , 255 , 0));
    img.setPixel(x - y1-50 , y + x1 , qRgb(255 , 255 , 0));
    img.setPixel(x - y1-50 , y - x1 , qRgb(255 , 255 , 0));
}*/
/*void MainWindow::displayCircle1(int x , int y , int x1 , int y1 ,  QImage &img)
{
    img.setPixel(x - y1 , y - x1-50 , qRgb(255 , 255 , 0));
    img.setPixel(x + x1 , y - y1-50 , qRgb(255 , 255 , 0));
    img.setPixel(x + y1 , y - x1-50 , qRgb(255 , 255 , 0));
    img.setPixel(x - x1 , y - y1-50 , qRgb(255 , 255 , 0));


    img.setPixel(x + y1 , y + x1+50 , qRgb(255 , 255 , 0));
    img.setPixel(x - y1 , y + x1+50 , qRgb(255 , 255 , 0));
    img.setPixel(x + x1 , y + y1+50  , qRgb(255 , 255 , 0));
    img.setPixel(x - x1 , y + y1+50 , qRgb(255 , 255 , 0));
}
*/
void MainWindow::BresenhamCircleDrawingAlgoForSbiLogo(int x , int y , int radius, QImage & img)
{
  float decision_factor = 3 - 2*radius;


  int x1 = 5;
  int y1 = radius;
      while( x1 < y1)
          {
              if(decision_factor <= 0)
              {
                  decision_factor += 4*x1 + 6;
                  x1++;
              }
              else
              {
                  decision_factor += 4*(x1 - y1) + 10;

                  x1++;
                  y1--;
              }
              img.setPixel(x + x1 , y + y1  , qRgb(255 , 255 , 0));
              img.setPixel(x - x1 , y + y1 , qRgb(255 , 255 , 0));
          }

       x1  = 0 ;
       y1 = radius+1;
       while( x1 < y1)
          {
              if(decision_factor <= 0)
              {
                  decision_factor += 4*x1 + 6;
                  x1++;
              }
              else
              {
                  decision_factor += 4*(x1 - y1) + 10;

                  x1++;
                  y1--;
              }
              img.setPixel(x + x1 , y - y1 , qRgb(255 , 255 , 0));
              img.setPixel(x + y1 , y + x1 , qRgb(255 , 255 , 0));
              img.setPixel(x + y1 , y - x1 , qRgb(255 , 255 , 0));

              img.setPixel(x - x1 , y - y1 , qRgb(255 , 255 , 0));
              img.setPixel(x - y1 , y + x1 , qRgb(255 , 255 , 0));
              img.setPixel(x - y1 , y - x1 , qRgb(255 , 255 , 0));
          }


}
void MainWindow::displaysmily()
{
QImage image( 300 , 300 , QImage::Format_RGB888);

//BresenhamCircleDrawingAlgo(100 , 100 , 75 , image);
BresenhamCircleDrawingAlgo(100 , 100 , 50 , image);
DDACircleDrawingAlgo(100 , 100 , 75 , image);
DDACircleDrawingAlgo(80 , 80 , 5 , image);
DDACircleDrawingAlgo(120 , 80 , 5 , image);
//BresenhamLineDrawingAlgo(80 , 120 , 120 , 120 , image);
ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::displayCircletouchingCircle()
{
  QImage image( 300 , 300 , QImage::Format_RGB888);
  BresenhamCircleDrawingAlgo(150 , 150  , 30 , image);
  BresenhamCircleDrawingAlgo(180 , 150-(60*0.866)  , 30 , image);
  BresenhamCircleDrawingAlgo(180 , 150+(60*0.866)  , 30 , image);
  BresenhamCircleDrawingAlgo(120 , 150-(60*0.866)  , 30 , image);
  BresenhamCircleDrawingAlgo(120 , 150+(60*0.866)  , 30 , image);
  BresenhamCircleDrawingAlgo(210 , 150  , 30 , image);
  BresenhamCircleDrawingAlgo(90 , 150  , 30 , image);
  BresenhamCircleDrawingAlgo(150 , 150  , 60 , image);
  BresenhamCircleDrawingAlgo(150 , 150  , 90 , image);
  ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::displayLogoOfLG()
{
     QImage image( 300 , 300 , QImage::Format_RGB888);
     DDACircleDrawingAlgo(150 , 150  , 50 , image);
     DDACircleDrawingAlgo(140  , 140 , 5 , image);
     BresenhamCircleDrawingAlgo(150 , 150 , 30 , image);
     BresenhamLineDrawingAlgo(165 , 150 , 180 , 150 , image);
     BresenhamLineDrawingAlgo(150 , 130  , 150  , 160, image);
     BresenhamLineDrawingAlgo(150 , 160  , 165  , 160, image);
     ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::SeedfillAlgo(int x , int y)
{
    QColor currentcolour(image.pixel(x , y));
    image.setPixel(x , y , qRgb( 0 , 0 , 255));
    if(currentcolour == qRgb(0 , 0 , 0))
    {
       SeedfillAlgo(x+1 , y);
       SeedfillAlgo(x-1 , y);
       SeedfillAlgo(x , y+1);
       SeedfillAlgo(x , y-1);
    }
}
void MainWindow::displaySbiLogo()
{


   // BresenhamCircleDrawingAlgoForSbiLogo(150 , 150 , 10 , image);
   // BresenhamCircleDrawingAlgoForSbiLogo(150 , 150 , 50 , image);
   // BresenhamCircleDrawingAlgo(150 , 150 , 10 , image);
   // BresenhamCircleDrawingAlgo(150 , 150 , 50 , image);
    DDACircleDrawingAlgo(150 , 150 , 10 , image);
    DDACircleDrawingAlgo(150 , 150 , 50 , image);
    BresenhamLineDrawingAlgo(145 , 159 , 145 , 200 , image);
    BresenhamLineDrawingAlgo(155 , 159 , 155 , 200 , image);


    SeedfillAlgo(180 , 150 );
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::displayTriangleinsideTriangle()
{
    BresenhamLineDrawingAlgo(150 , (200 - 86.6)  , 200 , 200 , image);
    BresenhamLineDrawingAlgo(100 , 200 , 150 , (113.14) , image);
    BresenhamLineDrawingAlgo(100 , 200 , 200 , 200 , image);

    BresenhamLineDrawingAlgo(125 , 157 , 175 , 157 , image);
    BresenhamLineDrawingAlgo(125 , 157 , 150 , 200 , image);
    BresenhamLineDrawingAlgo(150 , 200 , 175 , 157 , image);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::displayCircleInsideHexagon()
{
    BresenhamCircleDrawingAlgo(150 , 150 , 50 , image);

    BresenhamLineDrawingAlgo(100 , 120 , 100 , 180 ,image );
    BresenhamLineDrawingAlgo(200 , 120 , 200 , 180 ,image );

    BresenhamLineDrawingAlgo(150 , 90 ,  200 , 120 ,image );
    BresenhamLineDrawingAlgo(150 , 210 , 200 , 180 ,image );

    BresenhamLineDrawingAlgo(150 , 90 , 100 , 120 ,image );
    BresenhamLineDrawingAlgo(150 , 210 , 100 , 180 ,image );

    BresenhamLineDrawingAlgo(100 , 120 , 200 , 180 ,image );

    BresenhamLineDrawingAlgo(150 , 90 , 150 , 210 ,image );
    BresenhamLineDrawingAlgo(200 , 120 , 100 , 180 ,image );
    ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::semicircleAroundSquare()
{
    BresenhamLineDrawingAlgo(100 , 100 , 100 , 200 ,image );
    BresenhamLineDrawingAlgo(100 , 100 , 200 , 100 ,image );

    BresenhamLineDrawingAlgo(100 , 200 ,  200 , 200 ,image );
    BresenhamLineDrawingAlgo(200 , 100 , 200 , 200 ,image );

    BresenhamLineDrawingAlgo(100 , 100 , 200 , 200 ,image );
    BresenhamLineDrawingAlgo(100 , 200 , 200 , 100 ,image );

    BresenhamCircleDrawingAlgo(150 , 150 , 50 , image);
    BresenhamCircleDrawingAlgo(150 , 150 , 50 , image);


    ui->label->setPixmap(QPixmap::fromImage(image));

}
void MainWindow::displaySquareAroundSquare()
{
    BresenhamLineDrawingAlgo(100 , 100 , 100 , 200 ,image );
    BresenhamLineDrawingAlgo(100 , 100 , 200 , 100 ,image );

    BresenhamLineDrawingAlgo(100 , 200 ,  200 , 200 ,image );
    BresenhamLineDrawingAlgo(200 , 100 , 200 , 200 ,image );

     BresenhamLineDrawingAlgo(250 , 140 , 220 , 140 ,image );
     BresenhamLineDrawingAlgo(220 , 140 , 220 , 80 ,image );
     BresenhamLineDrawingAlgo(250 , 140 , 250 , 50 ,image );
     BresenhamLineDrawingAlgo(160 , 80 , 220 , 80 ,image );
     BresenhamLineDrawingAlgo(160 , 50 , 250 , 50 ,image );
     BresenhamLineDrawingAlgo(160 , 50 , 160 , 80 ,image );

     BresenhamLineDrawingAlgo(250 , 160 , 220 , 160 ,image );
     BresenhamLineDrawingAlgo(220 , 160 , 220 , 220 ,image );
     BresenhamLineDrawingAlgo(250 , 160 , 250 , 250 ,image );
     BresenhamLineDrawingAlgo(160 , 220 , 220 , 220 ,image );
     BresenhamLineDrawingAlgo(160 , 250 , 250 , 250 ,image );
     BresenhamLineDrawingAlgo(160 , 220 , 160 , 250 ,image );

     BresenhamLineDrawingAlgo(50 , 140 , 80 , 140 ,image );
     BresenhamLineDrawingAlgo(80 , 140 , 80 , 80 ,image );
     BresenhamLineDrawingAlgo(50 , 140 , 50 , 50 ,image );
     BresenhamLineDrawingAlgo(140 , 80 , 80 , 80 ,image );
     BresenhamLineDrawingAlgo(140 , 50 , 50 , 50 ,image );
     BresenhamLineDrawingAlgo(140 , 50 , 140 , 80 ,image );

     BresenhamLineDrawingAlgo(50 , 160 , 80 , 160 ,image );
     BresenhamLineDrawingAlgo(80 , 160 , 80 , 220 ,image );
     BresenhamLineDrawingAlgo(50 , 160 , 50 , 250 ,image );
     BresenhamLineDrawingAlgo(140 , 220 , 80 , 220 ,image );
     BresenhamLineDrawingAlgo(140 , 250 , 50 , 250 ,image );
     BresenhamLineDrawingAlgo(140 , 250 , 140 , 220 ,image );

     SeedfillAlgo(150 , 150);
     SeedfillAlgo(170 , 60);
     SeedfillAlgo(130 , 60);
     SeedfillAlgo(130 , 230);
     SeedfillAlgo(170 , 230);

    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::displayTriangleinscribedCircle()
{
   DDACircleDrawingAlgo(150 , 150 , 50 , image);

   BresenhamLineDrawingAlgo(150 , 200 , 150 , 150 ,image );
   BresenhamLineDrawingAlgo(150 , 150 , 193.3 , 125 ,image );
   BresenhamLineDrawingAlgo(150 , 150 , 106.7 , 125 ,image );
   BresenhamLineDrawingAlgo(150 , 200 , 106.7 , 125  ,image );
   BresenhamLineDrawingAlgo(150 , 200 , 193.3 , 125 ,image );
   BresenhamLineDrawingAlgo(193.3 , 125 ,106.7 , 125 ,image );

   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::displaySemicircleAroundCircle()
{
   DDACircleDrawingAlgo(150 , 150 , 55 , image);

   BresenhamCircleDrawingAlgo(150 , 150 , 25 , image);
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::displayFigure()
{
    BresenhamLineDrawingAlgo(100 , 100 , 50 , 150 ,image );
    BresenhamLineDrawingAlgo(100 , 100 , 150 , 150 ,image );
    BresenhamLineDrawingAlgo(50 , 150 ,  80 , 150 ,image );
    BresenhamLineDrawingAlgo(120 , 150 , 150 , 150  ,image );
    BresenhamLineDrawingAlgo(80 , 150 , 80 , 200 ,image );
    BresenhamLineDrawingAlgo(120 , 200 ,120 , 150,image );
    BresenhamLineDrawingAlgo(120 , 200 ,120 , 150,image );
    BresenhamLineDrawingAlgo(80 , 200 ,120 , 200,image );
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::figure()
{
    BresenhamLineDrawingAlgo(150 , 50 , 150 , 150 ,image );
    BresenhamLineDrawingAlgo(150 , 150 , 120 , 100  ,image );
    BresenhamLineDrawingAlgo(150 , 150 , 180 , 100 ,image );
    BresenhamLineDrawingAlgo(150 , 50 ,120 , 100,image );
    BresenhamLineDrawingAlgo(150 , 50 ,180 , 100,image );

    BresenhamLineDrawingAlgo(150 , 150 , 50 , 200 ,image );
    BresenhamLineDrawingAlgo(150 , 150 ,120 , 200,image );
    BresenhamLineDrawingAlgo(150 , 150 , 90 , 150 ,image );
    BresenhamLineDrawingAlgo(50 , 200 , 120 , 200 ,image );
    BresenhamLineDrawingAlgo(50 , 200 ,  90 , 150 ,image );

    BresenhamLineDrawingAlgo(150 , 150 ,  250 , 200 ,image );
    BresenhamLineDrawingAlgo(150 , 150 , 175 , 200  ,image );
    BresenhamLineDrawingAlgo(150 , 150 , 210 , 150 ,image );
    BresenhamLineDrawingAlgo(250 , 200 ,175, 200,image );
    BresenhamLineDrawingAlgo(250 , 200 ,210 , 150,image );
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::on_pushButton_clicked()
{
   displayCircletouchingCircle();
}
