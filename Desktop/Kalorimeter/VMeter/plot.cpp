#include "plot.h"

#include "vexception.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCore/qtimer.h>
#include <QErrorMessage>
#include <QDateTime>

#include <mutex>


//global variables
std::mutex updateData;

//functions
Plot::~Plot()
{
    try
    {
        Logger::log << L_INFO << "closing serial interface...\n";
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
    std::lock_guard<std::mutex> guard(updateData);
    try
    {
        Logger::log << L_DEBUG << "Open: " << serialPort->isOpen() << " Readable: " << serialPort->isReadable() << "\n";
        if(! (serialPort->isOpen() && serialPort->isReadable()))
            return;

        int bytes_available = serialPort->bytesAvailable();
        if (bytes_available >= 4)
        {
            QByteArray byte_array = serialPort->read(bytes_available);
            QString data = QString::fromUtf8(byte_array);
            Logger::log << L_DEBUG << "read: " << data << "\n";

            QStringList temps = data.split("\n");
            QString last = temps.at(temps.size()-2).trimmed();
            double temp = last.toDouble();
            Logger::log << L_DEBUG << "Read value " << temp << "\n";

            long timeNow = QDateTime::currentSecsSinceEpoch();
            long timeSinceStart = timeNow - startTimestamp;
            long timestampDiff = timeNow - lastTimestamp;
            lastTimestamp = timeNow;

            m_x = timeSinceStart;
            m_y = temp;
            m_series->append(m_x, m_y);
            double scrollStart = 100 * ((m_axis->tickCount()-1.0)/m_axis->tickCount());
            if(m_step >= scrollStart)
                scroll((plotArea().width()*(timestampDiff/100.0)), 0);
            else
                m_step+=timestampDiff;
            Logger::log << L_DEBUG << m_step << " " << scrollStart << "\n";
        }
    } catch(...)
    {
        Logger::log << L_ERROR << "fatal error in plotting engine occured!\n";
    }


}

void Plot::init()
{
    QObject::connect(&intervalTimer, &QTimer::timeout, this, &Plot::handleTimeout);
    intervalTimer.setInterval(1000);

    startTimestamp = lastTimestamp = QDateTime::currentSecsSinceEpoch();

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
            throw SerialException("could not connect to serial interface");
        }
        serialPort->setBaudRate(Main::settings->value("interface/serial/baudrate","9600").toInt());
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);


        Logger::log << L_INFO << "Initialized serial interface " << serialPort->portName() << " with baudrate " << serialPort->baudRate() << "\n";
    }catch(...)
    {
        Logger::log << L_ERROR << "Failed to open serial interface!\n";
        throw SerialException("failed to establish connection to serial interface");
    }

    m_axis = new QValueAxis();
    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(5);
    axisX()->setRange(0, 100);
    axisY()->setRange(-5, 100);


    intervalTimer.start();
}
