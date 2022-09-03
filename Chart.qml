import QtQuick 2.13
import QtQuick.Controls 2.13

import QtCharts 2.0


ChartView {
    theme: ChartView.ChartThemeBrownSand
    antialiasing: true

    PieSeries {
        size: 1
        holeSize: 0.7

        id: pieSeries
        PieSlice {
            id: full
            label: "Заполнено";
            value: _occupiedSpace
            color: "#99CC4E";
            borderColor: "#163430"
        }
        PieSlice {
            id: free
            label: "Свободно";
            value: spinBox_size_buffer.value - _occupiedSpace
            color: "#DF8939";
            borderColor: "#13060C"
        }
    }
}



