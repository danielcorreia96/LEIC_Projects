#include <stdio.h>
/*Projecto IAED - Rede de Bancos*/

#define MAXNOME		42
#define MAXBANCOS 	1000
#define	BOM			1
#define	MAU			0

typedef struct banco {
	char nome[MAXNOME];
	int classificacao;
	long int ref;
	int parceiros;
	int dinheiro[MAXBANCOS];
}Banco;

Banco adicionaBanco();
void classmauBanco();
void promoveBanco();
void emprestimo();
void amortizar();
void listagem1();
void listagem1_aux(int i);
void despromover();
void numerobancos();
void listarbancos();
void ligacoes();

/*Variaveis globais*/
Banco lista[MAXBANCOS];
int contador;

int main()
{
	int n;
	char comando;
	while (1)	{
		comando = getchar();
		switch (comando) {
			case 'a': /*AdicionaBanco*/
				lista[contador] = adicionaBanco();
				contador += 1;
				break;
			case 'k':/*classmauBanco*/
				classmauBanco();
				break;
			case 'r':/*promoveBanco*/
				promoveBanco();
				break;
			case 'e':/*emprestimo*/
				emprestimo();
				break;
			case 'p':/*amortizar*/
				amortizar();
				break;
			case 'l':/*listagem*/
				scanf("%d", &n);
				if (n==0)
					listarbancos();
				else if (n == 1)
					listagem1();
				else if (n==2)
					ligacoes();
				break;
			case 'K':/*despromover*/
				despromover();
				break;
			case 'x':
				numerobancos();
				return 0;
		}
		getchar();
	}
	return 0;
}
Banco adicionaBanco() {
	Banco a;
	scanf("%s", a.nome);
	scanf("%d", &a.classificacao);
	scanf("%ld", &a.ref);
	return a;
}

void classmauBanco() {
	long int ref;
	int i=0;
	scanf("%ld", &ref);
	while (i <= contador) {
		if (lista[i].ref == ref) {
			lista[i].classificacao = MAU;
		}
		i++;
	}
}

void promoveBanco() {
	long int ref;
	int i=0;
	scanf("%ld", &ref);
	while (i <= contador) {
		if (lista[i].ref == ref) {
			lista[i].classificacao = BOM;
		}
		i++;
	}
}

void emprestimo() { /*ref 1 empresta a ref 2 - comando e*/
	long int ref1, ref2;
	int i, valor, indice1=0, indice2=0;
	scanf("%ld", &ref1);
	scanf("%ld", &ref2);
	scanf("%d", &valor);
	for (i = 0; i < contador; i++)
	{
		if (ref1 == lista[i].ref)
			indice1 = i;
		else if (ref2 == lista[i].ref)
			indice2 = i;
	}
	if (lista[indice2].dinheiro[indice1] == 0 && lista[indice1].dinheiro[indice2] == 0) {
		lista[indice2].parceiros += 1;
		lista[indice1].parceiros += 1;
	}
	lista[indice2].dinheiro[indice1] += valor;
}

void amortizar() { /*ref1 paga ao ref2 - comando p*/
	long int ref1, ref2;
	int i, valor, indice1=0, indice2=0;
	scanf("%ld", &ref1);
	scanf("%ld", &ref2);
	scanf("%d", &valor);
	for (i = 0; i < contador; i++)
	{
		if (ref1 == lista[i].ref)
			indice1 = i;
		else if (ref2 == lista[i].ref)
			indice2 = i;
	}
	if (valor <= lista[indice1].dinheiro[indice2])
		lista[indice1].dinheiro[indice2] -= valor;

	if (lista[indice2].dinheiro[indice1] == 0 && lista[indice1].dinheiro[indice2] == 0) {
		lista[indice2].parceiros -= 1;
		lista[indice1].parceiros -= 1;		
	}
}

void despromover() {
	int i,j, indice=0, soma, maior_soma = 0;
	for (i = 0; i < contador; i++) {

		if (lista[i].classificacao == BOM) {
			soma = 0;
			for (j = 0; j < contador; j++) {

				if (lista[j].classificacao == MAU)
					soma += lista[j].dinheiro[i]; 
			}
		
			if (soma >= maior_soma) {
				maior_soma = soma;
				indice = i;
			}
		}
	}
	if (maior_soma != 0)
		lista[indice].classificacao = MAU;
		printf("*");
		listagem1_aux(indice);
		numerobancos();

}


void numerobancos(){
	int i,contador2=0;
	for (i = 0; i < contador; i++) {
		if (lista[i].classificacao == BOM) {
			contador2++;
		}
	}
	printf( "%d %d\n", contador, contador2);
}

void listarbancos(){
	int i;	
	for (i = 0; i < contador; i++) {
		printf("%ld %s %d\n", lista[i].ref, lista[i].nome, lista[i].classificacao);
	}
}

void listagem1() {
	int i;
	for (i = 0; i < contador; i++) {
		listagem1_aux(i);
	}
}

void listagem1_aux(int i) {
	int j, inp = 0, outp = 0, outv = 0, outvm = 0, inv = 0, invm = 0;
	for (j = 0; j < contador; j++) {
	/* Parceiros a quem o banco a tem uma divida - inp, inv, invm */
		if (lista[i].dinheiro[j] > 0) {
			inp += 1;
			inv += lista[i].dinheiro[j];
			if (lista[j].classificacao == MAU)
				invm += lista[i].dinheiro[j];
		}
	/* Parceiros a quem o banco a emprestou - outp, outv, outvm */
		if (lista[j].dinheiro[i] > 0) {
			outp += 1;
			outv += lista[j].dinheiro[i];
			if (lista[j].classificacao == MAU)
				outvm += lista[j].dinheiro[i];
		}
	}
	printf("%ld %s %d %d %d %d %d %d %d\n",lista[i].ref, lista[i].nome, lista[i].classificacao, inp, outp, outv, outvm, inv, invm);
}
/*void ligacoes() {
	int l,i,j,num_ligacoes,num_bancos;
	for (l = 0; l <= contador; l++) {
		num_bancos = 0;
		for (i=0; i < contador; i++) {
			num_ligacoes = 0;
			for (j=0; j < contador; j++) {
				if (lista[i].dinheiro[j] != 0 || lista[j].dinheiro[i] != 0)
					num_ligacoes++;
				else if
			}
			if (num_ligacoes == l)
				num_bancos++;
		}
		if (num_bancos != 0)
			printf("%d %d\n", l, num_bancos);
	}
}*/

void ligacoes() {
	int l,i,num_bancos;
	for (l = 0; l <= contador; l++) {
		num_bancos = 0;
		for (i=0; i < contador; i++) {
			if (lista[i].parceiros == l)
				num_bancos++;
		}
		if (num_bancos != 0)
			printf("%d %d\n", l, num_bancos);
	}
}
