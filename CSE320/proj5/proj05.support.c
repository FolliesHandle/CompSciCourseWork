#include <stdio.h>
#include <stdbool.h>
#include "proj05.support.h"

/*---------------------------------------------------------------------------
    Name: celsius2fahrenheit
    Purpose:  Convert a number from any base to its twos compliment
    Receive:  Character string of the number, int representing base, address to store representation
    Return:   A 1 if the conversion was succesful, a 0 if not
---------------------------------------------------------------------------*/
int convert(const char str[], int base, int* representation)
{
  *representation = 0;
  bool flag_val = false; //represents if a value has been found yet
  bool flag_neg = false; //represents if theres a negative value
  int i = 0;
  // Runs through all items in the list and converts one by one while adding to
  // representation
  while(str[i] != 0){

    if(str[i] == '-'){
      if(flag_val)
      {
        break;
      }
      flag_neg = true;
      i++;
    }
    else if(str[i] == '+')
    {
      if(flag_val)
      {
        break;
      }
      i++;
    }
    else if(str[i] == '\t')
    {
      if(flag_val)
      {
        break;
      }
      i++;
    }
    else if(str[i] == '\n')
    {
      if(flag_val)
      {
        break;
      }
      i++;
    }
    else if(str[i] == ' ')
    {
      if(flag_val)
      {
        break;
      }
      i++;
    }
    else if(str[i] <= '9' && str[i] >= '0'){
      int temp = str[i] - '0';
      if(temp_checker(temp, base)){ break;}
      *representation = *representation*base + temp;
      i++;
      flag_val = true;
    }
    else if(str[i] <= 'Z' && str[i] >= 'A'){
      int temp = (str[i] - 'A') + 10;
      if(temp_checker(temp, base)){ break;}
      *representation = *representation*base + temp;
      i++;
      flag_val = true;
    }
    else if (str[i] <= 'z' && str[i] >= 'a')
    {
      int temp = (str[i] - 'a') + 10;
      if(temp_checker(temp, base)){ break;}
      *representation = *representation*base + temp;
      i++;
      flag_val = true;
    }
    else
    {
      break;
    }
  }

  if(flag_neg == true){
    *representation = 0 - *representation;
  }
  else if (flag_val == true){
    return 1;
  }
  return 0;
}
