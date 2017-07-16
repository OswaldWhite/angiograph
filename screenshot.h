#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>
#include <QFileInfo>

class ScreenShot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isStopped READ isStopped WRITE setIsStopped NOTIFY isStoppedChanged)
    Q_PROPERTY(QString m_source READ source NOTIFY sourceChanged)


public:
    explicit ScreenShot();

public slots:
    Q_INVOKABLE void startTranslation();
    Q_INVOKABLE QString source();
    void getBottomImage() ;
    Q_INVOKABLE void copyFilesToProperFolder() const;
    bool isStopped() const;
    Q_INVOKABLE void setIsStopped(bool isStopped);

signals:
    void bottomImageRecieved();
    void topImageRecieved();
    void sourceChanged();
    void isStoppedChanged(bool isStopped);

private:
    QString m_source;
    bool m_isStopped;
    int m_counter;
};

#endif // SCREENSHOT_H
