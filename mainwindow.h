#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagefiltering.h"
#include <QString.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ImageFiltering myimg;

private slots:
    void on_buttonAddNoise_clicked();

    void on_AddSaP_clicked();

    void on_AddGN_clicked();

    void on_FilterImage_clicked();

    void on_FilterImage_Gaus_clicked();

    void on_FilterImage_Median_clicked();

    void on_FilterImage_Median_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
