#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    widget_ui_init();
    signal_slot_connect();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
//    QBitmap bmp(this->size());
//    bmp.fill();
//    QPainter painter(&bmp);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(Qt::white);
//    painter.setBrush(QColor(0, 255, 255));
//    painter.drawRoundedRect(bmp.rect(), 20, 20);
//    setMask(bmp);


/*    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(255, 255, 255)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 20, 20)*/;
}

void Widget::widget_ui_init()
{
    QScreen* screen = QApplication::screens().at(0);
    QSize scrSize = screen->size();
//    qDebug() << scrSize;
    qint32 width = scrSize.width();
    qint32 length = scrSize.height();
    qint32 x = width / 2 - (width / 4);
    qint32 y = length / 2 - (length * 0.3);
    //window
    this->setWindowTitle("BaaNetKit");
    this->setGeometry(x, y, width * 0.5, length * 0.6);
    this->setFixedSize(width * 0.48, length *0.6);
    this->setWindowIcon(QIcon(QPixmap(":/logo.png")));
    QApplication::setWindowIcon(QIcon(QPixmap(":/icon.jpg")));
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->stackedWidget->setCurrentIndex(0);
    ui->btnClose->setFlat(true);
    ui->btnMin->setFlat(true);
    ui->btnClose->setText("");
    ui->btnMin->setText("");


    //server
    ui->btnTcpServer->setText("TCP服务器");
    ui->btnTcpServer->setCheckable(true);
    ui->btnTcpClient->setText("TCP客户端");
    ui->btnTcpClient->setCheckable(true);
    ui->btnUdp->setText("UDP连接");
    ui->btnUdp->setCheckable(true);

    ui->labLocalIp->setText("本地IP");
    ui->labLocalPort->setText("本地端口");

    ui->btnBeginListen->setText("开始监听");
    ui->btnStopListen->setText("关闭监听");
    ui->btnStopListen->setEnabled(false);

    ui->labConntionCount->setText("未连接");
    ui->labChoseClient->setText("选择客户端");
    ui->labClientInfo->setText("客户端");

    ui->labSendSpace->setText("发送区");
    ui->cbSendTimly->setText("定时发送");
    ui->labMs->setText("ms");

    ui->btnServerSend->setText("发送");
    ui->btnSendBrodcast->setText("广播发送");
    ui->cbServerSendHex->setText("16进制");
    ui->btnServerSendClear->setText("清除");
    ui->cbServerFrontLen->setText("长度前缀");
    ui->cbServerEndSign->setText("符号后缀");

    ui->labAcceptSpace->setText("接收区");
    ui->btnServerAcceptClear->setText("清除");
    ui->cbServerAcceptHex->setText("16进制");
    ui->cbServerAcceptIp->setText("显示IP");
    ui->cbServerAcceptPort->setText("显示端口");
    ui->cbServerAcceptTime->setText("显示时间");

    ui->sbTime->setValue(1000);

    QPixmap iconMap(":/icon.jpg");
    iconMap = iconMap.scaled(100, 100);
    ui->labIcon->setPixmap(iconMap);
    ui->labTitle->setText("BaaNetKit");

    //tcp client
    ui->labTcpDstIp->setText("服务器IP");
    ui->labTcpDstPort->setText("服务器端口");
    ui->btnTcpConnect->setText("连接");
    ui->btnTcpDisconnect->setText("断开连接");
    ui->labTcpTip->setText("提示：服务器断开连接");
    ui->labTcpInfo->setText("连接信息");
    ui->labTcpSendSpace->setText("发送区");
    ui->btnTcpSend->setText("发送");
    ui->cbTcpSendTimely->setText("定时发送");
    ui->sbTcpTime->setValue(1000);
    ui->labTcpMs->setText("ms");
    ui->cbTcpSendHex->setText("16进制");
    ui->cbTcpSendFrontLen->setText("长度前缀");
    ui->cbTcpSendDivSign->setText("尾部分隔");
    ui->btnTcpSendClear->setText("清空");
    ui->labTcpAcceptSpace->setText("接收区");
    ui->cbTcpAcceptHex->setText("16进制");
    ui->cbTcpAcceptIp->setText("显示IP");
    ui->cbTcpAcceptPort->setText("显示端口");
    ui->cbTcpAcceptTime->setText("显示时间");
    ui->btnTcpAcceptClear->setText("清空");

    //udp
    ui->labUdpLocalIp->setText("本地IP");
    ui->labUdpLocalPort->setText("本地端口");
    ui->btnUdpBind->setText("开始绑定");
    ui->btnUdpUnbind->setText("结束绑定");
    ui->btnUdpUnbind->setEnabled(false);
    ui->labUdpTip->setText("未绑定端口");
    ui->labUdpDstIp->setText("目标IP");
    ui->labUdpDstPort->setText("目标端口");
    ui->labUdpGroupIp->setText("绑定组IP");
    ui->btnUdpGroupSend->setText("绑定组");
    ui->labUdpAbout->setText("友情提示");
    ui->labUdpSendSpace->setText("发送区");
    ui->cbUdpSendTimely->setText("定时发送");
    ui->sbUdpTimely->setValue(1000);
    ui->btnUdpSend->setText("发送");
    ui->btnUdpGroupSend->setText("广播发送");
    ui->cbUdpSendHex->setText("16进制");
    ui->cbUdpFrontLen->setText("长度前缀");
    ui->cbUdpEndSign->setText("符号后缀");
    ui->btnUdpSendClear->setText("清空");
    ui->labAcceptSpace->setText("接收区");
    ui->cbUdpAcceptPort->setText("显示端口");
    ui->cbUdpAcceptIp->setText("显示IP");
    ui->cbUdpAcceptHex->setText("16进制");
    ui->cbUdpAcceptTime->setText("显示时间");
    ui->btnUdpAcceptClear->setText("清空");
    ui->labUdpMs->setText("ms");
    ui->labUdpAcceptSpace->setText("发送区");
    ui->btnUdpJoinMulticastGroup->setText("加入组播");
    update_local_ip();
}

