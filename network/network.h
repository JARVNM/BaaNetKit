#pragma once
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QHostAddress>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QVector>
#include <QTimer>
#include <QUdpSocket>
class Network : public QObject
{
    Q_OBJECT
public:
    Network();
    QStringList getLocalIp();
    void start_tcpserver(QString ip, qint32 port);
    void stop_tcpserver();
    void serverSendData(QString data, QString ip, qint32 port);
    void beginTimely(QString data, qint32 time, QString ip, qint32 port);
    void stopTimely();

    void start_tcpConnect(QString ip, qint32 port);
    void stop_tcpConnect();
    void tcpSendData(const QByteArray& message);

    void start_udpConnect(QString ip, qint32 port);
    void stop_udpConnect();
    void udpSendData(const QByteArray& message, QString ip, qint32 port);
signals:
//server
    void serverListenFailedSignal();
    void serverListenSuccessedSignal();
    void serverClosedSignal();
    void newConnectionSignal(QMap<QString, qint32>);
    void serverReadyReadSignal(QString, QString, qint32);
    void disconnectedSignal(QMap<QString, qint32>);
    
//tcp
    void tcpConnectedSuccessSignal();
    void tcpConnectFailedSignal();
    void tcpDisconnectedSignal();
    void tcpReadyReadSignal(QString data, QString ip, qint32 port);

//udp
    void udpReadyReadSignal(QString data, QString ip, qint32 port);
    void udpBindSuccessSignal();
private:
//server
    QTcpServer *server;
    QVector<QTcpSocket*> socketVec;
    QString server_ip;
    qint32 server_port;
    QString t_ip;
    qint32 t_port;
    qint32 t_time;
    QString t_data;
    QMap<QString, qint32> clientMap;
    int client_count;
    void init_tcpserver();
    QTimer t;
    void timelyHandler();

//tcp
    QTcpSocket* tcpsocket;
    bool tcpsocketState;

//udp
    QUdpSocket* udpsocket;
private slots:
//server
    void newConnectionSlot();
    void readyReadSlot();
    void disconnectedSlot();

//tcp
    void tcpConnectedSlot();
    void tcpDisconnectedSlot();
    void tcpReadyReadSlot();

//udp
    void udpReadyReadSlot();

};
