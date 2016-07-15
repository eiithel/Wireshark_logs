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

    double result = time1-time2;
    return result;

}

void Core::compare(){

    int size=_mmap.size();

    _mmap.values();//si une clé est associée avec +sieurs valeurs valeurs, elles seront toutes dans la liste (a tester)

    QList<int> List_seqNumber;
    QList<double> timer = _mmap.values();
    QList<double> durations;
    if(timer.empty())
        return;
    timer.removeFirst();//on enleve le descriptif du fichier csv.

    List_seqNumber = _mmap.uniqueKeys();

    while(!timer.empty()){
        for(int i=0; i<timer.count(); i+2){
            double res = compute_time(timer.takeAt(i), timer.takeAt(i+1));
            durations.push_back(res);
        }
    }
}

//QMap<QString, int> map;
//...
//QMap<QString, int>::const_iterator i = map.lowerBound("HDR");
//QMap<QString, int>::const_iterator upperBound = map.upperBound("HDR");
//while (i != upperBound) {
//    cout << i.value() << endl;
//    ++i;
//}


/*
void Core::process_line(QString line){
    int srcID = -1;
    int seqNumber = -1;
    QString outputLine = "";
    QByteArray outputData;
    QTime actualTime;

    if(line.contains("bwMonitorTimeout"))
    {
        seqNumber = extract_seqNumber;

        switch(srcID)
        {
        case 1:
            outVideoSrc1.write(outputData);
            break;
        case 2:
            outVideoSrc2.write(outputData);
            break;
        case -1:
            addHistory(QString("Unable to find srcID in %1").arg(line));
            break;
        default:
            addHistory(QString("Undefined srcID in %1").arg(line));
            break;
        }
    }
    else if(line.contains("popFrontAudioBuffer"))
    {
        srcID = extract_srcID(line);

        if(firstTime)
        {
            m_startingTime = formatTime(extract_time(line));
            firstTime = false;
        }

        actualTime = formatTime(extract_time(line));

        outputLine = QString("%1,%2,%3,%4,%5\n").arg(extract_date(line)).arg(m_startingTime.msecsTo(actualTime))
                .arg(extract_realAudio_size(line)).arg(extract_allowedAudio_size(line)).arg(srcID);
        outputData = outputLine.toUtf8();

        switch(srcID)
        {
        case 1:
            outAudioSrc1.write(outputData);
            break;
        case 2:
            outAudioSrc2.write(outputData);
            break;
        case -1:
            addHistory(QString("Unable to find srcID in %1").arg(line));
            break;
        default:
            addHistory(QString("Undefined srcID in %1").arg(line));
            break;
        }

    }
    else if(line.contains("REQUEST_FRAME_ADAPTATION"))
    {
        srcID = extract_srcID(line);

        if(firstTime)
        {
            m_startingTime = formatTime(extract_time(line));
            firstTime = false;
        }

        actualTime = formatTime(extract_time(line));

        outputLine = QString("%1,%2,%3,%4\n").arg(extract_date(line)).arg(m_startingTime.msecsTo(actualTime))
                .arg(extract_adaptation_factor(line)).arg(srcID);
        outputData = outputLine.toUtf8();

        switch(srcID)
        {
        case 1:
            outAdaptationSrc1.write(outputData);
            break;
        case 2:
            outAdaptationSrc2.write(outputData);
            break;
        case -1:
            addHistory(QString("Unable to find srcID in %1").arg(line));
            break;
        default:
            addHistory(QString("Undefined srcID in %1").arg(line));
            break;
        }
    }
}

int Core::extract_srcID(QString line)
{
    int pos = -1;
    int id = -1;
    if((pos = line.indexOf("SrcID")) > -1)
    {
        id = line.mid(pos+8,1).toInt();
    }
    else if((pos = line.indexOf("srcID")) > -1)
    {
        id = line.mid(pos+8,1).toInt();
    }

    return id;
}
*/