void Widget::signal_slot_connect()
{
    connect(ui->btnMin, &QPushButton::clicked, this, &Widget::tbtnMinClick);
    connect(ui->btnClose, &QPushButton::clicked, this, &Widget::tbtnCloseClick);

    connect(ui->btnTcpServer, &QPushButton::clicked, this, &Widget::btnTcpServerClickedSlot);
    connect(ui->btnTcpClient, &QPushButton::clicked, this, &Widget::btnTcpClinetClickedSlot);
    connect(ui->btnUdp, &QPushButton::clicked, this, &Widget::btnUdpClickedSlot);

    connect(ui->btnServerAcceptClear, &QPushButton::clicked, this, &Widget::btnTcpServerAcceptClearClickedSlot);
    connect(ui->btnServerSendClear, &QPushButton::clicked, this, &Widget::btnTcpServerSendClearClickedSlot);

    connect(ui->btnBeginListen, &QPushButton::clicked, this, &Widget::btnTcpServerStartEndClickedSlot);
    connect(ui->btnStopListen, &QPushButton::clicked, this, &Widget::btnTcpServerStartEndClickedSlot);
    connect(&this->network, &Network::serverListenSuccessedSignal, this, &Widget::tcpserverListenSuccessedSlot);
    connect(&this->network, &Network::serverListenFailedSignal, this, &Widget::tcpserverListenFailedSlot);
    connect(&this->network, &Network::newConnectionSignal, this, &Widget::tcpserverNewConnectionSlot);

    connect(&this->network, &Network::serverReadyReadSignal, this, &Widget::tcpserverReadyReadSlot);
    connect(&this->network, &Network::disconnectedSignal, this, &Widget::tcpserverDisconnectedSlot);
    connect(ui->btnServerSend, &QPushButton::clicked, this, &Widget::btnTcpserverSendClickedSlot);
    connect(ui->cbSendTimly, &QCheckBox::stateChanged, this, &Widget::cbSendTimelyStatusChangeSlot);

    //tcp
    connect(ui->btnTcpConnect, &QPushButton::clicked, this, &Widget::btnTcpConnectClickedSlot);
    connect(&network, &Network::tcpConnectedSuccessSignal, this, &Widget::tcpConnectedSuccessSlot);
    connect(&network, &Network::tcpConnectFailedSignal, this, &Widget::tcpConnectFailedSlot);
    connect(ui->btnTcpDisconnect, &QPushButton::clicked, this, &Widget::btnTcpDisconnectClickedSlot);
    connect(&network, &Network::tcpReadyReadSignal, this, &Widget::tcpReadyReadSlot);
    connect(ui->btnTcpSend, &QPushButton::clicked, this, &Widget::btnTcpSendClickedSlot);

    //udp
    connect(ui->btnUdpBind, &QPushButton::clicked, this, &Widget::btnUdpBindClickedSlot);
    connect(ui->btnUdpUnbind, &QPushButton::clicked, this, &Widget::btnUdpUnbindClickedSlot);
    connect(ui->btnUdpSend, &QPushButton::clicked, this, &Widget::btnUdpSendClickedSlot);
    connect(&network, &Network::udpBindSuccessSignal, this, &Widget::udpBindSuccessedSlot);
    connect(&network, &Network::udpReadyReadSignal, this, &Widget::udpReadyReadSlot);
    connect(ui->btnUdpSendClear, &QPushButton::clicked, this, &Widget::btnUdpSendClearClickedSlot);
    connect(ui->btnUdpAcceptClear, &QPushButton::clicked, this, &Widget::btnUdpAcceptClearClickedSlot);
}

