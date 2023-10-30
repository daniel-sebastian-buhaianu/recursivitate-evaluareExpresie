#include <iostream>
#include <fstream>
#include <cstring>
#define LGMAX 204
using namespace std;
// variabile globale
struct { char ns; int v; } TS[LGMAX];
char e[LGMAX];
int i, lg, NrS;
// functii ajutatoare
void Citire();
int eval(char);
int EvaluareExpresie();
int EvaluareFactor();
int EvaluareTermen();
// functia principala
int main()
{
	Citire();
	cout << "Valoarea expresiei este: " << EvaluareExpresie();
	return 0;
}
void Citire()
{
	ifstream fin("evalexp.in");
	fin.getline(e, LGMAX);
	lg = strlen(e);
	while (fin >> TS[NrS].ns >> TS[NrS].v) NrS++;
	fin.close();
}
int eval(char c)
{
	// functia intoarce valoarea operandului c
	int k;
	if (c >= '0' && c <= '9') return c-'0';
	// caut valoarea variabilei in tabela de simboluri
	for (k = 0; TS[k].ns != c; k++);
	return TS[k].v;
}
int EvaluareFactor()
{
	int f;
	if (e[i] == '(') // factorul e o expresie intre paranteze
	{
		i++; // trec peste (
		f = EvaluareExpresie();
		i++; // trec peste )
	}
	else
	{
		// factorul este o litera sau o cifra
		f = eval(e[i]);
		i++; // trec peste factor
	}
	return f;
}
int EvaluareTermen()
{
	int f = EvaluareFactor(); // evaluez primul factor
	while (i < lg && e[i] == '*') // mai urmeaza factori
	{
		i++; // trec peste *
		f *= EvaluareFactor();
	}
	return f;
}
int EvaluareExpresie()
{
	int t = EvaluareTermen(); // evaluez primul termen
	while (i < lg && e[i] == '+') // mai urmeaza termeni
	{
		i++; // trec peste +
		t += EvaluareTermen();
	}
	return t;
}
// solutia oficiala
