#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vexception.h"

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
    settingsDialog->setWindowModality(Qt::ApplicationModal);
    settingsDialog->exec();
}

void MainWindow::updateToSettings()
{
    QString serialPortDesc = Main::settings->value("interface/serial",
                                                   QSerialPortInfo::availablePorts().first().portName()).toString();

    plot = std::unique_ptr<Plot>(new Plot(serialPortDesc));
    try
    {
        //tries to connect to configured serial interface
        plot->init();
    }catch(SerialException se)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Zu dem seriellen Interface konnte keine Verbindung hergestellt werden! Bitte wählen Sie ein anderes.");
        msgBox->exec();
        showSettingsDialog();
        return updateToSettings();
    }
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
