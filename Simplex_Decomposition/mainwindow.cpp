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

    connect(ui->Faces, SIGNAL(clicked(bool)), ui->GLwidget, SLOT(attArestas(bool)));


    connect(ui->Imp, SIGNAL(pressed()), ui->GLwidget, SLOT(Importar()));
    connect(ui->Exp, SIGNAL(pressed()), ui->GLwidget, SLOT(Exportar()));
    connect(ui->panoramica, SIGNAL(pressed()), ui->GLwidget, SLOT(Video()));
    connect(ui->f, SIGNAL(pressed()), ui->GLwidget, SLOT(F()));
    connect(ui->t, SIGNAL(pressed()), ui->GLwidget, SLOT(T()));


    connect(ui->Vel, SIGNAL(valueChanged(int)), ui->GLwidget, SLOT(attVelocidade(int)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), ui->GLwidget, SLOT(attFile(QString)));
    connect(ui->pasta, SIGNAL(textChanged(QString)), ui->GLwidget, SLOT(attPath(QString)));


    connect(ui->advFront, SIGNAL(pressed()), ui->GLwidget, SLOT(GetSimplex()));
    connect(ui->A, SIGNAL(pressed()), ui->GLwidget, SLOT(ASimplex()));
    connect(ui->P, SIGNAL(pressed()), ui->GLwidget, SLOT(PSimplex()));

    connect(ui->fator, SIGNAL(valueChanged(double)), ui->GLwidget, SLOT(attFator(double)));
    connect(ui->eixo, SIGNAL(valueChanged(int)),ui->GLwidget, SLOT(attEixo(int)));
    connect(ui->Expandir, SIGNAL(pressed()), ui->GLwidget,SLOT(Expandir()));
    connect(ui->busca, SIGNAL(clicked(bool)), ui->GLwidget,SLOT(EBusca(bool)));

    ui->GLwidget->I = ui->Inf;

}

MainWindow::~MainWindow()
{
    delete ui;


}
