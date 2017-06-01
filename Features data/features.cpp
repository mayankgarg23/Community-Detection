#include <bits/stdc++.h>

using namespace std;

int adj[4000][4000];
int f[4000][1000];
int m,V;

int main()
{
    
    memset(adj,-1,sizeof(adj));
    memset(f,-1,sizeof(f));
    string line;
   
    
    //ifstream nodefile("interactions[Nodes].csv");
    //ifstream edgefile("interactions[Edges].csv");
    //ifstream nodefile("example_input [Nodes].csv");
    //ifstream edgefile("example_input [Edges].csv");
    ifstream edgefile("features_1.txt");
    //ifstream edgefile("group_153631204680678_2016_10_06_17_49_15_interactions [Edges].csv");
    int sumw=0;
    if(edgefile.is_open())
    {
      
        while(getline(edgefile,line))
        {
            stringstream ss(line);
            string s,type;
            int x,y;
            int i=1,fn=0;
            while(getline(ss,s,' '))
            {
                if(i==1)
                {
                    //cout<<s<<endl;
                	char* c=new char[s.length()+1];
                	strcpy(c,s.c_str());
                	m=atoi(c);
                	
                	//cout<<nodes[V]<<" ";
                }
                if(i>1)
                {
                   stringstream sss(s);
                   string s2;
                   getline(sss,s2,';');
                   if(s2.compare("education_school_id")==0)
                   {
                   		getline(sss,s2,';');
                   		char* c=new char[s2.length()+1];
                   		strcpy(c,s2.c_str());
                   		int n=atoi(c);
                   		f[m][fn]=n;
                   		//cout<<f[V][fn]<<" ";
                   		fn++;
                   }
                }
                i++;
            }
            //cout<<endl;
        }
    }
    edgefile.close();
    V=m+1;

    // for(int i=0;i<V;i++)
    // {
    // 	for(int j=0;j<V;j++)
    // 		cout<<f[i][j]<<" ";
    // 	cout<<endl;
    // }
    // cout<<endl<<endl;
    
    for(int i=0;i<V;i++)
    {
    	for(int j=i+1;j<V;j++)
    	{
    		int x=0,y;
    		while(f[i][x]!=-1)
    		{
    			y=0;
    			while(f[j][y]!=-1)
    			{
    				if(f[i][x]==f[j][y])
    				{
    					if(adj[i][j]==-1)
    						adj[i][j]=adj[j][i]=1;
    					else
    						{
    							adj[i][j]++;
    							adj[j][i]++;
    						}
    				}
    				y++;
    			}
    			x++;
    		}
    	}
    }
    
    for(int i=0;i<V;i++)
    {
    	for(int j=0;j<V;j++)
    	{
    		if(adj[i][j]!=-1)
    			sumw+=adj[i][j];
    	}
    }


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
    	myfile.open("nodes.csv");
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
    	myfile.open("edges.csv");
    	myfile<<"Source,Target,Type,id,weight"<<endl;
    	for(int g=0;g<V;g++)
    	{	
    			for(int h=0;h<g;h++)
    			{
    				if(adj[g][h]>0)
    					myfile<<g<<","<<h<<",Undirected,"<<counted++<<","<<adj[g][h]<<endl;
    			}
    		
    	}
    	myfile.close();

    return 0;
}
