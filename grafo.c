#include "grafo.h" // Inclui o cabeçalho "grafo.h" que contém as declarações de funções e estruturas.
#include <stdio.h> // Inclui a biblioteca padrão de entrada/saída.
#include <stdlib.h> // Inclui a biblioteca padrão de alocação de memória.
#include <limits.h> // Inclui a biblioteca que fornece constantes de limites, incluindo INT_MAX.

// Função para criar um novo nó (aresta) em um grafo ponderado.
No* criarNo(int destino, int peso) {
    // Aloca memória para um novo nó.
    No* novoNo = (No*)malloc(sizeof(No));
    // Verifica se a alocação de memória foi bem-sucedida.
    if (novoNo == NULL) {
        exit(1); // Encerra o programa com código de erro 1 em caso de falha na alocação.
    }
    // Define o campo 'destino' do novo nó com o valor fornecido como destino.
    novoNo->destino = destino;
    // Define o campo 'peso' do novo nó com o valor fornecido como peso.
    novoNo->peso = peso;
    // Inicializa o campo 'proximo' do novo nó como nulo, indicando que inicialmente não há próximo nó na lista.
    novoNo->proximo = NULL;
    // Retorna o ponteiro para o novo nó.
    return novoNo;
}

// Função para criar uma nova lista de adjacência.
ListaAdj* criarListaAdj() {
    // Aloca memória para uma nova lista de adjacência.
    ListaAdj* lista = (ListaAdj*)malloc(sizeof(ListaAdj));
    // Verifica se a alocação de memória foi bem-sucedida.
    if (lista == NULL) {
        exit(1); // Encerra o programa com código de erro 1 em caso de falha na alocação.
    }
    // Inicializa a cabeça da lista como nula.
    lista->cabeca = NULL;
    // Retorna o ponteiro para a nova lista de adjacência.
    return lista;
}


// Função para alocar dinamicamente memória para um novo grafo ponderado.
GrafoPonderado* alocarGrafo(int numCidades) {
    // Aloca memória para uma nova estrutura GrafoPonderado.
    GrafoPonderado* grafo = (GrafoPonderado*)malloc(sizeof(GrafoPonderado));
    // Verifica se a alocação de memória foi bem-sucedida.
    if (grafo == NULL) {
        exit(1); // Encerra o programa com código de erro 1 em caso de falha na alocação.
    }
    // Inicializa o número de cidades na estrutura do grafo.
    grafo->numCidades = numCidades;
    // Aloca memória para a lista de adjacência do grafo.
    grafo->listaAdjacencia = (ListaAdj*)malloc(numCidades * sizeof(ListaAdj));
    // Verifica se a alocação da lista de adjacência foi bem-sucedida.
    if (grafo->listaAdjacencia == NULL) {
        // Tratamento de erro: libera a memória alocada para a estrutura do grafo e encerra o programa com código de erro 1.
        free(grafo);
        exit(1);
    }
    // Inicializa a lista de adjacência, definindo a cabeça de cada lista como nula.
    for (int i = 0; i < numCidades; i++) {
        grafo->listaAdjacencia[i].cabeca = NULL;
    }
    return grafo;
}

// Desaloca Grafo
void desalocarGrafo(GrafoPonderado* grafo) {
    // Verifica se o ponteiro para o grafo não é nulo.
    if (grafo != NULL) {
        // Loop externo para percorrer todas as cidades do grafo.
        for (int i = 0; i < grafo->numCidades; i++) {
            // Inicializa um ponteiro para o primeiro nó na lista de adjacência da cidade atual.
            No* atual = grafo->listaAdjacencia[i].cabeca;
            // Loop interno para liberar a memória de todos os nós na lista de adjacência da cidade atual.
            while (atual != NULL) {
                // Armazena o próximo nó antes de liberar a memória do nó atual.
                No* proximo = atual->proximo;
                // Libera a memória alocada para o nó atual.
                free(atual);
                // Atualiza o ponteiro para o próximo nó na lista.
                atual = proximo;
            }
        }
        // Libera a memória alocada para a lista de adjacência.
        free(grafo->listaAdjacencia);
        // Libera a memória alocada para a estrutura GrafoPonderado.
        free(grafo);
    }
}

