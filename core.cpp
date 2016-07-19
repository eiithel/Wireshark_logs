#include "core.h"
#include <algorithm>
#include <iostream>
#include <QVectorIterator>
#include <QList>
#include <QtMath>
#include <QDebug>
#include <QTextStream>
#include <QStringList>
#include <QChar>

Core::Core()
{

}

/*
 *Cette fonction vient lire chaque ligne et extrait seqNumber
 *et time pour chaque trame. Elle stocke cette info dans une mmap.
 */
void Core::process_line(QString line){

    _RTTlist.append(extractRTT(line));

}

int Core::extract_seqNumber(QString line){

    int pos = -1;
    int seqNumber = -1;
    if((pos = line.indexOf("Seq")) > -1)
    {
        seqNumber = line.mid(pos+4,4).toInt();
    }

    return seqNumber;
}

double Core::extract_time(QString line){

    int pos = -1;
    double time =-1;
    QStringList wordList;
    QString temp;

    line.begin();
    wordList=line.split(",");
    temp = wordList.at(1);
    temp.remove(QChar('"'));

    return time = temp.toDouble();
}


double Core::extractRTTi(QString line){

    int pos = -1;
    double RTTi =-1;
    line.begin();

    //to implement later
    return RTTi;

}


double Core::extractRTT(QString line){

    int pos = -1;
    double RTT =-1;
    QStringList wordList;
    QString temp;

    line.begin();
    wordList=line.split(",");
    temp = wordList.at(2);
    temp.remove(QChar('"'));

    return RTT = temp.toDouble();

}

double Core::getAvgRTT(QList<double> RTT){
    double sum = 0.0;
    for(double a : RTT)
        sum += a;
    return sum/RTT.size();
}

double Core::getJitter(QList<double> RTT){

    double mean = getAvgRTT(RTT);
    double temp = 0;
    for(double a :RTT)
        temp += (mean-a)*(mean-a);
    temp = temp/RTT.size();
    return temp/2; //variance RTT/2 pour avoir jitter
}

double Core::getAvgDelay(QList<double> RTT){

    double mean = getAvgRTT(RTT);
    mean /=2; //on divise RTT par 2 pour avoir la latence
    return mean;
}

QList<double> Core::getRTTlist(){
    return _RTTlist;
}


void Core::report(double Jitter, double AvgRTT){
    QFile outfile(QString("/home/ethel/qwt-5.2/test-ethel/wireshark/report.csv"));

    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Unable to create file";
        return;
    }

#if FIRST_TEST
    outfile.write("Jitter,AvgRTT\n");
#endif
    QTextStream stream(&outfile);
    stream << Jitter << "," << AvgRTT << "\n";

    outfile.close();
}

void Core::displayRTTlist(){

    _RTTlist.removeAll(0);
    //on enleve les premieres valeurs qui sont à 0 pour etre sur que les échanges de donné ont commencé.

    int size = _RTTlist.size();
    for(int i=0;i<size;i++){
        qDebug() << _RTTlist.at(i);
    }
}


