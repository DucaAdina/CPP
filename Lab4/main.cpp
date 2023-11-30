#include "dynamicArray.h"
#include <cassert>

void test1()
{
    DynamicArray arr = createDynamicArrayWithCapacity(10);// Se creează o variabilă arr de tip DynamicArray și se inițializează cu rezultatul apelului funcției createDynamicArrayWithCapacity(10). Se solicită astfel crearea unui obiect DynamicArray cu o capacitate inițială de 10 elemente.
    assert(arr.elementCapacity == 10);
    // Verifică dacă câmpul elementCapacity al obiectului arr este setat corect la 10. daca aceasta conditie nu se adevereste, programul genereaza eroare
}

void test2()
{
    DynamicArray arr = DynamicArray();
   assert(arr.currentIndex == 0);
    addElementToArray(&arr, 5);
    assert(arr.currentIndex == 1);//erifică dacă currentIndex a fost actualizat corect după adăugarea unui element. În acest caz, ar trebui să fie 1, indicând că un element a fost adăugat cu succes.
}
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

void test4()
{
    DynamicArray arr = DynamicArray();
    addElementToArray(&arr, 5);// adaugam 5 in prima celula a lui arr
    int el = getElementAtIndex(&arr, 0);// controlam daca elementul arr[0]==5
    assert(el == 5);
}

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