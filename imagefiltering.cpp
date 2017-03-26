#include "imagefiltering.h"
#include <QTime>
#include <QtGlobal>
#include <QtAlgorithms>

ImageFiltering::ImageFiltering()
{
    QString path("C:\\Users\\Dasha\\Documents\\IMG_3392.JPG");
    myImage.load(path);
}

void ImageFiltering::ImageToMatrix()
{
    QRgb c;
    height = myImage.height();
    width = myImage.width();
    QSize size(width,height);
    noiseImage = QImage(size, QImage::Format_RGB32);
    filterImage = QImage(size, QImage::Format_RGB32);
    rmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            rmatrix[i] = new int [height];
    gmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            gmatrix[i] = new int [height];
    bmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            bmatrix[i] = new int [height];
    rfmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            rfmatrix[i] = new int [height];
    gfmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            gfmatrix[i] = new int [height];
    bfmatrix = new int *[width];
        for (int i = 0; i < width; ++i)
            bfmatrix[i] = new int [height];
    qDebug() << "height" <<height;
    qDebug() << "width" << width;
    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
        {
            c = myImage.pixel(i,j);
            rmatrix[i][j] = qRed(c);
            gmatrix[i][j] = qGreen(c);
            bmatrix[i][j] = qBlue(c);
        }
    QTime now = QTime::currentTime();
    qsrand(now.msec());
}

void ImageFiltering::MatrixToImage()
{
    QRgb value;
    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
        {
            value = qRgb(rmatrix[i][j], gmatrix[i][j], bmatrix[i][j]);
            noiseImage.setPixel(i, j, value);
        }
}

void ImageFiltering::FilterMatrixToImage()
{
    QRgb value;
    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
        {
            value = qRgb(rfmatrix[i][j], gfmatrix[i][j], bfmatrix[i][j]);
            filterImage.setPixel(i, j, value);
        }
}

void ImageFiltering::ImpulseNoise()
{
    int noise = height*width*0.05;
    for (int i = 0; i<noise; i++)
    {
        int x = qrand() % width;
        int y = qrand() % height;
        rmatrix[x][y] = 255;
        gmatrix[x][y] = 255;
        bmatrix[x][y] = 255;
    }
    MatrixToImage();
}

void ImageFiltering::SaPNoise()
{
    int noise = height*width*0.025;
    for (int i = 0; i<noise; i++)
    {
        int x = qrand() % width;
        int y = qrand() % height;
        rmatrix[x][y] = 255;
        gmatrix[x][y] = 255;
        bmatrix[x][y] = 255;
    }
    for (int i = 0; i<noise; i++)
    {
        int x = qrand() % width;
        int y = qrand() % height;
        rmatrix[x][y] = 0;
        gmatrix[x][y] = 0;
        bmatrix[x][y] = 0;
    }
    MatrixToImage();
}

void ImageFiltering::GaussianNoise()
{
    int noise = height*width*0.05;
    for (int i = 0; i<noise; i++)
    {
        int x = qrand() % width;
        int y = qrand() % height;
        rmatrix[x][y] = qrand() % 256;
        gmatrix[x][y] = qrand() % 256;
        bmatrix[x][y] = qrand() % 256;
    }
    MatrixToImage();
}

void ImageFiltering::BoxFilter(int edge)
{
    int rtmp = 0;
    int gtmp = 0;
    int btmp = 0;
    int k = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            for (int column=-edge/2; column<=edge/2; column++)
            {
                int line = column;
                if (column+j >= height)
                {
                    line = height - (column+j);
                }
                else if (j+column < 0)
                {
                    line = -(j+column);
                }
                for (int row=-edge/2; row<=edge/2; row++)
                {
                    int r = row;
                    if (row + i >= width)
                    {
                        r = width - (row + i);
                    }
                    else if (row + i < 0)
                    {
                        r = -(row+i);
                    }
                    rtmp = rtmp + rmatrix[i+r][j+line];
                    gtmp = gtmp + gmatrix[i+r][j+line];
                    btmp = btmp + bmatrix[i+r][j+line];
                    k++;
                }
            }
            rfmatrix[i][j] = rtmp/k;
            gfmatrix[i][j] = gtmp/k;
            bfmatrix[i][j] = btmp/k;
            rtmp = 0;
            gtmp = 0;
            btmp = 0;
            k = 0;
        }
    FilterMatrixToImage();
}

void ImageFiltering::MedianFilter(int edge)
{
    QList<int> rtmp;
    QList<int> gtmp;
    QList<int> btmp;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            int k = 0;
            for (int column=-edge/2; column<=edge/2; column++)
            {
                int line = column;
                if (column+j >= height)
                {
                    line = height - (column+j);
                }
                else if (j+column < 0)
                {
                    line = -(j+column);
                }
                for (int row=-edge/2; row<=edge/2; row++)
                {
                    int r = row;
                    if (row + i >= width)
                    {
                        r = width - (row + i);
                    }
                    else if (row + i < 0)
                    {
                        r = -(row+i);
                    }
                    rtmp.append(rmatrix[i+r][j+line]);
                    gtmp.append(gmatrix[i+r][j+line]);
                    btmp.append(bmatrix[i+r][j+line]);
                    k++;
                }
            }
            qSort(rtmp.begin(), rtmp.end());
            qSort(gtmp.begin(), gtmp.end());
            qSort(btmp.begin(), btmp.end());
            rfmatrix[i][j] = rtmp.at(int((edge*edge-1)/2));
            gfmatrix[i][j] = gtmp.at(int((edge*edge-1)/2));
            bfmatrix[i][j] = btmp.at(int((edge*edge-1)/2));
            rtmp.clear();
            gtmp.clear();
            btmp.clear();
        }
    FilterMatrixToImage();
}

void ImageFiltering::AddMedianFilter(int edge, int times)
{
    for (int i=0; i<times; i++)
    {
        MedianFilter(edge);
        rmatrix = rfmatrix;
        gmatrix = gfmatrix;
        bmatrix = bfmatrix;
    }
}

void ImageFiltering::GaussianFilter()
{
}
