#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void printFactors(long long int number)
{
  for (long long int divsor = 1; divsor <= number; divsor++)
  {
    if (number % divsor == 0)
      printf("%lld ", divsor);
  }
  printf("\n");
}

void primeChecker(long long int number)
{
  int count = 0;
  for (int divsor = 2; divsor <= number / 2; divsor++)
  {
    if (number % divsor == 0)
    {
      count++; // seems easier than returning TRUE
      break;
    }
  }

  if (count == 0 && number != 1)
  {
    printf("The number %lld is a prime number.\n", number);
  }
  else
  {
    printf("The number %lld has the factors ", number);
    printFactors(number);
  }
}

int main(int argc, char *argv[])
{

  if (argc <= 1)
  {
    printf("Please enter into the cmd line\n");
    return -1;
  }

  long long int input = atol(argv[1]);

  if (input <= 0)
  {
    printf("Please input a positive whole number\n");
    return -1;
  }

  printf("PrimeChecker V.1) Prime number entered = %lld\n", input);

  primeChecker(input);
}
