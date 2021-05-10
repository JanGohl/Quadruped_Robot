#include <Arduino.h>

extern int mode; // what to do

extern float target_z_1, target_z_2, target_z_3, target_z_4; //  target position in z

extern float relative_z; // how much to move

extern float interpolation_rate_pos; // interpolation on positions

void stand_up(){

    interpolation_rate_pos = 1;

    target_z_1++;
    target_z_2++;
    target_z_3++;
    target_z_4++;

    if( target_z_1 == relative_z && target_z_2 == relative_z && target_z_3 == relative_z && target_z_4 == relative_z ) mode = 0;
}