void Widget::update_local_ip()
{
    QStringList addressStrList = network.getLocalIp();
    ui->cbLocalIp->clear();
    ui->cbLocalIp->addItem("0.0.0.0");
    ui->cbLocalIp->addItems(addressStrList);
    ui->cbUdpIp->clear();
    ui->cbUdpIp->addItem("0.0.0.0");
    ui->cbUdpIp->addItems(addressStrList);
}

//private slots
void Widget::tbtnMinClick()
{
    qDebug() << "min click";
    this->showMinimized();
}

void Widget::tbtnCloseClick()
{
    qDebug() << "close click";
    this->close();
}

void Widget::btnTcpServerClickedSlot()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->btnTcpServer->setChecked(true);
    ui->btnTcpClient->setChecked(false);
    ui->btnUdp->setChecked(false);
}

void Widget::btnTcpClinetClickedSlot()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->btnTcpServer->setChecked(false);
    ui->btnTcpClient->setChecked(true);
    ui->btnUdp->setChecked(false);
}

void Widget::btnUdpClickedSlot()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->btnTcpServer->setChecked(false);
    ui->btnTcpClient->setChecked(false);
    ui->btnUdp->setChecked(true);
//    ui->btnUdp->setStyleSheet("background-color: rgb(0, 108, 255);");

}

void Widget::btnTcpServerSendClearClickedSlot()
{
    ui->tbServerSend->clear();
}

void Widget::btnTcpServerAcceptClearClickedSlot()
{
    ui->tbServerAccept->clear();
}

void Widget::btnTcpServerStartEndClickedSlot()
{
    QAbstractButton* btn = (QAbstractButton*)sender();

    if(btn->objectName() == "btnBeginListen")//begin
    {
        QString ip = ui->cbLocalIp->currentText();
        qint32 port = ui->sbLocalPort->value();
        network.start_tcpserver(ip, port);
    }
    else
    {
        network.stop_tcpserver();
        ui->btnBeginListen->setEnabled(true);
        ui->btnStopListen->setEnabled(false);
        ui->cbLocalIp->setEnabled(true);
        ui->sbLocalPort->setEnabled(true);
    }
}

