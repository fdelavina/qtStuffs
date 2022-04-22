#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QPixmap>
#include "filedownloader.h"

class DOWNLOADSOOLOGIC_EXPORT Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QString url, QObject *parent = 0);
    ~Manager();

private slots:
    void loadImage();
    void saveDownloadFile();
private:
    QUrl m_imageUrl;
    FileDownloader* m_instanceDownloader;
    QPixmap m_image;
};

#endif // MANAGER_H
