#include <iostream>

void stackMemory()
{
    int a = 0;
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    /*alocarea are loc la chemarea functiei. a este creat cand programul 
    intra in functie si distrus cand functia se termina. Principiul LIFO 
    face ca a+1 sa fie distrus primul atunci cand se iese din functie,
    din acest motiv a devine din nou 0  */
    stackMemory(); // prints 0
    stackMemory(); // prints 0
    stackMemory(); // prints 0
    return 0;
}
