#ifndef RECORD_H
#define RECORD_H

#include "entry.h"

#include <vector>


class Record
{
private:
    QString name;
    std::vector<Entry> entries;
public:
     static int ID;

    /**
     * @brief Record
     * @param n
     * @param e (muss bereits aufsteigend sortiert sein)
     */
    Record(QString& n, std::vector<Entry>& e) : name(n), entries(e) {++ID;}
    Record() = default;

    auto getLowestEntry() -> Entry&;
    auto getHighestEntry() -> Entry&;
    auto getEntryAt(int) -> Entry&;
    auto getName() const -> QString;
    auto getSize() const -> int;
    auto setEntries(std::vector<Entry> e) -> void;
    auto setName(QString& n) -> void;
    auto getHighestTemp() -> double;
    auto getLowestTemp() -> double;
    auto getEntries() -> std::vector<Entry>&;

    auto writeToXML(QString path) -> bool;
    static auto ReadFromXML(QString path) -> Record;

};


#endif // RECORD_H
