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


int flag = -1;


Core::Core()
{

}


QStringList Core::splitLine(QString line){

    QStringList FieldList;

    line.begin();
    FieldList=line.split(",");

    FieldList.replaceInStrings(QChar('"'), "");
    return FieldList;
}



/*
 *Cette fonction vient lire chaque ligne et extrait seqNumber
 *et time pour chaque trame. Elle stocke cette info dans une mmap.
 */
void Core::process_line(QString line){

    _RTTlist.append(extractRTT(line));

    QStringList list =splitLine(line);
    double deltaTCP = extractDeltaTCP(list);
    _DeltaTcpList.append(deltaTCP);
    double time = extract_time(line);

    report(deltaTCP,time);


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

    double i;
    QStringList list =splitLine(line);

    i=(list.at(1)).toDouble();

    return i;
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

double Core::extractDeltaTCP(QStringList list){
    return (list.at(2)).toDouble();
}


double Core::getAvg(QList<double> RTT){
    double sum = 0.0;
    for(double a : RTT)
        sum += a;
    return sum/RTT.size();
}

double Core::getJitter(QList<double> RTT){

    double mean = getAvg(RTT);
    double temp = 0;
    for(double a :RTT)
        temp += (mean-a)*(mean-a);
    temp = temp/RTT.size();
    return temp/2; //variance RTT/2 pour avoir jitter
}

double Core::getAvgDelay(QList<double> RTT){

    double mean = getAvg(RTT);
    mean /=2; //on divise RTT par 2 pour avoir la latence
    return mean;
}

QList<double> Core::getRTTlist(){
    return _RTTlist;
}

QList<double> Core::getDeltaTcplist(){
    return _DeltaTcpList;
}



void Core::displayRTTlist(){

    _RTTlist.removeAll(0);
    //on enleve les premieres valeurs qui sont à 0 pour etre sur que les échanges de donné ont commencé.

    int size = _RTTlist.size();
    for(int i=0;i<size;i++){
        qDebug() << _RTTlist.at(i);
    }
}

void Core::diplayDeltaTcpList(){

    _DeltaTcpList.removeAll(0);
    int size = _DeltaTcpList.size();
    for(int i=0;i<size;i++){
        qDebug() << _DeltaTcpList.at(i);
    }
}



void Core::report(double DeltaTcp, double time){


    QFile outfile(QString("/home/ethel/qwt-5.2/test-ethel/wireshark/report.csv"));

    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Unable to create file";
        return;
    }


#if FIRST_TEST


    if(flag<0)
    {
        outfile.write("DeltaTCP, time\n");
        flag=0;
    }
#endif
    QTextStream stream(&outfile);
    stream << DeltaTcp << "," << QString::number(time, 'f', 6) << "\n";

    outfile.close();
}


void Core::reportGlobal(double Jitter, double DeltaTCP){
    QFile outfile(QString("/home/ethel/qwt-5.2/test-ethel/wireshark/reportGlobal.csv"));

    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Unable to create file";
        return;
    }

#if FIRST_TEST
    outfile.write("Jitter, DeltaTCP\n");
#endif
    QTextStream stream(&outfile);
    stream << Jitter << "," << DeltaTCP << "\n";

    outfile.close();
}

