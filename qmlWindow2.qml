import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    width: 500
    height: 500
    visible: false
    color: "gray"
    title: qsTr("Second Window")

    Rectangle {
        id: rec
        objectName: "myRectangle"
        width: 300
        height: 300
        color : "black"
        anchors.centerIn: parent

        Rectangle {
            id: rect_1
            objectName: "myRectangle_1"
            width: 150
            height: 150
            anchors.centerIn: parent
            color: "yellow"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("mouse clicked")
                }
                onPressed: {
                    rect_1.color = "green"
                }
                onReleased: {
                    rect_1.color = "blue"
                }
            }
        }
    }
}
