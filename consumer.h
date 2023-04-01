#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    Consumer(int, int, int);
    ~Consumer();

public slots:
    // Метод генерирующий последовательность
    void Generate();

    // Метод добавления элемента в буффер.
    void Add(uint8_t);

    void comparison(const std::vector<uint8_t> &);

private:
    int m_count;
    int m_max_value;
    int m_min_value{0};
    int m_id_thread{0};
    std::vector<uint8_t> m_data;

private slots:

signals:
    void equals(int, QString, int, QString);
    void add();
    void finished();

};

#endif // CONSUMER_H
