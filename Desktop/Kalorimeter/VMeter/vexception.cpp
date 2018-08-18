#include "vexception.h"

QString VException::getMessage() const
{
    return message;
}

void VException::setMessage(const QString &value)
{
    message = value;
}
