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
    Q_PROPERTY(int _size_buffer READ _size_buffer WRITE setSizeBuffer)
    Q_PROPERTY(int _size_query READ _size_query WRITE setSizeQuery)
    Q_PROPERTY(int _speed_query READ _speed_query WRITE setSpeedQuery)
public:
    explicit ThreadBuffer(QObject *parent = nullptr);
    ~ThreadBuffer();

    int  _size_buffer() {
        return m_size_buffer;
    }

    int _size_query() {
        return m_size_query;
    }

    int _speed_query() {
        return m_speed_query;
    }

private:
    QThread *m_threadBuffer;
    QTimer  *m_timerBuffer;
    Buffer  *m_buffer;

    QThread *m_threadConsumer;
    QTimer  *m_timerConsumer;
    Consumer*m_Consumer;

    int  m_size_buffer{0};
    int  m_size_query{0};
    int  m_speed_query{0};

public slots:
    void on_click_buffer();
    void on_click_consumer();

    void on_click_buffer_stop();

    void setSizeBuffer(int _size);
    void setSizeQuery(int _size);
    void setSpeedQuery(int _speed);

private slots:

signals:
    void comparison_data(std::vector<uint8_t>);

};

#endif // THREADBUFFER_H
