#include <iostream>
#include <assert.h>
#include <array>
#include <span>
#pragma once

struct DynamicArray
{
    int* arr;
    size_t elementCapacity;
    size_t currentIndex = 0; 
};



DynamicArray createDynamicArrayWithCapacity( size_t capacity );
void addElementToArray (DynamicArray* buffer, int lenght);
int getElementAtIndex(DynamicArray* array, size_t index );
std::span<int> getCurrentSpan(DynamicArray* buffer);
void freeDynamicArray(DynamicArray* buffer);

