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

		Logger::log << L_INFO << "Program initialized.\n";

		return EXIT_SUCCESS;
	}

	int shutdown()
	{
		Logger::log << L_INFO << "Shutting down program.\n";
		return EXIT_SUCCESS;
	}

	void showGui()
	{
		kalorimeter->showMaximized();
	}

}
