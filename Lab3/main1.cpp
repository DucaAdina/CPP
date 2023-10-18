#include <iostream>

//Объявите в новом файле main.cpp функцию которая принимает int и возвращает int с именем hello

int hello (int parameter);

//Вызовите функцию в функции main и выведите результат в консоль

int main()
{
    int result = hello(100);
    std::cout << result;
    return 0;
}
//Попробуйте скомпилировать. Объясните полученную ошибку

 /*daca executam doar codul pana la acest moment, el genereaza eroare deoarece
 este prezent doar prototipul functiei si nu este definit ce returneaza functia*/

//Определите функцию в файле main.cpp (любое валидное тело) и попробуйте скомпилировать. (Должно пойти)
int hello (int parameter)
{
    return parameter;
}


