#ifndef _HEADER_DARK_H_
#define _HEADER_DARK_H_


//Repeat N times. _cnt as the counter.
#define repcnt(__N__) for(auto _cnt=__N__; _cnt ; --_cnt)

//Repeat N times. _cnt as the counter.Minus S each time.
#define repcntby(__N__,__S__) for(auto _cnt=__N__; _cnt ; --_cnt)

//Repeat from A till B._iter as the counter.
#define repin(__A,__B) for(auto _iter=__A; _iter!=__B ; ++_iter )

//Repeat from A till B by C._iter as the counter.
#define repinby(__A,__B,__C) for(auto _iter=__A; _iter!=__B ; _iter+=__C)

//Repeat from A to B. _iter as the counter.
#define rep(__A,__B) for(auto _iter=__A; _iter<=__B ; ++_iter )

//Repeat from A to B by C._iter as the counter.
#define repby(__A,__B,__C) for(auto _iter=__A; _iter<=__B ; _iter+=__C)

//As it means.Equals to if not.
#define unless(__CONDITION__) if(!(__CONDITION__))

//As it means.Equals to while not.
#define until(__CONDITION__) while(!(__CONDITION__))







#endif