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
    DynamicArray(const int* src, size_t count);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
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
    long long find(int value) const;
    int  max() const;
    int  min() const;

    // --- Модификация ---
    bool insertAt(size_t index, int value);
    bool removeAt(size_t index);
    bool removeValue(int value);
    void removeAll(int value);

    // --- Сортировка ---
    void sort();

    // --- Итераторы ---
    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end()   const;

    // --- Операции с итераторами ---
    iterator insert(iterator pos, int value);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    // --- Потоковый ввод/вывод ---
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
    friend std::istream& operator>>(std::istream& is, DynamicArray& arr);
};