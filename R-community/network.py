import networkx as nx
from os import listdir
from os.path import isfile, join
import itertools
import matplotlib.pyplot as plt
import os
import re
import scipy 
from scipy.sparse import *
from operator import itemgetter
from sklearn.cluster import KMeans
import numpy as np
import sys
import pandas as pd


def load_egonet_files(path):
   
    onlyfiles = [fyle for fyle in listdir(path) if fyle.endswith('.egonet')]
    return onlyfiles

#########################################################################################################

def build_graph(n):
    edges = []
    nodes = []
    path = '/home/mayank/Desktop/Major 2/egonets'
    egonets = load_egonet_files(path)
    for egonet in egonets[n:n+1]:
        ego = int(re.match( r'([0-9]+).egonet', egonet).group(1))
        m = open(os.path.join(path,egonet), "r")
        friends = [line[:-1].replace(':','').split(' ') for line in m.readlines()]
        friends = [map(int, friend[:1]) if friend[1] == '' else map(int, friend) for friend in friends]
        edges += [(ego,friend[0]) for friend in friends] 
        
        for friend in friends:
            edges += [(friend[0], user) for user in friend[1:] if len(friend)>1] 
        
        nodes += list(itertools.chain.from_iterable(friends)) + [ego]
    edges = list(set(tuple(sorted(edge)) for edge in edges))        
    nodes = list(set(nodes))
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)
    
    return G, nodes

#########################################################################################################

def to_R(n):
    G, nodes = build_graph(n)
    A = nx.to_numpy_matrix(G)
    df = pd.DataFrame(A, index=nodes, columns=nodes)
    df.to_csv('graph-{}.csv'.format(n),index=True)

#########################################################################################################

if __name__ == '__main__':

    for n in range(110):
        to_R(n)
