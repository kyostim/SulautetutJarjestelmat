#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "bgvideoprocessor.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_horizontalSliderHSVHueLower_valueChanged(int value);

    void on_horizontalSliderHSVSaturationLower_valueChanged(int value);

    void on_horizontalSliderHSVValueLower_valueChanged(int value);

    void on_horizontalSliderHSVHueUpper_valueChanged(int value);

    void on_horizontalSliderHSVSaturationUpper_valueChanged(int value);

    void on_horizontalSliderHSVValueUpper_valueChanged(int value);

    void on_checkBoxAutoCalibration_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int _timerId = -1;

    BGVideoProcessor *_bgVideoProcessor = nullptr;

};

#endif // MAINWINDOW_H
