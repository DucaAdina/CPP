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

///....................Чем переменная a в static_1 отличается от переменной из static_2? (Подсказка: global vs static.) Как сделать пример static_2 эквивалентным первому (в плане невозможности импортировать переменную в другом файле)?
int* stackMemory1()// variabila a se distruge după ce funcția se încheie.
{
    int a = 1;
    return &a;
}

int* stackMemory2()//stiva de apel va distruge variabila b după încheierea funcției.
{
    int b = 2;
    return &b;
}

int main()
{
    int* b = stackMemory1();
    int a1 = *b; // 1
    int* c = stackMemory2();
    int a2 = *c; // 2
    int a3 = *b; // 2

    std::cout << a1 << std::endl; // prints 1
    std::cout << a2 << std::endl; // prints 2
    std::cout << a3 << std::endl; // prints 2
    std::cout << ((std::byte*) b - (std::byte*) c) << std::endl; // prints 0, pointers are equal

    return 0;
}