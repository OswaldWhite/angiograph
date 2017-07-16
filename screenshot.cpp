#include "screenshot.h"
#include <QDebug>
#include <QTimer>

ScreenShot::ScreenShot()
{
    m_source = "";
    m_isStopped = true;
    m_counter = 0;
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

void ScreenShot::copyFileToProperFolder() const
{

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
