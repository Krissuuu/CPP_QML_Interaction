import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.14

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "black"
    title: qsTr("Hello World")

    Button {
        id: viewBtn
        text: "Show"
        width: 120
        height: 40
        onClicked: {
            qmlWindows2.visible = true;
        }
    }

    Button {
        id: changeColorBtn
        text: "changeColor"
        width: 120
        height: 40
        anchors.top: viewBtn.bottom
        anchors.left: viewBtn.left
        anchors.topMargin: 10
        onClicked: {
            qmlWindows2.color = Qt.rgba(Math.random(),
                                       Math.random(),
                                       Math.random(),
                                       1)
        }
    }
}
