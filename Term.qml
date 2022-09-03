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
            width: 150
            title: "id Потока"
            role: "row"
        }
        TableViewColumn {
            width: 480
            title: "Последовательность"
            role: "query"
        }
        TableViewColumn {
            width: 120
            title: "Status"
            role: "status"
        }
    }


