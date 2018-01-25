#ifndef MAIN_H
#define MAIN_H

#include "database.h"

#include <QObject>
#include <QApplication>

class Main
{
public:
    Main();
    ~Main();

    auto getDB() -> Database&;
    auto run(QApplication &app) -> void;
private:
    Database db;
};

#endif // MAIN_H
