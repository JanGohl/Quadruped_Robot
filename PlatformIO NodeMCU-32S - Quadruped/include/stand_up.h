#include <Arduino.h>

extern int mode; // what to do

extern float target_z_1, target_z_2, target_z_3, target_z_4; //  target position in z

extern float relative_z; // how much to move

void stand_up(){

    target_z_1 = relative_z;
    target_z_2 = relative_z;
    target_z_3 = relative_z;
    target_z_4 = relative_z;

    mode = 0;
    
    //
        mode = 3;
    //
}