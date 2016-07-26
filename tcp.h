#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QString>

class Tcp
{
public:
    Tcp();


    // ajout de _src et _dest pour vérifier qui envoit et qui reçoit. (Peut normalement être géré en filtrant bien sur wireshark).
    QString _src;
    QString _dest;

};

#endif // TCP_H
