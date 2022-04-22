#include "manager.h"
#include <QDebug>
#include <QFile>
#include <QBuffer>
#include <QImageWriter>

Manager::Manager(QString url, QObject *parent) :
    QObject(parent)
{
    m_imageUrl = url;
    m_instanceDownloader = new FileDownloader(m_imageUrl);

    connect(m_instanceDownloader, SIGNAL (downloaded()), this, SLOT (saveDownloadFile()));
}

Manager::~Manager()
{
    delete m_instanceDownloader;
}

void Manager::loadImage()
{
    qDebug()<<"data downloaded";
    m_image.loadFromData(m_instanceDownloader->downloadedData());
}

void Manager::saveDownloadFile()
{
    qDebug()<<"data downloaded";
    //Save File

    QString filename= "hola.png";
    QImage image = QImage::fromData(m_instanceDownloader->downloadedData(), "png");
                image = image.scaled(10000, 10000, Qt::AspectRatioMode::KeepAspectRatio);

    QImageWriter imageMetadata(filename, "png");
    bool result = false;
    if (imageMetadata.canWrite())
    {
        result = imageMetadata.write(image);
    }

    if (result)
    {
        qDebug()<<"data save in file: "<<filename;
    }
    else
    {
        qDebug()<<"file not saved";
    }


}
