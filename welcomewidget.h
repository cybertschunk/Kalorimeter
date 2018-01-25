#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QObject>
#include <QtWidgets>

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    WelcomeWidget(QWidget *parent= 0);
private:
    QLabel          *message;
    QVBoxLayout     *mainLayout;
    QHBoxLayout     *dialogLayout;
    QPushButton     *load,*connect;
signals:
    void openClicked();
    void connectClicked();
public slots:
    void openSlot();
    void connectSlot();
};

#endif // WELCOMEWIDGET_H
