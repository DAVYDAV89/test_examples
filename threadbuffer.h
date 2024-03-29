#ifndef THREADBUFFER_H
#define THREADBUFFER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "buffer.h"
#include "consumer.h"


class ThreadBuffer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int _size_buffer WRITE setSizeBuffer)
    Q_PROPERTY(int _size_data WRITE setSizeData)
    Q_PROPERTY(int _size_query WRITE setSizeQuery)
    Q_PROPERTY(int _speed_query WRITE setSpeedQuery)
    Q_PROPERTY(int _max_value WRITE setMaxValue)
    Q_PROPERTY(int _count_consumer READ get_count_consumer WRITE setCountConsumer)
    Q_PROPERTY(int _count_thread READ get_count_thread )
public:
    explicit ThreadBuffer(QObject *parent = nullptr);
    ~ThreadBuffer();

    int get_count_consumer() {
        return m_count_consumer;
    }

    int get_count_thread() {
        return m_thread_id;
    }

private:
    QThread *m_threadBuffer;
    QTimer  *m_timerBuffer;
    Buffer  *m_buffer;

    QThread *m_threadConsumer;
    QTimer  *m_timerConsumer;
    Consumer*m_Consumer;

    int  m_size_buffer{100000};
    int  m_size_query{10};
    int  m_size_data{10000};
    int  m_speed_query{1};
    int  m_max_value{10};
    int  m_occupiedSpace{0};
    int  m_thread_id{0};
    int  m_count_consumer{0};

    void GreateConsumer();

public slots:
    void on_click_buffer();
    void on_click_consumer();

    void on_click_buffer_stop();

    void setSizeBuffer(int _size);
    void setSizeData(int _size);
    void setSizeQuery(int _size);
    void setSpeedQuery(int _speed);
    void setMaxValue(int _max_value);
    void setCountConsumer(int _count_consumer);

private slots:
    void setOccupiedSpace(int _occupiedSpace );
    void show_equals(int _id_thread, QString _sequence, int _begin_sequence, QString _dateTime);

signals:
    void comparison_data(std::vector<uint8_t>);  
    void occupiedSpaceChanged(int m_occupiedSpace);
    void finished();
    void showEquals(int _id_thread, QString _sequence, int _begin_sequence, QString _dateTime);
};

#endif // THREADBUFFER_H
