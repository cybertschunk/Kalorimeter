#ifndef MAIN_H
#define MAIN_H
#include "logger.h"
#include "mainwindow.h"

#include <QSettings>
#include <QApplication>
#include <QCoreApplication>
#include <QVector>
#include <QErrorMessage>


class Logger;
class MainWindow;

namespace Main
{

    extern MainWindow* mainWindow;
    extern QSettings* settings;


    void run(QApplication &app);
    int init();
    int shutdown();
    void showGui();
    int initSettings();

    class KalorimeterApp : public QApplication
    {
    public:
        KalorimeterApp(int &argc, char ** arg) : QApplication(argc, arg) {}
    private:
        bool notify(QObject* receiver, QEvent* event) Q_DECL_OVERRIDE
        {
            try
            {
                return QApplication::notify(receiver, event);
            }
            catch (...)
            {
                QErrorMessage error;
                error.showMessage("Ein schwerer Fehler ist aufgetreten. Das Programm funktioniert evtl. nicht mehr richtig.");
            }

            return false;
        }
    };



}

#endif // MAIN_H
