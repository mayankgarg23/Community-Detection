#include <bits/stdc++.h>
#define N 309
using namespace std;

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
	for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
        	cout<<sim[i][j]<<" ";
        }
        cout<<endl;
    }
    
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
    	myfile.open("jaccard_nodes.csv");
    	myfile<<"id,modularity_class"<<endl;
    	for(int g=0;g<c.size();g++)
    	{	
    		if(c[g].size()>0)
    		{
    			for(int h=0;h<c[g].size();h++)
    			{
    				myfile<<c[g][h]<<","<<g<<endl;
    			}
    		}
    	}
    	myfile.close();

    	int counted=0;
    	myfile.open("jaccard_edges.csv");
    	myfile<<"Source,Target,Type,id,weight"<<endl;
    	for(int g=0;g<N;g++)
    	{	
    			for(int h=0;h<g;h++)
    			{
    				if((float)sim[g][h]>0.0)
    					myfile<<g<<","<<h<<",Undirected,"<<counted++<<","<<(float)sim[g][h]<<endl;
    			}
    		
    	}
    	myfile.close();

    return 0;
}