// Ler grafo
void leGrafo(GrafoPonderado* grafo) {
    // Obtém o número de cidades do grafo.
    int numCidades = grafo->numCidades;
    // Loop externo para percorrer todas as cidades do grafo.
    for (int i = 0; i < numCidades; i++) {
        // Loop interno para ler as distâncias entre a cidade 'i' e todas as outras cidades.
        for (int j = 0; j < numCidades; j++) {
            // Declaração das variáveis para origem, destino e distância entre as cidades.
            int origem, destino, distancia;
            // Lê os valores de origem, destino e distância da aresta entre as cidades.
            scanf("%d %d %d", &origem, &destino, &distancia);
            // Atualiza a lista de adjacência com a distância lida.
            No* novoNo = criarNo(destino, distancia);
            novoNo->proximo = grafo->listaAdjacencia[origem].cabeca;
            grafo->listaAdjacencia[origem].cabeca = novoNo;
        }
    }
}

// Função para obter a distância entre duas cidades no grafo.
int obterDistancia(GrafoPonderado* grafo, int cidadeOrigem, int cidadeDestino) {
    // Inicializa um ponteiro do tipo No, apontando para a cabeça da lista de adjacência da cidade de origem no grafo.
    No* atual = grafo->listaAdjacencia[cidadeOrigem].cabeca;
    // Inicia um loop while que continua até que o ponteiro 'atual' seja NULL, indicando o fim da lista.
    while (atual != NULL) {
        // Verifica se o nó atual na lista de adjacência é a cidade de destino.
        if (atual->destino == cidadeDestino) {
            // Se for, retorna o peso (ou distância) associado a esse nó, que é a distância até a cidade de destino.
            return atual->peso;
        }
        // Atualiza o ponteiro 'atual' para o próximo nó na lista de adjacência.
        atual = atual->proximo;
    }
    // Se a cidade de destino não for encontrada na lista de adjacência da cidade de origem, retorna -1.
    return -1;
}

// Função recursiva para encontrar o melhor caminho em um grafo ponderado usando lista de adjacência.
void encontraCaminhoRec(int posicao, int distancia, int contador, int* visitado, int* caminhoAtual, int* melhorCaminho, int numCidades, GrafoPonderado* grafo, int* menorDistancia) {
    // Verifica se todas as cidades foram visitadas (exceto a cidade de origem).
    if (contador == numCidades - 1) {
        // Procura por uma aresta que retorne à cidade de origem (posição 0) para formar um ciclo completo.
        No* vizinho = grafo->listaAdjacencia[posicao].cabeca;
        while (vizinho != NULL) {
            int cidadeDestino = vizinho->destino;
            // Se encontrarmos um ciclo completo com distância total menor que a menor distância conhecida, atualizamos o melhor caminho e a menor distância.
            if (cidadeDestino == 0 && vizinho->peso != 0 && distancia + vizinho->peso < *menorDistancia) {
                *menorDistancia = distancia + vizinho->peso;
                for (int i = 0; i < numCidades; i++) {
                    melhorCaminho[i] = caminhoAtual[i];
                }
            }
            vizinho = vizinho->proximo;
        }
        // Retorna da recursão.
        return;
    }
    // Explora as arestas saindo da posição atual para encontrar todas as cidades ainda não visitadas.
    for (No* vizinho = grafo->listaAdjacencia[posicao].cabeca; vizinho != NULL; vizinho = vizinho->proximo) {
        int proximaCidade = vizinho->destino;
        // Verifica se a próxima cidade não foi visitada e se a aresta atual não é uma aresta sem peso (peso != 0).
        if (visitado[proximaCidade] == 0 && vizinho->peso != 0) {
            // Marca a próxima cidade como visitada e adiciona ao caminho atual.
            visitado[proximaCidade] = 1;
            caminhoAtual[contador] = proximaCidade;
            // Chama a função recursivamente para a próxima cidade.
            encontraCaminhoRec(proximaCidade, distancia + vizinho->peso, contador + 1, visitado, caminhoAtual, melhorCaminho, numCidades, grafo, menorDistancia);
            // Desmarca a cidade após a chamada recursiva para permitir a exploração de outros caminhos.
            visitado[proximaCidade] = 0;
        }
    }
}

