#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 10
#define E 50
using namespace std;

int main()
{
    srand((int)time(NULL));
    cout << V << " " << E << endl;
    for(int i = 0; i < E; i++) 
    {
            cout << rand() % V << " " << rand() % V << " " << 1 << endl;
    }
    cout << rand() % V  << " " << rand() % V << endl;
}