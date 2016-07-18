#include "core.h"
#include <algorithm>
#include <iostream>
#include <QVectorIterator>
#include <QList>
#include <QtMath>
#include <QDebug>
#include <QTextStream>

Core::Core()
{

}

/*
 *Cette fonction vient lire chaque ligne et extrait seqNumber
 *et time pour chaque trame. Elle stocke cette info dans une mmap.
 */
void Core::process_line(QString line){

    _mmap.insert(extract_seqNumber(line),extract_time(line));

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

    int size=_mmap.size();

    _mmap.values();//si une clé est associée avec +sieurs valeurs valeurs, elles seront toutes dans la liste (a tester)

    QList<double> timer = _mmap.values();
    QList<double> durations;
    //    if(timer.empty())
    //        return; utiliser une exception a la place

    timer.removeFirst();//on enleve le descriptif du fichier csv.


    int size_max= timer.size() -1;

    for (int i=0; i< size_max; i++){
        double res = compute_delay(timer.at(i), timer.at((i+1)));
        durations.push_back(res);
        i++;
    }
    return durations;

}


double Core::getAvgRTT(QList<double> delays){
    double sum = 0.0;
    for(double a : delays)
        sum += a;
    return sum/delays.size();
}

double Core::getJitter(QList<double> delays){
    double mean = getAvgRTT(delays);
    double temp = 0;
    for(double a :delays)
        temp += (mean-a)*(mean-a);
    return temp/delays.size();

}


double Core::maxDelaySD(QList<double> delays){

}

double Core::maxDelayDS(QList<double> delays){

}

void Core::Report(double Jitter, double AvgRTT){
    QFile outfile(QString("/home/ethel/qwt-5.2/test-ethel/wireshark/report.csv"));

    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Unable to create file";

        return;
    }
    outfile.write("Jitter,AvgRTT\n");
    //    outfile.write(QString(Jitter));
    //    outfile.write(",");
    //    outfile.write(QString(AvgRTT));
    QTextStream stream(&outfile);
    stream << Jitter << "," << AvgRTT << "\n";

    outfile.close();
}
