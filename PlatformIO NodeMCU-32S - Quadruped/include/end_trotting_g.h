#include <Arduino.h>

extern int trot; // trotting cycle
extern int etgs; // end trotting gate stage

extern bool trotting_g_f; // if end of trotting gate is necessary

extern float target_z_1, target_z_2, target_z_3, target_z_4; //  target position in z

extern float relative_z; // relative z height to hold

extern float static_stab_x; // how much moving body by trotting 

void end_trotting_g(){

    etgs++;

    target_z_1 = relative_z;
    target_z_2 = relative_z;
    target_z_3 = relative_z;
    target_z_4 = relative_z;

    if( etgs >= 2 ){

        trotting_g_f = 0;
        etgs = 0;

    }
    
    trot = 0;

    static_stab_x = 0;

}