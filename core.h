#ifndef CORE_H
#define CORE_H

#include <QFile>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMultiMap>

#define DEBUG   true


typedef struct {
    int seqNumber;
    int time;

}element;




class Core
{
public:
    Core();

    void process_line(QString line);
    int extract_seqNumber(QString line);
    double extract_time(QString line);
    double compute_delay(double time1, double time2);
    QList<double> getDelayList();

    //private:
    QVector<element> tab_els;
    QMap<int, double> _map;//key seqNumber, value time
    QMap<int, double> _resmap;
    QMultiMap<int, double> _mmap;//utilisation d'un multimap à la place de map (plusieurs key identiques)

};

#endif // CORE_H
