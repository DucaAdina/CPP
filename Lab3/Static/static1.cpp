#include <iostream>
/*
Чем переменная a в static_1 отличается от переменной из static_2? 
(Подсказка: global vs static.) Как сделать пример static_2 эквивалентным первому 
(в плане невозможности импортировать переменную в другом файле)?*/
void staticMemory()
{
    static int a = 0;
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    staticMemory(); // prints 0
    staticMemory(); // prints 1
    staticMemory(); // prints 2
    return 0;
}

/* variabila a este declarată ca o variabilă statică în interiorul funcției 
staticMemory(). 
O variabilă statică are o durată de viață care depășește durata de viață a 
funcției în care este definită. Aceasta înseamnă că variabila a nu este distrusă 
la încheierea funcției, ci își păstrează valoarea între apelurile funcției.
De aceea, prima dată când se apelează staticMemory(), variabila a este inițializată cu 0
La fiecare apel ulterior, valoarea sa este păstrată și incrementată
Astfel, variabila a păstrează o stare persistentă între apelurile funcției, 
ceea ce duce la rezultate diferite.*/