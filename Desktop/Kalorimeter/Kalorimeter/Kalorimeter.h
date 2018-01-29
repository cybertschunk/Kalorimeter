#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Kalorimeter.h"

class Kalorimeter : public QMainWindow
{
	Q_OBJECT

public:
	Kalorimeter(QWidget *parent = Q_NULLPTR);

private:
	Ui::KalorimeterClass ui;
};
