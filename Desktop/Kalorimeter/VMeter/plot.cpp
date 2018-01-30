#include "plot.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCore/qtimer.h>
#include <QErrorMessage>

Plot::~Plot()
{
    try
    {
        serialPort->close();
    }catch(...)
    {
        QErrorMessage error;
        error.showMessage("Failed to close serial interface!");
        Logger::log << L_ERROR << "Failed to close serial interface!\n";
    }

    intervalTimer.stop();
}

void Plot::handleTimeout()
{
    Logger::log << L_DEBUG << "Open: " << serialPort->isOpen() << " Readable: " << serialPort->isReadable() << "\n";
    if(! (serialPort->isOpen() && serialPort->isReadable()))
        return;

    int bytes_available = serialPort->bytesAvailable();
    if (bytes_available >= 4)
    {
        QByteArray byte_array = serialPort->read(bytes_available);
        QString data = QString::fromUtf8(byte_array);
        QStringList temps = data.split("\n");
        double temp = temps.last().toDouble();
        Logger::log << L_DEBUG << "Read value " << temp << "\n";

        qreal x = plotArea().width() / m_axis->tickCount();
        qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
        m_x += y;
        m_y = temp;
        m_series->append(m_x, m_y);
        scroll(x, 0);
    }

}

void Plot::init()
{
    QObject::connect(&intervalTimer, &QTimer::timeout, this, &Plot::handleTimeout);
    intervalTimer.setInterval(1000);

    //Initializing serial interface
    try
    {

        if(!serialPort->open(QIODevice::ReadWrite))
        {
            Logger::log << L_ERROR << "Failed to open serial interface " << serialPort->portName() << " with error"
                        <<  serialPort->errorString() << "\n";
            Logger::log << L_INFO << "Available serial interfaces: \n";
            for(QSerialPortInfo pI : QSerialPortInfo::availablePorts())
               Logger::log << L_INFO << pI.portName() << " " << pI.description() << "\n";

        }
        serialPort->setBaudRate(Main::settings->value("interface/serial/baudrate","9600").toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);


        Logger::log << L_INFO << "Initialized serial interface " << serialPort->portName() << " with baudrate " << serialPort->baudRate() << "\n";
    }catch(...)
    {
        QErrorMessage error;
        error.showMessage("Failed to open serial interface!");
                       Logger::log << L_ERROR << "Failed to open serial interface!\n";
    }

    m_series = new QSplineSeries(this);
    m_axis = new QValueAxis(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(5);
    axisX()->setRange(0, 10);
    axisY()->setRange(-5, 100);


    intervalTimer.start();
}
