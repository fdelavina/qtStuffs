#ifndef CLIENTWS_H
#define CLIENTWS_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include "globalLib/Global/globalLib.h"

class FRANSICOMM_EXPORT EchoClient : public QObject
{
    Q_OBJECT
public:
    EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    ~EchoClient();
Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QByteArray message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // ECHOCLIENT_H
