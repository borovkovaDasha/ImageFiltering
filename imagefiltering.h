#ifndef IMAGEFILTERING_H
#define IMAGEFILTERING_H
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QDebug>

class ImageFiltering
{
public:
    ImageFiltering();
    QImage myImage;
    QImage noiseImage;
    QImage filterImage;
    void ImageToMatrix();
    void MatrixToImage();
    void FilterMatrixToImage();
    void ImpulseNoise();
    void SaPNoise();
    void GaussianNoise();
    void GaussianFilter();
    void MedianFilter(int edge);
    void BoxFilter(int edge);
    void AddMedianFilter(int edge, int times);
    int height;
    int width;
    int** rmatrix;
    int** gmatrix;
    int** bmatrix;
    int** rfmatrix;
    int** gfmatrix;
    int** bfmatrix;
};

#endif // IMAGEFILTERING_H
