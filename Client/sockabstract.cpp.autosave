#include "sockabstract.h"

sockAbstract::sockAbstract()
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectSuc()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMsg()));
    tcpHead = 0;
}

sockAbstract::~sockAbstract()
{

}

void sockAbstract::init()
{
    tcpSocket->abort();
    tcpSocket->connectToHost("120.26.77.201", 4000);


}

void sockAbstract::connectSuc()
{
    QMessageBox msgBox;
    msgBox.setText("connect!");
    msgBox.exec();
}

void sockAbstract::readMsg()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (tcpHead == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint8))
            return;

        in >> tcpHead;

        blockSize = msgLen(tcpHead);
     }

     if (tcpSocket->bytesAvailable() < blockSize)
        return;
     /*QString nextFortune;
     in >> nextFortune;

     if (nextFortune == currentFortune) {
         QTimer::singleShot(0, this, SLOT(requestNewFortune()));
         return;
     }

     currentFortune = nextFortune;
     statusLabel->setText(currentFortune);
     getFortuneButton->setEnabled(true);*/
}

void sockAbstract::sendToSock(char * Msg)
{
    QDataStream out(tcpSocket);
    out.setVersion(QDataStream::Qt_4_0);
    if (tcpSocket->isWritable())
    {
        out << Msg;
    }
}

quint16 sockAbstract::msgLen(quint8 tcpHead)
{
    quint8 front4 = (tcpHead & 0xf0) >> 4;
    if (front4 == 1)
    {
        return 1;
    }
    if (front4 >= 4)
    {
        quint8 front34 = (front4 & 0x3) >> 2;
        quint8 front2 = (front4 & 0xc) >> 2;
        if (front2 == 1) return 2;
        if (front2 == 2)
        {
            if (front34 == 0) return 2;
            if (front34 == 1) return 3;
            if (front34 == 2) return 4;
            if (front34 == 3) return 5;
        }
        if (front2 == 3) return 5;
    } else
    {
        if (tcpHead == 0x01) return  6;
        if (tcpHead == 0x02) return  6;
        if (tcpHead == 0x03) return  12;
        if (tcpHead == 0x24) return  1;
        if (tcpHead == 0x25) return  12;
        if (tcpHead == 0x26) return  23;
        if (tcpHead == 0x08) return  7;
        if ((tcpHead >= 0x20) && (tcpHead <= 23)) return  0;
        if (tcpHead == 0x07) return  2;
    }
    return 0;
}
