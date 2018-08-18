#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QErrorMessage>
#include <QSerialPortInfo>
#include <QChartView>
#include <QMessageBox>

#include <memory>

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
    delete ui;
}

void MainWindow::showSettingsDialog()
{
    settingsDialog->showNormal();
}

void MainWindow::updateToSettings()
{
    //check if any serial interfaces are available
    if(QSerialPortInfo::availablePorts().isEmpty())
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Es wurde kein serielles Interface gefunden. Bitte schließen Sie den Arduino an!");
        msgBox->exec();
        return updateToSettings();
    }

    QString serialPortDesc = Main::settings->value("interface/serial",
                                                   QSerialPortInfo::availablePorts().first().portName()).toString();
    plot = std::unique_ptr<Plot>(new Plot(serialPortDesc));

    plot->setAnimationOptions(QChart::AllAnimations);
    plot->setTitle("Kalorimeter");

    QChartView* chartView = new QChartView(this);
    chartView->setChart(plot.get());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    chartView->repaint();
    this->setCentralWidget(chartView);
}

void MainWindow::init()
{
    updateToSettings();
    settingsDialog = new SettingsDialog(this);
    buildConnects();
}

void MainWindow::buildConnects()
{
    //Menu
    QObject::connect(ui->actionBeenden,&QAction::triggered,this,&MainWindow::close);
    QObject::connect(ui->actionEinstellungen,&QAction::triggered,this,&MainWindow::showSettingsDialog);
    QObject::connect(settingsDialog,&SettingsDialog::settingsChanged,this,&MainWindow::updateToSettings);
}
