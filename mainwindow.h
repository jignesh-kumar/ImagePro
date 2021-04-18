#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QFileDialog>
#include "qdebug.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_LoadImage_clicked();
    void mouseMoveEvent(QMouseEvent *event);
    void point_of_image(QPoint);

signals:
    void cordinatesUpdate(QPoint);

private:
    Ui::MainWindow *ui;
    cv::Mat image; // the image variable
};
#endif // MAINWINDOW_H
