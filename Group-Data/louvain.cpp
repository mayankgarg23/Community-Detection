#include <bits/stdc++.h>

using namespace std;

int adj[1500][1500];
string nodes[1500];
int V;

int main()
{
    V=0;
    memset(adj,-1,sizeof(adj));
    string line;
    map<string,int> m;
    

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
							sum+=adj[s][c[k][x]]; //k(i,in)
					}
					for(int x=0;x<c[k].size();x++)
					{
						for(int y=0;y<V;y++)
						{
							if(adj[y][c[k][x]]>0)
								sum_in+=adj[y][c[k][x]]; //summation(tot)
						}
					}
					for(int x=0;x<V;x++)
					{
						if(adj[x][s]>0)
						links_in+=adj[x][s]; //k(i)
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
	myfile.open("op.csv");
	myfile<<"id,modularity_class"<<endl;
	for(int g=0;g<c.size();g++)
	{	
		if(c[g].size()>0)
		{
			for(int h=0;h<c[g].size();h++)
			{
				myfile<<nodes[c[g][h]]<<","<<g<<endl;
			}
		}
	}
    return 0;
}