// Função para encontrar o caminho mais curto em um grafo ponderado usando força bruta.
void encontraCaminho(GrafoPonderado* grafo, int* melhorCaminho) {
    int numCidades = grafo->numCidades;
    // Aloca um array para controlar as cidades visitadas.
    int* visitado = (int*)malloc(numCidades * sizeof(int));
    // Aloca um array para rastrear o caminho atual.
    int* caminhoAtual = (int*)malloc(numCidades * sizeof(int));
    // Inicializa a menorDistancia com um valor máximo.
    int menorDistancia = INT_MAX;
    // Marca a cidade de origem (0) como visitada e inicia o caminho atual.
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = 0;
    }
    visitado[0] = 1;
    caminhoAtual[0] = 0;
    // Chama a função encontraCaminhoRec para encontrar o caminho mais curto.
    encontraCaminhoRec(0, 0, 0, visitado, caminhoAtual, melhorCaminho, numCidades, grafo, &menorDistancia);
    // Libera a memória alocada para os arrays de controle.
    free(visitado);
    free(caminhoAtual);
}

// Função para imprimir o caminho mais curto encontrado e a distância total.
void imprimeCaminho(GrafoPonderado* grafo, int* caminho, int distancia) {
    // Imprime a cidade de origem (0) para iniciar o caminho.
    printf("Melhor caminho: 0 ");
    // Percorre as cidades do caminho, exceto a última, e as imprime.
    for (int i = 0; i < grafo->numCidades - 1; i++) {
        printf("%d ", caminho[i]);
    }
    // Imprime a cidade de origem (0) novamente para completar o ciclo.
    printf("0\n");
    // Imprime a distância total do caminho encontrado.
    printf("Melhor distancia: %d\n", distancia);
}

// Função para ordenar as listas de adjacência de um grafo ponderado.
void ordenaLista(GrafoPonderado* grafo) {
    // Loop externo para percorrer todas as cidades do grafo.
    for (int i = 0; i < grafo->numCidades; i++) {
        // Obtém o ponteiro para a lista de adjacência da cidade atual.
        ListaAdj* lista = &grafo->listaAdjacencia[i];
        // Verifica se a lista está vazia ou tem apenas um elemento, o que significa que já está ordenada.
        if (lista->cabeca == NULL || lista->cabeca->proximo == NULL) {
            continue; // Pula para a próxima iteração do loop se a lista já estiver ordenada.
        }
        // Inicializa uma lista temporária para armazenar os elementos ordenados.
        ListaAdj listaOrdenada;
        listaOrdenada.cabeca = NULL;
        // Percorre os elementos da lista original.
        No* atual = lista->cabeca;
        while (atual != NULL) {
            // Armazena o próximo nó antes de removê-lo da lista original.
            No* proximo = atual->proximo;
            // Insere o nó na lista ordenada.
            if (listaOrdenada.cabeca == NULL || atual->peso <= listaOrdenada.cabeca->peso) {
                // Caso especial: insere no início da lista ordenada.
                atual->proximo = listaOrdenada.cabeca;
                listaOrdenada.cabeca = atual;
            } else {
                // Procura o local correto na lista ordenada para inserir o nó.
                No* anterior = NULL;
                No* atualOrdenada = listaOrdenada.cabeca;
                while (atualOrdenada != NULL && atual->peso > atualOrdenada->peso) {
                    anterior = atualOrdenada;
                    atualOrdenada = atualOrdenada->proximo;
                }
                // Insere o nó na posição correta.
                anterior->proximo = atual;
                atual->proximo = atualOrdenada;
            }
            // Move para o próximo nó na lista original.
            atual = proximo;
        }
        // Atualiza a cabeça da lista original para apontar para a lista ordenada.
        lista->cabeca = listaOrdenada.cabeca;
    }
}
// Função para imprimir as listas de adjacência ordenada.
void imprimeOrdenado(GrafoPonderado* grafo) {
    // Loop para percorrer todos os vértices do grafo.
    for (int i = 0; i < grafo->numCidades; i++) {
        // Imprime mensagem indicando a lista de adjacências do vértice i.
        printf("Adjacencias do vertice %d: ", i);
        // Inicializa um ponteiro para o primeiro nó na lista de adjacências do vértice i.
        No* atual = grafo->listaAdjacencia[i].cabeca;
        // Loop para percorrer todos os nós na lista de adjacências do vértice i.
        while (atual != NULL) {
            // Imprime as informações do nó atual, incluindo o destino e o peso da aresta.
            printf("(%d, %d) -> ", atual->destino, atual->peso);
            // Atualiza o ponteiro para apontar para o próximo nó na lista de adjacências.
            atual = atual->proximo;
        }
        // Imprime "NULL" para indicar o final da lista de adjacências do vértice i.
        printf("NULL\n");
    }
}
