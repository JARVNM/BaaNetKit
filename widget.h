#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QDir>
#include "network/network.h"
#include <QIcon>
#include <QPixmap>
#include <QMap>
#include <QTime>
#include <QScreen>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QBitmap>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void tbtnMinClick();
    void tbtnCloseClick();

    //mode
    void btnTcpServerClickedSlot();
    void btnTcpClinetClickedSlot();
    void btnUdpClickedSlot();

    void btnTcpServerSendClearClickedSlot();
    void btnTcpServerAcceptClearClickedSlot();
    void btnTcpServerStartEndClickedSlot();

    void tcpserverListenSuccessedSlot();
    void tcpserverListenFailedSlot();
    void tcpserverNewConnectionSlot(QMap<QString, qint32> map);
    void tcpserverReadyReadSlot(QString data, QString ip, qint32 port);
    void tcpserverDisconnectedSlot(QMap<QString, qint32> map);

    void btnTcpserverSendClickedSlot();
    void cbSendTimelyStatusChangeSlot();

    void btnTcpConnectClickedSlot();
    void btnTcpDisconnectClickedSlot();
    void tcpConnectedSuccessSlot();
    void tcpConnectFailedSlot();
    void tcpReadyReadSlot(QString data, QString ip, qint32 port);
    void btnTcpSendClearClickedSlot();
    void btnTcpAcceptClearClickedSlot();
    void btnTcpSendClickedSlot();

    void udpReadyReadSlot(QString data, QString ip, qint32 port);
    void udpBindSuccessedSlot();
    void btnUdpBindClickedSlot();
    void btnUdpUnbindClickedSlot();
    void btnUdpSendClickedSlot();
    void btnUdpJoinMulticastClickedSlot();
    void btnUdpAcceptClearClickedSlot();
    void btnUdpSendClearClickedSlot();
private:
    Network network;
    void widget_ui_init();
    void signal_slot_connect();
    void update_local_ip();
    QString getStr2Hex(QString str);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
