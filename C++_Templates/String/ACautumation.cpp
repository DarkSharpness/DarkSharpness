// �����ֵ���д�ں��������
// ƥ��ÿ�������˼���
// ���Ӷ�O(ÿ���ַ���������� + �ı�����)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
const ll M=2e6+10;
//��ʽǰ���Ǽӱ� ����=����=�ַ����Ⱥ� 
typedef unsigned int dot;



//����������
int n,ans[N];
char s[M];
class ACAutomation{


    int id[N][26],nxt[N],cnt=0;
    // id[i][k]ָ��idΪi�Ľڵ���һ����ĸΪchar(k+'a')ʱ�ı��
    //nxt[i]�ǽڵ�iʧ��ʱָ�����һ���ڵ�ı��
    //cnt�ǽڵ�����
    int match[N],size[N];
    //match[i]��ԭ�����Ϊi�ĵ������ϵı��
    //size[i]�ǳ��ִ����ۼ���
    public:
    void insert(char *c,int num)//�����ַ�
    {
        int len=strlen(c),j=0;
        for(int i=0 ; i<len ; ++i)//��Trie��
        {
            int x=c[i]-'a';
            if(!id[j][x])id[j][x]=++cnt;//���ڵ�
            j=id[j][x];//��j
        }
        match[num]=j;//�������
    }
    void buildnxt()//���nxt����
    {
        queue <int> q;
        for(int i=0 ; i<26;++i) if(id[0][i]) nxt[id[0][i]]=0,q.push(id[0][i]);
        //��Ԥ����ڶ���(����Ϊ1)��nxt����,�еĵ���ѹ�����
        while(!q.empty())//bfs���
        {
            int v=q.front();q.pop();
            for(int i=0 ; i<26 ; ++i)//ö����һ�ַ��Ƕ���
            {//�ӽڵ�id[v][i]
                if(id[v][i]) nxt[id[v][i]]=id[nxt[v]][i],q.push(id[v][i]);
                //��������ӽڵ�
                //���ӽڵ��nxtָ��ı�� Ϊ �Լ���nxtָ��Ϊi(������ַ�)��id�� Ȼ��ѹ�����
                else id[v][i]=id[nxt[v]][i];
                //������
                //��ǰ�ڵ���ӽڵ�ָ���Լ���nxtָ���i��(����ʱ�൱�ڷ�����)
                //ǰ��Ĳ��Ѿ�������� ���nxt[v]�ĵ�i���ڵ㲻���� 
                //��ô���Ѿ���Ԥ����ǰ����ڵ�
            }
        }
    }
    void dfs(int id)//����nxt[i]ָ��i����
    {
        for(int i=head[id];i;i=e[i].nxt)
        {
            int v=e[i].v;
            dfs(v);
            size[id]+=size[v];//�Լ����ʴ������Ƕ��ӵ��ۼ�
        }
    }
    void query(char *c)
    {
        int len=strlen(c),j=0;
        for(int i=0 ; i<len;++i)//�����size
        {
            j=id[j][c[i]-'a'];//����һ��,�����������ͨ��Ԥ���������ǰ��
            size[j]++;
            //ƥ�������-1 val��Ϊ�˷�ֹ��һ���ĵ���
        }
        for(int i=1 ; i<=cnt ; ++i) adde(nxt[i],i);//�ӱ�
        dfs(0);//����dfs
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