#include <iostream>
#include <stdlib.h>

// This is the same example, but with the malloc() function,
// it uses the C heap instead of the C++ heap.

int* heapMemory()// functia returneaza un pointer a unui int
{
    void* memory = malloc(sizeof(int));// aloca un spațiu de memorie de dimensiunea unui întreg
    // malloc aloca spațiu pentru date la runtime 
    int* a = (int*) memory;//  memory care returna void, este convertit la int pentru a putea fi utilizat pentru stocarea unui întreg
    *a = 0; /*daca in exemplul 1 initializarea cu 0 o facea new, acum noi atribuim aceasta valoare,
    in caz  contrar la aceasta adresa se pot pastra valori precedente*/  
    std::cout << "a: " << *a << std::endl;
    *a = *a + 1;
     std::cout << "a+1: " << *a << std::endl;
    return a;
}

int main()
{
    int* a = heapMemory(); // prints 0
    int* b = heapMemory(); // prints 0

    // no
    bool areAddressesEqual = ((size_t) a == (size_t) b);
    std::cout << "are addresses equal: " << (areAddressesEqual ? "yes" : "no") << std::endl;

    // yes
    bool areValuesEqual = (*a == *b);
    std::cout << "are values equal: " << (areValuesEqual ? "yes" : "no") << std::endl;

    *a = 5;
    *b = 10;
    // Prints -5.
    std::cout << (*a - *b) << std::endl;

    //free  elibereaza spațiul alocat la inceputul programului
    free(a);
    free(b);

    return 0;
}