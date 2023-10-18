#include <iostream>

//Объявите в новом файле f.cpp функцию которая принимает int и возвращает int с именем hello
/* int hello (int parameter); */

//Попробуйте скомпилировать (оба файла разом). Объясните ошибки
/*apare eroare din cauza nedefinirii functiei, compilatorul nu stie ce trebuie sa faca u acest parametru  */

//Определите фунцию hello в файле f.cpp и попробуйте скомпилировать. (Должно пойти)

int hello (int parameter)
{
 return parameter;
}

/*
Для укрепления можете проделать то же с глобальной переменной, но это по желанию.
 Глобальные переменные мы не будет привязывать в других файлах, передавайте контекст параметрами
 
int hello(int parameter) 
{
    return parameter;
}
*/