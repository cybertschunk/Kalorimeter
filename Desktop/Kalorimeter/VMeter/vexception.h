#ifndef VEXCEPTION_H
#define VEXCEPTION_H

#include <QString>

#include <exception>

class VException : public std::exception
{
public:
    explicit VException() = default;
    explicit VException(QString& what): message(what) {}
    explicit VException(const char* what) : message(QString::fromUtf8(what)) {}
    explicit VException(std::string what) : message(QString::fromStdString((what))) {}
    QString getMessage() const;
    void setMessage(const QString &value);

private:
    QString message;
};

class SerialException : public VException
{
    using VException::VException;
};

class NoSerialInterfaceException : public SerialException
{
    using SerialException::SerialException;
};



#endif // VEXCEPTION_H