void Widget::tcpserverListenFailedSlot()
{
    ui->labConntionCount->setText("监听失败");
}

void Widget::tcpserverListenSuccessedSlot()
{
    ui->labConntionCount->setText("监听成功");
    ui->tbClientInfo->clear();
    ui->tbClientInfo->append("已连接上服务器的设备有：");
    ui->btnBeginListen->setEnabled(false);
    ui->btnStopListen->setEnabled(true);
    ui->cbLocalIp->setEnabled(false);
    ui->sbLocalPort->setEnabled(false);
}

void Widget::tcpserverNewConnectionSlot(QMap<QString, qint32> map)
{
    //qDebug() << "new connection slot";
    // QString infocnt = QString("已连接设备%1个").arg(cnt);
    // ui->labConntionCount->setText(infocnt);
    // ui->tbClientInfo->append(QString("设备%1(%2)").arg(cnt).arg(info));
    // //ui->cbChoseClient->insertItem(0, info);
    // ui->cbChoseClient->addItem(info);
    QMap<QString, qint32>::const_iterator i = map.constBegin();
    ui->tbClientInfo->clear();
    ui->cbChoseClient->clear();
    ui->tbClientInfo->append("已连接上服务器的设备有：");
    int ii = 1;
    while(i != map.constEnd())
    {
        QString addr = i.key();
        qint32 port = i.value();
        QString info_cb = QString("%1").arg(addr);
        QString info_tb = QString("设备%1(%2)").arg(ii).arg(addr);
        ui->tbClientInfo->append(info_tb);
        ui->cbChoseClient->addItem(info_cb);
        ii++;
        ++i;
    }
    ui->labConntionCount->setText(QString("已连接设备%1个").arg(map.size()));
}

void Widget::tcpserverReadyReadSlot(QString data, QString ip, qint32 port)
{
    QString time;
    QString info;
    if(ui->cbServerAcceptTime->isChecked())
        time = QTime::currentTime().toString();
    else
        time = "";

    if(ui->cbServerAcceptHex->isChecked())
        data = getStr2Hex(data);

    if(ui->cbServerAcceptPort->isChecked() && ui->cbServerAcceptIp->isChecked())
        info = QString("(%1:%2)").arg(ip).arg(QString::number(port));
    else if(ui->cbServerAcceptPort->isChecked() && !ui->cbServerAcceptIp->isChecked())
        info  = QString("(%1)").arg(QString::number(port));
    else if(!ui->cbServerAcceptPort->isChecked() && ui->cbServerAcceptIp->isChecked())
        info = QString("(%1)").arg(ip);
    else
        info = "";

    QString data_show = QString("%1\%2").arg(time).arg(info);
    if(data_show.length() != 0)
        data_show += ":" + data;
    else
        data_show += data;
    ui->tbServerAccept->append(data_show);
}

QString Widget::getStr2Hex(QString str)
{
    QString targetStr = "";
    QByteArray bits = str.toLatin1().toHex();
    int len = bits.length() / 2;

    for(int i = 0; i < len; i++)
    {
        targetStr += bits.mid(i * 2, 2) + " ";

    }

    return targetStr;
}

void Widget::tcpserverDisconnectedSlot(QMap<QString, qint32> map)
{
    QString currentInfo = ui->cbChoseClient->currentText();
    ui->cbChoseClient->clear();


    QMap<QString, qint32>::const_iterator i = map.constBegin();
    ui->tbClientInfo->clear();
    ui->cbChoseClient->clear();
    ui->tbClientInfo->append("已连接上服务器的设备有：");
    int ii = 1;
    while(i != map.constEnd())
    {
        QString addr = i.key();
        qint32 port = i.value();
        QString info_cb = QString("%1").arg(addr);
        QString info_tb = QString("设备%1(%2)").arg(ii).arg(addr);
        ui->tbClientInfo->append(info_tb);
        ui->cbChoseClient->addItem(info_cb);
        if(info_cb == currentInfo)
            ui->cbChoseClient->setCurrentText(info_cb);
        ii++;
        ++i;
    }
    ui->labConntionCount->setText(QString("已连接设备%1个").arg(map.size()));
}

