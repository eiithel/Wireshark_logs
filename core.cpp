#include "core.h"
#include <algorithm>
#include <iostream>
#include <QVectorIterator>
#include <QList>
#include <QtMath>
#include <QDebug>
#include <QTextStream>
#include <QChar>

Core::Core()
{

}

QStringList Core::splitLine(QString line){

    QStringList wordList;

    line.begin();
    wordList=line.split(",");

    //    int lenght = wordList.size();

    //    for(int i=0; i<lenght; i++){
    //        wordList.
    //    }
    //    temp.remove(QChar('"'));

    wordList.replaceInStrings(QChar('"'), "");
    return wordList;


    //RTT = temp.toDouble();

}





/*
 *Cette fonction vient lire chaque ligne et extrait seqNumber
 *et time pour chaque trame. Elle stocke cette info dans une mmap.
 */
void Core::process_line(QString line1 , QString line2){

    if(!isResponseOf(line1, line2)){
        return;
    }

    double time1, time2;
    time1 = extract_time(line1);
    time2 = extract_time(line2);

    QStringList list1= splitLine(line1);
    QStringList list2 =splitLine(line2);

    QString tmp1 = list1.at(1);
    QString tmp2 = list2.at(1);


    double delay = compute_delay(tmp1.toDouble(), tmp2.toDouble());

    //    _mmap.insert(extractRTT(line),extract_time(line));

    //    _RTTlist.append(extractRTT(line));

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

}


double Core::extractRTT(QString line){

    double RTT =-1;
    QStringList wordList;
    QString temp;

    line.begin();
    wordList=line.split(",");
    temp = wordList.at(2);
    temp.remove(QChar('"'));

    RTT = temp.toDouble();

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

/*Cette fonction retourne vraie si seq trame1 = ack trame2 ou seq trame2 = ack trame1
 */
bool Core::isResponseOf(QString line1, QString line2){

    QStringList wordList1 , wordList2;
    QString temp1, temp2, temp3, temp4;
    int seq1, ack1, seq2, ack2;

    line1.begin();
    line2.begin();
    wordList1=line1.split("=");
    wordList2=line2.split("=");

    temp1= wordList1.at(1);// "726 Ack" --> Seq
    temp2= wordList1.at(2);// "2897 Win" --> Ack

    temp3 =wordList2.at(1);// "726 Ack" --> Seq
    temp4 =wordList2.at(2);// "2897 Win" --> Ack

    wordList1=temp1.split(" ");
    temp1 = wordList1.at(0);// "726" Seq
    wordList1=temp2.split(" ");
    temp2 = wordList1.at(0);// "2897" Ack

    wordList2=temp3.split(" ");
    temp3 = wordList2.at(0);// "726" Seq
    wordList2=temp4.split(" ");
    temp4 = wordList2.at(0);// "2897" Ack

    temp1.remove(QChar('"'));
    temp2.remove(QChar('"'));
    temp3.remove(QChar('"'));
    temp4.remove(QChar('"'));

    seq1=temp1.toInt();//726
    ack1=temp2.toInt();//2897
    seq2=temp3.toInt();//2897
    ack2=temp4.toInt();//726

    if(seq1 == ack2 || seq2 == ack1){
        return true;
    }
    return false;
}



