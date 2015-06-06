#include <iostream>
#include <cstdio>
#include <memory.h>
#include <algorithm>

#define N 50
#define M 1000000
#define T 100

using namespace std;

struct GRAPH
{
    int n, e;
    int edge[N][N];
    int vertex[N];
    int degIn[N], degOut[N];
    int deg[N];
    int Rank[N];
};

struct LABEL
{
    int v1, v2, d;
};

struct node
{
    int  num;
    int index;
} r[100];

bool compare(node a, node b)
{
    return a.num > b.num;
}

void initGraph(GRAPH &G)
{
    cin >> G.n >> G.e;
    memset(G.deg, 0 , sizeof(G.deg)/sizeof(int));
    for(int i = 0; i < G.n; i++)
    {
        for(int j = 0; j < G.n; j++)
        {
            if(i == j)
            {
                G.edge[i][j] = 0;
            }
            else
            {
                G.edge[i][j] = M;
            }
        }
    }
}

void scanfGraph(GRAPH &G)
{
    int x, y, w;
    memset(G.deg, 0, sizeof(G.deg)/sizeof(int));
    memset(G.degIn, 0, sizeof(G.degIn)/sizeof(int));
    memset(G.degOut, 0, sizeof(G.degOut)/sizeof(int));
    for(int i = 0; i < G.e; i++)
    {
        cin >> x >> y >> w;
        G.edge[x][y] = w;
        G.degOut[x]++;
        G.degIn[y]++;
        G.deg[x]++;
        G.deg[y]++;
    }
}

void printGraph(GRAPH G)
{
    cout << "存进去的图为：" << endl;
    for(int i = 0; i < G.n; i++)
    {
        for(int j = 0; j < G.n; j++)
        {
            cout << G.edge[i][j] << " ";
        }
        cout << endl;
    }
    /*
    cout << "每个点的度，入度，出度为：" << endl;
    for(int i = 0; i < G.n; i++)
    {
        cout << i << " " << G.deg[i] << " " << G.degIn[i] << " " << G.degOut[i] << endl;
    }
    */
}

void getRank(GRAPH &G)
{
    for(int i = 0; i < G.n; i++)
    {
        r[i].num = G.deg[i];
        r[i].index = i;
        //cout << "print the information of r" << endl;
        //cout << r[i].num << " " << r[i].index << endl;
    }
    //根据Num降序排序
    sort(r, r + G.n, compare);
    //知道了某个点的具体RANK
    for(int i = 0; i < G.n; i++)
    {
        G.Rank[r[i].index] = i;
    }
    //每个点的rank
    for(int i = 0; i < G.n; i++)
    {
        cout << i << " " << G.Rank[i] << endl;
    }
}

//pre  = all = set of labels cobering all edges e <= E
void initLabel(GRAPH &G, LABEL *pre, LABEL *all)
{
    for(int k = 0; k < G.n; k++)
    {
        for(int i = 0; i < G.n; i++)
        {
            for(int j = 0; j < G.n; j++)
            {
                if(G.edge[i][j] > 0 && G.edge[i][j] < T)
                {
                    pre[k].v1 = i;
                    pre[k].v2 = j;
                    pre[k].d = G.edge[i][j];
                    all[k].v1 = i;
                    all[k].v2 = i;
                    all[k].d = G.edge[i][j];
                }
            }
        }
    }
}


void Update(GRAPH &G, LABEL *pre, LABEL *all)
{
    for(int i = 0; i < G.n; i++)
    {

    }
}

//now start the algorithm
void start(GRAPH &G, LABLE *pre, LABEL *all)
{
    while(true)
    {

    }
}
int main()
{
    GRAPH G;
    LABEL pre[N], all[N];
    int a;
    freopen("a.txt", "r", stdin);
    initGraph(G);
    scanfGraph(G);
    //printGraph(G);
    getRank(G);
    initLabel(G, pre, all);
    start(G, pre, all);
    return 0;
}
