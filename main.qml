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
    property int _row: 0
    property int _begin_index_sequence: 0
    property int _size_sequence: 0


    Connections{
        target: appCore

        onOccupiedSpaceChanged:{
            _occupiedSpace = m_occupiedSpace
//            console.log("_occupiedSpace:", _occupiedSpace );
        }
        onShowEquals:{
            _begin_index_sequence = _begin_sequence
            _size_sequence = spinBox_size_query.value
            dataModel.insert(_row++, {id: _id_thread, sequence: _sequence, begin_sequence: _begin_sequence, dataTime: _dateTime})

//            console.log("thread:", _id_thread );
//            console.log("_sequence:", _sequence );
//            console.log("_begin_sequence:", _begin_sequence );
//            console.log("_dateTime:", _dateTime );
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
                from:   500
                to:     500000
                stepSize: 100
                editable: true

                Layout.row: 0
                Layout.column: 1
                Layout.fillWidth: true
            }

            Label {
                id: label_size_data
                text: qsTr("Кол-во данных заполнения буфера в сек: ")
                Layout.row: 1
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_size_data
                from: 5
                to: 20
                stepSize: 1
                editable: true

                Layout.row: 1
                Layout.column: 1
                Layout.fillWidth:  true
            }

            Label {
                id: label_size_query
                text: qsTr("Размер Запроса: ")
                Layout.row: 2
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_size_query
                from: 5
                to: 20
                stepSize: 1
                editable: true

                Layout.row: 2
                Layout.column: 1
                Layout.fillWidth:  true
            }

            Label {
                id: label_max_data
                text: qsTr("Макс. зн. данных: ")
                Layout.row: 3
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_max_data
                from: 5
                to: 50
                stepSize: 1
                editable: true

                Layout.row: 3
                Layout.column: 1
                Layout.fillWidth:  true
            }

            Label {
                id: label_speed_query
                text: qsTr("Скорость генерации запросов, сек: ")
                Layout.row: 4
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_speed_query
                from: 3
                to: 50
                stepSize: 1
                editable: true

                Layout.row: 4
                Layout.column: 1
                Layout.fillWidth:  true
            }


            Label {
                id: label_count_consumer
                text: qsTr("Количество запросов: ")
                Layout.row: 5
                Layout.column: 0
                font.pointSize: 15
            }
            SpinBox {
                id: spinBox_count_consumer
                from: 1
                to: 100
                stepSize: 1
                editable: true

                Layout.row: 5
                Layout.column: 1
                Layout.fillWidth:  true
            }

            Button {
                text: "Запустить"
                Layout.fillWidth: true
                Layout.row: 0
                Layout.column: 3
                Layout.rowSpan: 2
                Layout.fillHeight:  true

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

                        spinBox_size_buffer.enabled = false
                        spinBox_size_data.enabled = false
                        spinBox_size_query.enabled = false
                        spinBox_max_data.enabled = false

                        appCore._size_buffer     = spinBox_size_buffer.value
                        appCore._size_data       = spinBox_size_data.value
                        appCore._size_query      = spinBox_size_query.value
                        appCore._max_value       = spinBox_max_data.value
                        dataModel.clear()

                        appCore.on_click_buffer()
                        add_query.enabled = true
                    }
                    else {
                        this.text = "Запустить"
                        add_query.enabled = false

                        spinBox_size_buffer.enabled = true
                        spinBox_size_data.enabled = true
                        spinBox_size_query.enabled = true
                        spinBox_max_data.enabled = true

                        spinBox_count_consumer.enabled = true
                        spinBox_count_consumer.value = 1
                        spinBox_count_consumer.to = 100

                        _row = 0
                        _occupiedSpace = 0
                        _begin_index_sequence = 0
                        _size_sequence = 0

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
                Layout.fillHeight:  true

                font.pointSize: 15
                background: Rectangle {
                    color: parent.down ? "#d7d7d7" : "#f7f7f7"
                    border.color: "#26282a"
                    border.width: 2
                    radius: 15
                }
                onClicked: {
                    appCore._speed_query = spinBox_speed_query.value
                    appCore._count_consumer  = spinBox_count_consumer.value
                    appCore.on_click_consumer()

//                    console.log("_count_thread:", appCore._count_thread);

                    if (appCore._count_thread === 100 ) {
                        this.enabled = false
                        spinBox_count_consumer.enabled = false
                        spinBox_count_consumer.value = 0
                    }
                    else
                        spinBox_count_consumer.to = 100 - spinBox_count_consumer.value
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
//                    onClicked: {
//                    }
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
