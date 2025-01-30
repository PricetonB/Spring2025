#include <iostream>
using namespace std;

int add(int a, int b);


void print(int& num) {
  cout <<  &num <<  " " << sizeof(num) << " " << num << "\n";
} 


int main() 
{
	int a = 5;
	int b = 7;
  print(a);
  print(b);
}


