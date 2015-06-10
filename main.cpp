/*
 * @name: Shangbin Yang
 * @email: rccoder@foxmail.com
 * @date: 2015-6-7
 * @Company: Harbin Institute of Technology
 */

#include <iostream>
#include <cstdio>
#include <memory.h>
#include <algorithm>

#define N 210
#define M 1000000
#define T 100
#define MAXDISTANCE 10000

using namespace std;

/*
 * @description: 存储输入的图，有下面几个元素
 *               n - 图的顶点个数
 *               e - 图的边个数
 *               edge[N][N] - 两点之间的距离
 *               vertex[N] - 顶点标记
 *               deg[N] - 顶点的度
 *               degIn[N] degOut[N] - 顶点入度出度
 *               Rank[N] - 顶点按照度排列后的Rank
 */
struct GRAPH
{
    int n, e;
    int edge[N][N];
    int vertex[N];
    int degIn[N], degOut[N];
    int deg[N];
    int Rank[N];
};

/*
 * @description: 用来存储后面生成的LABEL,元素如下：
 *              v1 - 起始节点
 *              v2 - 结束节点
 *              d - v1到v2之间的距离
 */
struct LABEL
{
    int v1, v2, d;
};

/*
 * @description: 后续进行Rank排序时使用，num标记值，index标记下标
 */
struct node
{
    int  num;
    int index;
} r[M];

/*
 * preLabel allLabel的集合个数，全局变量
 */
int preN = 0;
int allN = 0;

/*
 * @Function: compare
 * @description: 用来比较倒序比较大小，配合sort使用
 */
bool compare(node a, node b)
{
    return a.num > b.num;
}

/*
 * @Function: initGraph
 * @description: 初始化图，主要完成对边长度的初始化
 */
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

/*
 * @Function: scanfGraph
 * @description: 输入图
 */
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

/*
 * @Function: printGraph
 * @description: 输出图，测试使用
 */
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

/*
 * @Function: getRank
 * @description: 按照度的大小倒序进行Rank排序
 *
 */
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

/*
 * @Function: initLabel
 * @description: 初始化pre,all标签集合, 两个内容在初始化的时候相等
 */
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

/*
 * @Function: getDistance
 * @discription: 在label里面得到最小值
 */
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

/*
 * @Function: Update
 * @description: 更新图，使用1245 rules
 */
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

/*
 * @Function: start
 * @description: 开始算法的正式使用
 */
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

/*
 * @Function: findDistance
 * @description: 在all 这个label里面找到最短距离
 */
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
            cout << "The Distance from " << n1 << " to " << n2 << " is " << all[i].d << endl;
            flag = 0;
            break;
        }
    }
    if(flag)
    {    
        for(int i = 0; i < allN; i++)
        {
            for(int j = 0; j < allN; j++)
            {
                //cout << i << "  " << j << endl;
                if(n1 == all[i].v1 && n2 == all[j].v2 && all[i].v2 == all[j].v1)
                {
                    cout << "The Distance from " << n1 << " to " << n2 << " is " << all[i].d+all[j].d << endl;
                    flag = 0;
                    break;
                }
            }
            if(!flag)
            {
                break;
            }
        }
    }
    if (flag)
    {
        cout << "The Distance from " << n1 << " to " << n2 << " is " << "too long" << endl;
    }
}

int main()
{
    GRAPH G;//假定最多有N组数据
    LABEL pre[N], all[N];
    freopen("data.txt", "r", stdin);
    initGraph(G);
    scanfGraph(G);
    //printGraph(G);
    getRank(G);
    initLabel(G, pre, all);
    start(G, pre, all);
    int n1 = 0, n2 = 0;
    findDistance(n1, n2, G, all);
    return 0;
}
