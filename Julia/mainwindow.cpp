#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(500,500,QImage::Format_RGB888);

int w =500 , h=500 , zoom = 1;

float cx = -0.7 , cy = 0.27015, movex = 0.0, movey = 0.0;
int maxIter = 255;

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

void MainWindow::Julia(){
    for(int x1 = 0;x1 < w;x1++)
    {
        for(int y1 = 0;y1 < h;y1++)
        {
            float zx = 1.5*(x1-w/2)/(0.5*zoom*w)+movex;
            float zy = 1.0*(y1-h/2)/(0.5*zoom*h)+movey;
            int i = maxIter;
            while(zx*zx + zy*zy < 4 && i > 1)
            {
                float temp = zx*zx - zy*zy + cx;
                zy = 2*zx*zy + cy;
                zx = temp;
                i -=1;
            }
            image.setPixel(x1,y1,qRgb(i*7,i,i));
        }
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    Julia();
}
