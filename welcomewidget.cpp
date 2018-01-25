#include "welcomewidget.h"

#include <QHBoxLayout>

#include <iostream>


WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent)
{
    message = new QLabel();
    message->setText("Laden Sie ein Projekt oder verbinden Sie sich mit dem Kalorimeter.");
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(message);

    connect = new QPushButton(this);
    QObject::connect(connect,SIGNAL( clicked() ), this, SLOT(connectSlot() ) );
    connect->setText("Verbinden!");
    load = new QPushButton("Laden....",this);
    QObject::connect(load,SIGNAL( clicked() ), this, SLOT( openSlot() ) );

    dialogLayout = new QHBoxLayout();
    dialogLayout->setAlignment(Qt::AlignCenter);
    dialogLayout->addWidget(load);
    dialogLayout->addWidget(connect);
    mainLayout->addLayout(dialogLayout);
}

void WelcomeWidget::connectSlot()
{
    emit connectClicked();
}

void WelcomeWidget::openSlot()
{
    emit openClicked();
}

//void WelcomeWidget::connectClicked()
//{
//    std::cout << "connects to database...";
//}

//void WelcomeWidget::openClicked()
//{
//    std::cout << "Loads file...";
//}

