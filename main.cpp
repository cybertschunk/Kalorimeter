#include "main.h"
#include "mainwindow.h"
#include "record.h"
#include "serial.h"

#include <QApplication>
#include <QtWidgets>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::cout << "Starting...\n";
    try
    {
    Main main;
    main.run(app);
    } catch(...)
    {
        std::cerr << "A fatal error has occured!\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

auto Main::run(QApplication& app) -> void
{
    Record::ID = 0;
    MainWindow *mainWindow = new MainWindow(this);
    Serial serial;
    QList<QSerialPortInfo> data = Serial::listAvailableDevices();
    for(int i = 0; i< data.size(); ++i)
        std::cout << data.at(i).portName().toStdString() << std::endl;
    mainWindow->showMaximized();
    app.exec();
}

Main::Main()
{
    db = Database("first");
}

Main::~Main()
{
}

auto Main::getDB() -> Database&
{
    return db;
}
