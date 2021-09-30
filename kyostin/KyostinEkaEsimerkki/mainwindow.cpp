#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _centriaImageProcessor = new CentriaImageProcessor(this);
}

MainWindow::~MainWindow()
{
    if(_centriaImageProcessor != nullptr)
    {
        delete _centriaImageProcessor;
        _centriaImageProcessor = nullptr;
    }
    delete ui;
}


void MainWindow::on_pushButtonNappi_clicked()
{
    cv::Mat image=cv::imread("/home/centria/projects/KyostinEkaEsimerkki/kuva.jpg");
    cv::imshow("image",image);
}
