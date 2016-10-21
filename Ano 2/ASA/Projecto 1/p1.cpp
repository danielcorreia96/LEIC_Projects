#include <iostream>
#include <vector>
#include <list>

#define NIL -1

using namespace std;
vector< list<int> > grafo;	// lista de adjacencias do grafo
vector<bool> visitado;		// guarda estado de visita dos vertices
vector<bool> fundamental;	// guarda os vertices fundamentais
vector<int> descoberta;		// tempo de descoberta de cada vertice visitado
vector<int> minimo; 		// minimo(d[u],d[w]) - caso das back edges
vector<int> parent; 		// guarda os vertices predecessores da arvore DFS
int timer;

void find_fundamentals(int);

int main()
{
    /* 1. Inicializacao do grafo */
    int utilizadores,ligacoes;
    cin >> utilizadores >> ligacoes;
    
    grafo = vector< list<int> >(utilizadores + 1);
    int v1, v2;
    for (int i = 1; i <= ligacoes; i++) {
		cin >> v1 >> v2;	
		grafo[v1].push_back(v2);
		grafo[v2].push_back(v1);
    }
	
    /* 2. Descobrir e imprimir vertices fundamentais */
    find_fundamentals(utilizadores);
    
    return 0;
}

void dfs(int u){
	int filhos = 0;		// numero de filhos da arvore DFS
	
	/* Marcar o vertice como visitado */
	visitado[u] = true;		
	
	/* Inicializar tempo de descoberta e minimmo */
	descoberta[u] = minimo[u] = timer++;
	
	/* Percorrer vertices adjacentes */
	list<int>::iterator it;
	for(it = grafo[u].begin(); it != grafo[u].end(); it++){
		int v = *it; // vertice adjacente de u
		
		/* Verificar se v nao foi visitado */
		if(visitado[v] == false){
			/* atualizar contador de filhos e predecessor de v */
			filhos++;
			parent[v] = u;
			dfs(v);
			
			/* Verificar se a subarvore se v esta relaciona com um antecessor de u */
			minimo[u] = min(minimo[u],minimo[v]);
			
			/* Caso 1: back edge */
			if(parent[u] != NIL && minimo[v] >= descoberta[u]){
				fundamental[u] = true;
			}
			
			/* Caso 2: vertice de inicio da DFS */
			if(parent[u] == NIL && filhos > 1){
				fundamental[u] = true;
			}
		}
		/* Se v ja tiver sido visitado e nao for predecessor, atualizo o minimo de u */
		else if(v != parent[u]) {
			minimo[u] = min(minimo[u],descoberta[v]);
		}
	}
	
}
void find_fundamentals(int vertices){
	
	/* Inicializar os vectores e tempo */
	visitado = vector<bool>(vertices+1);
	fundamental = vector<bool>(vertices+1);
	descoberta = vector<int>(vertices+1);
	minimo = vector<int>(vertices+1);
	parent = vector<int>(vertices+1,NIL);
	timer = 1;
	
	/* Aplicar algoritmo recursivo */
	for(int i = 1; i <= vertices; i++){
		if(visitado[i] == false){
			dfs(i);  
		}
	}
	
	/* Imprimir resultados */
	int contador = 0, minf = -1 , maxf = -1;
	for(int i=1; i <= vertices; i++){
		if(fundamental[i]){
			contador++;
			if(i < minf || minf == -1)
				minf = i;
			if(i > maxf || maxf == -1)
				maxf = i;
		}
	}
	cout << contador << "\n";
	cout << minf << " " <<  maxf << "\n";
  
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