void Widget::btnTcpserverSendClickedSlot()
{

    QString info = ui->cbChoseClient->currentText();
    if(info.isEmpty())
        return;
    QStringList ip_port = info.split(":");
    QString ip = ip_port.at(0);
    qint32 port = ip_port.at(1).toInt();
    QString data = ui->tbServerSend->toPlainText();

    if(ui->cbServerSendHex->isChecked())
        data = this->getStr2Hex(data);

    network.serverSendData(data, ip, port);
}

void Widget::cbSendTimelyStatusChangeSlot()
{
    QString info = ui->cbChoseClient->currentText();
    if(info.isEmpty())
        return;
    QStringList list = info.split(":");
    QString ip = list.at(0);
    qint32 port = list.at(1).toInt();
    QString data = ui->tbServerSend->toPlainText();
    if(ui->cbServerSendHex->isChecked())
        data = this->getStr2Hex(data);
    if(ui->cbSendTimly->isChecked())
        network.beginTimely(data, ui->sbTime->value(),
            ip, port);
    else
        network.stopTimely();
}

void Widget::btnTcpConnectClickedSlot()
{
    QString ip = ui->leTcpDstIp->text();
    qint32 port = ui->leTcpDstPort->value();
    network.start_tcpConnect(ip, port);
}

void Widget::btnTcpDisconnectClickedSlot()
{
    network.stop_tcpConnect();
    ui->btnTcpConnect->setEnabled(true);
    ui->btnTcpDisconnect->setEnabled(false);
}

void Widget::tcpConnectedSuccessSlot()
{
    ui->btnTcpConnect->setEnabled(false);
    ui->btnTcpDisconnect->setEnabled(true);
}

void Widget::tcpConnectFailedSlot()
{
    qDebug() << "connect failed";
}

void Widget::tcpReadyReadSlot(QString data, QString ip, qint32 port)
{
    QString time;
    QString info;
    if(ui->cbTcpAcceptTime->isChecked())
        time = QTime::currentTime().toString();
    else
        time = "";
    if(ui->cbTcpAcceptHex->isChecked())
        data = getStr2Hex(data);

    if(ui->cbTcpAcceptPort->isChecked() && ui->cbTcpAcceptIp->isChecked())
        info = QString("(%1:%2)").arg(ip).arg(QString::number(port));
    else if(ui->cbTcpAcceptPort->isChecked() && !ui->cbTcpAcceptIp->isChecked())
        info = QString("(%1)").arg(QString::number(port));
    else if(!ui->cbTcpAcceptPort->isChecked() && ui->cbTcpAcceptIp->isChecked())
        info = QString("(%1)").arg(ip);
    else
        info = "";

    QString data_show = QString("%1\%2").arg(time).arg(info);
    if(data_show.length() != 0)
        data_show += ":" + data;
    else
        data_show += data;

    // ui->tbTcpAccept->insertPlainText(data_show);
    ui->tbTcpAccept->appendPlainText(data_show);
}

void Widget::btnTcpSendClearClickedSlot()
{
    ui->tbTcpSend->clear();
}

void Widget::btnTcpAcceptClearClickedSlot()
{
    ui->tbTcpAccept->clear();
}

