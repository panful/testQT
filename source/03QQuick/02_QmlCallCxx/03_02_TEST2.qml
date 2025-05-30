import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.15
import MyFunctions 1.0  // 导入 C++ 类型

Window {
    visible: true
    width: 450
    height: 450
    title: qsTr("Test Window")
    color: "green"

    MyFunctions {
        id: myFunctions
    }

    Button {
        text: "TEST2"
        anchors.centerIn: parent
        onClicked: {
            myFunctions.myFunc()  // 调用 C++ 函数
        }
    }
}
