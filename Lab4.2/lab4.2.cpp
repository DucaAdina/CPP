#include <iostream>
#include <assert.h>
#include <array>
#include <span>

template <typename T>
class DynamicArray
{
    private:
   // int* arr;
    T* arr;
    size_t elementCapacity;
    size_t currentIndex = 0;
};

   //Вместо factory функций, используйте дефолтный конструктор, и конструктор с параметром capacity.

   public: 
    DynamicArray() : arr(nullptr), elementCapacity(0), currentIndex(0) {}// constr implicit

    DynamicArray(size_t capacity) : elementCapacity(capacity), currentIndex(0)// constr cu parametru
    {
      // arr = (int*)malloc(capacity * sizeof(int));// nr de elemente pe care vrem sa le alocam * dimensiunea în octeți a unui el int
       arr = new T[capacity];
    }

// Вместо free / destroy, определите деструктор.

    ~DynamicArray()
    {
        delete[] arr;// elibereaza memoria alocata pentru vector
    }


// Переопределите конструктор копирования.

    DynamicArray(const DynamicArray& other);
    {
        elementCapacity = other.elementCapacity;
        currentIndex = other.currentIndex;
         arr = new T[elementCapacity];
       // arr = (int*)malloc(elementCapacity * sizeof(int));

         std::copy(other.arr, other.arr + currentIndex, arr);
       
    }


//Переопределите оператор присваивания
DynamicArray& operator=(const DynamicArray& other) {
    
            if (this != &other) {
            delete[] arr;

            elementCapacity = other.elementCapacity;
            currentIndex = other.currentIndex;
             arr = new T[elementCapacity];
            //arr = (int*)malloc(elementCapacity * sizeof(int));

            std::copy(other.arr, other.arr + currentIndex, arr);
        }
 return *this;
}
    
// Определите move конструктор.

 DynamicArray(DynamicArray&& other) : arr(nullptr), elementCapacity(0), currentIndex(0) {
    std::cout << "Move constructor called" << std::endl;

  // Крадем указатель из другого объекта.
    arr = other.arr;
    elementCapacity = other.elementCapacity;
    currentIndex = other.currentIndex;

   // Очищаем указатель из другого объекта
    other.arr = nullptr;
    other.elementCapacity = 0;
    other.currentIndex = 0;
}

// Переопределите индексатор под доступ к элементу.
  // int& operator[](size_t index) {
        T& operator[](size_t index){
        assert(index < currentIndex);
        return arr[index];
    }
// Создайте функцию для доступа к элементам массива по индексу. Выполняйте проверку длины в этой функции, используя assert.
// returnez valoarea dupa indexul dat in getElementAtIndex(&arr, 0);
   // int& getElementAt(size_t index) {
        T& getElementAt(size_t index) {
        assert(index < currentIndex);
        return arr[index];// // retrunam ca un int adresa primului element din buffer
    }

// addElementToArray сделайте методом и назовите add.
void add(const T& value) {
        if (currentIndex == elementCapacity) {
            size_t newCapacity = elementCapacity * 2;
             T* newMemoryBlock = new T[newCapacity];
           // int* newMemoryBlock = (int*)malloc(newCapacity * sizeof(int));

            std::copy(arr, arr + currentIndex, newMemoryBlock);
             delete[] arr;

            arr = newMemoryBlock;
            elementCapacity = newCapacity;
        }

        arr[currentIndex] = value;
        currentIndex++;
    }
// Предоставьте возможность считывать значения полей, определив методы size и capacity (read-only properties).
      size_t size() const {
        return currentIndex;
    }
    size_t capacity() const {
        return elementCapacity;
    }
     std::span<T> getSpan() const {
        return std::span<T>(arr, currentIndex);
    }
// В функции main, протестируйте все фичи, и покажите примеры использования.
void test() {

    DynamicArray<int> arr{};
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);

    assert(arr.size() == 3);
    assert(arr[0] == 5);
    assert(arr[1] == 6);
    assert(arr[2] == 7);
    assert(arr.capacity() == 4);

  
    DynamicArray<double> arrDouble(2);
    arrDouble.push_back(3.14);
    arrDouble.push_back(2.71);

    assert(arrDouble.size() == 2);
    assert(arrDouble[0] == 3.14);
    assert(arrDouble[1] == 2.71);
    assert(arrDouble.capacity() == 2);
}

int main() {
  
    DynamicArray<int> arr1{};
    arr1.push_back(5);
    arr1.push_back(6);
    arr1.push_back(7);

    assert(arr1.size() == 3);
    assert(arr1[0] == 5);
    assert(arr1[1] == 6);
    assert(arr1[2] == 7);
    assert(arr1.capacity() == 4);

    
    DynamicArray<double> arr2(2);
    arr2.push_back(3.14);
    arr2.push_back(2.71);

    assert(arr2.size() == 2);
    assert(arr2[0] == 3.14);
    assert(arr2[1] == 2.71);
    assert(arr2.capacity() == 2);

   
    test();

    return 0;
}

/*
Какие ошибки позволяет совершить процедуральная версия по сравнению с OOP версией? (подсказка: публичные поля, создание копий).
Какую версию проще понять / использовать? В каких ситуациях? Почему?

In versiunea procedurala structura si campurile ei sunt publice si in acest fel oricare parte a codului care utilizează obiectul DynamicArray poate accesa și modifica direct membrii sai, fara a trece prin metodele publice ale clasei. 
De asemenea, in cazul procedural, nu avem constructor de copiere, si nici operator de atribuire, iar pentru copierea un obiect DynamicArray, trebuie sa copiem manual datele si sa eliberam resursele vechi.
Cand un obiect este copiat sau atribuit,alocam memorie noua pentru a stoca datele într-un alt bloc de memorie, apoi pentr a elibera memoria veche
Din cauza ca facem aceste lucruri manual, pot aparea erori de gestionare a memoriei

In versiunea OOP putem seta campourileclasei private, avem constructor, destructor, operatorul de atribuire. Astfel operatiile sunt efectuate manual, iar riscul aparitiei erorilor este mai scazut

*/