void Widget::btnTcpSendClickedSlot()
{
    QString data = ui->tbTcpSend->toPlainText();
    if(data.length() == 0)
        return;
    if(ui->cbTcpSendHex->isChecked())
        data = getStr2Hex(data);

    if(ui->cbTcpSendDivSign->isChecked())
        data += ui->leTcpSendEndSign->text();

    QByteArray message = data.toLocal8Bit();
    QByteArray dataBa;
    QDataStream stream(&dataBa, QIODevice::WriteOnly);
    quint32 messageLength = message.length();
    if(ui->cbTcpSendFrontLen->isChecked())
        stream << messageLength;
    stream.writeRawData(message.constData(), messageLength);
    qDebug() << dataBa;
    network.tcpSendData(dataBa);
}

void Widget::udpReadyReadSlot(QString data, QString ip, qint32 port)
{
    QString time;
    QString info;

    if(ui->cbUdpAcceptTime->isChecked())
        time = QTime::currentTime().toString();
    else
        time = "";

    if(ui->cbUdpAcceptHex->isChecked())
        data = getStr2Hex(data);

    if(ui->cbUdpAcceptPort->isChecked() && ui->cbUdpAcceptIp->isChecked())
        info = QString("(%1:%2)").arg(ip).arg(QString::number(port));
    else if(ui->cbUdpAcceptPort->isChecked() && !ui->cbUdpAcceptIp->isChecked())
        info = QString("(%1)").arg(QString::number(port));
    else if(!ui->cbUdpAcceptPort->isChecked() && ui->cbUdpAcceptIp->isChecked())
        info = QString("(%1").arg(ip);
    else
        info = "";

    QString data_show = QString("%1\%2").arg(time).arg(info);
    if(data_show.length() != 0)
        data_show += ":" + data;
    else
        data_show += data;

    ui->tbUdpAccept->append(data_show);
}

void Widget::udpBindSuccessedSlot()
{
    ui->btnUdpBind->setEnabled(false);
    ui->btnUdpUnbind->setEnabled(true);
}

void Widget::btnUdpBindClickedSlot()
{
    if(ui->sbUdpPort->text().isEmpty())
        return;
    else
    {
        QString ip;
        if(ui->cbUdpIp->currentText().isEmpty())
            ip = QHostAddress::LocalHost;
        else
            ip = ui->cbUdpIp->currentText();
        qint32 port = ui->sbUdpPort->value();
        network.start_udpConnect(ip, port);
    }
}

void Widget::btnUdpUnbindClickedSlot()
{
    ui->btnUdpBind->setEnabled(true);
    ui->btnUdpUnbind->setEnabled(false);
    network.stop_udpConnect();
}

void Widget::btnUdpSendClickedSlot()
{
    if(ui->teUdpSend->toPlainText().isEmpty())
        return;
    QString ip = ui->leUdpDstIp->text();
    qint32 port = ui->sbUdpPort->value();
    QString data = ui->teUdpSend->toPlainText();
    if(ui->cbUdpEndSign->isChecked())
        data += ui->leUdpEndSign->text();
    if(ui->cbUdpSendHex->isChecked())
        data = getStr2Hex(data);
    if(ui->cbUdpFrontLen->isChecked())
    {
        QByteArray message = data.toLocal8Bit();
        QByteArray dataBa;
        QDataStream stream(&dataBa, QIODevice::WriteOnly);
        quint32 messageLength = message.length();
        stream << messageLength;
        stream.writeRawData(message.constData(), messageLength);
        network.udpSendData(dataBa, ip, port);
    }
    else
    {
        QByteArray message = data.toLocal8Bit();
        network.udpSendData(message, ip, port);
    }
}

void Widget::btnUdpJoinMulticastClickedSlot()
{
    QString mulIp = ui->leUdpMulticastIp->text();
    if(mulIp.isEmpty())
        return;


}

void Widget::btnUdpAcceptClearClickedSlot()
{
    ui->tbUdpAccept->clear();
}

void Widget::btnUdpSendClearClickedSlot()
{
    ui->teUdpSend->clear();
}
