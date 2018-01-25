#include "serial.h"

#include <QSerialPortInfo>

auto Serial::listAvailableDevices() -> QList<QSerialPortInfo>
{
    QSerialPortInfo portInfo;
    return portInfo.availablePorts();
}
