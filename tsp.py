import networkx as nx

# Define the TSP problem
class TSP:
    def __init__(self, graph):
        self.graph = graph
        
    def fitness(self, tour):
        # distance = nx.path_weight(graph, [1, 2, 3, 4], weight='weight')
        print(f'Tour: {tour} with length {len(tour)}')
        # distance = nx.path_weight(self.graph, tour, weight='weight')
        distance = sum(tour)
        return tour[0]
    
    def get_bounds(self):
        return ([1]*self.graph.number_of_nodes(), [self.graph.number_of_nodes()]*self.graph.number_of_nodes())
    
