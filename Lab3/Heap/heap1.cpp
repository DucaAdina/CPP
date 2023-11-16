

#include <iostream>

int* heapMemory()// functia returneaza pointerul unui int
{
    int* a = new int{};//alocam memorie pentru int. new creaza o variabila la o adresa valoarea 0
    std::cout << "a: " << *a << std::endl;//0 
    // assign to memory at address stored in a = deference a + 1
    *a = *a + 1; 
    std::cout << "a+1: " << *a << std::endl;// valoarea se schimba si este 1, adresa ramane aceeasi
    return a;
}

int main()
{
    int* a = heapMemory(); // prints 0
    int* b = heapMemory(); // prints 0

    // The addresses won't be equal, every new invocation gets a new `a`.
    //fiecare apel a functiei heapMemory alocă memorie nouă, deci a si b au adrese diferite 
    bool areAddressesEqual = ((size_t) a == (size_t) b);
    std::cout << "are addresses equal: " << (areAddressesEqual ? "yes" : "no") << std::endl;

    // valorile sunt egale pentru ca de fiecare data new ofera 0 pentru o noua adresa
    bool areValuesEqual = (*a == *b);
    std::cout << "are values equal: " << (areValuesEqual ? "yes" : "no") << std::endl;

    // And it's legal to use them again, even outside `heapMemory`'s stack frame.
    *a = 5;
    *b = 10;
    // Prints -5.
    std::cout << (*a - *b) << std::endl;

    // Don't forget to reclaim the memory.
    // Forgetting to do this is called a memory leak.
    // Practically, you should always do this, even though all memory
    // is reclaimed automatically when the program exits.
    // Especially in long-lived applications.
    delete a;
    delete b;

    return 0;
}