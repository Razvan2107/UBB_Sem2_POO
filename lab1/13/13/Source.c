#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
Aceasta functie verifica daca un numar este un numar prim
:param x: numarul care se va verifica daca e prim
:return: 1/True in cazul afirmativ, respectiv 0/False contrar
*/
bool prim(int x)
{
	if (x == 0 || x == 1)
		return 0;
	else if (x == 2)
		return 1;
	else if (x % 2 == 0)
		return 0;
	else
		for (int d = 3; d <= x/2; d += 2)
			if (x % d == 0)
				return 0;
	return 1;
}

/*
Aceasta functie verifica daca al doilea parametru este un divizor prim al primului parametru
:param n: primul parametru care  este numarul mai mare
:param d: al doilea parametru care este numarul mai mic
:return: 1/True daca d este divizor prim al lui n si 0/False daca d nu este divizor al lui n sau daca nu este prim
:rtype: bool
*/
bool divizor(int n, int d)
{
	return n % d == 0 && prim(d);
}

/*
Aceasta functie calculeaza radacina patrata a unui numnar
:param n: numarul caruia i se va calcula radacina patrata
:return: radacina patrata
:rtype: float
*/
float radacina(int n)
{
	double i = 0, j = n/2;
	while (j != i) 
	{
		i = j;
		j = (n / i + i) / 2;
	}
	return j;
}

/*
Aceasta functie afiseaza un numar real cu un anumit numar de cifre de dupa virgula
:param n: numarul real
:param d: numarul de cifre de dupa zecimale
:return: numarul real cu un numar precizat de virgule
:rtype: float
*/
float precizie(int n,int d)
{
	int zecimale = 1,i=1;
	while (i <= d)
	{
		zecimale *= 10;
		i++;
	}
	return ((int)(zecimale * radacina(n)))/(float)zecimale;
}

int main()
{
	bool ok = 0;
	printf("Optiunile disponibile sunt: \n 1.problema 13 \n 2.problema 7 \n 3.exit \n");
	while (ok == 0)
	{
		int opt;
		printf("Optiunea aleasa este : ");
		scanf_s("%d", &opt);
		if (opt == 1)
		{
			int n, d = 2;
			printf("Numarul care se va descompune in factori primi este: ");
			scanf_s("%d", &n);
			while (d <= n)
			{
				if (divizor(n, d))
				{
					printf("%d \n", d);
					while (n % d == 0)
						n /= d;
				}
				d++;
			}
		}
		else if (opt == 2)
		{
			int n,d;
			printf("Numarul caruia i se afla radacina patrata este: ");
			scanf_s("%d", &n);
			printf("Numarul de zecimale ale preciziei este de: ");
			scanf_s("%d", &d);
			printf("%f \n", precizie(n,d));
		}
		else if (opt == 3)
		{
			ok = 1;
			printf("La revedere!\n");
		}
		else
			printf("Comanda invalida!\n");
	}
	return 0;
}