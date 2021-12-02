import QtQuick 2.7
import qmlsymbols 1.0
//import QtQuick.Controls 2.3 //Qt 5.10
import QtQuick.Controls 2.2 // Qt 5.9
import QtQuick.Layouts 1.1

Item {
    id: root

    RowLayout
    {
        anchors.fill: parent

        GaugeCompass {
            id: gaugeCompassCourse
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            // x: 317
            y: 42
            name: "SHIP.course"
        }

        Gauge {
            id: gaugeSpeed
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            // x: 182
            y: 42
            name: "SHIP.speed"
            units: "Kts"
        }
    }
}
