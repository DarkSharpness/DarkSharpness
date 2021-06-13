// 这是字典树写在函数里面的
// 匹配每个出现了几次
// 复杂度O(每个字符串的最长长度 + 文本长度)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
const ll M=2e6+10;
//链式前向星加边 边数=点数=字符长度和 
typedef unsigned int dot;



//主函数部分
int n,ans[N];
char s[M];
class ACAutomation{


    int id[N][26],nxt[N],cnt=0;
    // id[i][k]指代id为i的节点下一个字母为char(k+'a')时的编号
    //nxt[i]是节点i失配时指向的下一个节点的编号
    //cnt是节点总数
    int match[N],size[N];
    //match[i]是原来编号为i的点在树上的编号
    //size[i]是出现次数累加器
    public:
    void insert(char *c,int num)//插入字符
    {
        int len=strlen(c),j=0;
        for(int i=0 ; i<len ; ++i)//造Trie树
        {
            int x=c[i]-'a';
            if(!id[j][x])id[j][x]=++cnt;//开节点
            j=id[j][x];//跳j
        }
        match[num]=j;//反向关联
    }
    void buildnxt()//求出nxt数组
    {
        queue <int> q;
        for(int i=0 ; i<26;++i) if(id[0][i]) nxt[id[0][i]]=0,q.push(id[0][i]);
        //先预处理第二层(长度为1)的nxt数组,有的点则压入队列
        while(!q.empty())//bfs求解
        {
            int v=q.front();q.pop();
            for(int i=0 ; i<26 ; ++i)//枚举下一字符是多少
            {//子节点id[v][i]
                if(id[v][i]) nxt[id[v][i]]=id[nxt[v]][i],q.push(id[v][i]);
                //如果存在子节点
                //则子节点的nxt指向的编号 为 自己的nxt指向为i(即这个字符)的id的 然后压入队列
                else id[v][i]=id[nxt[v]][i];
                //不存在
                //则当前节点的子节点指向自己的nxt指针第i个(访问时相当于返回了)
                //前面的层已经处理过了 如果nxt[v]的第i个节点不存在 
                //那么他已经被预处理到前面存在的
            }
        }
    }
    void dfs(int id)//按照nxt[i]指向i走树
    {
        for(int i=head[id];i;i=e[i].nxt)
        {
            int v=e[i].v;
            dfs(v);
            size[id]+=size[v];//自己访问次数就是儿子的累加
        }
    }
    void query(char *c)
    {
        int len=strlen(c),j=0;
        for(int i=0 ; i<len;++i)//处理出size
        {
            j=id[j][c[i]-'a'];//向下一层,如果不存在已通过预处理会跳到前面
            size[j]++;
            //匹配完就是-1 val是为了防止有一样的单词
        }
        for(int i=1 ; i<=cnt ; ++i) adde(nxt[i],i);//加边
        dfs(0);//往下dfs
        for(int i=1;i<=n ;++i) printf("%d\n",size[match[i]]);
    }
}AC;

int main()
{
    scanf("%d",&n);
    for(int i=1 ; i<=n ; ++i) 
        scanf("%s",s),AC.insert(s,i);
    AC.buildnxt();
    scanf("%s",s);
    AC.query(s);
    //for(ll i=1 ; i<=n ;++i)
        //printf("%d\n",tg[i]?ans[tg[i]]:ans[i]);
    return 0;
}