import QtQuick 2.0
import SceneGraphRendering 1.0

Item {
    width: 400
    height: 400

    // The checkers background
    //ShaderEffect {
    //    id: tileBackground
    //    anchors.fill: parent
    //
    //    property real tileSize: 16
    //    property color color1: Qt.rgba(0.9, 0.9, 0.9, 1);
    //    property color color2: Qt.rgba(0.85, 0.85, 0.85, 1);
    //
    //    property size pixelSize: Qt.size(width / tileSize, height / tileSize);
    //
    //    fragmentShader: "qrc:/scenegraph/fboitem/shaders/checker.frag.qsb"
    //}

    MyRenderer {
        id: renderer
        anchors.fill: parent
        anchors.margins: 10

        // The transform is just to show something interesting..
        transform: [
            Rotation { id: rotation; axis.x: 0; axis.z: 0; axis.y: 1; angle: 0; origin.x: renderer.width / 2; origin.y: renderer.height / 2; },
            Translate { id: txOut; x: -renderer.width / 2; y: -renderer.height / 2 },
            Scale { id: scale; },
            Translate { id: txIn; x: renderer.width / 2; y: renderer.height / 2 }
        ]
    }

    // Just to show something interesting
    SequentialAnimation {
        PauseAnimation { duration: 5000 }
        ParallelAnimation {
            NumberAnimation { target: scale; property: "xScale"; to: 0.6; duration: 1000; easing.type: Easing.InOutBack }
            NumberAnimation { target: scale; property: "yScale"; to: 0.6; duration: 1000; easing.type: Easing.InOutBack }
        }
        NumberAnimation { target: rotation; property: "angle"; to: 80; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: rotation; property: "angle"; to: -80; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: rotation; property: "angle"; to: 0; duration: 1000; easing.type: Easing.InOutCubic }
        NumberAnimation { target: renderer; property: "opacity"; to: 0.5; duration: 1000; easing.type: Easing.InOutCubic }
        PauseAnimation { duration: 1000 }
        NumberAnimation { target: renderer; property: "opacity"; to: 0.8; duration: 1000; easing.type: Easing.InOutCubic }
        ParallelAnimation {
            NumberAnimation { target: scale; property: "xScale"; to: 1; duration: 1000; easing.type: Easing.InOutBack }
            NumberAnimation { target: scale; property: "yScale"; to: 1; duration: 1000; easing.type: Easing.InOutBack }
        }
        running: true
        loops: Animation.Infinite
    }

    Rectangle {
        id: labelFrame
        anchors.margins: -10
        radius: 5
        color: "white"
        border.color: "black"
        opacity: 0.8
        anchors.fill: label
    }

    Text {
        id: label
        anchors.bottom: renderer.bottom
        anchors.left: renderer.left
        anchors.right: renderer.right
        anchors.margins: 20
        wrapMode: Text.WordWrap
        text: "The blue rectangle with the vintage 'Q' is an FBO, rendered by the application on the scene graph rendering thread. The FBO is managed and displayed using the QQuickFramebufferObject convenience class."
    }


}
