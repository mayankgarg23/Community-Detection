#include <bits/stdc++.h>
#define N 309
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

int adj[N][N];
// int f[4000][1000];
// int m,V;
int colA=0;
int rowA=0;
float sumw=0;
int main()
{
    
    //memset(adj,-1,sizeof(adj));
    string line;
    ifstream file;
    file.open("graph-0.csv");
    if(file.good())
    {  
        while(getline(file,line))
        {
            stringstream ss(line);
            string s;
            while(getline(ss,s,','))
            {
                adj[rowA][colA] = atoi(s.c_str());
                colA++;
            }
            rowA++;
            colA=0;
        }
    }
    file.close();
    // for(int i=0;i<4;i++)
    // {
    //     for(int j=0;j<4;j++)
    //     {
    //     	cout<<adj[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    float sim[N][N]={{0.0}};
    int cn=0,tn=0;
    for(int k=0;k<N;k++)
    {
    	for(int i=0;i<N;i++)
    	{
    		for(int j=0;j<N;j++)
    		{
    				if(adj[k][j]==1 && adj[i][j]==1)
    					cn++;
    				if((adj[k][j]==1 && adj[i][j]==0) || (adj[k][j]==0 && adj[i][j]==1) || (adj[k][j]==1 && adj[i][j]==1))
    					tn++;
    		}
    		//cout<<cn<<" "<<tn<<endl;
    		float jaccard = (float)(cn)/tn;
    		//cout<<"Jaccard"<<jaccard<<endl;
    		sim[k][i]=(float)jaccard;
      		cn=0;tn=0;
      	}
	}
	for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
        	if(isnan(sim[i][j]))
        		sim[i][j]=0;
        }
    }
	// for(int i=0;i<N;i++)
 //    {
 //        for(int j=0;j<N;j++)
 //        {
 //        	cout<<sim[i][j]<<" ";
 //        }
 //        cout<<endl;
 //    }
    
    for(int i=0;i<N;i++)
    {
    	for(int j=0;j<N;j++)
    	{
    		//if(adj[i][j]!=-1)
    			sumw+=(float)sim[i][j];
    	}
    }


    	vector<vector<int> > c;
     	for(int i=0;i<N;i++)
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
    					float sum=0.0,sum_in=0.0,links_in=0.0;
    					for(int x=0;x<c[k].size();x++)
    					{
    						if((float)sim[s][c[k][x]]>0.0)
    							sum+=(float)sim[s][c[k][x]];
    					}
    					for(int x=0;x<c[k].size();x++)
    					{
    						for(int y=0;y<N;y++)
    						{
    							if((float)sim[y][c[k][x]]>0.0)
    								sum_in+=(float)sim[y][c[k][x]];
    						}
    					}
    					for(int x=0;x<N;x++)
    					{
    						if((float)sim[x][s]>0.0)
    							links_in+=(float)sim[x][s];
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
    	myfile.open("jaccard_central_node.csv");
    	for(int g=0;g<c.size();g++)
    	{	
    		if(c[g].size()>0)
    		{
                myfile<<"nodes"<<endl;
    			for(int h=0;h<c[g].size();h++)
    			{
    				myfile<<c[g][h]<<endl;
    			}
                myfile<<endl;

                //calculating shortest distance
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
            myfile<<"most central node is: "<<c[g][indmax]<<endl<<endl;
    	}
    }
    return 0;
}
