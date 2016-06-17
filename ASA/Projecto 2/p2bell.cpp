#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <algorithm>
using namespace std;

struct Ligacao {
	int origem;
	int destino;
	int custo;
};
vector<Ligacao> grafo;

vector<int> distancias;

vector<int> filiais;

vector<int> perda;

vector<int> perda_filiais;

int n_localidades;
int n_filiais;
int n_ligacoes;

int ponto_de_encontro;
int perda_total;

const int INFINITO = INT_MAX;

void print_output(){
	if(ponto_de_encontro == 0){
		cout << "N";
	}
	else {
		cout <<  ponto_de_encontro << " " << perda_total << "\n";
		for (int i = 0; i < n_filiais; i++)
		{
			cout << perda_filiais[i] << " ";
		}		
	}
	cout << "\n";
}
void get_ponto_de_encontro(){
	vector<int>::iterator result = min_element(perda.begin(),perda.end());
	ponto_de_encontro = distance(perda.begin(),result);
	perda_total = *result;
}

void bellman_ford(int filial){
	vector<Ligacao>::iterator it_ligacao;
	for (int i = 1; i < n_localidades + 1; i++) {
		bool flag = true;
		for (it_ligacao = grafo.begin(); it_ligacao != grafo.end(); it_ligacao++) {
			Ligacao e = *it_ligacao;
			if (distancias[e.origem] != INFINITO && distancias[e.origem] + e.custo < distancias[e.destino]){
				distancias[e.destino] = distancias[e.origem] + e.custo;
				flag = false;
			}
		}
		if(flag){break;}
	}
    for(int i = 1; i <= n_localidades; i++){
    	if (distancias[i] == INFINITO  || perda[i] == INFINITO)
    	{
    		perda[i] = INFINITO;
    	}
    	else{
    		perda[i] += distancias[i];
    	}
    }
}

void bellman_ford_2(int filial, int index_filial){
	vector<Ligacao>::iterator it_ligacao;
	for (int i = 1; i < n_localidades + 1; i++) {
		bool flag = true;
		for (it_ligacao = grafo.begin(); it_ligacao != grafo.end(); it_ligacao++) {
			Ligacao e = *it_ligacao;
			if (distancias[e.origem] != INFINITO && distancias[e.origem] + e.custo < distancias[e.destino]){
				distancias[e.destino] = distancias[e.origem] + e.custo;
				flag = false;
			}
		}
		if(flag){break;}
	}
	perda_filiais[index_filial] = distancias[ponto_de_encontro];

}

int main()
{
	/* Leitura 1a linha de input */
	cin >> n_localidades >> n_filiais >> n_ligacoes;
	/* Inicializacao das estruturas */	

	/* Leitura das filiais */
	for (int i = 0; i < n_filiais; i++){
		int filial;
		cin >> filial;
		filiais.push_back(filial);
	}
	/* Leitura das ligacoes */
	for (int i = 0; i < n_ligacoes; i++){
		int v1, v2, peso;
		cin >> v1 >> v2 >> peso;
		Ligacao l = {v1,v2,peso};
		grafo.push_back(l);
	}

	perda = vector<int>(n_localidades + 1, 0);
	perda[0] = INFINITO;
	for (int i = 0; i < n_filiais; ++i)
	{
		int filial = filiais[i];
		distancias = vector<int>(n_localidades + 1, INFINITO);
		distancias[filial] = 0;
		bellman_ford(filial);
	};

	get_ponto_de_encontro();
	perda_filiais = vector<int>(n_filiais, 0);
	for (int i = 0; i < n_filiais; ++i)
	{
		int filial = filiais[i];
		distancias = vector<int>(n_localidades + 1, INFINITO);
		distancias[filial] = 0;
		bellman_ford_2(filial, i);
	}
	/* Apresentar resultados */
	print_output();

	return 0;
}