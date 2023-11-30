#include <iostream>
#include <assert.h>
#include <array>
#include <span>

class DynamicArray
{
    int* arr;
    size_t elementCapacity;
    size_t currentIndex = 0;
};

   //Вместо factory функций, используйте дефолтный конструктор, и конструктор с параметром capacity.

   public: 
    DynamicArray() : arr(nullptr), elementCapacity(0), currentIndex(0) {}

    DynamicArray(size_t capacity) : elementCapacity(capacity), currentIndex(0)
    {
        arr = (int*)malloc(capacity * sizeof(int));
    }

// Вместо free / destroy, определите деструктор.

    ~DynamicArray()
    {
        delete[] arr;
    }

// Переопределите конструктор копирования.

    DynamicArray(const DynamicArray& other)
    {
        elementCapacity = other.elementCapacity;
        currentIndex = other.currentIndex;
        arr = (int*)malloc(elementCapacity * sizeof(int));
        memcpy(arr, other.arr, currentIndex * sizeof(int));
    }

   