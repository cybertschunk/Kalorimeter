#include "record.h"

#include <QtXml>
#include <QDebug>
#include <QString>

int Record::ID = 0;

auto Record::getLowestEntry() -> Entry&
{
    return entries.at(0);
}
auto Record::getHighestEntry() -> Entry&
{
    return entries.at(entries.size() -1);
}
auto Record::getEntryAt(int i) -> Entry&
{
    return entries.at(i);
}

auto Record::writeToXML(QString path) -> bool
{

    //Initialising
    QDomDocument document;
    QDomElement root = document.createElement("record");
    root.setAttribute("name",getName());
    document.appendChild(root);
    QFile file(path);
    if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open the file " << path << "for writing failed.";
        return false;
    }

    //Appending data
    for(int i = 0; i < entries.size(); ++i)
    {
        QDomElement eElem = document.createElement("entry");
        Entry e = entries.at(i);

        eElem.setAttribute("timestamp",e.getTimestamp().toString(Qt::TextDate));
        eElem.setAttribute("temp1",e.getTemp1());
        eElem.setAttribute("temp2",e.getTemp2());
        root.appendChild(eElem);
    }

    //Writing the data to file
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
    qDebug() << "Writing is done!";

}

auto Record::ReadFromXML(QString path) -> Record
{
    Record rc;
    QFile file(path);
    QDomDocument document;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open the file for reading.";
        return rc;
    }

    // loading
    if(!document.setContent(&file))
    {
        qDebug() << "Failed to load the file for reading.";
        return rc;
    }
    file.close();

    QDomElement root = document.firstChildElement();
    QString name = root.attribute("name");
    QDomNodeList nodes = root.elementsByTagName("entry");
    std::vector<Entry> entries(nodes.size());
    for(int i = 0; i < nodes.size(); ++i)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            QString ts = e.attribute("timestamp");
            QString t1 = e.attribute("temp1");
            QString t2 = e.attribute("temp2");

            const QDateTime dt = QDateTime::fromString(ts,Qt::TextDate);
            const double temp1 = t1.toDouble();
            const double temp2 = t2.toDouble();
            Entry ent = Entry(dt,temp1,temp2);
            entries[i] = ent;
        }
    }

    rc = Record(name,entries);
    qDebug() << "Reading finished!";
    return rc;
}

auto Record::getName() const -> QString
{
    return name;
}

auto Record::setName(QString& n) -> void
{
    name = n;
}

auto Record::setEntries(std::vector<Entry> e) -> void
{
    entries = e;
}
auto Record::getSize() const -> int
{
    return entries.size();
}

auto Record::getHighestTemp() -> double
{
    double tmp = -2000;
    for(Entry e: entries)
    {
        if(e.getTemp1() > tmp)
            tmp = e.getTemp1();
        if(e.getTemp2() > tmp)
            tmp = e.getTemp2();
    }
    return tmp;
}

auto Record::getLowestTemp() -> double
{
    double tmp = 2000;
    for(Entry e: entries)
    {
        if(e.getTemp1() < tmp)
            tmp = e.getTemp1();
        if(e.getTemp2() < tmp)
            tmp = e.getTemp2();
    }
    return tmp;
}

auto Record::getEntries() -> std::vector<Entry>&
{
    return entries;
}
