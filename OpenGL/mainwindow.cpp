#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Eye_x_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Eye_X(double)));
    connect(ui->Eye_y_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Eye_Y(double)));
    connect(ui->Eye_z_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Eye_Z(double)));

    connect(ui->La_x_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Lo_X(double)));
    connect(ui->La_y_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Lo_Y(double)));
    connect(ui->La_z_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Lo_Z(double)));

    connect(ui->Av_x_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Av_X(double)));
    connect(ui->Av_y_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Av_Y(double)));
    connect(ui->Av_z_2,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(Av_Z(double)));

    connect(ui->FechoAnimado,SIGNAL(pressed()), ui->GLwidget, SLOT(FechoAnimado()));
    connect(ui->Fecho,SIGNAL(pressed()), ui->GLwidget, SLOT(Fecho()));
    connect(ui->Imp, SIGNAL(pressed()), ui->GLwidget, SLOT(Importar()));
    connect(ui->Exp, SIGNAL(pressed()), ui->GLwidget, SLOT(Exportar()));
    connect(ui->panoramica, SIGNAL(pressed()), ui->GLwidget, SLOT(Video()));

    connect(ui->Vel, SIGNAL(valueChanged(int)), ui->GLwidget, SLOT(attVelocidade(int)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), ui->GLwidget, SLOT(attFile(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;



}





