//Projektheader
#include "mainwindow.h"
#include "datawidget.h"

//Std-Header
#include <iostream>
#include <vector>

//QT-Header
#include <QTabWidget>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(Main* m, QWidget *parent) : QWidget(parent)
{
    main = m;
    mainLayout = new QGridLayout(this);
    layoutTabs = new QTabWidget();
    mainLayout->addWidget(layoutTabs);
    welWidget = new WelcomeWidget();
    layoutTabs->addTab(welWidget,"Willkommen");
    QObject::connect(welWidget,SIGNAL(connectClicked() ),this, SLOT(connectSlot()) );
    QObject::connect(welWidget,SIGNAL(openClicked()), this, SLOT(openSlot())  );
}



void MainWindow::openSlot()
{
    QFileDialog *openDialog = new QFileDialog(this);
    openDialog->setFileMode(QFileDialog::ExistingFile);
    QString path = openDialog->getOpenFileName(this, tr("Öffne Datei"), QDir::homePath());
    DataWidget *dataW = new DataWidget(this,DataWidget::FILE_MODE,main,path);
    layoutTabs->addTab(dataW,dataW->getName());
}

void MainWindow::connectSlot()
{
    DataWidget *dataW = new DataWidget(this, DataWidget::DB_MODE,main,"");
    layoutTabs->addTab(dataW,dataW->getName());
}

/**
 *
 * welcomeMessage = new QLabel("Dies ist ein Test!");
    continueButton = new QPushButton("Weiter");
    cancelButton = new QPushButton("Abbrechen");
    layout = new QVBoxLayout(this);
    layout->addWidget(welcomeMessage);
    layout->addWidget(cancelButton);
    layout->addWidget(continueButton);

    connect(continueButton,SIGNAL( clicked() ), this, SLOT( continueNow() ) );
    connect(cancelButton,SIGNAL(clicked() ), qApp, SLOT( quit() ));
 */
