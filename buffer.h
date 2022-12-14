#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <QObject>

class Buffer : public QObject
{
    Q_OBJECT
public:
    Buffer(int size = 1024, int count = 512, uint8_t max_value = 10);
    ~Buffer();

private:
    uint8_t*    _data;          // Хранимые данные.
    int         _size;          // Размер циклического буффера.
    int         _count;         // Размер последовательности
    int         _occupiedSpace; // Занятое мето.
    int         _max_value;     // Макс генерируемое значение
    const int _min_value{0};


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
