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
    Q_PROPERTY(int _size_buffer /*READ _size_buffer*/ WRITE setSizeBuffer)
    Q_PROPERTY(int _size_query /*READ _size_query*/ WRITE setSizeQuery)
    Q_PROPERTY(int _speed_data /*READ _speed_data */WRITE setSpeedData)
    Q_PROPERTY(int _speed_query /*READ _speed_query*/ WRITE setSpeedQuery)
    Q_PROPERTY(int _max_value /*READ _max_value */WRITE setMaxValue)
    Q_PROPERTY(int _count_consumer /*READ _max_value */WRITE setCountConsumer)
public:
    explicit ThreadBuffer(QObject *parent = nullptr);
    ~ThreadBuffer();

//    int  _size_buffer() {
//        return m_size_buffer;
//    }

//    int _size_query() {
//        return m_size_query;
//    }

//    int _speed_data() {
//        return m_speed_data;
//    }

//    int _speed_query() {
//        return m_speed_query;
//    }

//    int _max_value() {
//        return m_max_value;
//    }

private:
    QThread *m_threadBuffer;
    QTimer  *m_timerBuffer;
    Buffer  *m_buffer;

    QThread *m_threadConsumer;
    QTimer  *m_timerConsumer;
    Consumer*m_Consumer;

    int  m_size_buffer{100000};
    int  m_size_query{10};
    int  m_speed_data{10000};
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
    void setSizeQuery(int _size);
    void setSpeedData(int _speed);
    void setSpeedQuery(int _speed);
    void setMaxValue(int _max_value);
    void setCountConsumer(int _count_consumer);

private slots:
    void setOccupiedSpace(int _occupiedSpace );
    void show_equals(int _id_thread, QString _sequence, int _begin_sequence, QString _dateTime);

signals:
    void comparison_data(std::vector<uint8_t>);  
    void occupiedSpaceChanged(int m_occupiedSpace);
    void showEquals(int m_id_thread, QString m_sequence, int m_begin_sequence, QString m_dateTime);
    void finished();
};

#endif // THREADBUFFER_H
