import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import screenshot 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    visibility: "FullScreen"
    title: qsTr("Angiograph")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: headerTabBar.currentIndex
        Page {
            Image {
                id: image
                width: 920
                height: 690
                anchors.left: parent.left

                anchors.top: parent.top

                source: "images/1.PNG"

                transform: [
                    Scale {
                        id: zoomScale
                    },
                    Translate {

                    }
                ]
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.AllButtons
                    onClicked: {
                        var zoomIn = mouse.button === Qt.LeftButton;
                        zoomScale.origin.x = mouse.x;
                        zoomScale.origin.y = mouse.y;
                        zoomScale.xScale = zoomIn ? 3 : 1;
                        zoomScale.yScale = zoomIn ? 3 : 1;
                    }
                }
            }

        }

//        Page {
//            Video {
//        id: video
//        width : 800
//        height : 600
//        source: "video.avi"

//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                video.play()
//            }
//        }

//        focus: true
//        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
//        Keys.onLeftPressed: video.seek(video.position - 5000)
//        Keys.onRightPressed: video.seek(video.position + 5000)
//    }
//        }
    }

    FileDialog {
        id: fileDialog
        title: "Выберите файл"

        folder: "file:///D:/"
        nameFilters: [ "Image files (*.jpg *.png *.bmp)", "All files (*)" ]
        selectMultiple: false
        selectFolder: false
        onAccepted: {
            image.source = fileDialog.fileUrl
            console.log(fileDialog.folder)
        }
    }

    Screenshot {
        id: screenshot

        onBottomImageRecieved: {
            image.source = "file:///" + screenshot.source()
            //screenshotImage.source = "file:///" + screenshot.source()
        }
    }

    header: TabBar {
        id: headerTabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Поток изображений")
        }

//        TabButton {
//            text: qsTr("Просмотреть видео")
//        }
    }

    footer: TabBar {
        id: footerTabBar
        TabButton {
            text: qsTr("Начать трансляцию")
            onClicked: {
                screenshot.setIsStopped(false)
                screenshot.startTranslation()
            }
        }
        TabButton {
            text: qsTr("Остановить трансляцию")
            onClicked: {
                screenshot.setIsStopped(true);
            }
        }
//        TabButton {
//            text: qsTr("Получить скриншот")
//            onClicked: {
//                screenshot.getLastImage()
//            }
//        }
        TabButton {
            text: qsTr("Открыть скриншот")
            onClicked: {
                fileDialog.open()
            }
        }
        TabButton {
            text: qsTr("Выход")
            onClicked: Qt.quit()
        }
    }
}
