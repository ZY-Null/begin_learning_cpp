#include <stdio.h>
#include "public/stl_encap/array_new.hpp"

void FuncTest()
{
    CEntityArray<int, 10> cArray;
    
    for(int i = 1; i <= 10; i++)
    {
        cArray[i] = i*i*i;
    }
    for(int i = 1; i <= 10; i++)
    {
        printf("%d, ", cArray[i]);
    }
    printf("\n");
    
    for(int i = -1; i >= -10; i--)
    {
        printf("%d, ", cArray[i]);
    }
    printf("\n");
    
    return;
}

void FuncTest2()
{
    CCycleArray<int, 10> cArray;
    for(int i{0}; i < 10; i++)
    {
        cArray[i] = i * i;
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d, ", cArray[i]);
    }
    printf("\n");

    cArray.Push(99);
    for(int i = 0; i < 10; i++)
    {
        printf("%d, ", cArray[i]);
    }
    printf("\n");

    cArray.Push(66);
    for(int i = 0; i < 10; i++)
    {
        printf("%d, ", cArray[i]);
    }
    printf("\n");
    
}

int main(int argc, char const *argv[])
{
    FuncTest();
    FuncTest2();
    return 0;
}
