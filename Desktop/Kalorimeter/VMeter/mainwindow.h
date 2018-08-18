#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "plot.h"
#include "settingsdialog.h"
#include "main.h"


class Plot;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void showSettingsDialog();
    void updateToSettings();
private:

    void init();
    void buildConnects();

    Ui::MainWindow *ui;
    SettingsDialog* settingsDialog;
    std::unique_ptr<Plot> plot;

};

#endif // MAINWINDOW_H
