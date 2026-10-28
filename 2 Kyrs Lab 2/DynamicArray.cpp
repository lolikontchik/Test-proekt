#include "DynamicArray.h"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <utility>

// ==================== Вспомогательные ====================

void DynamicArray::reserve(size_t newCapacity) {
    if (newCapacity == capacity_) return;

    int* newData = newCapacity ? new int[newCapacity] : nullptr;
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

void DynamicArray::shrinkIfNeeded() {
    if (capacity_ > kMinCapacity && size_ <= capacity_ / 4) {
        reserve(capacity_ / 2);
    }
}

// ==================== Конструкторы / деструктор ====================

DynamicArray::DynamicArray()
    : data_(nullptr), size_(0), capacity_(0) {
}

DynamicArray::DynamicArray(const int* src, size_t count)
    : data_(count ? new int[count] : nullptr),
    size_(count),
    capacity_(count)
{
    for (size_t i = 0; i < count; ++i) {
        data_[i] = src[i];
    }
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(other.size_ ? new int[other.size_] : nullptr),
    size_(other.size_),
    capacity_(other.size_)
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept
    : data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

// ==================== Присваивание ====================

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        DynamicArray tmp(other);
        swap(tmp);
    }
    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

// ==================== Размер / состояние ====================

size_t DynamicArray::size()     const { return size_; }
size_t DynamicArray::capacity() const { return capacity_; }
bool   DynamicArray::empty()    const { return size_ == 0; }

// ==================== Обмен ====================

void DynamicArray::swap(DynamicArray& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

// ==================== Поиск ====================

long long DynamicArray::find(int value) const {
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] == value) return static_cast<long long>(i);
    }
    return -1;
}

int DynamicArray::max() const {
    assert(size_ > 0 && "max() на пустом массиве!");
    int m = data_[0];
    for (size_t i = 1; i < size_; ++i) {
        if (data_[i] > m) m = data_[i];
    }
    return m;
}

int DynamicArray::min() const {
    assert(size_ > 0 && "min() на пустом массиве!");
    int m = data_[0];
    for (size_t i = 1; i < size_; ++i) {
        if (data_[i] < m) m = data_[i];
    }
    return m;
}

// ==================== Модификация ====================

bool DynamicArray::insertAt(size_t index, int value) {
    if (index > size_) return false;

    if (size_ == capacity_) {
        size_t newCap = capacity_ ? capacity_ * 2 : kMinCapacity;
        reserve(newCap);
    }

    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;
    ++size_;
    return true;
}

bool DynamicArray::removeAt(size_t index) {
    if (index >= size_) return false;

    for (size_t i = index; i + 1 < size_; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
    shrinkIfNeeded();
    return true;
}

bool DynamicArray::removeValue(int value) {
    long long idx = find(value);
    if (idx < 0) return false;
    return removeAt(static_cast<size_t>(idx));
}

void DynamicArray::removeAll(int value) {
    size_t write = 0;
    for (size_t read = 0; read < size_; ++read) {
        if (data_[read] != value) {
            data_[write++] = data_[read];
        }
    }
    size_ = write;
    shrinkIfNeeded();
}

// ==================== Сортировка ====================

void DynamicArray::sort() {
    for (size_t i = 1; i < size_; ++i) {
        int key = data_[i];
        size_t j = i;
        while (j > 0 && data_[j - 1] > key) {
            data_[j] = data_[j - 1];
            --j;
        }
        data_[j] = key;
    }
}

// ==================== Итераторы ====================

DynamicArray::iterator       DynamicArray::begin() { return data_; }
DynamicArray::iterator       DynamicArray::end() { return data_ + size_; }
DynamicArray::const_iterator DynamicArray::begin() const { return data_; }
DynamicArray::const_iterator DynamicArray::end()   const { return data_ + size_; }

// ==================== Операции с итераторами ====================

DynamicArray::iterator DynamicArray::insert(iterator pos, int value) {
    size_t index = static_cast<size_t>(pos - data_);
    insertAt(index, value);
    return data_ + index;
}

DynamicArray::iterator DynamicArray::erase(iterator pos) {
    size_t index = static_cast<size_t>(pos - data_);
    removeAt(index);
    return data_ + index;
}

DynamicArray::iterator DynamicArray::erase(iterator first, iterator last) {
    size_t start = static_cast<size_t>(first - data_);
    size_t stop = static_cast<size_t>(last - data_);
    if (start >= stop || stop > size_) return data_ + start;

    size_t removed = stop - start;
    for (size_t i = start; i + removed < size_; ++i) {
        data_[i] = data_[i + removed];
    }
    size_ -= removed;
    shrinkIfNeeded();
    return data_ + start;
}

// ==================== Потоковый ввод/вывод ====================

std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
    os << '[';
    for (size_t i = 0; i < arr.size_; ++i) {
        if (i) os << ", ";
        os << arr.data_[i];
    }
    os << ']';
    return os;
}

std::istream& operator>>(std::istream& is, DynamicArray& arr) {
    size_t count = 0;
    if (!(is >> count)) return is;

    DynamicArray tmp;
    for (size_t i = 0; i < count; ++i) {
        int v;
        if (!(is >> v)) return is;
        tmp.insertAt(tmp.size(), v);
    }
    arr.swap(tmp);
    return is;
}