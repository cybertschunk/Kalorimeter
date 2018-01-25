#ifndef ENTRY_H
#define ENTRY_H

#include <QDateTime>

#include <iostream>
#include <memory>

class Entry
{
private:
    std::shared_ptr<QDateTime> timestamp;
    double temp1;
    double temp2;
public:
    Entry(){}
    Entry(const QDateTime ts, const double t1, const double t2);
    Entry(const Entry& e);
    ~Entry();
    auto getTimestamp() const -> QDateTime;
    auto getTemp1() const -> double;
    auto getTemp2() const -> double;

    //Operatoren
    Entry& operator=(const Entry& e);
    friend bool operator==(const Entry& e1, const Entry& e2);
    friend bool operator <(const Entry& e1, const Entry& e2);
    friend std::ostream& operator<<(std::ostream& lop, const Entry& e1);
};

#endif // ENTRY_H
