#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "main.h"
#include "logger.h"
#include "vexception.h"

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

bool SettingsDialog::detectUserChange()
{
    if(Main::settings->value("interface/serial").toString() == serialDescriptionToPortName(ui->serialInterfaceComboBox->currentText()))
        if(Main::settings->value("interface/serial/baudrate").toString() == ui->bautRateComboBox->currentText())
            return false;
    return true;
}

void SettingsDialog::saveSettings()
{
    //cancel if no changes have been made
    if(!detectUserChange())
    {
        this->reject();
        return;
    }

    Logger::log << L_INFO << "Updating settings...\n";
    Main::settings->setValue("interface/serial",serialDescriptionToPortName(ui->serialInterfaceComboBox->currentText()));
    Main::settings->setValue("interface/serial/baudrate",ui->bautRateComboBox->currentText());

    Logger::log << L_INFO << "Saved following settings:\n";
    for(QString key : Main::settings->allKeys())
        Logger::log << L_INFO << key << " : " << Main::settings->value(key).toString() << "\n";
    this->accept();

    emit settingsChanged();
}

void SettingsDialog::init()
{
    //check if any serial interfaces are available
    if(QSerialPortInfo::availablePorts().isEmpty())
        throw NoSerialInterfaceException("No serial interface has been found!");

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
