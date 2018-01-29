#include "Plot.h"

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QtCore/qtimer.h>

void Plot::handleTimeout()
{
	int bytes_available = serialPort.bytesAvailable();
	if (bytes_available >= 4)
	{
		QByteArray byte_array = serialPort.read(bytes_available);
		QString data = QString::fromUtf8(byte_array);
		QStringList temps = data.split("\n");
		double temp = temps.last().toDouble();

		qreal x = plotArea().width() / m_axis->tickCount();
		qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
		m_x += y;
		m_y = temp;
		m_series->append(m_x, m_y);
		scroll(x, 0);
	}

}

Plot::~Plot()
{
	
}

void Plot::init()
{
	QObject::connect(&intervalTimer, &QTimer::timeout, this, &Plot::handleTimeout);
	intervalTimer.setInterval(1000);

	m_series = new QSplineSeries(this);
	QPen green(Qt::red);
	green.setWidth(3);
	m_series->setPen(green);
	m_series->append(m_x, m_y);

	addSeries(m_series);
	createDefaultAxes();
	setAxisX(m_axis, m_series);
	m_axis->setTickCount(5);
	axisX()->setRange(0, 10);
	axisY()->setRange(-5, 10);

	intervalTimer.start();
}
