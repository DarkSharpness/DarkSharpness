#include <General/basic.h> 

namespace dark {

/**
 * @brief Maintain a set of vertices.
 * by union_set 
 * in approximately O(1) time.
 * 
 * @tparam SIZE The maximum number of vertices.
 */
template <size_type SIZE>
class Union_Set {
    private:
    size_type anc[SIZE];
    size_type siz[SIZE];

    public:
    /**
     * @brief Find the ancestor of a vertex.
     * in approximately O(1) time.
     * Note that the ancestor may be any one of
     * the verticle in the set. 
     * 
     * @param X The verticle to find ancestor of.
     */
    size_type find(size_type X) {
        if(anc[X] == X) return X;
        else return anc[X] = find(anc[X]);
    }

    /**
     * @brief Link 2 vertices.
     * in approximately O(1) time.
     * Note that it's ok if X and Y have 
     * been in the same set. 
     * 
     * @param X Vertex 1
     * @param Y Vertex 2
     */
    inline void merge(size_type X,size_type Y) {
        size_type ancx = find(X);
        size_type ancy = find(Y);
        if(ancx == ancy) return;
        if(siz[ancx] > siz[ancy]) {
            anc[ancy] = ancx;
            siz[ancx] += siz[ancy];
        } else {
            anc[ancx] = ancy;
            siz[ancy] += siz[ancx];
        }
    }
    

    inline bool judge(size_type X,size_type Y) {
        return find(X) == find(Y);
    }


    Union_Set() {
        Iter(i,(size_type)(0),SIZE) anc[i] = i;
        memset(siz,0,sizeof(siz));
    }

};



}

