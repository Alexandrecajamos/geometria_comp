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


    connect(ui->NX,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(New_X(double)));
    connect(ui->NY,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(New_Y(double)));
    connect(ui->NZ,SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(New_Z(double)));
    connect(ui->Part, SIGNAL(valueChanged(int)), ui->GLwidget, SLOT(Part_Ref(int)));
    connect(ui->add, SIGNAL(pressed()), ui->GLwidget, SLOT(Add()));

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

//    connect(ui->Inf, SIGNAL())
    ui->GLwidget->I = ui->Inf;

}

MainWindow::~MainWindow()
{
    delete ui;



}






//void MainWindow::on_Inf_linkActivated(QString &link)
//{
//    QString T = QString::fromStdString(ui->GLwidget->Info);
//    link = T;

//    //link = "teste"; //QString::fromStdString(ui->GLwidget->Info);
//}


