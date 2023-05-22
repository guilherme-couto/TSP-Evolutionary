import pygmo
import tsplib95
import networkx as nx
import sys
from tsp import TSP

# Check if command line arguments are valid
if len(sys.argv) != 2:
    print("Usage: python3 main.py <instance name>")
    sys.exit(1)

# Read the instance from command line
instance_name = sys.argv[1]

# Check if the instance is valid
if instance_name not in ['berlin52.tsp', 'br17.atsp', 'ch130.tsp', 'ftv70.atsp']:
    print("Invalid instance name. Valid instances are: berlin52.tsp, br17.atsp, ch130.tsp, ftv70.atsp")
    sys.exit(1)

# Read the instance
instance = tsplib95.load(f"instances/{instance_name}")

# Get a graph representation of the instance
graph = instance.get_graph()

# Relabel nodes and print them
graph = nx.relabel_nodes(graph, lambda x: x+1)
print(f"Nodes: {graph.nodes}")

# Set the problem
prob = pygmo.problem(TSP(graph))

# Set the population and the algorithm
pop_size = 17  # From reference of gaco 
k = 15          # From reference of gaco
budget = 20000 if graph.number_of_nodes() < 50 else 70000
pop = pygmo.population(prob, size=pop_size)
algo = pygmo.algorithm(pygmo.gaco(gen=budget, ker=k, q=1.0, oracle=1e9, acc=0.0, threshold=1, n_gen_mark=7, impstop=100000, evalstop=budget, focus=0.0, memory=False, seed=0))

algo.set_verbosity(0)

# Evolve the population
pop = algo.evolve(pop)

# Print the best solution
print(f"Best solution: {pop.champion_x}")
print(f"Best fitness: {pop.champion_f}")
