#include "consumer.h"

#include <QDebug>
#include <QDateTime>
#include <algorithm>
#include <numeric>

using namespace std;

Consumer::Consumer(int count, int max_value, int id_thread)
    : _count(count)
    , _max_value(max_value)
    , _id_thread(id_thread)
{
//    qDebug() << __PRETTY_FUNCTION__ << _id_thread;

    srand(time(NULL));
}

Consumer::~Consumer()
{
    qDebug() << __PRETTY_FUNCTION__ << _id_thread;
}

void Consumer::Generate()
{
    _data.clear();
    for (int i = 0; i < _count; ++i) {
        Add((uint8_t)rand() % (_max_value - _min_value + 1) + _min_value);
    }
    emit add();
}

void Consumer::Add(uint8_t el)
{
    _data.push_back(el);
}

void Consumer::comparison(const vector<uint8_t> &_buffer)
{
    if (_data.size() == 0 || _buffer.size() == 0)
        return;

//    qDebug() << "--------comparison--thread------" << _id_thread;

//    for (const auto &el : _data) {
//        qDebug() << "el_querty " << el;
//    }

//    for (const auto &el : _buffer) {
//        qDebug() << "el_buffer: " << el;
//    }

    auto _index{
        std::search(std::begin(_buffer), std::end(_buffer), std::begin(_data), std::end(_data))
    };
    if ( _index != std::end(_buffer) ) {
        auto it = find( _buffer.begin(), _buffer.end(), *_index);

        QString _sequence;
        for (const auto &el : _data) {
            _sequence += QString::number(el);
        }
        _data.clear();

        qDebug() << "_sequence: " << _sequence << "thread: " << _id_thread;

        QString _dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy/hh:mm:ss");

        int _begin_sequence = it - _buffer.begin();

//        qDebug() << "---------sequence found----------" << it - _buffer.begin();
        emit equals(_id_thread, _sequence, _begin_sequence, _dateTime);
    }
}
