
#include <iostream>

using std::cout, std::cin, std::endl;

int mystery(int, int);

int main()
{
 int x, y;

 cout << "Entre com dois inteiros: ";
 cin >> x >> y;
 cout << "Resultado: " << mystery(x, y) << endl;
 return 0;
}

//O parâmetro b deve ser um inteiro positivo
int mystery(int a, int b)
{
 if (b == 1)
   return a;
 else
   return a + mystery(a, b - 1);
}

