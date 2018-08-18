#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "main.h"


int main(int argc, char *argv[])
{
    Main::KalorimeterApp app(argc, argv);
    Main::run(app);

    return EXIT_SUCCESS;
}

namespace Main {

    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<QSettings> settings;

    //Methods
    void run(QApplication & app)
    {
        try
        {
            //Initialization
            init();

            //Guis anzeigen
            showGui();

            //ausführen
            app.exec();
        }
        catch (...)
        {
            QErrorMessage error;
            error.showMessage("Ein schwerer Fehler ist aufgetreten. Das Programm funktioniert evtl. nicht mehr richtig.");
        }

        shutdown();
    }

    int init()
    {
        //Initializing logger
        Logger::log.init(Logger::All);
        initSettings();

        mainWindow= std::unique_ptr<MainWindow>(new MainWindow(Q_NULLPTR));

        Logger::log << L_INFO << "Program initialized.\n";

        return EXIT_SUCCESS;
    }

    /**
     * cleans up and shuts down the program
     *
     * @brief shutdown
     * @return
     */
    int shutdown()
    {
        Logger::log << L_INFO << "Shutting down program.\n";

        Main::settings->sync();
        if (Main::settings->status() != 0) {
            Logger::log << L_ERROR << "failed to write the settings to" << Main::settings->fileName().toStdString() << "\n";
            return EXIT_FAILURE;
        }
        else
            Logger::log << L_INFO << "wrote the settings to" << Main::settings->fileName().toStdString() << "\n";

        return EXIT_SUCCESS;
    }

    void showGui()
    {
        mainWindow->showMaximized();
    }

    int initSettings()
    {
        settings = std::unique_ptr<QSettings>(new QSettings("Evangelische_Schule_Neuruppin", "Kalorimeter"));
        settings->setIniCodec("UTF-8");
        Logger::log << L_INFO << "reading config file from " << Main::settings->fileName() << "\n";
        settings->sync();
        Logger::log << L_INFO << "Settings initialized!\n";

        Logger::log << L_INFO << "Read following settings:\n";
        for(QString key : Main::settings->allKeys())
            Logger::log << L_INFO << key << " : " << Main::settings->value(key).toString() << "\n";

        return EXIT_SUCCESS;
    }

}
