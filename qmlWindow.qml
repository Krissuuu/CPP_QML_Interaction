import QtQuick 2.0
import QtQuick.Controls 2.14

Item{
    property string msg_name: "Kris.Su"
    property int msg_age: 25

    signal qmlSendMsg(string arg1, int arg2)

    id: root
    width: 100
    height: 100

    Rectangle {
        id: rect
        objectName: "rectangle"
        anchors.fill: parent
        color: "green"

        Rectangle {
            id: rect_1
            objectName: "rectangle_1"
            width: 100
            height: 100
            anchors.centerIn: parent
            color: "red"
        }
    }

    Button {
        id: send
        text: "send"
        width: 120
        height: 40
        onClicked: {
            root.qmlSendMsg(msg_name, msg_age)
        }
    }

    function qml_method(val_arg, val_arg2){
        console.log("qml method runing", val_arg, val_arg2)
        return val_arg + val_arg2
    }
    function qmlRecvMsg(arg1, arg2){
        console.log("qml slot runing", arg1, arg2)
    }
}
