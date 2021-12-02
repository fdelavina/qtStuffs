import QtQuick 2.7
//import QtQuick.Controls 2.3 //Qt 5.10
import QtQuick.Controls 2.2 // Qt 5.9

Rectangle {
    id: root
    color: myPalette.window
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    Demo {
        anchors.fill: parent
    }

    /*Rectangle {
        id: lightrect
        z: 10
        anchors.fill: parent
        color: "black"
        opacity: 0
        // opacity: lightsl.value / 100
    }*/
}
