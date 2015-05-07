#ifndef SOCKABSTRACT_H
#define SOCKABSTRACT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QmessageBox>
class sockAbstract : public QObject
{
    Q_OBJECT
public:
    QTcpSocket *tcpSocket;
    sockAbstract();
    ~sockAbstract();
    void init();
    //virtual quint16 AnalyMsg(char * Msg);
    virtual quint16 msgLen(quint8 tcpHead);
    void sendToSock(char * Msg);
private slots:
    void connectSuc();
    void readMsg();
private:

    quint8 tcpHead;
    quint16 blockSize;
};

#endif // SOCKABSTRACT_H
