/*
 * A Mandelbrot Set is a set of complex number z that does not diverge under the transformation
 * (Xn+1 - Xn^2 +z )with Xo - 0.Where, both X and z represent the complex numbers. Write Java program to
a) Plot the Mandelbrot set for the threshold |x|= 2.
b) Plot Julia set choosing z ≠ 0. Use 254 colors for plotting in both cases.


*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(500 , 500 , QImage::Format_RGB888);
int ImageHeight = 431;
int ImageWidth = 431;

QRgb clr = qRgb(0 , 255 , 255);
QRgb clr1 = qRgb(255 , 0 , 0);

float cx=-0.7,cy = 0.27015,movex = 0.0,movey = 0.0;
int maxIter = 255;
int w =500,h=500,zoom=1;

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



void MainWindow::on_pushButton_clicked()
{
    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
    double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;

    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

    unsigned MaxIterations = 100;

    for(unsigned y = 0; y < ImageHeight; ++y)
    {
        double c_im = MaxIm - y*Im_factor;

        for(unsigned x=0; x < ImageWidth ; ++x)
        {
            double c_re = MinRe + x*Re_factor;

            double Z_re = c_re, Z_im = c_im;

            bool isInside = true;
            unsigned n;
            for( n = 0; n < MaxIterations ; ++n)
            {
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4)
                {
                    isInside = false;
                    break;
                }

                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;

            }
            if(isInside) {

                 image.setPixel(x , y , qRgb( x*4+y , y*2 , n*2-x+y));
            }

        }
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int x1 = 0;x1 < w;x1++){
            for(int y1 = 0;y1 < h;y1++){
                float zx = 1.5*(x1-w/2)/(0.5*zoom*w)+movex;
                float zy = 2.0*(y1-h/2)/(0.5*zoom*h)+movey;
                int i = maxIter;
                while(zx*zx + zy*zy < 4 && i > 1)
                {
                    float temp = zx*zx - zy*zy + cx;
                    zy = 2*zx*zy + cy;
                    zx = temp;
                    i -=1;
                }
                image.setPixel(x1,y1,qRgb(i*5,i*3,i*2));
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
}
/*  -- mandelbrot ----

The Mandelbrot and the closely related Julia sets are both based on the idea of choosing two
complex numbers z0 and c, and then repeatedly evaluating zn=zn-12+c. If zn does not tend to
infinity the point (z0,c) is in the set (colored blue or black in the pictures on this page).
If we consider all possible z0 and c then we end up with a four dimensional set, whicht is rather
 hard to visualise.
 
Outline Proof: if |z|>2, then |z2 +c | ≥ |z2|-|c| > 2|z|-|c|. If |z|>|c|, then 2|z| - |c| > |z|.
So, if |z| > 2 and |z| > |c|, then |z2 + c|  > |z|, so the sequence is increasing. This is not the
same as proving the sequence tends to infinity, but with a bit more work you can see that in fact
the distance from the origin will get bigger more quickly the further you get from a distance of 2,
because the difference of the distance from 2 will roughly double with each iteration while we are
still near two, and will increase even more thereafter. Now, after the the first iteration, |z|=|c|,
so if |c|>2, the sequence diverges and this means that the Mandelbrot set lies within |c|≤2).
*/

/*  -- julia ---

*/
