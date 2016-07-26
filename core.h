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

    QStringList splitLine(QString line1);

    void process_line(QString line1, QString line2);
    int extract_seqNumber(QString line);
    double extract_time(QString line);
    double extractRTTi(QString line);//Get RTT initial (3-way TCP handshake)
    double extractRTT(QString line);//Get RTT ti ACK the segment

    double compute_delay(double time1, double time2);//pb on se base sur les n° de séquence pour reconnaître un paquet mais il faudrait aussi vérifier que src <==> dst
    QList<double> getDelayList();

    //getters
    double getJitter(QList<double> RTT);//Get Jitter.
    double getAvgRTT(QList<double> RTT); //Get Average Round Trip Time
    double getAvgDelay(QList<double> RTT);//Get Average delay


    QList<double> getRTTlist();//return RTTlist

    void report(double Jitter, double AvgRTT);// Append the report of the session to a .csv file.

    void displayRTTlist();

    bool isResponseOf(QString line1, QString line2);

    //private:

    QList<double> _RTTlist;

    QMap<int, double> _map;//key seqNumber, value time
    QMap<int, double> _resmap;
    QMultiMap<int, double> _mmap;//utilisation d'un multimap à la place de map (plusieurs keys identiques)

};

#endif // CORE_H
