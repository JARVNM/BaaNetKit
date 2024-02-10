#include "./network.h"

Network::Network() : client_count(0), clientMap(), socketVec(), tcpsocketState(false)
{
    server = new QTcpServer();
    connect(server, &QTcpServer::newConnection, this, &Network::newConnectionSlot);
    connect(&t, &QTimer::timeout, this, &Network::timelyHandler);

    tcpsocket = new QTcpSocket();
    connect(tcpsocket, &QTcpSocket::connected, this, &Network::tcpConnectedSlot);
    connect(tcpsocket, &QTcpSocket::disconnected, this, &Network::tcpDisconnectedSlot);
    connect(tcpsocket, &QTcpSocket::readyRead, this, &Network::tcpReadyReadSlot);

    udpsocket = new QUdpSocket();
    connect(udpsocket, &QUdpSocket::readyRead, this, &Network::udpReadyReadSlot);
}

QStringList Network::getLocalIp()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QStringList addressStrList;
    addressStrList.clear();
    foreach(QHostAddress address, list)
    {
        if(address.isNull())
            continue;
        QAbstractSocket::NetworkLayerProtocol protocol = address.protocol();
        if(protocol != QAbstractSocket::IPv4Protocol)
            continue;
        addressStrList.append(address.toString());
    }

    return addressStrList;
}

void Network::start_tcpserver(QString ip, qint32 port)
{
    this->server_ip = ip;
    this->server_port = port;
    init_tcpserver();
}

void Network::stop_tcpserver()
{
    init_tcpserver();
}

void Network::init_tcpserver()
{
    QHostAddress serverAddress = QHostAddress(this->server_ip);
    if(!server->isListening())
    {
        qDebug() << "start";
        if(!server->listen(serverAddress, this->server_port))
        {
            emit serverListenFailedSignal();
        }
        else
        {
            emit serverListenSuccessedSignal();
        }
    }
    else
    {
        qDebug() << "end";
        server->close();
        //server = nullptr;
        foreach(QTcpSocket* s, socketVec)
        {
            delete s;
            s = nullptr;
        }
        socketVec.clear();
        clientMap.clear();
        emit serverClosedSignal();
    }
}

void Network::newConnectionSlot()
{
    QString clientInfo;
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Network::readyReadSlot);
    connect(socket, &QTcpSocket::disconnected, this, &Network::disconnectedSlot);
    clientMap[socket->peerAddress().toString()+":"+
        QString::number(socket->peerPort())] = socket->peerPort();
    socketVec.append(socket);
    qDebug() << clientMap;
    emit newConnectionSignal(clientMap);
}

void Network::readyReadSlot()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << "get message";
    if(socket != nullptr)
    {
        if(socket->isReadable())
        {
            QByteArray data_byte = socket->readAll();
            QString data_str = QString::fromLocal8Bit(data_byte);
            QString ip = socket->peerAddress().toString();
            qint32 port = socket->peerPort();
            emit serverReadyReadSignal(data_str, ip, port);
        }
    }
}

void Network::disconnectedSlot()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if(socket == nullptr)
        return;
    QString ip = socket->peerAddress().toString();
    QString port = QString::number(socket->peerPort());
    QString key = ip + ":" + port;
    QVector<QTcpSocket*>::iterator ite = socketVec.begin();
    while(ite != socketVec.end())
    {
        if(*ite == socket)
        {
            
            socketVec.erase(ite);
            break;
        }

        ite++;   
    }
    if(clientMap.contains(key))
        clientMap.remove(key);
    
    emit disconnectedSignal(clientMap);
    //qDebug() << clientMap;
}

void Network::serverSendData(QString data, QString ip, qint32 port)
{
    foreach(QTcpSocket* s, socketVec)
    {
        QString curIp = s->peerAddress().toString();
        qint32 curPort = s->peerPort();
        if(ip == curIp && port == curPort)
        {
            s->write(data.toLocal8Bit());
            break;
        }
    }
}

void Network::beginTimely(QString data, qint32 time, QString ip, qint32 port)
{
    t_ip = ip;
    t_port = port;
    t_data = data;
    t_time = time;
    t.start(time);
}

void Network::timelyHandler()
{
    serverSendData(t_data, t_ip, t_port);
    t.start(t_time);
}

void Network::stopTimely()
{
    t.stop();
}

 void Network::start_tcpConnect(QString ip, qint32 port)
 {
    if(!tcpsocketState)
    {
        tcpsocket->connectToHost(ip, port);
        if(tcpsocket->waitForConnected(3000))
        {
            qDebug() << "connect success";
            tcpsocketState = true;
            emit tcpConnectedSuccessSignal();
        }
        else
        {
            qDebug() << "connect failed";
            emit tcpConnectFailedSignal();
            return;
        }
    }
 }

 void Network::stop_tcpConnect()
 {
    tcpsocket->close();
    tcpsocketState = false;
 }

 void Network::tcpConnectedSlot()
 {
    qDebug() << "connect";
 }

 void Network::tcpDisconnectedSlot()
 {
    qDebug() << "disconnect";
 }

 void Network::tcpReadyReadSlot()
 {
    QByteArray dataBa = tcpsocket->readAll();
    QString dataStr = QString::fromLocal8Bit(dataBa);
    QString ip = tcpsocket->peerAddress().toString();
    qint32 port = tcpsocket->peerPort();
    emit tcpReadyReadSignal(dataStr, ip, port);
 }

 void Network::udpReadyReadSlot()
 {
     QHostAddress ipHost;
     quint16 port;
     QByteArray str;
     qint64 size = udpsocket->bytesAvailable();
     str.resize(size);
     qint32 len = udpsocket->readDatagram(str.data(), size, &ipHost, &port);
     if(len <= 0)
         return;
     QString data = QString::fromLocal8Bit(str.data());
     qDebug() << data;
     emit udpReadyReadSignal(data, ipHost.toString(), (qint32)port);
 }

 void Network::tcpSendData(const QByteArray& message)
 {
     tcpsocket->write(message);
 }

 void Network::start_udpConnect(QString ip, qint32 port)
 {
    udpsocket->bind(port);
    emit udpBindSuccessSignal();
 }

 void Network::stop_udpConnect()
 {
     udpsocket->close();
 }

 void Network::udpSendData(const QByteArray &message, QString ip, qint32 port)
 {
     udpsocket->writeDatagram(message, QHostAddress(ip), port);
 }
