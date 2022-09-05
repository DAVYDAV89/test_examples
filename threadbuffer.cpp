#include "threadbuffer.h"
#include <QDebug>

ThreadBuffer::ThreadBuffer(QObject *parent)
    : QObject{parent}
{
    qRegisterMetaType<std::vector<uint8_t>>("std::vector<uint8_t>");
}

ThreadBuffer::~ThreadBuffer()
{
    emit finished();
}


void ThreadBuffer::on_click_buffer()
{
    m_threadBuffer = new QThread;
    m_timerBuffer = new QTimer;
    m_buffer = new Buffer(m_size_buffer, m_size_data, m_max_value);

    connect(this, SIGNAL(finished()),  m_buffer,  SIGNAL(finished()));

    connect(m_threadBuffer,     SIGNAL(started()),  m_timerBuffer,      SLOT(start()));
    connect(m_buffer,           SIGNAL(finished()), m_threadBuffer,     SLOT(quit()));
    connect(m_threadBuffer,     SIGNAL(finished()), m_timerBuffer,      SLOT(deleteLater()));
    connect(m_buffer,           SIGNAL(finished()), m_buffer,           SLOT(deleteLater()));
    connect(m_threadBuffer,     SIGNAL(finished()), m_threadBuffer,     SLOT(deleteLater()));
    connect(m_timerBuffer,      SIGNAL(timeout()),  m_buffer,           SLOT(Generate()));

    connect(m_buffer,           SIGNAL(set_occupiedSpace(int)), this, SLOT(setOccupiedSpace(int)));

//    m_timerBuffer->setInterval(m_speed_data * 1000);
    m_timerBuffer->setInterval(1000);
    m_timerBuffer->moveToThread(m_threadBuffer);
    m_buffer -> moveToThread(m_threadBuffer);
    m_threadBuffer -> start();
}

void ThreadBuffer::on_click_consumer()
{
    for (int i = 0; i < m_count_consumer; ++i)
        GreateConsumer();
}

void ThreadBuffer::GreateConsumer()
{
    if (m_thread_id > 100)
        return;

    m_threadConsumer = new QThread;
    m_timerConsumer = new QTimer;
    m_Consumer = new Consumer(m_size_query, m_max_value, ++m_thread_id);

    connect(this, SIGNAL(finished()),  m_Consumer,  SIGNAL(finished()));

    connect(m_threadConsumer, SIGNAL(started()),  m_timerConsumer,  SLOT(start()));
    connect(m_Consumer,       SIGNAL(finished()), m_threadConsumer, SLOT(quit()));
    connect(m_threadConsumer, SIGNAL(finished()), m_timerConsumer,  SLOT(deleteLater()));
    connect(m_Consumer,       SIGNAL(finished()), m_Consumer,       SLOT(deleteLater()));
    connect(m_threadConsumer, SIGNAL(finished()), m_threadConsumer, SLOT(deleteLater()));
    connect(m_timerConsumer,  SIGNAL(timeout()),  m_Consumer,       SLOT(Generate()));
    connect(m_Consumer,       SIGNAL(add()),      m_buffer,         SLOT(Get()));

    connect(m_buffer, SIGNAL(get(std::vector<uint8_t>)), m_Consumer, SLOT(comparison(std::vector<uint8_t>)));

    connect(m_Consumer,  SIGNAL(equals(int, QString, int, QString)),
            this, SLOT(show_equals(int, QString, int, QString)));

    m_timerConsumer->setInterval(m_speed_query * 60000);
    m_timerConsumer->moveToThread(m_threadConsumer);
    m_Consumer-> moveToThread(m_threadConsumer);
    m_threadConsumer-> start();
}

void ThreadBuffer::on_click_buffer_stop()
{
    if (m_threadBuffer->isFinished()) {
        return;
    }

    emit finished();
    m_thread_id = 0;
}

void ThreadBuffer::setSizeBuffer(int _size)
{
    if (m_size_buffer == _size)
        return;

    m_size_buffer = _size;
}

void ThreadBuffer::setSizeData(int _size)
{
    if (m_size_data == _size)
        return;

    m_size_data = _size;
}

void ThreadBuffer::setSizeQuery(int _size)
{
    if (m_size_query == _size)
        return;

    m_size_query = _size;
}


void ThreadBuffer::setSpeedQuery(int _speed)
{
    if (m_speed_query == _speed)
        return;

    m_speed_query = _speed;
}

void ThreadBuffer::setMaxValue(int _max_value)
{
    if (m_max_value == _max_value)
        return;

    m_max_value = _max_value;
}

void ThreadBuffer::setCountConsumer(int _count_consumer)
{
    m_count_consumer = _count_consumer;
}

void ThreadBuffer::setOccupiedSpace(int _occupiedSpace)
{
    if (m_occupiedSpace == _occupiedSpace)
        return;

    m_occupiedSpace = _occupiedSpace;
    emit occupiedSpaceChanged(m_occupiedSpace);
}

void ThreadBuffer::show_equals(int _id_thread, QString _sequence, int _begin_sequence, QString _dateTime)
{
//    qDebug() << __PRETTY_FUNCTION__ ;

//    qDebug() << "thread: " << _id_thread;
//    qDebug() << "_sequence: " << _sequence;
//    qDebug() << "_index: " << _begin_sequence;
//    qDebug() << "_dateTime: " << _dateTime;
    emit showEquals(_id_thread, _sequence, _begin_sequence,_dateTime);
}

