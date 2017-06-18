Trabalho 3 de Algoritmos e Teoria dos Grafos.
Docente: André Guedes.
Discente: Alessandro Elias, GRR20110589

O algoritmo implementado foi o de Tarjan, utilizando uma matriz de
adjacência, pois a complexidade é O(V + E) (considerando somente o algoritmo de Tarjan).

ReadGraph()
        // Foi necessário fazer dois loops tendo complexidade de n2
	// (n = número de vértices) devido a geração de ID's.

        Para cada v € V(G)
                 seta id
                 armazene nome dos vértices.
		 Mapeie Id vértice
		 Mapeie Nome Id

        Para cada v € V(G)
                 Obtenha toda vizinhança(v)

GetAllStrongConnectedComponents()
	Para cada i € |V|
	     pre[i] <= Não visitado
	     low[i] <= Não visitado
	     EstaNapilha <= falso

	Para cada i € |V|
	     Se pre[i] Não foi visitado
	     	GetStrongConnectedComponents

GetStrongConnectedComponents(u, pre[], low[], pilha, EstaNaPilha[])
	// Aloque na heap para compartilhar entre as chamadas
	// recursivas. Poderia ter passado como parâmetro.
	time <= 0;

	pre[u] <= low[u] <= ++time
	empilhe(u)
	Seta_u_EstaNapilha(u)
	Para cada i € {Lista de adjacência de u}
	     obtenha vértice v do índice i
	     Se pre[u] não foi visitado?
	     	// CHAMADA RECURSIVA
		GetStrongConnectedComponents(u, pre[], low[], pilha, EstaNaPilha[])
		low[u] <= MIN{ low[u], low[v] }

	     // atualize u somente se v esta na pilha. é um arco de
	     // retorno; não é um arco cruzado.
	     senão se v esta na pilha?
	     	MIN{ low[u], pre[v] }


	Se low[u] == pre[u]
	   // enumere os componentes fortemente conexo.
	   Enquanto Topo da Pilha != u
	   	w <= topo da pilha
		imprima o nome do vértice que faz parte da componente
		Seta_w_Não Esta Mais Na Pilha

	   w <= Topo da pilha
	   imprima o nome do vértice que faz parte da componente
	   Seta_w_Não Esta Mais Na Pilha



As demais funções são helpers, para imprimir ou ler o grafo a partir
da linguagem dot, o que considero irrelevante para a correção do trabalho.
