import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.2

    TableView {
        anchors.margins: 10
        anchors.fill: parent
//        clip: true

        TableViewColumn {
            width: 100
            title: "№ Потока"
            role: "id"
        }
        TableViewColumn {
            width: 350
            title: "Последовательность"
            role: "sequence"
        }
        TableViewColumn {
            width: 150
            title: "Начало вхождения"
            role: "begin_sequence"
        }

        TableViewColumn {
            width: 150
            title: "Время обнаружения"
            role: "dataTime"
        }
    }
