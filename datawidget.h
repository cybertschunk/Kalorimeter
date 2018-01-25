#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include "record.h"
#include "main.h"

#include <QObject>
#include <QWidget>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QString>
#include <QMainWindow>

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    DataWidget(QWidget *parent, int m, Main*, QString p = "");
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *qe);
    auto getName() -> QString;

    const static int DB_MODE = 1;
    const static int FILE_MODE = 2;

private:

    auto initRc() -> void;
    auto updateBorders() -> void;
    auto scaleData() -> void;
    auto scaleEntryTemp1(Entry e) -> QPointF;
    auto scaleEntryTemp2(Entry e) -> QPointF;

    Main* main;
    QString path;
    int mode;
    Record rc;

    //GUI
    QBoxLayout *mainLayout;

    //Drawing data
    int width;
    int height;
    int xdistance, ydistance;
    double pixPerDeg;
    double pixPerMilli;
    int startx, endx, starty, endy;
    QGraphicsView* view;
    QGraphicsScene* scene;
    auto paintData() -> void;

    //Data
    QDateTime startTime;
    QDateTime endTime;
    double minTemp;
    double maxTemp;
};

#endif // DATAWIDGET_H
