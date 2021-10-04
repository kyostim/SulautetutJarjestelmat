#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _bgVideoProcessor = new BGVideoProcessor(this);

    _timerId = startTimer(200);
}

MainWindow::~MainWindow()
{
    if(_timerId >= 0)
    {
        killTimer(_timerId);
        _timerId = -1;
    }
    if(_bgVideoProcessor != nullptr)
    {
        delete _bgVideoProcessor;
        _bgVideoProcessor = nullptr;
    }
    delete ui;

}


void MainWindow::timerEvent(QTimerEvent *event)
{
    if(_bgVideoProcessor != nullptr)
    {
        ui->labelHSVHueLowerValue->setText(QString::number(_bgVideoProcessor->LowerHue));
        ui->labelHSVSaturationLowerValue->setText(QString::number(_bgVideoProcessor->LowerSaturation));
        ui->labelHSVValueLowerValue->setText(QString::number(_bgVideoProcessor->LowerValue));
        ui->horizontalSliderHSVHueLower->setValue(_bgVideoProcessor->LowerHue);
        ui->horizontalSliderHSVSaturationLower->setValue(_bgVideoProcessor->LowerSaturation);
        ui->horizontalSliderHSVValueLower->setValue(_bgVideoProcessor->LowerValue);


        ui->labelHSVHueUpperValue->setText(QString::number(_bgVideoProcessor->UpperHue));
        ui->labelHSVSaturationUpperValue->setText(QString::number(_bgVideoProcessor->UpperSaturation));
        ui->labelHSVValueUpperValue->setText(QString::number(_bgVideoProcessor->UpperValue));
        ui->horizontalSliderHSVHueUpper->setValue(_bgVideoProcessor->UpperHue);
        ui->horizontalSliderHSVSaturationUpper->setValue(_bgVideoProcessor->UpperSaturation);
        ui->horizontalSliderHSVValueUpper->setValue(_bgVideoProcessor->UpperValue);

        ui->checkBoxAutoCalibration->setChecked(_bgVideoProcessor->AutoCalibration);
    }
}

void MainWindow::on_pushButtonStart_clicked()
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->Start();
    }
}

void MainWindow::on_pushButtonStop_clicked()
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->Stop();
    }
}

void MainWindow::on_horizontalSliderHSVHueLower_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->LowerHue = (uchar)value;
    }
}

void MainWindow::on_horizontalSliderHSVSaturationLower_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->LowerSaturation = (uchar)value;
    }
}

void MainWindow::on_horizontalSliderHSVValueLower_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->LowerValue = (uchar)value;
    }
}

void MainWindow::on_horizontalSliderHSVHueUpper_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->UpperHue = (uchar)value;
    }
}

void MainWindow::on_horizontalSliderHSVSaturationUpper_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->UpperSaturation = (uchar)value;
    }
}

void MainWindow::on_horizontalSliderHSVValueUpper_valueChanged(int value)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->UpperValue = (uchar)value;
    }
}

void MainWindow::on_checkBoxAutoCalibration_stateChanged(int arg1)
{
    if(_bgVideoProcessor != nullptr)
    {
        _bgVideoProcessor->AutoCalibration = ui->checkBoxAutoCalibration->isChecked();
    }
}
