#ifndef CORE_H
#define CORE_H

#include <QFile>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMultiMap>
#include <QStringList>

#define DEBUG   true
#define FIRST_TEST false //indique que c'est le début de l'analyse statistique.


class Core
{
public:
    Core();

    QStringList splitLine(QString line);
    void process_line(QString line);//extract RTT value from csv input file
    int extract_seqNumber(QString line);//extract time from csv input file
    double extract_time(QString line);//extract time from csv input file
    double extractRTTi(QString line);//Get RTT initial (3-way TCP handshake)
    double extractRTT(QString line);//Get RTT ti ACK the segment
    double extractDeltaTCP(QStringList list);

    double compute_delay(double time1, double time2);

    //getters
    double getJitter(QList<double> RTT);//Get Jitter.
    double getAvg(QList<double> RTT); //Get Average Round Trip Time
    double getAvgDelay(QList<double> RTT);//Get Average delay


    QList<double> getRTTlist();//return RTTlist
    QList<double> getDeltaTcplist();//return DeltatTcplist

    void report(double Jitter, double AvgRTT);// Append the report of the session to a .csv file.
    void report(double DeltaTcp);// Append the DeltaTcp report to a .csv file.

    void displayRTTlist();
    void diplayDeltaTcpList();//ok

    //private:

    QList<double> _RTTlist;
    QList<double> _DeltaTcpList;

};

#endif // CORE_H
