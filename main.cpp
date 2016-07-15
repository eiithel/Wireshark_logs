#include <QCoreApplication>
#include "core.h"

#include <QByteArray>
#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <iostream>
#include <istream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Debut programme";

    Core core;
    QFile file;
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/wireshark/tcp1");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        core.process_line(QString(line));// vient stocker els dans tableau
    }

    QList<double> durations;

    durations = core.getDurationList();// va associer les els avec meme id et calculer duration, rend un fichier .csv

    //affichage des durées calculées sur la console
    qDebug() << "durees calculees:";

    for(int i=0; i< durations.size();i++){
        qDebug() << durations[i];

    file.close();

    }

    return a.exec();
}
