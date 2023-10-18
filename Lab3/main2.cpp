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

//Попробуйте скомпилировать только файл main.cpp. Объясните ошибки
/*daca executam doar main.cpp, el genereaza eroare deoarece
 este prezent doar prototipul functiei si nu este definit ce returneaza functia
 definitia functiei din f.cpp face ca programul sa lucreze*/

//Добавьте к определению функции модификатор static Попробуйте скомпилировать. Объясните ошибки
/* static int hello (int parameter);
eroarea apare din cauza ca modificatorul static permite utilizarea si accesarea functiei doar in 
fisierul in care a fost declarata */

//Перекопируйте определение функции в main.cpp (включая static) Попробуйте скомпилировать. Объясните почему работает
/* int hello (int parameter)
{
 return parameter;
}

dupa ce am oferit definitie, functia statica pastreaza valorile pe tot parcursul programului din acest fisier si poate
rula pentru ca exista corpul functiei  */

//Объясните сколько копий тела функции hello скомпилируется в финальный executable (можете предположить, что компилятор не уберет неиспользованные копии)
// in acest caz vor fi doua copii ale corpului functiei, unul definit in main.cpp, altul in f.cpp

/*Для укрепления можете проделать то же с глобальной переменной, но это по желанию.
 Глобальные переменные мы не будет привязывать в других файлах, передавайте контекст параметрами

int parameter = 100;

int main() {
    int result = hello(parameter);
     std::cout << result;
    return 0;
}

*/



