#include "consumer.h"

#include <QDebug>
#include <algorithm>
#include <numeric>

using namespace std;

Consumer::Consumer(int count)
    : _count(count)
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
        Add((uint8_t)rand() % 3);
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

    for (const auto &el : _data) {
        qDebug() << "el_data: " << el;
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
        emit equals();
    } else {
//        qDebug() << "---------sequence NOT found----------";
    }



//    if (_data == _buffer ) {
//        qDebug() << "---------equals----------";
//        emit equals();
//    }
}
