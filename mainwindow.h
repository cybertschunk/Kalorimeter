#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "welcomewidget.h"

#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(Main* m,QWidget *parent = 0);

private:

    //Programmelemente
    Main* main;

    //GUI-Elemente
    QLabel          *welcomeMessage;
    QPushButton     *cancelButton;
    QPushButton     *continueButton;
    QGridLayout     *mainLayout;
    QTabWidget      *layoutTabs;
    WelcomeWidget   *welWidget;

public slots:
    void connectSlot();
    void openSlot();

};

#endif // MAINWINDOW_H
