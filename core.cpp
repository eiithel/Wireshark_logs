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

    _mmap.insert(extractRTT(line),extract_time(line));

    _RTTlist.append(extractRTT(line));

}

int Core::extract_seqNumber(QString line){

    int pos = -1;
    int seqNumber = -1;
    if((pos = line.indexOf("Seq")) > -1)
    {
        seqNumber = line.mid(pos+4,1).toInt();
    }

    return seqNumber;
}

double Core::extract_time(QString line){

    int pos = -1;
    double time =-1;
    line.begin();

    if((pos = line.indexOf(",")) > -1)
    {
        time = line.mid(pos+2,12).toDouble();
    }

    return time;
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


double Core::compute_delay(double time1, double time2){
    double result;

    if(time1 > time2){
        result = time1-time2;
    }else{
        result = time2-time1;
    }

    return result;
}

QList<double> Core::getDelayList(){

    _mmap.values();//si une clé est associée avec +sieurs valeurs valeurs, elles seront toutes dans la liste (a tester)

    QList<double> timer = _mmap.values();
    QList<double> durations;

    timer.removeFirst();//on enleve le descriptif du fichier csv.

    int size_max= timer.size() -1;

    for (int i=0; i< size_max; i++){
        double res = compute_delay(timer.at(i), timer.at((i+1)));
        durations.push_back(res);
        i++;
    }
    return durations;

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


