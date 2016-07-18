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
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/wireshark/fortune");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        core.process_line(QString(line));
    }

    QList<double> durations;

    durations = core.getDelayList();

    //affichage des delays calculés sur la console
    qDebug() << "retards calculees:\n";

    for(int i=0; i< durations.size();i++){
        qDebug() << durations[i];

    file.close();

    }

    return a.exec();
}
