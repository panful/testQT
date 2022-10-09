import QtQuick 2.0
import QtQuick.Window 2.0

//import QtQuick.Controls 1.1
import QtQuick.Controls 2.15

Window{
    visible: true
    width: 450
    height: 450
    title: qsTr("Test Window") //窗口标题
    color: "white"  //窗口背景色，如果铺满整个窗口，就不会显示出来

    Button {
        text: "Quit";
        anchors.centerIn: parent;
        onClicked: {
            Qt.quit();
        }
    }
}
