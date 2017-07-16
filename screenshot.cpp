#include "screenshot.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QDir>

ScreenShot::ScreenShot()
{
    m_source = "";
    m_isStopped = true;
    m_counter = 1;
}

void ScreenShot::startTranslation()
{
    QTimer::singleShot(1000, this, &ScreenShot::getBottomImage);
}

void ScreenShot::getBottomImage()
{
    if (m_isStopped) {
        return;
    }

    const QString format = "png";
    m_source = tr("d:/screenshot/screenshot%1").arg(m_counter) + tr(".") + format;
    qDebug() << "m_source = " << m_source;
    if (QFileInfo::exists(m_source)) {
        qDebug() << "File exist";
        m_counter++;
        emit bottomImageRecieved();
    } else {
        qDebug() << "File does not exist: " + m_source;
    }
    QTimer::singleShot(500, this, &ScreenShot::getBottomImage);
}

void ScreenShot::copyFilesToProperFolder() const
{
    //May look for better recourcive way
    QString filePathFrom = tr("D:/screenshot/");
    QString filePathFolder = tr("D:/save/");
    QDir dirFrom(filePathFrom);
    QDir dirToFolder(filePathFolder);

    if (!dirToFolder.exists()) {
        QDir dir1("D:/");
        dir1.mkdir("save");
    }

    QString newDir = tr("D:/save/%1").arg(QDate::currentDate().toString());
    QDir dirTo(newDir);

    //Make a way to save to folder of current time

    if (!dirTo.exists()) {
        QDir dir1("D:/save/");
        dir1.mkdir(QDate::currentDate().toString());
    }

    dirFrom.setNameFilters(QStringList() << "*.*");
    dirFrom.setFilter(QDir::Files);

    foreach(QString dirFile, dirFrom.entryList())
    {
        QString newFilePath = newDir + "/" + dirFile;
        QString oldFilePath = filePathFrom + dirFile;
        if (QFile::copy(oldFilePath, newFilePath)) {
            qDebug() << "Successful copy";
        } else {
            qDebug() << "Unsuccessful copy";
        }
    }
}

bool ScreenShot::isStopped() const
{
    return m_isStopped;
}

void ScreenShot::setIsStopped(bool isStopped)
{
    if (m_isStopped == isStopped)
        return;

    m_isStopped = isStopped;
    emit isStoppedChanged(m_isStopped);
}

QString ScreenShot::source()
{
    return m_source;
}
