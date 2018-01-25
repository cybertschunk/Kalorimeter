#ifndef SERIAL_H
#define SERIAL_H

#include <QList>
#include <QSerialPortInfo>

class Serial
{
public:
    Serial() = default;
    static auto listAvailableDevices() -> QList<QSerialPortInfo>;
};

#endif // SERIAL_H
