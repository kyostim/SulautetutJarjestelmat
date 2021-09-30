#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "centriaimageprocessor.h"

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
    void on_pushButtonNappi_clicked();

private:
    Ui::MainWindow *ui;

    CentriaImageProcessor* _centriaImageProcessor = nullptr;
};
#endif // MAINWINDOW_H
