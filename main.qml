import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.2
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: app
    visible: true
    width: 780
    height: 600
    title: qsTr("STC")

    property int _occupiedSpace: 0

    Connections{
        target: appCore

        onOccupiedSpaceChanged:{
            _occupiedSpace = m_occupiedSpace
//            console.log("_occupiedSpace:", _occupiedSpace );
        }
    }

    RowLayout {
        id: rowLayout3

        width: app.width
        height: Math.min(app.width, app.height)

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
                from: 4
                to: 1000000000
                stepSize: 100
                editable: true

                Layout.row: 0
                Layout.column: 1
                Layout.fillWidth: true
            }

            Label {
                id: label_size_query
                text: qsTr("Размер Запроса: ")
                Layout.row: 1
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_size_query
                from: 2
                to: 1000
                stepSize: 1
                editable: true

                Layout.row: 1
                Layout.column: 1
                Layout.fillWidth:  true
            }


            Label {
                id: label_max_data
                text: qsTr("Макс. зн. данных: ")
                Layout.row: 2
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_max_data
                from: 5
                to: 100
                stepSize: 1
                editable: true

                Layout.row: 2
                Layout.column: 1
                Layout.fillWidth:  true

            }

            Label {
                id: label_speed_data
                text: qsTr("Скорость генерации данных: ")
                Layout.row: 3
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_speed_data
                from: 100
                to: 100000000
                stepSize: 1
                editable: true

                Layout.row: 3
                Layout.column: 1
                Layout.fillWidth:  true

                //                Layout.rowSpan: 1
                //                Layout.columnSpan: 2
            }

            Label {
                id: label_speed_query
                text: qsTr("Скорость генерации запросов: ")
                Layout.row: 4
                Layout.column: 0
                font.pointSize: 15
                //                Layout.columnSpan: 2
            }
            SpinBox {
                id: spinBox_speed_query
                from: 1000
                to: 100000
                stepSize: 1
                editable: true

                Layout.row: 4
                Layout.column: 1
                Layout.fillWidth:  true

                //                Layout.columnSpan: 2
            }

            Button {
                text: "Запустить"
                Layout.fillWidth: true
                Layout.row: 0
                Layout.column: 3
                Layout.rowSpan: 2
                Layout.fillHeight:  true
                //                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                    if (this.text === "Запустить") {
                        this.text = "Остановить"

                        appCore._size_buffer     = spinBox_size_buffer.value
                        appCore._size_query      = spinBox_size_query.value
                        appCore._max_value       = spinBox_max_data.value
                        appCore._speed_data      = spinBox_speed_data.value

                        appCore.on_click_buffer()
                        add_query.enabled = true
                    }
                    else {
                        this.text = "Запустить"
                        add_query.enabled = false
                        appCore.on_click_buffer_stop()
                    }
                }
            }

            Button {
                text: "Показать график"
                Layout.fillWidth: true
                Layout.row: 2
                Layout.column: 3
                Layout.rowSpan: 2
                Layout.fillHeight:  true
                //                Layout.minimumWidth: 88

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {

                    if (chart.visible === true) {
                        chart.visible = false
                        app.width -= chart.width
                    }
                    else {
                        chart.visible = true
                        app.width += chart.width
                    }

                    this.text === "Показать график" ? this.text = "Спрятать график" : this.text = "Показать график"

                }
            }

            Button {
                id: add_query
                text: "Добавить запрос"
                enabled: false
                Layout.fillWidth: true
                Layout.row: 4
                Layout.column: 3
                Layout.rowSpan: 2
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
                    appCore._speed_query = spinBox_speed_query.value
                    appCore.on_click_consumer()
                }
            }

            Rectangle {
                id: term
                width: 300
                height: 300

                Layout.row: 6
                Layout.column: 0
                Layout.columnSpan: 4


                border.color: "gray"
                color: "#cccccc"
                radius: 15
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight:  true

                ListModel {
                    id: dataModel
                }
                Term{
                    id: termDisplay
                }
            }
            Chart{
                id: chart
                visible: false
                width: 300
                height: 300
                Layout.row: 0
                Layout.column: 4
                Layout.rowSpan: 7

                Layout.fillWidth: true
                Layout.fillHeight:  true
            }
        }
    }
}
