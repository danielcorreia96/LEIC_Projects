#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <algorithm>
using namespace std;

struct Ligacao {
	int destino;
	int custo;
};
vector< vector<Ligacao> > grafo;
vector<int> filiais;
vector<int> pesos_h;
vector<int> caminhos;
vector<int> perda;
int n_localidades;
int n_filiais;
int n_ligacoes;
int ponto_de_encontro;

const int INFINITO = INT_MAX;

void print_output(int perda_total){
	if(ponto_de_encontro == 0){
		cout << "N";
	}
	else {
		cout <<  ponto_de_encontro << " " << perda_total << "\n";
		for (int i = 0; i < n_filiais; i++)
		{
			cout << caminhos[i] - pesos_h[filiais[i]] + pesos_h[ponto_de_encontro] << " ";
		}		
	}
	cout << "\n";
}
int get_ponto_de_encontro(){
	vector<int>::iterator result = min_element(perda.begin(),perda.end());
	ponto_de_encontro = distance(perda.begin(),result);
	return *result;
}

void bellman_ford(){
	vector<Ligacao>::iterator it_ligacao;
	pesos_h = vector<int>(n_localidades + 1,0);
	for (int i = 1; i < n_localidades + 1; i++) {
		for (int n = 0; n < n_localidades + 1; n++) {
			if (grafo[n].size() != 0){
				for (it_ligacao = grafo[n].begin(); it_ligacao != grafo[n].end(); it_ligacao++) {
					Ligacao e = *it_ligacao;
					if (pesos_h[n] != INFINITO && pesos_h[n] + e.custo < pesos_h[e.destino])
						pesos_h[e.destino] = pesos_h[n] + e.custo;
				}				
			}
		}
	}
}

void grafo_repesagem(){
	/* Iterador para for each ligacao num grafo[i] */
	vector<Ligacao>::iterator it_ligacao;

	/* Adicionar arco para 0 */
	for(int i = 1; i < n_localidades + 1; i++){
		Ligacao e = {i,0};
		grafo[0].push_back(e);
	}
	/* Aplicacao do bellman-ford */
	bellman_ford();

	 /* Repesagem */
	for (int i = 1; i <= n_localidades; ++i){
		for (it_ligacao = grafo[i].begin(); it_ligacao != grafo[i].end(); it_ligacao++){
			Ligacao& e = *it_ligacao;
			e.custo = e.custo + pesos_h[i] - pesos_h[e.destino];
		}
	}
}


void dijkstra(int filial, int index_filial){
	vector<Ligacao>::iterator it_ligacao;
	vector<int> distancia(n_localidades + 1, INFINITO);
	set< pair<int,int> > conjunto;

	conjunto.insert(pair<int,int>(0,filial));

	while(conjunto.empty() == false){
		pair<int,int> topo = *conjunto.begin();
		conjunto.erase(conjunto.begin());
		int d = topo.first;
		int n = topo.second;
		distancia[n] = d; // distancia mais curta ate n tem valor d

		if(grafo[n].size() != 0){
			for(it_ligacao = grafo[n].begin(); it_ligacao != grafo[n].end(); it_ligacao++){
				Ligacao e = *it_ligacao;
				if (distancia[n] + e.custo < distancia[e.destino])
				{
					if(distancia[e.destino] != INFINITO){
						conjunto.erase(conjunto.find(pair<int,int>(distancia[e.destino],e.destino)));
					}
					conjunto.insert(pair<int,int>(distancia[n]+e.custo,e.destino));
					distancia[e.destino] = distancia[n] + e.custo;
				}
			}
		}
	}
    for(int i = 1; i <= n_localidades; i++){
    	if (distancia[i] == INFINITO  || perda[i] == INFINITO)
    	{
    		perda[i] = INFINITO;
    	}
    	else{
    		perda[i] += distancia[i] + pesos_h[i] - pesos_h[filial];
    	}
    }
}

void dijkstra_final(int filial, int index_filial){
	vector<Ligacao>::iterator it_ligacao;
	vector<int> distancia(n_localidades + 1, INFINITO);
	set< pair<int,int> > conjunto;

	conjunto.insert(pair<int,int>(0,filial));

	while(conjunto.empty() == false){
		pair<int,int> topo = *conjunto.begin();
		conjunto.erase(conjunto.begin());
		int d = topo.first;
		int n = topo.second;
		distancia[n] = d; // distancia mais curta ate n
		if(grafo[n].size() != 0){
			for(it_ligacao = grafo[n].begin(); it_ligacao != grafo[n].end(); it_ligacao++){
				Ligacao e = *it_ligacao;
				if (distancia[n] + e.custo < distancia[e.destino])
				{
					if(distancia[e.destino] != INFINITO){
						conjunto.erase(conjunto.find(pair<int,int>(distancia[e.destino],e.destino)));
					}
					conjunto.insert(pair<int,int>(distancia[n]+e.custo,e.destino));
					distancia[e.destino] = distancia[n] + e.custo;
				}
			}
		}
	}
	caminhos[index_filial] = distancia[ponto_de_encontro];

}
int main()
{
	/* Leitura 1a linha de input */
	cin >> n_localidades >> n_filiais >> n_ligacoes;
	/* Inicializacao das estruturas */
	grafo = vector < vector<Ligacao> >(n_localidades + 1);

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
		Ligacao l = {v2,peso};
		grafo[v1].push_back(l);
	}

	/* Repesagem do grafo */
	grafo_repesagem();

	/* Determinar caminhos mais curtos para cada filial */

	perda = vector<int>(n_localidades+1,0);
	perda[0] = INFINITO;
	for (int i = 0; i < n_filiais; i++){
		int filial = filiais[i];
		dijkstra(filial,i);
	}
	int mais_curto = get_ponto_de_encontro();

	caminhos = vector<int>(n_filiais);
	for (int i = 0; i < n_filiais; i++){
		int filial = filiais[i];
		dijkstra_final(filial,i);
	}
	/* Apresentar resultados */
	print_output(mais_curto);

	return 0;
}