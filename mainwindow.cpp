#include "mainwindow.h"
#include "ui_mainwindow.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customModel = new TreeCustomModel;
    ui->treeView->setModel(customModel);
    ui->treeView->show();
    connect(ui->btn_AddThing, &QPushButton::clicked, this, &MainWindow::AddItem );
}


void MainWindow::AddItem(){
    #ifdef QT_DEBUG
    qDebug() << "you just clicked the add button";
    #endif

    customModel->insertRow(0);
    ui->treeView->show();
}

MainWindow::~MainWindow()
{
    delete customModel;
    delete ui;

}
