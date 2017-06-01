library(igraph)
# read graph from csv file
dat = read.csv('graph-0.csv', header=TRUE, row.names=1, check.names=FALSE)
m = as.matrix(dat)
# build graph from adjacency matrix
g = graph.adjacency(m,mode="undirected",weighted=NULL)

# plots the graph
E(g)$color <- rgb(0,0,0,alpha=.2)
ego <- names(which.max(degree(g)))
V(g)[V(g) != ego]$color = 'blue'
V(g)[ego]$color = 'red'

windows()
plot(g, vertex.label=NA, vertex.size=5, layout=layout.fruchterman.reingold)
wc <- spinglass.community(g)
modularity(wc)
plot(g, vertex.label=NA, vertex.size=5, vertex.color=membership(wc),layout=layout.fruchterman.reingold)

