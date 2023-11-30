#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    TwoInts i2 = { }; // declaram o structură i2, (0 pentru a și b 0000 0000 )
    i2.a = 5; // schimbam i2 a la 5 
    i2.b = 7; // schimbam i2 a la 7 
    // adress36 0005 
    // adress40 0007
    std::cout << i2.a << std::endl; // afisam a i2 (5)
    std::cout << i2.b << std::endl; // afisam b i2 (7)

    StructWithArray s = { }; // adress8 0 pentru toate elementele
    s.arr[0] = 10; // adress44 00010 adress48 0000 adress52 0000 adress56 0000 adress60 0000 adress64 0000

    StructWithArray s1 = { }; // 0 pentru toate elementele de la adresele 68-88
    s1.arr[0] = 15; // adress68 00015

    StructWithArray* sPointer = &s; // adress92 0000 adress96 00044 scriem adresa de inceput a structurii s in pointerul care ocupa 8bytes
    sPointer->arr[0] = 20; // Prin intermediul pointerului sPointer, setam primul element al arrayului din structura s la 20  adress44 00020

    std::cout << s.arr[0] << std::endl; // 20
    s.arr[0] = 25; // adress44 00025
    std::cout << s.arr[0] << std::endl; // 25

    sPointer->arr[0] = 30; // adress44 00030
    std::cout << s.arr[0] << std::endl; // 30

    sPointer = &s1; // schimbam pointerul sPointer să indice către structura s1

    sPointer->arr[0] = 35; // primul element din s1=35 adresss68 00035
    std::cout << s.arr[0] << std::endl; // 30
    std::cout << s1.arr[0] << std::endl; // 35

    StructWithArray structArray[2] = { }; // array din 2 structuri 0 pentru toate elementele
    structArray[0].arr[3] = 77; // adress112 00077
    structArray[1].someNumber = &structArray[0].arr[3]; // adress138-142 0000 000112 (adrsa112)

    sPointer = &s; // sPointer indică  către adresa din structura s adress92-96 0000 00044
    int* pointer = &sPointer->arr[3]; // declaram un pointer care indică la elementul 3 al array-ului din structura s    adress146-150 0000 00056 (adresa lui arr[0] din s)
    s.arr[3] = 72; // adress56 00072
    std::cout << *pointer; // 72

    StructWithArray memory; 
    memset(&memory, 0, sizeof(StructWithArray)); // toti octetii din structura 0

    return 0;
}
