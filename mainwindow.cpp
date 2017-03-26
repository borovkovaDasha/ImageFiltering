#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix = QPixmap::fromImage(myimg.myImage, Qt::AutoColor);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->clear();
    QSize PicSize(350, 350);
    scene->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->Image->setScene(scene);
    ui->Image->resize(400,400);
    ui->ImageWithNoise->resize(400,400);
    ui->ImageWithFilter->resize(400,400);
    myimg.ImageToMatrix();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAddNoise_clicked()
{
    myimg.ImageToMatrix();
    myimg.ImpulseNoise();
    QGraphicsScene *scene1 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.noiseImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene1->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithNoise->setScene(scene1);
    ui->ImageWithNoise->resize(400,400);
}

void MainWindow::on_AddSaP_clicked()
{
    myimg.ImageToMatrix();
    myimg.SaPNoise();
    QGraphicsScene *scene1 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.noiseImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene1->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithNoise->setScene(scene1);
    ui->ImageWithNoise->resize(400,400);
}

void MainWindow::on_AddGN_clicked()
{
    myimg.ImageToMatrix();
    myimg.GaussianNoise();
    QGraphicsScene *scene1 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.noiseImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene1->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithNoise->setScene(scene1);
    ui->ImageWithNoise->resize(400,400);
}

void MainWindow::on_FilterImage_clicked()
{
    myimg.BoxFilter(ui->deepBox->value());
    QGraphicsScene *scene2 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.filterImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene2->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithFilter->setScene(scene2);
    ui->ImageWithFilter->resize(400,400);
}

void MainWindow::on_FilterImage_Gaus_clicked()
{
    myimg.GaussianFilter();
    QGraphicsScene *scene2 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.noiseImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene2->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithFilter->setScene(scene2);
    ui->ImageWithFilter->resize(400,400);
}

void MainWindow::on_FilterImage_Median_clicked()
{
    myimg.MedianFilter(ui->deepBox->value());
    QGraphicsScene *scene2 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.filterImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene2->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithFilter->setScene(scene2);
    ui->ImageWithFilter->resize(400,400);
}

void MainWindow::on_FilterImage_Median_2_clicked()
{
    myimg.AddMedianFilter(ui->spinKernel->value(),ui->spinTimes->value());
    QGraphicsScene *scene2 = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(myimg.filterImage, Qt::AutoColor);
    QSize PicSize(350, 350);
    scene2->addPixmap(pix.scaled(PicSize,Qt::KeepAspectRatio));
    ui->ImageWithFilter->setScene(scene2);
    ui->ImageWithFilter->resize(400,400);
}
