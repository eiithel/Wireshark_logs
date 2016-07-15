#include "core.h"
#include <algorithm>
#include <iostream>
#include <QVectorIterator>
#include <QList>

Core::Core()
{

}

/*
 *Cette fonction vient lire chaque ligne et extrait seqNumber
 *et time pour chaque trame. Elle stocke cette info dans un tableau de structures.
 */
void Core::process_line(QString line){

    //_map.insert(extract_seqNumber(line), extract_time(line));
    //attention pb, si jamais la clé est la même il supprime l'ancienne valeur.
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

double Core::compute_time(double time1, double time2){
    double result;

    if(time1 > time2){
        result = time1-time2;
    }else{
        result = time2-time1;
    }

    return result;
}

QList<double> Core::getDurationList(){

    int size=_mmap.size();

    _mmap.values();//si une clé est associée avec +sieurs valeurs valeurs, elles seront toutes dans la liste (a tester)

    QList<double> timer = _mmap.values();
    QList<double> durations;
    //    if(timer.empty())
    //        return; utiliser une exception a la place

    timer.removeFirst();//on enleve le descriptif du fichier csv.


    int size_max= timer.size() -1;

    for (int i=0; i< size_max; i++){
        double res = compute_time(timer.at(i), timer.at((i+1)));
        durations.push_back(res);
        i++;
    }
    return durations;

}
