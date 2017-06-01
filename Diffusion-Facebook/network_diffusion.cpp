#include <bits/stdc++.h>

using namespace std;

struct hnode
{
	int vno;
    double dval;
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
    void decreaseKey(int vno, double new_val)
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
     	harr[i].dval=0.0;
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
     	harr[i].dval=DBL_MAX;

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

    double getdval(int a)
    {
    	double d;
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

float adj[1500][1500];
string nodes[1500];
int V;
float d[1500];
double difftimes[1500][1500];

double getDiffusionTime(int a,int b)
{
    return(((double)d[a])/((double)adj[a][b]*adj[a][b]));
}

int main()
{
    V=0;
    memset(adj,-1,sizeof(adj));
    string line;
    map<string,int> m;
       
    //ifstream nodefile("graph1 [Nodes].csv");
    //ifstream edgefile("graph1 [Edges].csv");
    ifstream nodefile("nodes.csv");
    ifstream edgefile("edges.csv");
    //ifstream nodefile("group_153631204680678_2016_10_06_17_49_15_interactions [Nodes].csv");
    //ifstream edgefile("group_153631204680678_2016_10_06_17_49_15_interactions [Edges].csv");
    float sumw=0.0;
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
                    float w=(float)atof(c);
                    //int w=(int)atof(c);
                    if(type.compare("Directed")==0)
                    {
                        adj[x][y]=(float)w;
                    }
                    else if(type.compare("Undirected")==0)
                    {
                        adj[x][y]=adj[y][x]=(float)w;
                    }
                    sumw+=(float)w;
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

  
    for(int i=0;i<V;i++)
    {
        float sumr=0;
        for(int j=0;j<V;j++)
        {
            if((float)adj[i][j]>0.0)
                sumr+=(float)adj[i][j];
        }
        d[i]=(float)sumr;
    }


	//calculating shortest diffusion times
	
	for(int j=0;j<V;j++)
    {
        MinHeap h(V);
        h.insertRootNode(j);
        
        for(int i=0;i<V;i++)
        {
            if(i!=j)
            {
                h.insertNode(i);
            }   
        }
        
        while(h.heap_size>0)
        {
            hnode hn=h.extractMin();
            if(hn.dval<DBL_MAX)
                difftimes[j][hn.vno]=hn.dval;
            else 
                difftimes[j][hn.vno]=-1.0;

            int u=hn.vno;
            
            for(int i=0;i<V;i++)
            {
                if(i!=u && (float)adj[u][i]>0.0)
                {
                    if(h.isInHeap(i))
                    {
                        if(hn.dval<DBL_MAX)
                        {
                            double temp=getDiffusionTime(u,i);
                            if(h.getdval(i)>temp+hn.dval)
                            {
                                h.decreaseKey(i,temp+hn.dval);
                            }
                        }
                    }
                }
            }
        }
    }


	map<int,vector<pair<int,double> > > mp;
	map<int,vector<pair<int,double> > >::iterator it;
	
	for(int j=0;j<V;j++)
	{
		double max=-1.0;
		int count=0;
		for(int k=0;k<V;k++)
		{
			if(j!=k)
			{
				double temp=difftimes[j][k];
				if(temp!=-1.0)
				{
					count++;
					if(temp>max)
						max=temp;
				}
			}
		}
		if(count>0)
			mp[count].push_back(pair<int,double>(j,max));
	}
	
	it=mp.end();
	it--;
	double min=DBL_MAX;
	int ind=-1;
	for(int j=0;j<(it->second).size();j++)
	{
		if((it->second)[j].second<min)
		{
			min=(it->second)[j].second;
			ind=(it->second)[j].first;
		}
	}
	
	cout<<"central node for the whole network is: "<<ind<<endl<<endl;
			
		
	

	cout<<"diffusion process is started:"<<endl;
	map<double,vector<int> > mv;
	map<double,vector<int> >::iterator it2;
	bool isDiffComp[V];
	fill(isDiffComp,isDiffComp+V,false);
	int dnc=0;


 //       map<double,int> mp2;
 //    map<double,int>::iterator itmp2;
 //    mp2[0.0]=40;
	// for(int i=0;i<40;i++)
	// {
	// 	isDiffComp[i]=true;
	// 	//cout<<"node "<<i<<" - 0 time units"<<endl;
	// 	dnc++;
	// 	for(int j=0;j<V;j++)
	// 	{
	// 		if(adj[i][j]>0)
	// 			mv[difftimes[i][j]].push_back(j);
	// 	}
	// }

    map<double,int> mp2;
    map<double,int>::iterator itmp2;
    mp2[0.0]=1; //number of central node	
	isDiffComp[ind]=true;
	//cout<<"node "<<ind<<" - 0 time units"<<endl;
	dnc++;
	for(int j=0;j<V;j++)
	{
		if((float)adj[ind][j]>0.0)
			mv[difftimes[ind][j]].push_back(j);
	}


	   // map<double,int> mp2;
    // map<double,int>::iterator itmp2;
    // mp2[0.0]=lencn;
    // for(int i=0;i<lencn;i++)
    // {
    //     isDiffComp[cn[i]]=true;
    //     //cout<<"node "<<cn[i]<<" - 0 time units"<<endl;
    //     dnc++;
    //     for(int j=0;j<V;j++)
    //     {
    //         if(adj[cn[i]][j]>0)
    //             mv[difftimes[cn[i]][j]].push_back(j);
    //     }
    // }
    
    double totalTime;
    for(it2=mv.begin();it2!=mv.end();it2++)
    {
        for(int i=0;i<(it2->second).size();i++)
        {
            int z=(it2->second)[i];
            if(!isDiffComp[z])
            {
                isDiffComp[z]=true;
                cout<<"node "<<z<<" - "<<it2->first<<" time units"<<endl;
                if(mp2.find(it2->first)==mp2.end())
                    mp2[it2->first]=dnc+1;
                else mp2[it2->first]++;
                dnc++;
                totalTime=it2->first;
                for(int j=0;j<V;j++)
                {
                    if(adj[z][j]>0 && !isDiffComp[j])
                        mv[(it2->first)+difftimes[z][j]].push_back(j);
                }
            }
        }
    }
    cout<<"total number of nodes which get information are: "<<dnc<<endl;
    cout<<"time taken for the information to get diffused in the whole network is: "<<totalTime<<" time units"<<endl;
    int cnd=0;
    for(int i=0;i<V;i++)
    {
        if(!isDiffComp[i])
            cnd++;
    }
    cout<<"total number of nodes are: "<<V<<" and number of nodes which do not get information are: "<<cnd<<endl;
    cout<<"[";
    for(itmp2=mp2.begin();itmp2!=mp2.end();itmp2++)
    {
        cout<<itmp2->first<<",";
    }
    cout<<"]"<<endl;

    cout<<"[";
    for(itmp2=mp2.begin();itmp2!=mp2.end();itmp2++)
    {
        cout<<itmp2->second<<",";
    }
    cout<<"]"<<endl;
    return 0;
}