#include<iostream>
using namespace std;
int main(){
    
int i=69;   //Объявить і типа инт, Инициализировать на 69
int number=72; //  Определить переменную number типа инт, дать значение 72

cout <<  "i = " << i << endl;
cout << "number = " << number<< endl;
i +=number; //  Перезаписать значение і на 69 + 72

cout << "i+=number= "<< i <<endl;

int array[3]={0,0,0}; // Определить группу переменных (массив) из 3 элементов (инициализированных на 0)

int* iPointer = &i; // Создать указатель на і (iPointer)

number= *iPointer; // Считать данные по адресу из указателя в переменную number


*iPointer=15; // Вписать в і через указатель значение 15

cout << "i= " << i << endl;

iPointer = &array[0]; // Сменить адрес в iPointer на первый елемент массива

iPointer +=2 ;//Переместиться на 3 элемент массива, используя pointer arithmetic


// Вписать в первый элемент массива напрямую, и в 3 через iPointer, значения 5 и 6
array[0]=5;
cout << "array[0] = " << array[0] <<endl;

*iPointer = 6;
cout << "array[2] = "<< array[2] <<endl;
}