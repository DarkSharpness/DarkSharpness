#include <string>
#include <vector>

#ifndef _FG_BASIC_H_
#define _FG_BASIC_H_
namespace FG { // Finger glory namespace


struct weapon {
    std::string name; // Name of the weapon
    uint16_t FGid;    // The unique id of the weapon.1-base.
    /**
        The type of a FG weapon.
        type = 1 offensive-singular
        type = 2 offensive-group
        type = 3 defensive
        type = 4 bouncing
        type = 5 evasive
        type = 6 special_function
                //for example judging...

    */
    uint8_t  Ftype;   
    /*
        Define damage type:
            0. shoot   damage
            1. real shoot damage
            2. 
        For 


    */
    std::vector <double> data;
    
    



};






}

#endif