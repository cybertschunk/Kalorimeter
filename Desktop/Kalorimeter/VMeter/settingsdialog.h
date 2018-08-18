#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

public slots:
    void saveSettings();

signals:
    void settingsChanged();

private:
    Ui::SettingsDialog *ui;
    void init();
    QString serialDescriptionToPortName(QString description);
    bool detectUserChange();
};

#endif // SETTINGSDIALOG_H
