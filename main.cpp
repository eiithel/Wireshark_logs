#include <QCoreApplication>
#include "core.h"

#include <QByteArray>
#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <iostream>
#include <istream>

/*
 * programme permettant de faire l'analyse statistique des delays rencontrés lors de chaque séance.
 * Le programme se base sur un fichier .csv issu d'une session de capture wireshark.
 * Il est important d'ajouter la colonne "Time delta from previous captured frame" dans l'analyse WireShark.
 * Le programme ajoute une ligne au fichier report.csv avec le Jitter (variance) et la moyenne des délais calculés.
 *
 * /!\ Pour utiliser le programme pour la première fois, mettre la directive de préprocesseur FIRST_TIME à "true".
 *
 * */


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Debut programme";

    Core core;
    QFile file;
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/wireshark/dataV2");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QFile filecopy;
    file.copy("/home/ethel/qwt-5.2/test-ethel/wireshark/dataV2", "/home/ethel/qwt-5.2/test-ethel/wireshark/dataV2copy");
    filecopy.setFileName("/home/ethel/qwt-5.2/test-ethel/wireshark/dataV2copy");
    if (!filecopy.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    for(int i =0; i<9; i++){
        file.readLine();
    }// on ne va pas traiter les 10 premieres lignes (établissement de la connection, etc pas très important.

    for(int i=0; i<10;i++){
        filecopy.readLine();
    }//file et filecopy sont en decalage d'une ligne

    while (!file.atEnd() && !filecopy.atEnd())
    {
        QByteArray line1 = file.readLine();
        QByteArray line2 = filecopy.readLine();

        core.process_line(QString(line1), QString(line2));
        //        core.isResponseOf(QString(line1), QString(line2));
    }

    QList<double> RTTList = core.getRTTlist();

    double jitter = core.getJitter(RTTList);
    double avgDelay = core.getAvgDelay(RTTList);

#if DEBUG

    //affichage des delays calculés sur la console
    qDebug() << "retards calculees:\n";

    core.displayRTTlist();

    qDebug() << "\nDelay moyen:";
    qDebug() << avgDelay;
    qDebug() << "\nJitter:";
    qDebug() << jitter;

#endif

    core.report(jitter, avgDelay);// save statistics to a "report.csv" file

    file.close();
    filecopy.close();

    return a.exec();
}
