#pragma once

#include <cstddef>
#include <iosfwd>

class DynamicArray {
public:
    using iterator = int*;
    using const_iterator = const int*;

private:
    int* data_;
    size_t size_;
    size_t capacity_;

    static constexpr size_t kMinCapacity = 4;

    void reserve(size_t newCapacity);
    void shrinkIfNeeded();

public:
    // --- Конструкторы / деструктор ---
    DynamicArray();
    DynamicArray(const int* src, size_t count);           // из обычного массива
    DynamicArray(const DynamicArray& other);              // копирования
    DynamicArray(DynamicArray&& other) noexcept;          // перемещения
    ~DynamicArray();

    // --- Присваивание ---
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    // --- Размер / состояние ---
    size_t size()     const;
    size_t capacity() const;
    bool   empty()    const;

    // --- Обмен ---
    void swap(DynamicArray& other) noexcept;

    // --- Поиск ---
    long long find(int value) const;          // индекс или -1
    int  max() const;                          // требует непустого массива
    int  min() const;                          // требует непустого массива

    // --- Модификация ---
    bool insertAt(size_t index, int value);   // false при некорректном индексе
    bool removeAt(size_t index);              // false при некорректном индексе
    bool removeValue(int value);              // первое вхождение
    void removeAll(int value);                // все вхождения

    // --- Сортировка ---
    void sort();                               // по возрастанию

    // --- Итераторы ---
    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end()   const;

    // --- Операции с итераторами ---
    iterator insert(iterator pos, int value);  // вставка перед pos
    iterator erase(iterator pos);              // удаление одного
    iterator erase(iterator first, iterator last); // удаление диапазона [first, last)

    // --- Потоковый ввод/вывод ---
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
    friend std::istream& operator>>(std::istream& is, DynamicArray& arr);
};