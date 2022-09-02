#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    Consumer(int count = 1024);
    ~Consumer();

public slots:
    // Метод генерирующий последовательность
    void Generate();

    // Метод добавления элемента в буффер.
    void Add(uint8_t);

    void comparison(const std::vector<uint8_t> &);

private:
    int _count;
    std::vector<uint8_t> _data;

private slots:

signals:
    void equals();

};

#endif // CONSUMER_H
