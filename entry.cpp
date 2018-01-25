#include "entry.h"

Entry::Entry(const QDateTime ts, const double t1, const double t2) : timestamp(std::make_shared<QDateTime>(ts)), temp1(t1), temp2(t2){}

Entry::Entry(const Entry &e)
{
    timestamp = std::make_shared<QDateTime>(e.getTimestamp());
    temp1 = e.getTemp1();
    temp2 = e.getTemp2();
}

auto Entry::getTimestamp() const -> QDateTime
{
    return *timestamp;
}
auto Entry::getTemp1() const -> double
{
    return temp1;
}

auto Entry::getTemp2() const  -> double
{
    return temp2;
}

/**
 * Compares just the timestamp
 *
 * @brief operator ==
 * @param e1
 * @param e2
 * @return
 */

bool operator==(const Entry& e1, const Entry& e2)
{
    if(e1.getTimestamp() != e2.getTimestamp())
            return false;
    return true;
}

/**
 * Compares just the timestamp
 *
 * @brief operator <
 * @param e1
 * @param e2
 * @return
 */
bool operator<(const Entry& e1, const Entry& e2)
{
    if(e1.getTimestamp() < e2.getTimestamp())
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& lop, const Entry& e1)
{
    lop << e1.getTimestamp().toString().toStdString() << " : " << e1.getTemp1() << " " << e1.getTemp2();
    return lop;
}

Entry& Entry::operator=(const Entry& e)
{
   Entry tmp(e);
   std::swap(timestamp,tmp.timestamp);
   temp1 = e.temp1;
   temp2 = e.temp2;
   return *this;
}

Entry::~Entry(){}
