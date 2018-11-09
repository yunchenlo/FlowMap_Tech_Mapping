#include <iostream>
using namespace std;

int* t()
{
  int *b=new int[3];
  b[0]=1;
  b[1]=2;
  b[2]=3;
  return b;
} 

int main()
{
  int *a;
  a=t();
  cout << a[2] << endl;

  return 0;
}