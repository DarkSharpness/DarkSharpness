//This offers you a standard Treap,
//supporting various value type.
//Remeber you should offer operator
//">" "==" for the value type
#ifndef _Data_Treap_H_
#define _Data_Treap_H_
//#if __cplusplus >= 201103L
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Data/Tstack.h>


namespace std{


//typedef int value;


/**
 * @brief A balanced tree structure based on Treap algorithm.\n
 * You must offer the operator "==" and "<" for the value type.\n 
 * Sizeof : 64.
 * @tparam value Type you want to keep in the %Treap
 * 
 */
template  <typename value>
class Treap
{
#define nullnode 0  //空结点
#define none k==nullnode //没有儿子

private :
    //辅助结构:结点
    struct node
    {
        value val;         //值
        size_t siz;        //大小
        size_t rep;        //重复次数
        size_t lc, rc;     //左右儿子
        unsigned int rand; //随机值
        //赋值
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
    
    
    vector <node> t;  //节点数组.t[0]祭天
    size_t root;
    Tstack <size_t> q;//删除的数据可以重复利用

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
        try{
            Erase(root, _X);
        }
        catch(const char *)
        {
            ;
        }
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
     * @brief Erase multiple _X from Treap.
     * It will delete to a positive number or none.
     * 
     * @param _X   The element to be deleted.
     * @param _rep The times it should be removed.
     * 
     *  --- 
     * Note that even if _X doesn't exist in Treap,
     * no error will occur.
     */
    inline void multierase(const value &_X, const size_t &_rep)
    {
        if (!_rep)
            return; //0次就是不删除
        Multierase(root, _X, _rep);
    }
    
    /**
     * @brief Find out the rank of the element in Treap.
     * 
     * @param _X The element to be ranked.
     * @return The rank of the element in Treap.
     * Element not existing,it will be rank as the previous element.
     */
    inline size_t rankval(const value &_X)const{
        return rank1(root,_X);
    }
    
    /**
     * @brief Find out the element ranked _loc.
     * 
     * @param _loc The _loc of the element.
     * @return Value of the certain ranked element.
     */
    inline value  rankloc(const size_t &_loc)const{
        return rank2(root,_loc);
    }
    
    /**
     * @brief Find the previous element.
     * 
     * @param _X The element to find pre with.
     * @return Value of the previous element.
     */
    inline value  pre(const value &_X)const{
        size_t ans=0;
        Pre(root,_X,ans);
        return t[ans].val;
    }
    
    /**
     * @brief Find the succeeding element.
     * 
     * @param _X The element to find suc with.
     * @return Value of the succeeding element.
     */
    inline value  suc(const value &_X)const{
        size_t ans=0;//如果排名是最后一个就返回0
        Suc(root,_X,ans);
        return t[ans].val;
    }
      
    /**
     * @brief Access the total number of the elements.
     * Repetition are counted as well.
     * 
     * @return Size of the Treap 
     */
    inline size_t size()const{
        return t[root].siz;
    }
    /**
     * @brief Element number of the Treap.
     * Each repetition is counted only once.
     * 
     * @return  The element number,equal to the
     * least physical space required.
     */
    inline size_t number()const{
        return t.size()-1-q.size();
    }
    //The capacity of the Treap.
    inline size_t capacity()const{
        return t.capacity()-1;
    }
    /**
     * @brief Return the rest space required before
     * the vector malloc again.
     * 
     * @return The remaining space in the Treap.  
     */
    inline size_t remainder()const{
        return t.capacity()-t.size()+q.size();
    }

    //Shrink to save space.
    inline void shrink(){
        t.shrink_to_fit();
    }
    

    /**
     * @brief Construct an empty Treap.(with only nullnode)
     * 
     */
    Treap()
    {
        while(!q.empty()) q.pop();
        root = 0 ;
        t.clear();
        t.resize(1);
        t.front().rep=t.front().siz=0;
        srand(time(NULL));
        //cout << "构造" <<endl;
    }
    ~Treap()
    {

    }





private :
    
    //更新size
    inline void update(const size_t &k)
    {
        t[k].siz=t[t[k].lc].siz+t[t[k].rc].siz+t[k].rep;
    }
    //右节点往上
    inline void Lrot(size_t &k) 
    {
        size_t nex = t[k].rc;
        t[k].rc = t[nex].lc;
        t[nex].lc = k;
        t[nex].siz = t[k].siz;
        update(k);
        k = nex;
    }
    //左节点往上
    inline void Rrot(size_t &k)
    {
        size_t nex = t[k].lc;
        t[k].lc = t[nex].rc;
        t[nex].rc = k;
        t[nex].siz = t[k].siz;
        update(k);
        k = nex;
    }
    

