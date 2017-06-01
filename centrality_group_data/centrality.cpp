#include <bits/stdc++.h>

using namespace std;

struct hnode
{
	int vno,dval;
};


// Prototype of a utility function to swap two heap nodes
void swap(hnode *x, hnode *y);
 
// A class for Min Heap
class MinHeap
{
public:
    hnode *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

    // Constructor: Builds a heap from a given array a[] of given size
    MinHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        harr = new hnode[cap];
    }
 
    
    // A recursive method to heapify a subtree with root at given index
    // This method assumes that the subtrees are already heapified
    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l].dval < harr[i].dval)
            smallest = l;
        if (r < heap_size && harr[r].dval < harr[smallest].dval)
            smallest = r;
        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }
 
    int parent(int i) { return (i-1)/2; }
 
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
 
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
 
    // Method to remove minimum element (or root) from min heap
    hnode extractMin()
    {
        
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }
     
        // Store the minimum vakue, and remove it from heap
        hnode root = harr[0];
        harr[0] = harr[heap_size-1];
        heap_size--;
        MinHeapify(0);
     
        return root;
    }
 
    // Decreases value of key at index 'i' to new_val.  It is assumed that
    // new_val is smaller than harr[i].
    void decreaseKey(int vno, int new_val)
    {
        int i;
        for(i=0;i<heap_size;i++)
        {
        	if(harr[i].vno==vno)
        	{
        		harr[i].dval=new_val;
        		break;
        	}
        }
        while (i != 0 && harr[parent(i)].dval > harr[i].dval)
        {
           swap(&harr[i], &harr[parent(i)]);
           i = parent(i);
        }
    }
 
    // Returns the minimum key (key at root) from min heap
    hnode getMin() { return harr[0]; }
 
    // This function deletes key at index i. It first reduced value to minus
    // infinite, then calls extractMin()
    void deleteKey(int i)
    {
        decreaseKey(i, INT_MIN);
        extractMin();
    }
 
    void insertRootNode(int vno)
    {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }
     
        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i].vno = vno;
     	harr[i].dval=0;
    }

    // Inserts a new key 'k'
    void insertNode(int vno)
    {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }
     
        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i].vno = vno;
     	harr[i].dval=INT_MAX;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)].dval > harr[i].dval)
        {
           swap(&harr[i], &harr[parent(i)]);
           i = parent(i);
        }
    }

    void insertNode2(int vno,int d)
    {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }
     
        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i].vno = vno;
     	harr[i].dval=d;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)].dval > harr[i].dval)
        {
           swap(&harr[i], &harr[parent(i)]);
           i = parent(i);
        }
    }

    bool isInHeap(int a)
    {
    	bool flag=false;
    	for(int i=0;i<heap_size;i++)
    	{
    		if(harr[i].vno==a)
    		{
    			flag=true;
    			break;
    		}
    	}
    	return flag;
    }

    int getdval(int a)
    {
    	int d;
    	for(int i=0;i<heap_size;i++)
    	{
    		if(harr[i].vno==a)
    			d=harr[i].dval;
    	}
    	return d;
    }
};
 

// A utility function to swap two elements
void swap(hnode *x, hnode *y)
{
    hnode temp = *x;
    *x = *y;
    *y = temp;
}

int adj[1500][1500];
string nodes[1500];
int V;

