import QtQuick.Window 2.12
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: app
    visible: true
    width: 800
    height: 500
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("STC")

    RowLayout {
        id: rowLayout3

        anchors.fill: parent
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top:  parent.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        GridLayout {
            id: gridButton
            width: 335
            Layout.minimumWidth: 335

            Layout.fillWidth:  true
            Layout.fillHeight: true

            Label {
                id: label_size_buffer
                text: qsTr("Размер Буфера: ")
                Layout.fillWidth: true

                Layout.row: 0
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_size_buffer
                from: 0
                to: 99
                stepSize: 1
                editable: true

                Layout.row: 0
                Layout.column: 1
            }

            Label {
                id: label_size_query
                text: qsTr("Размер Запроса: ")
                Layout.row: 0
                Layout.column: 2
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_size_query
                from: 0
                to: 99
                stepSize: 1
                editable: true

                Layout.row: 0
                Layout.column: 3
            }

            Label {
                id: label_max_data
                text: qsTr("Макс. зн. данных: ")
                Layout.row: 1
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_max_data
                from: 0
                to: 99
                stepSize: 1
                editable: true

                Layout.row: 1
                Layout.column: 1
            }

            Label {
                id: label_speed_query
                text: qsTr("Скорость создания запросов: ")
                Layout.row: 1
                Layout.column: 2
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_speed_query
                from: 0
                to: 99
                stepSize: 1
                editable: true

                Layout.row: 1
                Layout.column: 3
//                Layout.rowSpan: 1
//                Layout.columnSpan: 2
            }


            Button {
                text: "Запустить"
                Layout.fillWidth: true
                Layout.row: 2
                Layout.column: 0
                Layout.columnSpan: 2
//                Layout.fillHeight:  true
//                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {

                }
            }

            Button {
                text: "Остановить"
                Layout.fillWidth: true
                Layout.row: 2
                Layout.column: 2
                Layout.columnSpan: 2
//                Layout.fillHeight:  true
//                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                }
            }

            Button {
                text: "Показать график"
                Layout.fillWidth: true
                Layout.row: 3
                Layout.column: 0
                Layout.columnSpan: 2
//                Layout.fillHeight:  true
//                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                }
            }

            Button {
                text: "Добавить запрос"
                Layout.fillWidth: true
                Layout.row: 3
                Layout.column: 2
                Layout.columnSpan: 2
//                Layout.fillHeight:  true
//                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                }
            }


//            Button {
//                text: "Показать график"
//                Layout.fillWidth: true
//                Layout.row: 3
//                Layout.column: 3
//                Layout.fillHeight:  true
//                width: 88
//                Layout.minimumWidth: 88

//                font.pointSize: 15
//                background: Rectangle {
//                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
//                    border.color: "#26282a"
//                    border.width: 2
//                    radius: 15
//                }
//                onClicked: {
//                }
//            }
//            Button {
//                text: "Добавить запрос"
//                Layout.minimumWidth: 87
//                Layout.row: 4
//                Layout.column: 0
//                Layout.fillWidth: true
//                Layout.fillHeight:  true
//                font.pointSize: 15
//                background: Rectangle {
//                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
//                    border.color: "#26282a"
//                    border.width: 2
//                    radius: 15
//                }
//                onClicked: {

//                }
//            }
        }
    }



    //    ColumnLayout {
    //        x: 10
    //        y: 10

    //        RowLayout {
    //            Label {
    //                text: qsTr("Размер Буфера:")
    //            }
    //            SpinBox {
    //                id: size_buffer
    //            }
    //            Label {
    //                text: qsTr("Размер запросов:")
    //            }
    //            SpinBox {
    //                id: size_query
    //            }
    //        }

    //        RowLayout {
    //            Label {
    //                text: qsTr("Макс. зн. данных:")
    //            }
    //            SpinBox {
    //                id: max_data
    //            }
    //            Label {
    //                text: qsTr("Скорость заполнения:")
    //            }
    //            SpinBox {
    //                id: speed_buffer
    //            }

    //        }

    //        Button {
    //            text: "Запустить"
    //            Layout.fillWidth: true
    //            Layout.row: 1
    //            Layout.column: 3
    //            Layout.fillHeight:  true
    //            Layout.minimumWidth: 88

    //            font.pointSize: 15
    //            background: Rectangle {
    //                color: parent.down ? "#d7d7d7" : "#f7f7f7"
    //                border.color: "#26282a"
    //                border.width: 2
    //                radius: 15
    //            }
    //            onClicked: {
    //            }
    //        }
    //    }
}
