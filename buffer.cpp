#include "buffer.h"

#include <QDebug>

using namespace std;
Buffer::Buffer(int size, int count, uint8_t max_value)
    : _size(size)
    , _count(count)
    , _max_value(max_value)
{
    _data = new uint8_t[_size];
    for (int i = 0; i < _size; ++i)
        _data[i] = 0;

    _occupiedSpace = _size;

    srand(time(NULL));
    connect(this, SIGNAL(add()),  this,  SLOT(Get()));
}

Buffer::~Buffer()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete[] _data;
}

void Buffer::Generate()
{
//    qDebug() << __PRETTY_FUNCTION__;

    for (int i = 0; i < _count; ++i) {
        Add((uint8_t)rand() % (_max_value - _min_value + 1) + _min_value);
    }
    emit add();
}

void Buffer::Add(uint8_t val)
{
//    qDebug() << "val: " << val;

    if (_occupiedSpace == _size)
        _occupiedSpace = 0;

    _data[_occupiedSpace++ % _size] = val;

    emit set_occupiedSpace(_occupiedSpace);
}


void Buffer::Get()
{
    vector<uint8_t> res;

    for (int i = 0; i < _size; ++i) {
//        qDebug() << "el: " << _data[i];
        res.push_back(_data[i]);
    }

//    qDebug() << "--------Buffer-------------";
//    for (const auto &el : res) {
//        qDebug() << "el: " << el;
//    }

    emit get(res);
}

