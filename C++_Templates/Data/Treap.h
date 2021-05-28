#ifndef _Data_Treap_H_
#define _Data_Treap_H_
#include <vector>
#include <Data/Tstack.h>


namespace std{

#define nullnode 0  //�ս��
#define none k==nullnode //û�ж���

typedef int value;
/**
 * @brief A balanced tree structure based on Treap algorithm.\n
 * You must offer the operator "==" and "<" for the value type.
 * 
 * 
 */
//template  <typename value>
class Treap
{
    //�����ṹ:���
    struct node
    {
        value val;         //ֵ
        size_t siz;        //��С
        size_t rep;        //�ظ�����
        size_t lc, rc;     //���Ҷ���
        unsigned int rand; //���ֵ
        //��ֵ
        inline node(const value &_val, const size_t &_siz, const size_t &_rep,
                    const unsigned int &_rd, const size_t &_lc, const size_t &_rc)
        {
            val = _val;
            siz = _siz;
            rep = _rep;
            rand = _rd;
            lc = _lc;
            rc = _rc;
        }
        node()
        {
            siz = 0;
            rep = 0;
            rand= 0;
            lc  = 0;
            rc  = 0;
        }
    };
    vector<node> t;  //�ڵ�����.t[0]����
    size_t root;
    Tstack <size_t> q;//ɾ�������ݿ����ظ�����
    //û�ж���
    //�ҽڵ�����
    inline void Lrot(size_t &k)
    {
        size_t nex = t[k].rc;
        t[k].rc = t[nex].lc;
        t[nex].lc = k;
        t[nex].siz = t[k].siz;
        t[k].siz = t[t[k].lc].siz + t[t[k].rc].siz + t[k].rep;
        k = nex;
    }
    //��ڵ�����
    inline void Rrot(size_t &k)
    {
        size_t nex = t[k].lc;
        t[k].lc = t[nex].rc;
        t[nex].rc = k;
        t[nex].siz = t[k].siz;
        t[k].siz = t[t[k].lc].siz + t[t[k].rc].siz + t[k].rep;
        k = nex;
    }
    void Insert(size_t &k, const value &x)
    {
        if (none) //�սڵ�,˵����Ҫ��������
        {
            if(q.empty()){//������û��Ԫ���� ��������
                k = t.size(); 
                t.emplace_back(x, 1, 1, rand(), nullnode , nullnode );
            }
            else { //�Ӷ������ҳ��Ѿ����ͷŵ�Ԫ�� ��Լ�ڴ�
                k = q.popfront();
                t[k].val=x;
                t[k].rep=t[k].siz=1;
                t[k].rand=rand();
                t[k].lc=t[k].rc=nullnode;
            }
            return;
        }
        ++t[k].siz;
        if (t[k].val == x) ++t[k].rep;
        else if (x < t[k].val)
        {
            Insert(t[k].lc, x);//��߷ǿ�
            if (t[k].rand > t[t[k].lc].rand)
                Rrot(k);
        }
        else
        {
            Insert(t[k].rc, x);
            if (t[k].rand > t[t[k].rc].rand)
                Lrot(k);
        }
    }
    void Erase(size_t &k, const value &x)
    {
        if(none) return ;
        if(t[k].val==x)//�ҵ��� ����ɾ�����
        {
            if(t[k].rep>1){                   //����һ��,ɾһ���Ϳ�����
                --t[k].rep;
                --t[k].siz;
                return;
            }
            //����ɾ���ɾ�,��������
            if(t[k].rc==nullnode||t[k].lc==nullnode){ //ֻ��0/1������,ֱ�Ӽ̳и�����
                //q.push(k);                    //k��ɾ����,���ڴ治���˷�
                k=t[k].lc+t[k].rc;         
            }
            else {//����������,��rand��С�Ľ���,�Լ���ȥ,ֱ���ײ���һ��û������
                if(t[t[k].lc].rand<t[t[k].rc].rand) Rrot(k); //randС��������
                else Lrot(k);
                Erase(k,x);
            }
            return;
        }
        --t[k].siz;
        if(x<t[k].val) Erase(t[k].lc,x);
	    else Erase(t[k].rc,x); 
    }
    void Multiinsert(size_t &k,const value &x,const size_t &multis)
    {
        if (none) //�սڵ�,˵����Ҫ��������
        {
            if(q.empty()){//������û��Ԫ���� ��������
                k = t.size(); 
                t.emplace_back(x, multis , multis, rand(), nullnode , nullnode );
            }
            else { //�Ӷ������ҳ��Ѿ����ͷŵ�Ԫ�� ��Լ�ڴ�
                k = q.popfront();
                t[k].val=x;
                t[k].rep=t[k].siz=multis;
                t[k].rand=rand();
                t[k].lc=t[k].rc=nullnode;
            }
            return;
        }
        t[k].siz+=multis;
        if (t[k].val == x) t[k].rep+=multis;
        else if (x < t[k].val)
        {
            Multiinsert(t[k].lc, x,multis);//��߷ǿ�
            if (t[k].rand > t[t[k].lc].rand)
                Rrot(k);
        }
        else
        {
            Multiinsert(t[k].rc, x,multis);
            if (t[k].rand > t[t[k].rc].rand)
                Lrot(k);
        }
    

    }
    void Multierase(size_t &k, const value &x, const size_t &_rep)
    {
    }
    size_t rank1(const size_t &k,const value &x)const{
        if(none) return 0;//������
        if(t[k].val==x)     return t[t[k].lc].siz+1;
        else if(t[k].val<x) return rank1(t[k].rc,x)+t[k].rep+t[t[k].lc].siz;
        else                return rank1(t[k].lc,x);
    }
    value rank2(const size_t &k,const size_t &x)const{
        if(none) return 0;
        //cout << x <<endl;
        if(x<=t[t[k].lc].siz)               return rank2(t[k].lc,x);
        else if(x<=t[t[k].lc].siz+t[k].rep) return t[k].val;
        else                                return rank2(t[k].rc,x-t[t[k].lc].siz-t[k].rep);
    }
    void pre(const size_t &k,const value &x,size_t &ans)const{
        if(none) return ;
        if(t[k].val<x) 
        {
            ans=k;
            pre(t[k].rc,x,ans);
        }
        else pre(t[k].lc,x,ans);
    }
    void suc(const size_t &k,const value &x,size_t &ans)const{
        if(none) return ;
        if(x<t[k].val) 
        {
            ans=k;
            suc(t[k].lc,x,ans);
        }
        else suc(t[k].rc,x,ans);
    }

public:
    /**
     * @brief Insert _X to Treap.
     * 
     * @param _X The element inserted.
     */
    inline void insert(const value &_X)
    {
        Insert(root, _X);
    }
    /**
     * @brief Erase element _X once from Treap.\n
     * If _X doesn't exist,nothing happens.
     * 
     * @param _X The element to be deleted
     */
    inline void erase(const value &_X)
    {
        Erase(root, _X);
    }
    /**
     * @brief Insert mutiple identical element to the Treap. 
     * @param _X The value to be added.
     * @param _rep How many times it is repeated.
     */
    inline void multiinsert(const value &_X,const size_t &_rep)
    {
        if(!_rep) return ;
        Multiinsert(root,_X,_rep);
    }
    /**
     * @brief ��Ԫ��_X��Treap��ɾ��_rep��
     * ���ɾ���˻�_X������,��ôɾ��û��
     * 
     * @param _X   ɾ����Ԫ��
     * @param _rep ɾ���Ĵ���
     */
    inline void multierase(const value &_X, const size_t &_rep)
    {
        if (!_rep)
            return; //0�ξ��ǲ�ɾ��
        Multierase(root, _X, _rep);
    }
    inline size_t rankval(const value &_X)const{
        return rank1(root,_X);
    }
    inline value rankloc(const size_t &_loc)const{
        return rank2(root,_loc);
    }
    inline value pre(const value &x)const{
        size_t ans=0;
        pre(root,x,ans);
        return t[ans].val;
    }
    inline value suc(const value &x)const{
        size_t ans=t.size();//������������һ���ͷ���0
        suc(root,x,ans);
        return t[ans].val;
    }
    //rank
    /**
     * @brief ��ʼ���ռ�,�����Treap����������,���Լ���vector�����ڴ������ʱ�俪֧
     * 
     * @param _siz ����Ŀռ��С
    */
    inline void respace(const size_t &_size)//Ԥ���ռ�
    {
        while(!q.empty()) q.pop();
        root=0;
        if(t.capacity()==_size+1)
        {
            t.empty();
            t.resize(1);
            t.front().rep=t.front().siz=0;
            return ;
        }
        t.empty();
        t.shrink_to_fit();
        t.reserve(_size+1);
        t.resize(1);
        t.front().rep=t.front().siz=0;
    }
    /**
     * @brief ����һ�� Treap ����
     * 
     */
    Treap()
    {
        while(!q.empty()) q.pop();
        root =0 ;
        t.clear();
        t.resize(1);
        t.front().rep=t.front().siz=0;
    }

};

#undef none
#undef null

}

#endif