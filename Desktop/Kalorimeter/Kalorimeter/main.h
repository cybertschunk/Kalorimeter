#pragma once
#include "Logger.h"
#include "Kalorimeter.h"

#include <QSettings>
#include <QApplication>
#include <QCoreApplication>
#include <QVector>
#include <QErrorMessage>


class Logger;
class Kalorimeter;

namespace Main
{

	extern Kalorimeter* kalorimeter;
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