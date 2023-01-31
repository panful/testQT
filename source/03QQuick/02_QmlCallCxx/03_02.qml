
/*
import QtQuick 2.6
import QtQuick.Window 2.2
 
import MyTestV 2.0

Window {
    visible: true
    width: 160
    height: 480
    title: qsTr("Hello World")
    color: "black"
    Column{
        width: parent.width
        height: parent.height
        spacing: 0
            Rectangle {
                id:top1
                color: "red";
                width:parent.height/3; height: parent.height/3;
                radius:  parent.height/6;
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //DATAMGR._txt = "top area is clicked";
                        DATAMGR.info();
                    }
                }
                Text {
                    id: top1txt
                    //text: DATAMGR._txt;
                    text: "test TEXT";
                    anchors.centerIn: parent;
                }
            }
 
            Rectangle {
                id:top2
                color: "green";
                width:parent.height/3; height: parent.height/3;
                radius:  parent.height/6;
            }
 
            Rectangle {
                color: "blue";
                width:parent.height/3; height: parent.height/3;
                radius:  parent.height/6;
            }
    }
}
*/


import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Window{
    visible: true
    width: 600
    height: 600
    title: "test"

    MouseArea{
        anchors.fill:parent
        onClicked: {
            menu.open()
        }
    }


    Menu{
        id:menu

        MenuItem{
            width:50
            height:50
            text:"menu1"

            MouseArea{
                anchors.fill:parent
                onClicked: {
                    menu2.open()
                }
            }
        }

        MenuItem{
            width:50
            height:50
            text:"menu2"
        }

        MenuItem{
            width:50
            height:50
            text:"menu3"
        }
    }

    Menu{
        id:menu2

        MenuItem{
            x:150
            y:50
            width:80
            height:50
            text:"menu1_1"
        }

        MenuItem{
            x:150
            y:50
            width:80
            height:50
            text:"menu1_2"
        }

        MenuItem{
            x:150
            y:50
            width:80
            height:50
            text:"menu1_3"
        }
    }

}