int main()
{
    V=0;
    memset(adj,-1,sizeof(adj));
    string line;
    map<string,int> m;
       
    //ifstream nodefile("graph1[Nodes].csv");
    //ifstream edgefile("graph1[Edges].csv");
    //ifstream nodefile("example_input [Nodes].csv");
    //ifstream edgefile("example_input [Edges].csv");
    ifstream nodefile("group_153631204680678_2016_10_06_17_49_15_interactions [Nodes].csv");
    ifstream edgefile("group_153631204680678_2016_10_06_17_49_15_interactions [Edges].csv");
    int sumw=0;
    if(edgefile.is_open())
    {
        getline(edgefile,line);
        while(getline(edgefile,line))
        {
            stringstream ss(line);
            string s,type;
            int x,y;
            int i=1;
            while(getline(ss,s,','))
            {
                if(i==1)
                {
                    if(m.find(s)==m.end())
                    {
                        x=V;
                        nodes[V]=s;
                        m[s]=V++;
                    }
                    else x=m[s];
                }
                if(i==2)
                {
                    if(m.find(s)==m.end())
                    {
                        y=V;
                        nodes[V]=s;
                        m[s]=V++;
                    }
                    else y=m[s];
                }
                if(i==3)
                    type=s;
                if(i==7)
                {
                    char* c=new char[s.length()+1];
                    strcpy(c,s.c_str());
                    int w=(int)atof(c);
                    if(type.compare("Directed")==0)
                   	{
                   		adj[x][y]=w;
                   	}
                    else if(type.compare("Undirected")==0)
                    {
                    	adj[x][y]=adj[y][x]=w;
                    }
                    sumw+=w;
                }
                i++;
            }
        }
    }
    edgefile.close();

    if(nodefile.is_open())
    {
        getline(nodefile,line);
        while(getline(nodefile,line))
        {
            stringstream ss(line);
            string s;
            getline(ss,s,',');
            if(m.find(s)==m.end())
            {
                nodes[V]=s;
                m[s]=V++;
            }
        }
    }
    nodefile.close();

    vector<vector<int> > c;
    for(int i=0;i<V;i++)
    {
    	vector<int> temp;
    	temp.push_back(i);
    	c.push_back(temp);
    }

	for(int i=0;i<c.size();i++)
	{
		for(int j=0;j<c[i].size();j++)
		{
			int s=c[i][j];
			float max=-1.0;
			int r=-1;
			for(int k=0;k<c.size();k++)
			{    				
				if(k!=i)
				{
					int sum=0,sum_in=0,links_in=0;
					for(int x=0;x<c[k].size();x++)
					{
						if(adj[s][c[k][x]]>0)
							sum+=adj[s][c[k][x]];
					}
					for(int x=0;x<c[k].size();x++)
					{
						for(int y=0;y<V;y++)
						{
							if(adj[y][c[k][x]]>0)
								sum_in+=adj[y][c[k][x]];
						}
					}
					for(int x=0;x<V;x++)
					{
						if(adj[x][s]>0)
							links_in+=adj[x][s];
					}
					float a=((float)sum)/(2.0*((float)sumw));
					float b=(((float)(sum_in*links_in))/(2.0*((float)(sumw*sumw))));
					float q=a-b;
					if(q>0.0 && q>max)
					{
						max=q;
						r=k;
					}
				}
			}
			if(max>0.0)
			{
				c[i].erase(c[i].begin()+j);
				c[r].push_back(s);
				j--;
			}
		}
	}
	ofstream myfile;
	myfile.open("group_data_central_node.csv");
	for(int g=0;g<c.size();g++)
	{
		if(c[g].size()>0)
		{
			myfile<<"nodes"<<endl;
			for(int h=0;h<c[g].size();h++)
			{
				myfile<<nodes[c[g][h]]<<endl;
			}
			myfile<<endl;

			//calculating shortest distances
			int v1=c[g].size();
			int sd[v1][v1];
			int np[v1][v1];
			for(int j=0;j<v1;j++)
			{
			    MinHeap h(v1);
			    np[j][j]=1;
			    h.insertRootNode(j);
			    
			    for(int i=0;i<v1;i++)
			    {
	            	if(i!=j)
	                {
	                    h.insertNode(i);
	                    np[j][i]=0;
	                }   
		        }
			    
			    while(h.heap_size>0)
			    {
			    	hnode hn=h.extractMin();
			    	sd[j][hn.vno]=hn.dval;

			    	int u=hn.vno;
			    	
			    	for(int i=0;i<v1;i++)
			    	{
			    		if(i!=u && adj[c[g][u]][c[g][i]]>0)
			    		{
			    			if(h.isInHeap(i))
			    			{
			    				if(hn.dval<INT_MAX)
		                        {
		                            if(h.getdval(i)>adj[c[g][u]][c[g][i]]+hn.dval)
				    				{
		                                h.decreaseKey(i,adj[c[g][u]][c[g][i]]+hn.dval);
		                                np[j][i]=np[j][u];
		                            }
		                            else if(h.getdval(i)==adj[c[g][u]][c[g][i]]+hn.dval)
			    						np[j][i]+=np[j][u];
		                        }
			    			}
			    		}
			    	}
			    }
			}

			float max=-1.0;
			int indmax=-1;
			for(int i=0;i<c[g].size();i++)
			{
				//calculating centrality measures
				float deg=0.0,far=0.0,close=0.0,betw=0.0;
				for(int j=0;j<c[g].size();j++)
				{
					if(j!=i)
					{
						if(adj[c[g][i]][c[g][j]]>0)
							deg+=1.0;
						if(adj[c[g][j]][c[g][i]]>0)
							deg+=1.0;
						if(sd[i][j]<INT_MAX)
							far+=(float)sd[i][j];
					}
				}
				if(far>0.0)
					close=1.0/far;
		    	
	            for(int x=0;x<v1;x++)
	            {
	                for(int y=0;y<v1;y++)
	                {
                        if(sd[x][i]<INT_MAX && sd[i][y]<INT_MAX && np[x][y]>0)
                        {
                            if(sd[x][y]==sd[x][i]+sd[i][y])
                                betw+=((float)(np[x][i]*np[i][y])/np[x][y]);
                        }
	                }
	            }
				float sumc=deg+close+betw;
				if(sumc>max)
				{
					max=sumc;
					indmax=i;
				}
			}
			myfile<<"most central node is: "<<nodes[c[g][indmax]]<<endl<<endl;
		}
	}

    return 0;
}
