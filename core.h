#ifndef CORE_H
#define CORE_H

#include <QFile>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMultiMap>
#include <QStringList>
#include <iomanip>


#define DEBUG   false
#define FIRST_TEST true //indique que c'est le début de l'analyse statistique.


class Core
{
public:
    Core();

    QStringList splitLine(QString line);//Décompose la ligne en une liste de mots.
    void process_line(QString line);//extract RTT value from csv input file
    int extract_seqNumber(QString line);//extract time from csv input file
    double extract_time(QString line);//extract time from csv input file
    double extractRTT(QString line);//Get RTT ti ACK the segment
    double extractDeltaTCP(QStringList list);//time in seconds since the last TCP segment in the current conversation

    double compute_delay(double time1, double time2);

    //getters
    double getJitter(QList<double> RTT);//Get Jitter.
    double getAvg(QList<double> RTT); //Get Average Round Trip Time
    double getAvgDelay(QList<double> RTT);//Get Average delay


    QList<double> getRTTlist();//return RTTlist
    QList<double> getDeltaTcplist();//return DeltatTcplist

//    void report(double Jitter, double DeltaTcp);// Append the report of the session to a .csv file.
    void report(double DeltaTcp, double time);// Append the DeltaTcp report to a .csv file.

    void reportGlobal(double Jitter, double DeltaTcp);//Enregistre les valeurs globales issues d'une session de test

    void displayRTTlist();
    void diplayDeltaTcpList();

    //private:

    QList<double> _RTTlist;
    QList<double> _DeltaTcpList;

};

#endif // CORE_H
