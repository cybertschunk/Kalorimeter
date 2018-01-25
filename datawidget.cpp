#include "datawidget.h"

#include <QPen>
#include <QPointF>
#include <QLineF>
#include <QRectF>
#include <QColor>
#include <QString>
#include <QGraphicsTextItem>
#include <QFontMetrics>

DataWidget::DataWidget(QWidget *parent, int m, Main *ma, QString p) : QWidget(parent), mode(m), path(p), main(ma)
{
    initRc();
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
    view->setRenderHints( QPainter::Antialiasing );
    mainLayout->addWidget(view);
    setLayout(mainLayout);
    updateBorders();
    paintData();
}

auto DataWidget::initRc() -> void
{
    if(mode == DB_MODE)
    {
        std::cout << "Reading entries from db.\n";
        rc.setEntries(main->getDB().readEntries());
        QString name = "Record";
        rc.setName(name);
    }

    if(mode == FILE_MODE)
    {
        std::cout << "Reading entries from file.\n";
        rc = Record::ReadFromXML(path);

    }

    startTime = rc.getLowestEntry().getTimestamp();
    endTime = rc.getHighestEntry().getTimestamp();
    minTemp = rc.getLowestTemp();
    maxTemp = rc.getHighestTemp();
}


auto DataWidget::paintData() -> void
{
    //Initialisieren
    QPen borderPen = QPen(Qt::CustomDashLine);
    borderPen.setWidth(2);
    borderPen.setColor(Qt::GlobalColor::black);
    QPen temp1Pen = QPen();
    temp1Pen.setWidth(1);
    temp1Pen.setColor(Qt::GlobalColor::red);
    QPen temp2Pen = QPen();
    temp2Pen.setColor(Qt::GlobalColor::yellow);
    temp2Pen.setWidth(1);
    QPen absPen = QPen(Qt::DashLine);
    absPen.setWidth(0);


    //Vorbereiten
    updateBorders();
    scaleData();
    scene->clear();

    //Der Rahmen.
    QLineF r1Line = QLineF(startx,starty,startx,endy);
    scene->addLine(r1Line,borderPen);
    QLineF r2Line = QLineF(startx,endy,endx,endy);
    scene->addLine(r2Line,borderPen);
    QLineF r3Line = QLineF(endx,endy,endx,starty);
    scene->addLine(r3Line,borderPen);
    //scene->addRect(borderRect,borderPen);

    //Die Messwerte
    for(int i = 0; i < rc.getSize()-1; ++i)
    {
        QPointF t1tmp1 = scaleEntryTemp1(rc.getEntryAt(i));
        QPointF t1tmp2 = scaleEntryTemp1(rc.getEntryAt(i+1));
        QPointF t2tmp1 = scaleEntryTemp2(rc.getEntryAt(i));
        QPointF t2tmp2 = scaleEntryTemp2(rc.getEntryAt(i+1));

        QLineF t1Line = QLineF(t1tmp1,t1tmp2);
        QLineF t2Line = QLineF(t2tmp1,t2tmp2);

        scene->addLine(t1Line,temp1Pen);
        scene->addLine(t2Line,temp2Pen);
    }

    //Die Achseneinteilung
    int xAbs = 10;
    int yAbs = 5;
    int xPixAbs = (endx-startx) / (xAbs-1);
    int yPixAbs = (endy-starty) / (yAbs-1);
    double mins = startTime.secsTo(endTime) / 60.0;
    double temp = maxTemp - minTemp;
    int i = 0;
    for(int x = startx; x <= endx; x+= xPixAbs)
    {
        QString text;
        text = text.setNum(mins*i,'f',2) + " min";
        QLineF tL = QLineF(x,starty,x,endy);
        scene->addLine(tL,absPen);
        QGraphicsTextItem *ti = scene->addText(text);
        ti->setPos(x,endy*1.01);
        ++i;
    }

    int g = 0;
    for(int y = endy; y >= starty; y-= yPixAbs)
    {
        QString text;
        QFontMetrics fm = QFontMetrics(scene->font());
        text = text.setNum(temp*g,'f',2) + " °C";
        QGraphicsTextItem* ti = scene->addText(text);
        int width = fm.size(Qt::TextSingleLine,text).width();
        ti->setPos(startx*0.90-width,y);
        ++g;
        QLineF tL = QLineF(startx,y,endx,y);
        scene->addLine(tL,absPen);
    }

}

auto DataWidget::scaleEntryTemp1(Entry e) -> QPointF
{
    double x = (startTime.msecsTo(e.getTimestamp()) * pixPerMilli) +startx;
    double y = endy - ((e.getTemp1() - minTemp) * pixPerDeg) ;
    std::cout << "Scaled to " << x << " " << y << " width: " << width << " heigtht: " << height << std::endl;
    return QPointF(x,y);
}

auto DataWidget::scaleEntryTemp2(Entry e) -> QPointF
{
    double x = (startTime.msecsTo(e.getTimestamp()) * pixPerMilli) + startx;
    double y = endy - ((e.getTemp2() - minTemp) * pixPerDeg) ;
    //std::cout << "Scaled 2 to " << x << " " << y << std::endl;
    return QPointF(x,y);
}

auto DataWidget::scaleData() -> void
{
    ydistance = 50; //Muss noch dynamische bestimmt werden.
    xdistance = 100;
    startx = xdistance;
    starty = ydistance;
    endx = width - xdistance;
    endy = height - ydistance;
    long millis = startTime.msecsTo(endTime);
    pixPerMilli = ((endx - startx) * 1.0) / (millis);
    pixPerDeg   = ((endy - starty) * 1.0) / (maxTemp - minTemp);

}

auto DataWidget::updateBorders() -> void
{
    width = view->width();
    height = view->height();
}

auto DataWidget::getName() -> QString
{
    return rc.getName();
}

void DataWidget::resizeEvent( QResizeEvent *e )
{
  //QMainWindow::resizeEvent(e);
    paintData();
}

void DataWidget::paintEvent(QPaintEvent *qe)
{
    paintData();
}

