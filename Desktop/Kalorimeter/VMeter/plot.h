#ifndef PLOT_H
#define PLOT_H

#include "main.h"

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
#include <QSerialPortInfo>

#include <mutex>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class Plot : public QChart
{
    Q_OBJECT

public:
    Plot(QString port, Qt::WindowFlags flags = 0,QGraphicsItem* parent=Q_NULLPTR) :
        QChart(QChart::ChartTypeCartesian,parent,flags),
        m_series(0),
        m_step(0),
        m_x(5),
        m_y(1)
        {serialPort = new QSerialPort(port);}

    void init();
    ~Plot();

public slots:
    void handleTimeout();

private:


    QTimer intervalTimer;

    QSerialPort* serialPort;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axis;
    qreal m_step;
    qreal m_x;
    qreal m_y;
    long startTimestamp;
    long lastTimestamp;

};
extern std::mutex updateData;

#endif
