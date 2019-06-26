#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(300 , 300 , QImage::Format_RGB888);

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
    else if(val > 0)
        return 1;
    else
        return 0;
}
void MainWindow::BresenhamSolidLine(int x1 , int y1 , int x2 , int y2 , QImage &img)
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
void MainWindow::BresenhamDottedLine(int x1 , int y1 , int x2 , int y2 , QImage &img)
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
           if(i %2 == 0)
           {
               img.setPixel(x , y , qRgb(0 , 255, 0));
           }

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
void MainWindow::BresenhamDashedLine(int x1 , int y1 , int x2 , int y2 , QImage &img)
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
       int count = 1;
       while(i <=dx )
       {
           if(count % 10)
              img.setPixel(x , y , qRgb(0 , 255, 255));
           else
               count = 0;
           count++;
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
void MainWindow::BresenhamDashedDottedLine(int x1 , int y1 , int x2 , int y2 , QImage &img)
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
       int count = 1;
       while(i <=dx )
       {
           if(count > 0 && count < 10 )
             img.setPixel(x , y , qRgb(0 , 255, 0));
           else if(count == 15)
              img.setPixel(x , y , qRgb(255 , 255, 0));
           else if (count == 20)
              count = 1;

              count ++;

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

void MainWindow::on_pushButton_clicked()   // solid line
{
   QImage image1(600 , 600 , QImage::Format_RGB888);

   int x1 = ui->textEdit->toPlainText().toUInt();
   int y1 = ui->textEdit_2->toPlainText().toUInt();
   int x2 = ui->textEdit_3->toPlainText().toUInt();
   int y2 = ui->textEdit_4->toPlainText().toUInt();

   BresenhamSolidLine(x1 , y1 , x2 , y2 , image1);

   ui->label->setPixmap(QPixmap::fromImage(image1));
}

void MainWindow::on_pushButton_2_clicked() // dotted line
{
    QImage image2(600 , 600 , QImage::Format_RGB888);

    int x1 = ui->textEdit->toPlainText().toUInt();
    int y1 = ui->textEdit_2->toPlainText().toUInt();
    int x2 = ui->textEdit_3->toPlainText().toUInt();
    int y2 = ui->textEdit_4->toPlainText().toUInt();

    BresenhamDottedLine(x1 , y1 , x2 , y2 , image2);
    ui->label->setPixmap(QPixmap::fromImage(image2));
}


void MainWindow::on_pushButton_3_clicked() // dashed line
{
    QImage image3(600 , 600 , QImage::Format_RGB888);

    int x1 = ui->textEdit->toPlainText().toUInt();
    int y1 = ui->textEdit_2->toPlainText().toUInt();
    int x2 = ui->textEdit_3->toPlainText().toUInt();
    int y2 = ui->textEdit_4->toPlainText().toUInt();

    BresenhamDashedLine(x1 , y1 , x2 , y2 , image3);
    ui->label->setPixmap(QPixmap::fromImage(image3));
}

void MainWindow::on_pushButton_4_clicked() // dashed- dotted line
{
    QImage image4(600 , 600 , QImage::Format_RGB888);

    int x1 = ui->textEdit->toPlainText().toUInt();
    int y1 = ui->textEdit_2->toPlainText().toUInt();
    int x2 = ui->textEdit_3->toPlainText().toUInt();
    int y2 = ui->textEdit_4->toPlainText().toUInt();

    BresenhamDashedDottedLine(x1 , y1 , x2 , y2 , image4);

    ui->label->setPixmap(QPixmap::fromImage(image4));
}

void MainWindow::on_pushButton_5_clicked() // thick line
{
    QImage image5(600 , 600 , QImage::Format_RGB888);
    int flag = 0;
    int x1 = ui->textEdit->toPlainText().toUInt();
    int y1 = ui->textEdit_2->toPlainText().toUInt();
    int x2 = ui->textEdit_3->toPlainText().toUInt();
    int y2 = ui->textEdit_4->toPlainText().toUInt();
    int w = ui->textEdit_5->toPlainText().toUInt();
    if(!w)
    {
      flag = 1;
    }
    else
    {
        for(int i = 0 ; i < 0.5*w ; i++)
        {
           BresenhamSolidLine(x1+ 0.866*i, y1-i , x2+0.866*i , y2-i , image5);
           BresenhamSolidLine(x1 + 0.866*i , y1+i , x2+0.866*i , y2+i , image5);
        }
    }
   if(flag)
       return;
    ui->label->setPixmap(QPixmap::fromImage(image5));
}

