import QtCharts 2.0

ChartView {
//    theme: ChartView.ChartThemeBrownSand
    legend.visible: false
    antialiasing: true

    PieSeries {
        size: 1
        holeSize: 0.9
        id: buffer
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
    PieSeries {
        size: 0.9
        holeSize: 0.8
        id: query

//        PieSlice { label: "До последовательности"; value: 40000; color: "#DF8939"; borderColor: "#13060C" }
//        PieSlice { label: "Последовательность"; value: 10000; color: "#163430"; borderColor: "#13060C" }
//        PieSlice { label: "После последовательности"; value: 100000 - 50000; color: "#DF8939"; borderColor: "#13060C" }


        PieSlice { label: "До последовательности"; value: _begin_index_sequence; color: "#DF8939"; borderColor: "#13060C" }
        PieSlice { label: "Последовательность"; value: _size_sequence; color: "#163430"; borderColor: "#13060C" }
        PieSlice { label: "После последовательности"; value: spinBox_size_buffer.value - (_begin_index_sequence + _size_sequence); color: "#DF8939"; borderColor: "#13060C" }
    }
}