    void Insert(size_t &k, const value &x){
        if (none) //空节点,说明需要重新申请
        {
            if(q.empty()){//队列里没有元素了 重新申请
                k = t.size(); 
                t.emplace_back(x, 1, 1, rand(), nullnode , nullnode );
                return ;
            }
            else { //从队列中找出已经被释放的元素 节约内存
                k = q.popfront();
                t[k].val=x;
                t[k].rep=t[k].siz=1;
                t[k].rand=rand();
                t[k].lc=t[k].rc=nullnode;
                return;
            }
        }
        ++t[k].siz;
        if (t[k].val == x) ++t[k].rep;
        else if (x < t[k].val)
        {
            Insert(t[k].lc, x);//左边非空
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
   

    void Erase (size_t &k, const value &x) {
        if(none) throw "not found";
        if(t[k].val==x)//找到了 就是删除这个
        {
            if(t[k].rep>1){                   //超过一个,删一个就可以了
                --t[k].rep;
                --t[k].siz;
                return;
            }
            //不能删除干净,分类讨论
            if(t[k].rc==nullnode||t[k].lc==nullnode){ //只有0/1个儿子,直接继承给父亲
                q.push(k);                    //k被删除了,但内存不能浪费
                k=t[k].lc+t[k].rc;         
            }
            else {//有两个儿子,把rand更小的交换,自己下去,直到底部或一边没儿子了
                if(t[t[k].lc].rand<t[t[k].rc].rand) Rrot(k); //rand小的在上面
                else Lrot(k);
                Erase(k,x);
            }
            return;
        }
        if(x<t[k].val) Erase(t[k].lc,x);
	    else Erase(t[k].rc,x); 
        --t[k].siz;//如果throw了,不会执行
    }
    

    void Multiinsert(size_t &k,const value &x,const size_t &multis)
    {
        if (none) //空节点,说明需要重新申请
        {
            if(q.empty()){//队列里没有元素了 重新申请
                k = t.size(); 
                t.emplace_back(x, multis , multis, rand(), nullnode , nullnode );
            }
            else { //从队列中找出已经被释放的元素 节约内存
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
            Multiinsert(t[k].lc, x,multis);//左边非空
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
    

    void Multierase (size_t &k, const value &x, const size_t &_rep)
    {
        if(none) return ;//减掉0个
        if(t[k].val==x)//找到了 就是删除这个
        {
            if(t[k].rep>_rep){                   //超过_rep个,删_rep个就可以了
                t[k].rep-=_rep;
                t[k].siz-=_rep;
                return ;
            }
            //不能删除干净,分类讨论

            if(t[k].rc==nullnode||t[k].lc==nullnode){ //只有0/1个儿子,直接继承给父亲
                q.push(k);                            //k被删除了,但内存不能浪费
                k=t[k].lc+t[k].rc;
            }
            else {//有两个儿子,把rand更小的交换,自己下去,直到底部或一边没儿子了
                if(t[t[k].lc].rand<t[t[k].rc].rand) Rrot(k); //rand小的在上面
                else Lrot(k);
                Multierase(k,x,_rep);
                update(k);
            }
            return;
        }
        if(x<t[k].val) Multierase(t[k].lc,x,_rep);
	    else Multierase(t[k].rc,x,_rep);
        update(k);   //防止没删除或删多了
        return ; 
    }
    

    size_t rank1(const size_t &k,const value  &x)const{
        if(none) return 0;//不存在
        if(t[k].val==x)     return t[t[k].lc].siz+1;
        else if(t[k].val<x) return rank1(t[k].rc,x)+t[k].rep+t[t[k].lc].siz;
        else                return rank1(t[k].lc,x);
    }
    

    value  rank2(const size_t &k,const size_t &x)const{
        if(none) return 0;
        //cout << x <<endl;
        if(x<=t[t[k].lc].siz)               return rank2(t[k].lc,x);
        else if(x<=t[t[k].lc].siz+t[k].rep) return t[k].val;
        else                                return rank2(t[k].rc,x-t[t[k].lc].siz-t[k].rep);
    }
    

    void Pre(const size_t &k,const value &x,size_t &ans)const{
        if(none) return ;
        if(t[k].val<x) 
        {
            ans=k;
            Pre(t[k].rc,x,ans);
        }
        else Pre(t[k].lc,x,ans);
    }
    

    void Suc(const size_t &k,const value &x,size_t &ans)const{
        if(none) return ;
        if(x<t[k].val) 
        {
            ans=k;
            Suc(t[k].lc,x,ans);
        }
        else Suc(t[k].rc,x,ans);
    }

};

//size : 64



#undef none
#undef null

}
//#endif
#endif