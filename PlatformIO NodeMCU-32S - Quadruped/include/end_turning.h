#include <Arduino.h>

extern int tur; // turning cycle
extern int ets; // end turning stage

extern bool turning_f; // if end of truning is  necessary

extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in y
extern float target_z_1, target_z_2, target_z_3, target_z_4; // target position in z

extern float y_dis, z_dis; // how much to move

extern float relative_z; // relative height to hold

void end_turning(){


    
}