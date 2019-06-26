/*
 * Write C++ program to draw the following pattern using Line drawing algorithms.
 * Use Bresenham’s line drawing algorithms for square and DDA line drawing algorithm for diamond.
                    _______
                    | /_\ |
                    |/| |\|
                    |\|_|/|
                    | \ / |
                    -------
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
void MainWindow::BresenhamsLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
    int x , y , i , Interchange , dx , dy , Decision_Parameter , s1 , s2 ;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    x = x1;
    y = y1;
    s1 = sign(x2 - x1);
    s2 = sign(y2 - y1);
    i = 1;

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

    while( i <= dx)
      {
        img.setPixel(x , y , qRgb(0 , 255 , 0));
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
void MainWindow::DDALineDrawingAlgo(int x1 , int y1 , int x2 , int y2 , QImage &img)
{
  float len;
  if(abs(x2-x1) > abs(y2-y1))
  {
      len = abs(x2-x1);
  }
  else
  {
      len = abs(y2 - y1);
  }

  float dx = (x2 - x1)/len;
  float dy = (y2 - y1)/len;

  float x = x1 + 0.5*sign(dx);
  float y = y1 + 0.5*sign(dy);


  int i = 1;
  while(i <= len)
  {
      img.setPixel(x , y , qRgb(0 , 255 , 0));
      if(dx > dy)
      {
        x += dx;
        y += dy;
        i++;
      }
  }
}
void MainWindow::DrawFigure(int x, int y , int width, int height, QImage &img)
{
     BresenhamsLineDrawingAlgo(x , y , (x+width) , y , img);
     BresenhamsLineDrawingAlgo(x , y , x, (y+height) , img);
     BresenhamsLineDrawingAlgo(x , y+height , x+width , y+height , img);
     BresenhamsLineDrawingAlgo(x+width , y , x+width , y+height , img);

      DDALineDrawingAlgo(x + (width/2) , y , x+width, y+(height)/2 , img);
      DDALineDrawingAlgo(x , (2*y +height)/2 , (2*x+width)/2 , y , img);
      DDALineDrawingAlgo(x , (2*y +height)/2  , (2*x + width)/2 , y+height , img);
      DDALineDrawingAlgo((2*x + width)/2 , y+height , x+width , y +height/2, img);

     BresenhamsLineDrawingAlgo((4*x+width)/4 , (4*y + 3*height)/4 , (4*x + 3*width)/4 ,(4*y+3*height)/4 , img);
     BresenhamsLineDrawingAlgo((4*x+width)/4 , (4*y + 3*height)/4 ,(4*x+width)/4 , (4*y +height)/4 , img);
     BresenhamsLineDrawingAlgo((4*x+width)/4 , (4*y +height)/4 , (4*x + 3*width)/4  ,(4*y + height)/4, img);
     BresenhamsLineDrawingAlgo((4*x + 3*width)/4  ,(4*y + height)/4, (4*x + 3*width)/4 ,(4*y+3*height)/4, img);

}
void MainWindow::on_pushButton_clicked()
{
  QImage image(300 , 300 , QImage::Format_RGB888);
  int x = ui->textEdit->toPlainText().toUInt();
  int y = ui->textEdit_2->toPlainText().toUInt();
  int width = ui->textEdit_3->toPlainText().toUInt();
  int height =  ui->textEdit_4->toPlainText().toUInt();

   DrawFigure(x , y , width , height , image);
  ui->label->setPixmap(QPixmap::fromImage(image));
}

/*   DDA Line Drawing Algorithm -
 *  1) start
 *  2) Accept two end points of line (x1 , y1 ) and (x2 , y2)
 *  3) Find out vertical and horizontal difference between endpoint i.e dy , dy respectively
 *  4) Greater of two of them will decide the length
 *  5) Determine the xinc and yinc with dx , dy , length
 *  6) If dx > dy then x is incremented by 1 and y is incremented by slope
 *  7) If dx < dy then x is incremented by 1/slope and y is incremented by 1
 *  8) Stop
 *
 *   Bresenham Line Drawing algorithm
 *
 *  1) Start
 *  2) Accept the two endpoint of line and set the initial point as x , y
 *  3) plot that point
 *  4) calculate all the constant from two endpoints such as dx , dy , decision_factor
 *  5) for each increment in x and decide y-value by checking G > 0 condition .
 *     If it is true the increment y value and update add (2dy - 2dx) otherwise add 2dy to G
 *     and don't increment y-value plot the next point
    6) Stop
 */
