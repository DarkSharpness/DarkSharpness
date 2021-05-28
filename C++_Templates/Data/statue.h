//服务于FG 没什么接口
#include <bitset>
namespace std
{
    #define ul unsigned long long

    /**
     * @brief 状态管理器 本质上是个bitset
     * @tparam siz 你需要管理的二进制状态数
     */
    template <size_t siz>
    class statue
    {
    private:
        bitset<siz> b;

    public:
        //这一位是否存在
        inline bool test(const ul &x) const{
            return b.test(x);
        }
        //找到最低位 
        inline ul lowbit() const{
            for (ul i = 0; i < siz; ++i)
                if (b.test(i)) return i;
            return -1ull;
        }
        //找到第x位1
        inline ul lowbit(ul x) const{
            for(ul i=0 ; i<siz ;++i)
            {
                if(b.test(i)) --x;
                if(!x) return i;
            }
            return -1ull;
        }
        //找到第x位后下一个1的位置
        inline ul nxt(const ul &x) const{
            for (ul i =x+1 ;i<siz; ++i)
                if (b.test(i))
                    return i;
            return -1ull;
        }
        //第x位 超出返回0
        inline const bool operator[](const ul &x) const{
            return x>=siz?0:b[x];
        }      
        //打开x位
        inline void on(const ul &x){
            b.set(x);
        }
        //关闭x位
        inline void off(const ul &x){
            b.reset(x);
        }
        //全开
        inline void on(){
            b.set();
        }
        //全关
        inline void off(){
            b.reset();
        }
        //返回01串 string 记得管理内存
        inline string bit_str()const{
            string str;
            str.reserve(siz);
            for(ul i=0 ; i<siz ;++i)
                b[i] ? str.append("1") : str.append("0");
            return str;
        }
        //返回01串 char * 记得管理内存随手free
        inline char *bit_cstr()const{
            char *c=(char *)malloc(siz+1);
            for(ul i=0 ; i<siz ; ++i)
                c[i]=b[i]? '1' :'0';
            c[siz]=0;
            return c;
        }
        //1的个数
        inline ul count()const{
            return b.count();
        }
        //取反
        inline ul c()const{
            b.all()
        }
        statue <siz>()
        {

        }
    };
    #undef ul
}
