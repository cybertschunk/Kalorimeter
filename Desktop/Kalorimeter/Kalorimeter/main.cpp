#include "Kalorimeter.h"
#include <QtWidgets/QApplication>
#include "main.h"


int main(int argc, char *argv[])
{
	Main::KalorimeterApp app(argc, argv);
	Main::run(app);
}

namespace Main {

	Kalorimeter* kalorimeter;
	QSettings* settings;

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

		kalorimeter = new Kalorimeter(Q_NULLPTR);

		initSettings();

		Logger::log << L_INFO << "Program initialized.\n";

		return EXIT_SUCCESS;
	}

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

		delete settings;

		return EXIT_SUCCESS;
	}

	void showGui()
	{
		kalorimeter->showMaximized();
	}

	int initSettings()
	{
		settings = new QSettings("Evangelische_Schule_Neuruppin", "Kalorimeter");
		settings->setIniCodec("UTF-8");
		Logger::log << L_INFO << "reading config file from " << Main::settings->fileName() << "\n";
		settings->sync();
		Logger::log << L_INFO << "Settings initialized!\n";
		return EXIT_SUCCESS;
	}

}
