from meu_grafo_lista_adj_dir import MeuGrafo

g = MeuGrafo()

g.adiciona_vertice("A")
g.adiciona_vertice("B")
g.adiciona_vertice("C")
g.adiciona_vertice("D")
g.adiciona_vertice("E")

g.adiciona_aresta('a1', 'A', 'B', 1)
g.adiciona_aresta('a2', 'B', 'B', 2)
g.adiciona_aresta('a3', 'C', 'D', 3)
g.adiciona_aresta('a4', 'D', 'D', -3)



