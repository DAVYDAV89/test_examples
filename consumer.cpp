#include "consumer.h"

#include <QDebug>
#include <algorithm>
#include <numeric>
#include <thread>
#include <iostream>

using namespace std;

Consumer::Consumer(int count, int max_value)
    : _count(count)
    , _max_value(max_value)
{
    srand(time(NULL));
}

Consumer::~Consumer()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void Consumer::Generate()
{
    _data.clear();
    for (int i = 0; i < _count; ++i) {
        Add((uint8_t)rand() % (_max_value - _min_value + 1) + _min_value);
    }
}

void Consumer::Add(uint8_t el)
{
    _data.push_back(el);
}

void Consumer::comparison(const vector<uint8_t> &_buffer)
{
    if (_data.size() == 0 || _buffer.size() == 0)
        return;

    qDebug() << "--------comparison-------------";

    for (const auto &el : _data) {
        qDebug() << "el_querty " << el;
    }

    for (const auto &el : _buffer) {
        qDebug() << "el_buffer: " << el;
    }

    auto _index{
        std::search(std::begin(_buffer), std::end(_buffer), std::begin(_data), std::end(_data))
    };
    if ( _index != std::end(_buffer) ) {
        auto it = find( _buffer.begin(), _buffer.end(), *_index);


        qDebug() << "---------sequence found----------" << it - _buffer.begin();
        cout << "threadID : " << std::this_thread::get_id() << endl;
        emit equals();
    }
}
