#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QErrorMessage>
#include <QSerialPortInfo>
#include <QChartView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete settingsDialog;
    delete plot;
    delete ui;
}

void MainWindow::showSettingsDialog()
{
    settingsDialog->showNormal();
}

void MainWindow::updateToSettings()
{
    QString serialPortDesc = Main::settings->value("interface/serial",
                                               QSerialPortInfo::availablePorts().first().portName()).toString();
    plot = new Plot(serialPortDesc);
    plot->setAnimationOptions(QChart::AllAnimations);
    plot->setTitle("Kalorimeter");

    QChartView* chartView = new QChartView();
    chartView->setChart(plot);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    chartView->repaint();
    this->setCentralWidget(chartView);
}

void MainWindow::init()
{
    settingsDialog = new SettingsDialog(this);

    updateToSettings();

    buildConnects();
}

void MainWindow::buildConnects()
{
    //Menu
    QObject::connect(ui->actionBeenden,&QAction::triggered,this,&MainWindow::close);
    QObject::connect(ui->actionEinstellungen,&QAction::triggered,this,&MainWindow::showSettingsDialog);
    QObject::connect(settingsDialog,&SettingsDialog::settingsChanged,this,&MainWindow::updateToSettings);
}
