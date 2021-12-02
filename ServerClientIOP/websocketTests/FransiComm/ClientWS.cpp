#include "ClientWS.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
}
//! [constructor]

//! [onConnected]
void EchoClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
//    connect(&m_webSocket, &QWebSocket::textMessageReceived,
//            this, &EchoClient::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &EchoClient::onTextMessageReceived);
    //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));

    QByteArray message = QByteArray::number(442, 16).toUpper();

    qDebug() << "Sent:" << 442 << "by HEX message" << message;

    m_webSocket.sendBinaryMessage(message);


}
//! [onConnected]

//! [onTextMessageReceived]
void EchoClient::onTextMessageReceived(QByteArray message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    //m_webSocket.close();
}
//! [onTextMessageReceived]

EchoClient::~EchoClient()
{
    m_webSocket.close();
}
