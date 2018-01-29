#pragma once

#include <QtCharts\qchart.h>
#include <QtSerialPort\qserialport.h>
#include <QtCore\qtimer.h>

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
	virtual ~Plot();

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

