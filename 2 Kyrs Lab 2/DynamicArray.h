#include <iostream>
#include <cassert>

class DynamicArray {
private:
    int* arrayData_;
    size_t arrayLength_;

public:
    DynamicArray() : arrayData_(nullptr), arrayLength_(0) {}

    ~DynamicArray() {
        delete[] arrayData_;
    }

    void push_back(int value) {
        size_t newLength = arrayLength_ + 1;
        int* new_data = new int[newLength];

        for (size_t i = 0; i < arrayLength_; ++i) {
            new_data[i] = arrayData_[i];
        }

        new_data[arrayLength_] = value;

        delete[] arrayData_;
        arrayData_ = new_data;
        arrayLength_ = newLength;
    }

    void pop_back() {
        assert(arrayLength_ > 0 && "Массив пуст, нечего удалять!");

        size_t newLength = arrayLength_ - 1;
        int* new_data = nullptr;

        if (newLength > 0) {
            new_data = new int[newLength];
            for (size_t i = 0; i < newLength; ++i) {
                new_data[i] = arrayData_[i];
            }
        }

        delete[] arrayData_;
        arrayData_ = new_data;
        arrayLength_ = newLength;
    }

    int arrayData(size_t index) const {
        assert(index < arrayLength_ && "Индекс вышел за пределы массива!");
        return arrayData_[index];
    }

    void arrayData(size_t index, int value) {
        assert(index < arrayLength_ && "Индекс вышел за пределы массива!");
        arrayData_[index] = value;
    }

    size_t arrayLength() const {
        return arrayLength_;
    }
};

int main() {
    DynamicArray arr;

    std::cout << "--- Добавление элементов ---" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        arr.push_back(i * 11);
        std::cout << "Добавлено. Текущая длина: " << arr.arrayLength() << std::endl;
    }

    std::cout << "\nСодержимое массива: ";
    for (size_t i = 0; i < arr.arrayLength(); ++i) {
        std::cout << arr.arrayData(i) << " ";
    }
    std::cout << std::endl;

    arr.arrayData(1, 99);
    std::cout << "После изменения индекса 1: " << arr.arrayData(1) << std::endl;

    std::cout << "\n--- Удаление элементов ---" << std::endl;
    while (arr.arrayLength() > 0) {
        arr.pop_back();
        std::cout << "Удалено. Текущая длина: " << arr.arrayLength() << std::endl;
    }
    return 0;
}