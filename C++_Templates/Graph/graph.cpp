#include <bits/stdc++.h>

namespace std{
class graph{
    struct edge{
        size_t to;//指向的节点
        edge* nxt;//下一条边
        inline edge(const size_t &_to,edge &_nxt)
        {
            to=_to;
            nxt=&_nxt;
        }
    };
    struct dot{

        inline auto begin(){
            ;
        }
        inline edge end(){
            return (edge*)NULL;
        }
    };
    vector <edge> e;
    vector <size_t> head;
    public:
    /**
     * @brief Add a edge to the graph.
     * 
     * @param _from Where the edge begins from.
     * @param _to   Where the edge points to.
     */
    inline void addedge(const size_t &_from,const size_t &_to)
    {
        e.emplace_back(_to,e[head[_from]]);
        head[_from]=e.size()-1;
    }
    /**
     * @brief Initializ dots with a certain size.
     * The previous memory will be cleared.
     * 
     * @param _size The target size of dots.
     */
    inline void setdots(const size_t &_size)
    {
        head.clear();
        head.resize(_size,size_t(-1));
    }
    //Clear the memory and initialize for second use
    inline void recycle()
    {
        head.clear();
        head.shrink_to_fit();
        e.clear();
        e.shrink_to_fit();
    }
    inline graph()
    {
        e.resize(1);
    }

};

}