from bibgrafo.grafo_lista_adj_dir import GrafoListaAdjacenciaDirecionado
from bibgrafo.grafo_errors import *
import heapq


class MeuGrafo(GrafoListaAdjacenciaDirecionado):

    def vertices_nao_adjacentes(self):
        '''
        Provê um conjunto de vértices não adjacentes no grafo.
        O conjunto terá o seguinte formato: {X-Z, X-W, ...}
        Onde X, Z e W são vértices no grafo que não tem uma aresta entre eles.
        :return: Um objeto do tipo set que contém os pares de vértices não adjacentes
        '''
        pass # Apague essa instrução e inicie seu código aqui

    def ha_laco(self):
        '''
        Verifica se existe algum laço no grafo.
        :return: Um valor booleano que indica se existe algum laço.
        '''
        pass

    def grau_entrada(self, V=''):
        '''
        Provê o grau de entrada do vértice passado como parâmetro
        :param V: O rótulo do vértice a ser analisado
        :return: Um valor inteiro que indica o grau do vértice
        :raises: VerticeInvalidoError se o vértice não existe no grafo
        '''
        pass

    def grau_saida(self, V=''):
        '''
        Provê o grau de saída do vértice passado como parâmetro
        :param V: O rótulo do vértice a ser analisado
        :return: Um valor inteiro que indica o grau do vértice
        :raises: VerticeInvalidoError se o vértice não existe no grafo
        '''
        pass

    def ha_paralelas(self):
        '''
        Verifica se há arestas paralelas no grafo
        :return: Um valor booleano que indica se existem arestas paralelas no grafo.
        '''
        pass

    def arestas_sobre_vertice(self, V):
        '''
        Provê uma lista que contém os rótulos das arestas que incidem sobre o vértice passado como parâmetro
        :param V: Um string com o rótulo do vértice a ser analisado
        :return: Uma lista os rótulos das arestas que incidem sobre o vértice
        :raises: VerticeInvalidoException se o vértice não existe no grafo
        '''
        pass

    def eh_completo(self):
        '''
        Verifica se o grafo é completo.
        :return: Um valor booleano que indica se o grafo é completo
        '''
        pass

    def dijkstra(self, vi, vf):
        distancias = {v.rotulo: float('inf') for v in self.vertices}
        distancias[vi] = 0

        anterior = {v.rotulo: None for v in self.vertices}
        visitados = set()

        fila = [(0, vi)]  # (distância acumulada, vértice atual)
        
        while fila:
            distancia_atual, atual = heapq.heappop(fila)

            if atual in visitados:
                continue
            visitados.add(atual)

            for aresta in self.arestas.values():
                # SOMENTE no sentido v1 -> v2
                if aresta.v1.rotulo == atual:
                    vizinho = aresta.v2.rotulo
                    peso = aresta.peso
                    
                    if peso < 0:
                        raise Exception("Peso negativo detectado!")
                    
                    nova_distancia = distancia_atual + peso
                    if nova_distancia < distancias[vizinho]:
                        distancias[vizinho] = nova_distancia
                        anterior[vizinho] = atual
                        heapq.heappush(fila, (nova_distancia, vizinho))

        # Reconstruir o caminho
        caminho = []
        atual = vf
        while atual is not None:
            caminho.insert(0, atual)
            atual = anterior[atual]

        if distancias[vf] == float('inf'):
            return None, float('inf')  # Sem caminho possível

        return caminho, distancias[vf]
    



    def bellman_ford(self, origem, destino):
        distancias = {v.
                      rotulo: float('inf') for v in self.vertices}
        anterior = {v.rotulo: None for v in self.vertices}
        distancias[origem] = 0

        for _ in range(len(self.vertices) - 1):
            for aresta in self.arestas.values():
                u = aresta.v1.rotulo
                v = aresta.v2.rotulo
                peso = aresta.peso
                if distancias[u] + peso < distancias[v]:
                    distancias[v] = distancias[u] + peso
                    anterior[v] = u

        # Verifica ciclos negativos
        for aresta in self.arestas.values():
            u = aresta.v1.rotulo
            v = aresta.v2.rotulo
            peso = aresta.peso
            if distancias[u] + peso < distancias[v]:
                raise Exception("Ciclo negativo detectado!")

        caminho = []
        atual = destino
        while atual is not None:
            caminho.insert(0, atual)
            atual = anterior[atual]

        if caminho[0] != origem:
            return None, float('inf')  # Sem caminho possível

        return caminho, distancias[destino]