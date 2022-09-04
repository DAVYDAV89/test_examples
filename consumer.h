#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    Consumer(int count = 1024, int max_value = 10, int id_thread = 0);
    ~Consumer();

public slots:
    // Метод генерирующий последовательность
    void Generate();

    // Метод добавления элемента в буффер.
    void Add(uint8_t);

    void comparison(const std::vector<uint8_t> &);

private:
    int _count;
    int _max_value;
    int _min_value{0};
    int _id_thread{0};
    std::vector<uint8_t> _data;

private slots:

signals:
    void equals(int, QString, int, QString);
    void add();
    void finished();

};

#endif // CONSUMER_H
