//������FG ûʲô�ӿ�
#include <bitset>
namespace std
{
    #define ul unsigned long long

    /**
     * @brief ״̬������ �������Ǹ�bitset
     * @tparam siz ����Ҫ����Ķ�����״̬��
     */
    template <size_t siz>
    class statue
    {
    private:
        bitset<siz> b;

    public:
        //��һλ�Ƿ����
        inline bool test(const ul &x) const{
            return b.test(x);
        }
        //�ҵ����λ 
        inline ul lowbit() const{
            for (ul i = 0; i < siz; ++i)
                if (b.test(i)) return i;
            return -1ull;
        }
        //�ҵ���xλ1
        inline ul lowbit(ul x) const{
            for(ul i=0 ; i<siz ;++i)
            {
                if(b.test(i)) --x;
                if(!x) return i;
            }
            return -1ull;
        }
        //�ҵ���xλ����һ��1��λ��
        inline ul nxt(const ul &x) const{
            for (ul i =x+1 ;i<siz; ++i)
                if (b.test(i))
                    return i;
            return -1ull;
        }
        //��xλ ��������0
        inline const bool operator[](const ul &x) const{
            return x>=siz?0:b[x];
        }      
        //��xλ
        inline void on(const ul &x){
            b.set(x);
        }
        //�ر�xλ
        inline void off(const ul &x){
            b.reset(x);
        }
        //ȫ��
        inline void on(){
            b.set();
        }
        //ȫ��
        inline void off(){
            b.reset();
        }
        //����01�� string �ǵù����ڴ�
        inline string bit_str()const{
            string str;
            str.reserve(siz);
            for(ul i=0 ; i<siz ;++i)
                b[i] ? str.append("1") : str.append("0");
            return str;
        }
        //����01�� char * �ǵù����ڴ�����free
        inline char *bit_cstr()const{
            char *c=(char *)malloc(siz+1);
            for(ul i=0 ; i<siz ; ++i)
                c[i]=b[i]? '1' :'0';
            c[siz]=0;
            return c;
        }
        //1�ĸ���
        inline ul count()const{
            return b.count();
        }
        //ȡ��
        inline ul c()const{
            b.all()
        }
        statue <siz>()
        {

        }
    };
    #undef ul
}
