#include <iostream>
#include <assert.h>
#include <array>
#include <span>

//Распишите код для структуры данных динамического массива
struct DynamicArray
{
    int* arr;
    size_t elementCapacity;
    size_t currentIndex = 0; 
};

// Создайте factory-функцию, которая возвращает массив изначальной максимальной длины, заданной параметром capacity.
// Создайте еще одну, которая выставляет какой-нибудь дефолтный capacity (например 4).


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

void test1()
{
    DynamicArray arr = createDynamicArrayWithCapacity(10);// Se creează o variabilă arr de tip DynamicArray și se inițializează cu rezultatul apelului funcției createDynamicArrayWithCapacity(10). Se solicită astfel crearea unui obiect DynamicArray cu o capacitate inițială de 10 elemente.
    assert(arr.elementCapacity == 10);
    // Verifică dacă câmpul elementCapacity al obiectului arr este setat corect la 10. daca aceasta conditie nu se adevereste, programul genereaza eroare
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

void test2()
{
    DynamicArray arr = DynamicArray();
   assert(arr.currentIndex == 0);
    addElementToArray(&arr, 5);
    assert(arr.currentIndex == 1);//verifică dacă currentIndex a fost actualizat corect după adăugarea unui element. În acest caz, ar trebui să fie 1, indicând că un element a fost adăugat cu succes.
}

// При добавлении элементов в массив, удваивайте длину, если массив полный. 
//Имеется в виду, аллоцируйте буфер двойной длины, и перекопируйте все элементы. 
//Добавляйте элемент в текущий конец массива.



void test3()
{
    DynamicArray arr = createDynamicArrayWithCapacity(1);// se initializeaza un array cu o capacitatea de 1
    addElementToArray(&arr, 5);
    assert(arr.elementCapacity == 1);
    addElementToArray(&arr, 10);
    assert(arr.elementCapacity == 2);// arrayul atinge capacitatea max, se dubleaza 
    addElementToArray(&arr, 20);
    assert(arr.elementCapacity == 4);// arrayul atinge capacitatea max, se dubleaza 
}

// Создайте функцию для доступа к элементам массива по индексу. Выполняйте проверку длины в этой функции, используя assert.
// returnez valoarea dupa indexul dat in getElementAtIndex(&arr, 0);

int getElementAtIndex(DynamicArray* array, size_t index )
{
   assert(index<array->currentIndex);
   return *(array->arr+index);// retrunam ca un int adresa primului element din buffer
    //return array->arr[index];
}

void test4()
{
    DynamicArray arr = DynamicArray();
    addElementToArray(&arr, 5);// adaugam 5 in prima celula a lui arr
    int el = getElementAtIndex(&arr, 0);// controlam daca elementul arr[0]==5
    assert(el == 5);
}

// Создайте функцию, которая возвращает текущий кусок массива как std::span. 
//Пусть добавление элементов в массив инвалидирует этот взятый кусок (то есть можете не париться и просто стирать эту 
//память без лишних проверок, если надо).

std::span<int> getCurrentSpan(DynamicArray* buffer) 
{
    return std::span<int>(buffer->arr, buffer->currentIndex);
}
/* constructorul std::span creaza un obiect care începe de la adresa buffer->arr și are o lungime dată de buffer->currentIndex. 
std::span oferă vedere asupra datelor, fără a deține sau gestiona memoria, adăugarea de elemente în array 
nu afectează secțiunea preluată.*/

void test5()
{
    DynamicArray arr{};
    addElementToArray(&arr, 5);
    addElementToArray(&arr, 6);
    addElementToArray(&arr, 7);

    std::span<int> span = getCurrentSpan(&arr);// oferă o vedere asupra datelor fără a deține sau gestiona memoria (5, 6, 7)

    assert(span.size() == 3);  // Verifică lungimea secțiunii =3, pentru ca am adăugat 3 elemente
    assert(span[0] == 5);
    assert(span[1] == 6);
    assert(span[2] == 7);
}


// Создайте функцию, которая очищает динамическую память, выделенную функциями массива. 
//Вызывайте эту функцию когда память массива больше не нужна (free / destroy).

void freeDynamicArray(DynamicArray* buffer)
{
    free(buffer->arr);
    buffer->arr = nullptr;
    buffer->elementCapacity = 0;
    buffer->currentIndex = 0;
}
// adaug functia de testare daca se realizeaza freeDynamicArray
void test6()
{
    DynamicArray arr{};

    addElementToArray(&arr, 1);
    addElementToArray(&arr, 2);
    addElementToArray(&arr, 3);
    assert(arr.arr != nullptr);
    assert(arr.currentIndex == 3);

    freeDynamicArray(&arr);
    assert(arr.arr == nullptr);
    assert(arr.elementCapacity == 0);
    assert(arr.currentIndex == 0);
}

/*Создайте функцию main в которой выполняются проверки всех этих фич (в отдельных фнукциях, или в отдельных скоупах). 
Сделайте функции статическими, чтобы их невозможно было притянуть в другом коде. 
По необходимости допишите своих тестов (как минимум 1).*/

static void tests()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
int main()
{
   tests();
    return 0;
}

/*Отделите код связанный со структурой в отдельный файл.

Объявления функций для взаимодейтсвия со структурой и саму структуру положите в файл dynamicArray.h.
В main.cpp включайте файл dynamicArray.h.
В файл dynamicArray.cpp положите имплементации функций.
Можете положить очень короткие функции в dynamicArray.h как inline.
Если есть вспомогательные функции, который используете в коде массива, 
но не в main, сделайте их static и не добавляйте их в dynamicArray.h.
Пропишите команду которой компилируйте в .bat (или .sh) скрипт в папке с лабой.*/
