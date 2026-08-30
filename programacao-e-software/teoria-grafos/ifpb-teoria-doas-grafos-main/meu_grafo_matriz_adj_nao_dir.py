from bibgrafo.grafo_matriz_adj_nao_dir import GrafoMatrizAdjacenciaNaoDirecionado
from bibgrafo.grafo_errors import *


class MeuGrafo(GrafoMatrizAdjacenciaNaoDirecionado):

    def vertices_nao_adjacentes(self):
        '''
        Provê um conjunto (set) de vértices não adjacentes no grafo.
        O conjunto terá o seguinte formato: {X-Z, X-W, ...}
        Onde X, Z e W são vértices no grafo que não têm uma aresta entre eles.
        :return: Um conjunto (set) com os pares de vértices não adjacentes
        '''
        vertices_nao_adjacentes = set()

        for i in range(len(self.matriz)):
            for j in range(i + 1, len(self.matriz)): 

                if len(self.matriz[i][j]) == 0:
                    vertices_nao_adjacentes.add(f"{self.vertices[i]}-{self.vertices[j]}")

        return vertices_nao_adjacentes

    def ha_laco(self):
        '''
        Verifica se existe algum laço no grafo.
        :return: Um valor booleano que indica se existe algum laço.
        '''
        for i in range(len(self.matriz)):
            if len(self.matriz[i][i]) > 0:
                return True
        return False

    def grau(self, V=''):
        '''
        Provê o grau do vértice passado como parâmetro
        :param V: O rótulo do vértice a ser analisado
        :return: Um valor inteiro que indica o grau do vértice
        :raises: VerticeInvalidoError se o vértice não existe no grafo
        '''
        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()
        
        v_obj = self.get_vertice(V)
        v_indice = self.indice_do_vertice(v_obj)
        grau = 0

        for j in range(len(self.matriz[v_indice])):
            if (self.matriz[v_indice][j] is not None) and v_indice == j:
                grau += len(self.matriz[v_indice][j])*2
            elif self.matriz[v_indice][j] is not None:
                grau += len(self.matriz[v_indice][j])

        return grau

    def ha_paralelas(self):
        '''
        Verifica se há arestas paralelas no grafo
        :return: Um valor booleano que indica se existem arestas paralelas no grafo.
        '''
        for linha in self.matriz:
            for elemento in linha:
                if len(elemento) > 1:
                    return True
        return False

    def arestas_sobre_vertice(self, V):
        '''
        Provê um conjunto (set) que contém os rótulos das arestas que
        incidem sobre o vértice passado como parâmetro
        :param V: O vértice a ser analisado
        :return: Um conjunto com os rótulos das arestas que incidem sobre o vértice
        :raises: VerticeInvalidoError se o vértice não existe no grafo
        '''

        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()
        
        arestas_sobre_vertice = set()

        v_obj = self.get_vertice(V)
        v_indice = self.indice_do_vertice(v_obj)

        for j in range(len(self.matriz[v_indice])):
            if (self.matriz[v_indice][j] is not None):
                for aresta in self.matriz[v_indice][j]:
                    arestas_sobre_vertice.add(aresta)

        return arestas_sobre_vertice
        
    def eh_completo(self):
        '''
        Verifica se o grafo é completo.
        :return: Um valor booleano que indica se o grafo é completo
        '''
        if self.ha_laco():
            return False

        grau_ref = self.grau(self.vertices[0].rotulo)

        for vertice in self.vertices:
            if self.grau(vertice.rotulo) != grau_ref:
                return False

        if grau_ref != len(self.vertices) - 1:
            return False

        return True
    

