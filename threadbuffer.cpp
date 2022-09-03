#include "threadbuffer.h"
#include <QDebug>

ThreadBuffer::ThreadBuffer(QObject *parent)
    : QObject{parent}
{

//    on_click_buffer();
//    on_click_consumer();

    qRegisterMetaType<std::vector<uint8_t>>("std::vector<uint8_t>");
}

ThreadBuffer::~ThreadBuffer()
{
    delete m_buffer;
    delete m_Consumer;

    m_threadBuffer->quit();
    m_threadBuffer->wait();

    if (m_threadBuffer->isRunning())
        m_threadBuffer->deleteLater();

//    if (m_timerBuffer->isActive())
//        m_timerBuffer->stop();
//    delete m_timerBuffer;
}

void ThreadBuffer::on_click_buffer()
{
    m_threadBuffer = new QThread;
    m_timerBuffer = new QTimer;
    m_buffer = new Buffer(m_size_buffer, m_size_query, m_max_value);

    connect(m_threadBuffer, SIGNAL(started()),  m_timerBuffer,  SLOT(start()));
    connect(m_threadBuffer, SIGNAL(finished()), m_timerBuffer,  SLOT(deleteLater()));
    connect(m_timerBuffer,  SIGNAL(timeout()),  m_buffer,       SLOT(Generate()));
    connect(m_buffer,       SIGNAL(set_occupiedSpace(int)), this, SLOT(setOccupiedSpace(int)));

    m_timerBuffer->setInterval(m_speed_data);
    m_timerBuffer->moveToThread(m_threadBuffer);
    m_buffer -> moveToThread(m_threadBuffer);
    m_threadBuffer -> start();
}

void ThreadBuffer::on_click_consumer()
{
    m_threadConsumer= new QThread;
    m_timerConsumer= new QTimer;
    m_Consumer = new Consumer(m_size_query, m_max_value);


    connect(m_threadConsumer, SIGNAL(started()),  m_timerConsumer,  SLOT(start()));
    connect(m_threadConsumer, SIGNAL(finished()), m_timerConsumer,  SLOT(deleteLater()));
    connect(m_timerConsumer,  SIGNAL(timeout()),  m_Consumer,       SLOT(Generate()));

    connect(m_buffer, SIGNAL(get(std::vector<uint8_t>)), m_Consumer, SLOT(comparison(std::vector<uint8_t>)));

    //    connect(m_Consumer,  SIGNAL(equals()),  this,       SLOT(show_equals()));

    m_timerConsumer->setInterval(m_speed_query);
    m_timerConsumer->moveToThread(m_threadConsumer);
    m_Consumer-> moveToThread(m_threadConsumer);
    m_threadConsumer-> start();
}

void ThreadBuffer::on_click_buffer_stop()
{
    if (m_threadBuffer->isFinished()) {
        return;
    }

    if (m_timerBuffer->isActive()) {
        m_timerBuffer->stop();
    }
}

void ThreadBuffer::setSizeBuffer(int _size)
{
    if (m_size_buffer == _size)
        return;

    m_size_buffer = _size;
}

void ThreadBuffer::setSizeQuery(int _size)
{
    if (m_size_query == _size)
        return;

    m_size_query = _size;
}

void ThreadBuffer::setSpeedData(int _speed)
{
    if (m_speed_data == _speed)
        return;

    m_speed_data = _speed;
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

void ThreadBuffer::setOccupiedSpace(int _occupiedSpace)
{

    if (m_occupiedSpace == _occupiedSpace)
        return;

    m_occupiedSpace = _occupiedSpace;
    emit occupiedSpaceChanged(m_occupiedSpace);
}

//void ThreadBuffer::get_data(std::vector<uint8_t> _buffer)
//{
////    qDebug() << __PRETTY_FUNCTION__;

//    for (const auto &el : _buffer) {
//        qDebug() << "el: " << el;
//    }
//}
