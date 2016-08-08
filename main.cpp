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

    //L'analyse se fait sur le fichier DataV3.csv issu de wireshark
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/wireshark/clitos");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        core.process_line(QString(line));
    }

    core.removeComa(core._reportFile);

    QList<double> RTTList = core.getRTTlist();
    QList<double> DeltaTCPList = core.getDeltaTcplist();

    double avgDelta = core.getAvg(DeltaTCPList);// avg moyen pour le tcp.time_delta

    double jitter = core.getJitter(DeltaTCPList);


#if DEBUG

    qDebug() << "affichage des DeltaTCP:";
    core.diplayDeltaTcpList();//ok

#endif

    core.reportGlobal(jitter, avgDelta);// save statistics to a "report.csv" file

    file.close();

    return a.exec();
}
