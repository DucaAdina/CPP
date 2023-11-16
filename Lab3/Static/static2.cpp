#include <iostream>

int a = 0;

void staticMemory()
{
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

/*Variabila a este definită ca o variabilă globală în afara oricărei funcții. 
Acest lucru înseamnă că variabila a este vizibilă și poate fi accesată din oricare 
funcție din program. Ea are o durată de viață care coincide cu durata de 
funcționare a programului. De aceea, variabila a își păstrează valoarea 
între apelurile funcției staticMemory(), și rezultatele sunt consecutive (0, 1, 2).

in programul 1 Variabila a este definită ca o variabilă statică în interiorul 
funcției staticMemory(). O variabilă statică are o durată de viață care depășește durata de viață a funcției, dar nu este vizibilă în afara funcției. Cu toate acestea, deoarece variabila a este statică, ea își păstrează valoarea între apelurile funcției staticMemory(), ceea ce duce la aceleași rezultate consecutive (0, 1, 2).


*/