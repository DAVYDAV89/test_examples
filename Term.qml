import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.2

    TableView {
        id: view

        anchors.margins: 10
        anchors.fill: parent
        model: dataModel
        clip: true

        TableViewColumn {
            id: _id
            width: 100
            title: "id Потока"
            role: "id"
        }
        TableViewColumn {
            width: 350
            title: "Последовательность"
            role: "sequence"
        }
        TableViewColumn {
            width: 100
            title: "Индекс"
            role: "begin_sequence"
        }

        TableViewColumn {
            width: 150
            title: "Время"
            role: "dataTime"
        }
    }


