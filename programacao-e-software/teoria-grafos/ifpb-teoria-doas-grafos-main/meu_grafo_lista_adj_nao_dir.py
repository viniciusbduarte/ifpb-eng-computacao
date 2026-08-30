from bibgrafo.grafo_lista_adj_nao_dir import GrafoListaAdjacenciaNaoDirecionado
from itertools import combinations
from collections import deque 
from bibgrafo.grafo_errors import *
from queue import Queue

class MeuGrafo(GrafoListaAdjacenciaNaoDirecionado):
        
    def vertices_nao_adjacentes(self):
        nao_adjacentes = set()
        vertices = [v.rotulo for v in self.vertices]
        adjacentes = set()
        
        for aresta in self.arestas.values():
            v1 = aresta.v1.rotulo
            v2 = aresta.v2.rotulo
            adjacentes.add(frozenset([v1, v2]))
        
        for i in range(len(vertices)):
            for j in range(i + 1, len(vertices)):
                par = frozenset([vertices[i], vertices[j]])
                if par not in adjacentes:
                    nao_adjacentes.add(f"{vertices[i]}-{vertices[j]}")
        
        return nao_adjacentes

    def ha_laco(self):
        for a in self.arestas.values():
            if a.v1 == a.v2:
                return True
        return False

    def grau(self, V=''):
        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()
        grau = 0
        for a in self.arestas.values():
            if a.v1.rotulo == V:
                grau += 1
            if a.v2.rotulo == V:
                grau += 1
        return grau

    def ha_paralelas(self):
        arestas_vistas = set()
        for a in self.arestas.values():
            v1 = a.v1.rotulo
            v2 = a.v2.rotulo
            par = frozenset([v1, v2])
            if par in arestas_vistas:
                return True
            arestas_vistas.add(par)
        return False

    def arestas_sobre_vertice(self, V):
        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()
        resultado = set()
        for rotulo, aresta in self.arestas.items():
            if aresta.v1.rotulo == V or aresta.v2.rotulo == V:
                resultado.add(rotulo)
        return resultado

    def eh_completo(self):
        if self.ha_laco():
            return False
        for i in range(len(self.vertices)):
            for j in range(i + 1, len(self.vertices)):
                v1 = self.vertices[i].rotulo
                v2 = self.vertices[j].rotulo
                conectado = False
                for a in self.arestas.values():
                    if (a.v1.rotulo == v1 and a.v2.rotulo == v2) or (a.v1.rotulo == v2 and a.v2.rotulo == v1):
                        conectado = True
                        break
                if not conectado:
                    return False
        return True
    
    def dfs(self, V=''):
        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()

        grafo_dfs = MeuGrafo()
        grafo_dfs.adiciona_vertice(V)
        visitados = set()

        def dfs_recursiva(u):
            visitados.add(u)
            for aresta in self.arestas.values():
                v1 = aresta.v1.rotulo
                v2 = aresta.v2.rotulo

                if v1 == u and v2 not in visitados:
                    grafo_dfs.adiciona_vertice(v2)
                    grafo_dfs.adiciona_aresta(aresta.rotulo, v1, v2)
                    dfs_recursiva(v2)
                elif v2 == u and v1 not in visitados:
                    grafo_dfs.adiciona_vertice(v1)
                    grafo_dfs.adiciona_aresta(aresta.rotulo, v2, v1)
                    dfs_recursiva(v1)

        dfs_recursiva(V)

        for v in self.vertices:
            if v.rotulo not in visitados:
                dfs_recursiva(v.rotulo)

        return grafo_dfs

    def bfs(self, V=''): 
        if not self.existe_rotulo_vertice(V):
            raise VerticeInvalidoError()

        grafo_bfs = MeuGrafo()
        grafo_bfs.adiciona_vertice(V)
        visitados = set([V])
        fila = Queue()
        fila.put(V)

        while not fila.empty():
            atual = fila.get()
            for aresta in self.arestas.values():
                v1 = aresta.v1.rotulo
                v2 = aresta.v2.rotulo

                if v1 == atual and v2 not in visitados:
                    grafo_bfs.adiciona_vertice(v2)
                    grafo_bfs.adiciona_aresta(aresta.rotulo, v1, v2)
                    visitados.add(v2)
                    fila.put(v2)

                elif v2 == atual and v1 not in visitados:
                    grafo_bfs.adiciona_vertice(v1)
                    grafo_bfs.adiciona_aresta(aresta.rotulo, v2, v1)
                    visitados.add(v1)
                    fila.put(v1)

        return grafo_bfs
            
    def ha_ciclo(self): 
        if not self.vertices:
            return False
        grafo_dfs = self.dfs(self.vertices[0].rotulo)
        return len(self.arestas) > len(grafo_dfs.arestas)
    
    def eh_arvore(self): 
        if self.ha_laco() or self.ha_ciclo():
            return False 
        if len(self.arestas) != len(self.vertices) - 1:
            return False
        
        folhas = [v.rotulo for v in self.vertices if self.grau(v.rotulo) == 1]

        return folhas

    def ha_adjacencia(self, V1 = "", V2 = ""):
        for aresta in self.arestas.values():
            v1 = aresta.v1.rotulo
            v2 = aresta.v2.rotulo
            if (V1 == v1 and V2 == v2) or (V1 == v2 and V2 == v1):
                return True
        return False
    
    def eh_bipartido(self):
        vertices = [v.rotulo for v in self.vertices]
        n = len(vertices)
        vertices_set = set(vertices)

        def grupo_sem_adjacencia(grupo):
            for i in range(len(grupo)):
                for j in range(i + 1, len(grupo)):
                    if self.ha_adjacencia(grupo[i], grupo[j]):
                        return False
            return True

        for i in range(1, n // 2 + 1):
            for grupo_a in combinations(vertices, i):
                grupo_b = list(vertices_set - set(grupo_a))
                grupo_a = list(grupo_a)

                if grupo_sem_adjacencia(grupo_a) and grupo_sem_adjacencia(grupo_b):
                    return True

        return False

