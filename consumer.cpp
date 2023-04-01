#include "consumer.h"

#include <QDebug>
#include <QDateTime>
#include <algorithm>
#include <numeric>

using namespace std;

Consumer::Consumer(int _count, int _max_value, int _id_thread)
    : m_count(_count)
    , m_max_value(_max_value)
    , m_id_thread(_id_thread)
{
//    qDebug() << __PRETTY_FUNCTION__ << _id_thread;

    srand(time(NULL));
}

Consumer::~Consumer()
{
    qDebug() << __PRETTY_FUNCTION__ << m_id_thread;
}

void Consumer::Generate()
{
    m_data.clear();
    for (int i = 0; i < m_count; ++i) {
        Add((uint8_t)rand() % (m_max_value - m_min_value + 1) + m_min_value);
    }
    emit add();
}

void Consumer::Add(uint8_t el)
{
    m_data.push_back(el);
}

void Consumer::comparison(const vector<uint8_t> &_buffer)
{
    if (m_data.size() == 0 || _buffer.size() == 0)
        return;

//    qDebug() << "--------comparison--thread------" << m_id_thread;
//    for (const auto &el : m_data) {
//        qDebug() << "el_querty " << el;
//    }

//    for (const auto &el : _buffer) {
//        qDebug() << "el_buffer: " << el;
//    }

    auto _index{
        search(begin(_buffer), end(_buffer), begin(m_data), end(m_data))
    };
    if ( _index != end(_buffer) ) {

        QString _sequence;
        for (const auto &el : m_data) {
            _sequence += QString::number(el) + " ";
        }
        m_data.clear();
//        qDebug() << "---------sequence found----------" << distance(_buffer.begin(), _index ) << " thread: " << _id_thread;
        emit equals(m_id_thread,
                    _sequence,
                    distance(_buffer.begin(), _index ),
                    QDateTime::currentDateTime().toString("dd.MM.yyyy/hh:mm:ss")
                    );
    }
}
