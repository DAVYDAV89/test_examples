# test_examples
поток «producer» генерирует в реальном времени данные типа std::uint8_t в диапазоне от 0 до max_value и складывает их в кольцевой буфер «buffer» большого размера. Несколько потоков «consumer» с определённой частотой генерируют запросы: массивы «query» маленького размера того же типа данных и ищут все вхождения «query» в «buffer» и выводят позиции начала вхождений, если они найдены
