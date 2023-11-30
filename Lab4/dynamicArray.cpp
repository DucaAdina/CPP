#include "dynamicArray.h"
#include <cstdlib>



DynamicArray createDynamicArrayWithCapacity( size_t capacity )
{
    //  alocăm memorie dinamică pentru un array de întregi, functia returnează un pointer la această zonă de memorie
    //un pointer de tip void* poate stoca adresa oricărui tip de date, deoarece void* este un pointer generic care nu are tip de date specific asociat.
    void* memoryBlock = malloc(capacity * sizeof(int));// nr de elemente pe care vrem sa le alocam * dimensiunea în octeți a unui el int
    //adresa primei celule de 16 bytes
    int* arr = (int*) memoryBlock;// pointerul *arr este inițializat cu adresa primului byte al blocului de memorie alocat anterior

    DynamicArray buffer;
    buffer.arr = arr;
    buffer.elementCapacity = capacity;
    buffer.currentIndex = 0;

    return buffer;
}

//Он должен давать доступ к размерности буфера (capacity), хранить текущее количество элементов (length / count).
void addElementToArray (DynamicArray* buffer, int lenght)
{
    size_t capacity = buffer->elementCapacity;// Se stochează capacitatea curentă a obiectului DynamicArray în variabila capacity

if (buffer->elementCapacity == buffer->currentIndex )// Se verifică dacă obiectul DynamicArray este plin, adică dacă numărul curent de elemente (currentIndex) este egal cu capacitatea totală alocată (elementCapacity). Dacă da, atunci trebuie să realocăm memorie pentru a permite adăugarea unui nou element.
{
// aloc buffer nou *2

   size_t newCapacity = buffer->elementCapacity * 2;
   int* memoryBlock = (int*) malloc(newCapacity * sizeof(int));

   // copiez datele din bufferul vechi
   size_t i = 0;
   while (true)
   {
       if (i >= buffer->elementCapacity)
            break;

        *(memoryBlock + i) = *(buffer->arr + i);
     //   memoryBlock[i] = buffer->arr[i];

        i++;
   }
   // sterg bufferul vechi
    free(buffer->arr);
    // resetez variabilele dupa pointerul DynamicArray
    // buffer->arr pointează deja către noul bloc de memorie alocat
    buffer->arr = memoryBlock;
    buffer->elementCapacity = newCapacity;
    
}

    buffer->arr[buffer->currentIndex] = lenght;//  adaugam elementul nou la sfârșitul arrayului
    buffer->currentIndex = buffer->currentIndex + 1;// poziția următoare în array disponibila pentru noul element
}

int getElementAtIndex(DynamicArray* array, size_t index )
{
   assert(index<array->currentIndex);
   return *(array->arr+index);// retrunam ca un int adresa primului element din buffer
    //return array->arr[index];
}

std::span<int> getCurrentSpan(DynamicArray* buffer) 
{
    return std::span<int>(buffer->arr, buffer->currentIndex);
}


void freeDynamicArray(DynamicArray* buffer)
{
    free(buffer->arr);
    buffer->arr = nullptr;
    buffer->elementCapacity = 0;
    buffer->currentIndex = 0;
}



