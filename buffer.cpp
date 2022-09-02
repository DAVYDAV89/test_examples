#include "buffer.h"

#include <QDebug>

using namespace std;
Buffer::Buffer(int size, int count)
    : _size(size)
    , _count(count)
{
    _data = new uint8_t[_size];
    _occupiedSpace = 0;

    min_value = 1;
    max_value = 3;

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
        Add((uint8_t)rand() % (max_value - min_value + 1) + min_value);
    }
    emit add();
}

void Buffer::Add(uint8_t val)
{
    _data[_occupiedSpace++ % _size] = val;
}


void Buffer::Get()
{
    vector<uint8_t> res;

    for (int i = 0; i < _size; ++i) {
        res.push_back(_data[i]);
    }

//    qDebug() << "--------Buffer-------------";
//    for (const auto &el : res) {
//        qDebug() << "el: " << el;
//    }

    emit get(res);
}

