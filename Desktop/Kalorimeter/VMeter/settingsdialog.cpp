#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "main.h"
#include "logger.h"

#include <QSerialPort>
#include <QSerialPortInfo>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    init();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::saveSettings()
{
    Logger::log << L_INFO << "Updating settings...\n";
    Main::settings->setValue("interface/serial",ui->serialInterfaceComboBox->currentText());
    Main::settings->setValue("interface/serial/baudrate",serialDescriptionToPortName(ui->bautRateComboBox->currentText()));

    Logger::log << L_INFO << "Saved following settings:\n";
    for(QString key : Main::settings->allKeys())
        Logger::log << L_INFO << key << " : " << Main::settings->value(key).toString() << "\n";
    this->accept();
}

void SettingsDialog::init()
{
    //Initialize boxes
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo port : ports)
        ui->serialInterfaceComboBox->addItem(port.description());

    //Set default values
    ui->serialInterfaceComboBox->setCurrentText(
                Main::settings->value("interface/serial",
                                      QSerialPortInfo::availablePorts().first().description()).toString());
    ui->bautRateComboBox->setCurrentText(Main::settings->value("interface/serial/baudrate/","9600").toString());

    //Connect
    QObject::connect(ui->okayButton,&QPushButton::pressed,this,&SettingsDialog::saveSettings);
    QObject::connect(ui->cancelButton,&QPushButton::pressed,this,&SettingsDialog::reject);

}


QString SettingsDialog::serialDescriptionToPortName(QString description)
{
    for(QSerialPortInfo pI : QSerialPortInfo::availablePorts())
        if(pI.description() == description)
            return pI.portName();
    return "";
}
