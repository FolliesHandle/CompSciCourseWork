/****************************************************************************
    Dominic Mazza
    Computer Project #5
  ****************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "proj05.support.h"

/*---------------------------------------------------------------------------
    Name: temp_checker
    Purpose:  Checks if a digit is larger than the base
    Receive:  The base and the digit
    Return:   A boolean representing whether or not temp is geq base
---------------------------------------------------------------------------*/
bool temp_checker(const int temp, const int base)
{
  if (temp >= base)
  {
    return true;
  }
  return false;
};

/*---------------------------------------------------------------------------
    Name: main
    Purpose:  Test cases for function
    Receive:  Nothing
    Return:   Nothing
---------------------------------------------------------------------------*/
int main(){
  char test1[5] = "12345 ";
  int base = 10;
  int representation = 0;
  convert(test1, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b11000000111001)
  {
    printf("%s\n", "test1 success\n");
  }

  char test2[4] = "1D1F ";
  base = 16;
  representation = 0;
  convert(test2, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b1110100011111)
  {
    printf("%s\n", "test2 success\n");
  }

  char test3[6] = "+12345 ";
  base = 10;
  representation = 0;
  convert(test3, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b11000000111001)
  {
    printf("%s\n", "test3 success\n");
  }

  char test4[6] = "-12345 ";
  base = 10;
  representation = 0;
  convert(test4, base, &representation);
  printf("%d\n", representation);
  if(representation == -0b11000000111001)
  {
    printf("%s\n", "test4 success\n");
  }

  char test5[4] = "1224 ";
  base = 8;
  representation = 0;
  convert(test5, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b1010010100)
  {
    printf("%s\n", "test5 success\n");
  }

  char test6[7] = "12345 \n";
  base = 10;
  representation = 0;
  convert(test6, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b11000000111001)
  {
    printf("%s\n", "test6 success\n");
  }

  char test7[7] = "12345 \t";
  base = 10;
  representation = 0;
  convert(test7, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b11000000111001)
  {
    printf("%s\n", "test7 success\n");
  }

  char test8[6] = "12345 ";
  base = 10;
  representation = 0;
  convert(test8, base, &representation);
  printf("%d\n", representation);
  if(representation == 0b11000000111001)
  {
    printf("%s\n", "test8 success\n");
  }

  char test9[5] = "";
  base = 10;
  representation = 0;
  if(convert(test9, base, &representation) == 0)
  {
    printf("%s\n", "test9 success\n");
  }
};
