#include <stdlib.h>
#include <iostream>
#include <cstddef>

// This program was designed to show you how the stack works.
// You shouldn't dereference pointers which are no longer in scope.
// Never do that, it's undefined behavior (anything can happen).

// Note that this program may break if you use optimizations.
// Also, I have only tried it on Zig C++ (Clang) on Windows.

// Also note, that this produces a warning on Zig C++ (Clang), which is expected.

// See the excel file for a visualization of the stack.

int* stackMemory1() 
{
    /*functia aloca memorie pentru variabila locala, atribuie valoare si returneaza adresa ei. la sfarsit, 
    variabila se disctruge */
    int a = 1;
    return &a;
}

int* stackMemory2()
{
    int b = 2;
    return &b;
}

int main()
{
    /* variabila b pastreaza adresa unei celule aleatorie din memorie, fiindca variabila definita
    in stackMemory1 nu mai exista */
    int* b = stackMemory1();
    /*posibil ca var a1 contine valoarea 1, dar nu este garantat, pentru ca memoria nu este gestionata de aplicatie*/
    int a1 = *b; // 1
    /* variabila b pastreaza adresa unei celule aleatorie din memorie, fiindca variabila definita
    in stackMemory2 nu mai exista. Functia StackMemory2 va utiliza aceeasi memorie ca StackMemory1, 
    atunci valoarea c==b*/
    int* c = stackMemory2();
    int a2 = *c; // 2
    int a3 = *b; // 2

    std::cout << a1 << std::endl; // prints 1
    std::cout << a2 << std::endl; // prints 2
    std::cout << a3 << std::endl; // prints 2
    std::cout << ((std::byte*) b - (std::byte*) c) << std::endl; // prints 0, pointers are equal

    return 0;
}