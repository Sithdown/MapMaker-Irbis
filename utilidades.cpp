// utilidades.cpp

#include <iostream>
#include <string>
#include "utilidades.h"

using namespace std;


string ThreeDigits(int n)
{
    string d1, d2, d3;
    int resto;

    resto = n%10;
    d1 = Digit2Str(resto);
    n = n-resto;

    resto = n%100;
    d2 = Digit2Str(resto);
    n = n-resto;

    resto = n%1000;
    d3 = Digit2Str(resto);
    n = n-resto;

    return d3+d2+d1;
}

string Digit2Str(int n)
{
        switch (n)
    {
        case 0:
            return "0";
        break;

        case 1:
            return "1";
        break;

        case 2:
            return "2";
        break;

        case 3:
            return "3";
        break;

        case 4:
            return "4";
        break;

        case 5:
            return "5";
        break;

        case 6:
            return "6";
        break;

        case 7:
            return "7";
        break;

        case 8:
            return "8";
        break;

        case 9:
            return "9";
        break;
    }
}
