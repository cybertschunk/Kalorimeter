#pragma once


#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCore/qtimer.h>
#include <QtSerialPort\qserialport.h>
#include <QtCore\qtimer.h>
#include <QtCharts\qchart.h>
#include <QSerialPort>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class Plot : public QChart
{
    Q_OBJECT

public:
    Plot(QSerialPort* port) : serialPort(port) { init(); }

public slots:
    void handleTimeout();

private:

    void init();

    QTimer intervalTimer;

    QSerialPort serialPort;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axis;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};

