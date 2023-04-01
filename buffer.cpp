#include "buffer.h"

#include <QDebug>

using namespace std;
Buffer::Buffer(int _size, int _count, uint8_t _max_value)
    : m_size(_size)
    , m_count(_count)
    , m_max_value(_max_value)
{
    m_data = new uint8_t[m_size];
    for (int i = 0; i < m_size; ++i)
        m_data[i] = 0;

    m_occupiedSpace = m_size;

    srand(time(NULL));
}

Buffer::~Buffer()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete[] m_data;
}

void Buffer::Generate()
{
//    qDebug() << __PRETTY_FUNCTION__;

    for (int i = 0; i < m_count; ++i) {
        Add((uint8_t)rand() % (m_max_value - m_min_value + 1) + m_min_value);
    }    

//        qDebug() << "--------m_data-------------";
//        for (int i = 0; i < m_size; ++i) {
//            qDebug() << "el: " << m_data[i];
//        }

}

void Buffer::Add(uint8_t val)
{
//    qDebug() << "val: " << val;

    if (m_occupiedSpace == m_size)
        m_occupiedSpace = 0;

    m_data[m_occupiedSpace++ % m_size] = val;

    emit set_occupiedSpace(m_occupiedSpace);
}


void Buffer::Get()
{
    vector<uint8_t> res;
    res.assign(m_data, m_data + m_size);


//    qDebug() << "--------Get-------------";
//    for (const auto &el : res) {
//        qDebug() << "el: " << el;
//    }

    emit get(res);
}

