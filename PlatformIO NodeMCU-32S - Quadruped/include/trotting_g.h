#include <Arduino.h>

extern int trot; // current pair of legs in trotting

extern float target_z_1, target_z_2, target_z_3, target_z_4; //  target position in z

extern float relative_z;

extern float z_dis;

extern float static_stab_x; // how much moving body by trotting 

void trotting_g(){

    switch( trot ){

        case 0:
            target_z_1 -= z_dis;
            target_z_4 -= z_dis;
            break;

        case 1:
            target_z_1 = relative_z;
            target_z_4 = relative_z;
            break;

        case 2:
            target_z_2 -= z_dis;
            target_z_3 -= z_dis;
            break;

        case 4:
            target_z_2 = relative_z;
            target_z_3 = relative_z;
            break;

    }

    trot++;
    trot %= 5;

    //static_stab_x = 5;
    
}