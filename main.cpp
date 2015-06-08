#include <iostream>
#include <cstdio>
#include <memory.h>
#include <algorithm>

#define N 500
#define M 1000000
#define T 100
#define MAXDISTANCE 10000
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

int preN = 0;
int allN = 0;

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
    /*
    for(int i = 0; i < G.n; i++)
    {
        cout << i << " " << G.Rank[i] << endl;
    }
    */
}

//pre  = all = set of labels cobering all edges e <= E
//preN allN记录这个集合里面有多少的数据

void initLabel(GRAPH &G, LABEL *pre, LABEL *all)
{
    for(int i = 0; i < G.n; i++)
    {
        for(int j = 0; j < G.n; j++)
        {
            //存在边的情况
            if(G.edge[i][j] > 0 && G.edge[i][j] < T)
            {
                pre[preN].v1 = i;
                pre[preN].v2 = j;
                pre[preN].d = G.edge[i][j];
                all[allN].v1 = i;
                all[allN].v2 = j;
                all[allN].d = G.edge[i][j];
                preN ++;
                allN ++;
            }
        }
    }
}

//在all label里面找到最小值
int getDistance(int v1, int v2, LABEL *all)
{
    for(int i =0;  i < allN; i++)
    {
        if(all[i].v1 == v1 && all[i].v2 == v2)
        {
            return all[i].d;
        }
    }
    return MAXDISTANCE;

}

//rule 1 2 4 5 update the label
void Update(GRAPH &G, LABEL * pre, LABEL * all)
{
    LABEL tmp[N];
    int k = 0;
    //rule1 2 4 5
    //cout << preN << "  " << allN << endl;
    //第一次有12组
    //cout << preN << "  " << allN << endl;
    int allNTep = allN;
    int preNTep = preN;
    for(int i = 0;  i < preNTep; i++)
    {
        int preV1 = pre[i].v1;
        int preV2 = pre[i].v2;
        //cout << endl;
        //cout << preV1 << " " << preV2 << "  " << pre[i].d << endl;;
        for(int j = 0; j < allNTep; j++)
        {
            int allV1 = all[j].v1;
            int allV2 = all[j].v2;

            if((G.Rank[preV1] < G.Rank[preV2]) && (preV1 == allV2) && (G.Rank[allV1] > G.Rank[allV2]) && (preV2 != allV1) && (pre[i].d + all[j].d < getDistance(allV1, preV2, all)))
            {
                //cout << "rule 1" << endl;
                //cout << allV1 << " " << allV2 << " " << all[j].d << endl;
                tmp[k].v1 = allV1;
                tmp[k].v2 = preV2;
                tmp[k].d = pre[i].d + all[j].d;
                k++;
            }
            else
            {
                if((G.Rank[preV1] < G.Rank[preV2]) && (preV1 == allV2) && (G.Rank[allV1] < G.Rank[allV2]) && (preV2 != allV1) && (pre[i].d + all[j].d < getDistance(allV1, preV2, all)))
                {
                    //cout << "rule 2" << endl;
                    //cout << allV1 << " " << allV2 << " " << all[j].d << endl;
                    tmp[k].v1 = allV1;
                    tmp[k].v2 = preV2;
                    tmp[k].d = pre[i].d + all[j].d;
                    k++;
                }
                else
                {
                    if((G.Rank[preV1] > G.Rank[preV2]) && (preV2 == allV1) && (G.Rank[allV1] < G.Rank[allV2]) && (preV1 != allV2) && (pre[i].d + all[j].d < getDistance(preV1, allV2, all)))
                    {
                        //cout << "rule 4" << endl;
                        //cout << allV1 << " " << allV2 << " " << all[j].d << endl;
                        tmp[k].v1 = preV1;
                        tmp[k].v2 = allV2;
                        tmp[k].d = pre[i].d + all[j].d;
                        k++;
                    }
                    else
                    {
                        if((G.Rank[preV1] > G.Rank[preV2]) && (preV2 == allV1) && (G.Rank[allV1] > G.Rank[allV2]) && (preV1 != allV2) && (pre[i].d + all[j].d < getDistance(preV1, allV2, all)) )
                        {
                            //cout << "rule 5" << endl;
                            //cout << allV1 << " " << allV2 << " " << all[j].d << endl;
                            tmp[k].v1 = preV1;
                            tmp[k].v2 = allV2;
                            tmp[k].d = pre[i].d + all[j].d;
                            k++;
                        }
                    }
                }
            }

        }
    }
    //tmp is the pre -> pre
    //add tmp to all
    preN = k;
    for(int i = 0; i < k; i++)
    {
        pre[i].v1 = tmp[i].v1;
        pre[i].v2 = tmp[i].v2;
        pre[i].d = tmp[i].d;
        allN++;
        all[allN].v1 = tmp[i].v1;
        all[allN].v2 = tmp[i].v2;
        all[allN].d = tmp[i].d;
        //print
        //cout << pre[i].v1 << "  " << pre[i].v2 << "  " << pre[i].d << endl;
        //cout << all[allN].v1 << "  " << all[allN].v2 << "  " << all[allN].d << "  " << allN << endl;
    }
}

//now start the algorithm
void start(GRAPH &G, LABEL *pre, LABEL *all)
{
    /*
    Update(G, pre, all);
    cout << "--------------------" << endl;
    Update(G, pre, all);
    cout << "--------------------" << endl;
    Update(G, pre, all);
    */
    int i = 0;
    while (preN)
    {
        i++;
        Update(G, pre, all);
        cout << i << "iteration" << endl;
    }
}

void findDistance(int n1, int n2, GRAPH G, LABEL *all)
{
    int flag = 1;
    cin >> n1 >> n2;
    /*
    for(int i = 0; i < allN; i++)
    {
        cout << all[i].v1 << " " << all[i].v2 << " " << all[i].d << endl;
    }
    */
    //直接就有的情况，下面还应该有其他的组合情况
    for(int i = 0; i < allN; i++)
    {
        if(n1 == all[i].v1 && n2 == all[i].v2)
        {
            cout << "The Distance from" << n1 << "to" << n2 << "is" << all[i].d << endl;
            flag = 0;
            break;
        }
    }

    for(int i = 0; i < allN; i++)
    {
        for(int j = 0; j < allN; j++)
        {
            //cout << i << "  " << j << endl;
            if(n1 == all[i].v1 && n2 == all[j].v2 && all[i].v2 == all[j].v1)
            {
                cout << "The Distance from" << n1 << "to" << n2 << "is" << all[i].d+all[j].d << endl;
                flag = 0;
                break;
            }
        }
        if(!flag)
        {
            break;
        }
    }
    if (flag)
    {
        cout << "The Distance from" << n1 << "to" << n2 << "is" << "too long" << endl;
    }
}

int main()
{
    GRAPH G;//假定最多有N组数据
    LABEL pre[N], all[N];
    freopen("a.txt", "r", stdin);
    initGraph(G);
    scanfGraph(G);
    //printGraph(G);
    getRank(G);
    initLabel(G, pre, all);
    start(G, pre, all);
    int n1, n2;
    findDistance(n1, n2, G, all);
    return 0;
}
