#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(cordinatesUpdate(QPoint)), this, SLOT(point_of_image(QPoint)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_LoadImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), ".",
                                                    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    image= cv::imread(fileName.toLatin1().data());

    // change color channel ordering
    cv::cvtColor(image,image,CV_BGR2RGB);

    // Qt image
    QImage img= QImage((const unsigned char*)(image.data), image.cols,image.rows, image.step ,QImage::Format_RGB888);

    ui->LB_Image->setPixmap(QPixmap::fromImage(img));
    ui->LB_Image->resize(img.size());
}

void MainWindow::point_of_image(QPoint point)
{
    qDebug() << "cordinatesUpdate";

    qDebug() <<point << ", " << ui->LB_Image->x() << ", " << ui->LB_Image->y();
    int x = point.x() - ui->LB_Image->x();
    int y = point.y() - ui->LB_Image->y();

    qDebug() << "X:" << x  << ", Y:" << y ;

    if(x >= 0 && y >= 0 )
    {
        cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);
        int blue = intensity.val[0];
        int green = intensity.val[1];
        int red = intensity.val[2];

        qDebug() << "blue: " << blue << ", green:" << green << ", red:" << red;

        qDebug() << "=" << (int)blue;

        QString strBlue = QString::number(blue);
        QString strGreen = QString::number(green);
        QString strRed = QString::number(red);

        ui->LB_Blue->setText("Blue : "+strBlue);
        ui->LB_Green->setText("Green : "+strGreen);
        ui->LB_Red->setText("Red : "+strRed);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    emit cordinatesUpdate(event->pos());
}
