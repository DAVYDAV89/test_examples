#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <QObject>

class Buffer : public QObject
{
    Q_OBJECT
public:
    Buffer(int, int, uint8_t);
    ~Buffer();

private:
    uint8_t*    m_data;          // Хранимые данные.
    int         m_size;          // Размер циклического буффера.
    int         m_count;         // Размер последовательности
    int         m_occupiedSpace; // Занятое мето.
    int         m_max_value;     // Макс генерируемое значение
    const int   m_min_value{0};


private slots:
    // Метод вывдящий все данные
    void Get();

public slots:
    // Метод генерирующий последовательность
    void Generate();

    // Метод добавления элемента в буффер.
    void Add(uint8_t);


signals:
    void finished();
    void add();
    void get(std::vector<uint8_t>);
    void set_occupiedSpace(int);
};

#endif // BUFFER_H
