import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.15

Window {
    visible: true
    width: 450
    height: 450
    title: qsTr("Test Window")
    color: "green"

    Button {
        text: "TEST1"
        anchors.centerIn: parent
        onClicked: {
            myFunctions.myFunc()  // 调用 C++ 函数
        }
    }
}
