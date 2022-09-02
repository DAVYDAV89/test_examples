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
public:
    explicit ThreadBuffer(QObject *parent = nullptr);
    ~ThreadBuffer();

private:
    QThread *m_threadBuffer;
    QTimer  *m_timerBuffer;
    Buffer  *m_buffer;

    QThread *m_threadConsumer;
    QTimer  *m_timerConsumer;
    Consumer*m_Consumer;

public slots:
    void on_click_buffer();
    void on_click_consumer();

private slots:

signals:
    void comparison_data(std::vector<uint8_t>);

};

#endif // THREADBUFFER_H
