#include <Arduino.h>

extern int wal; // turning cycle
extern int ews; // end turning stage

extern bool walking_f; // if end of truning is  necessary

extern float target_x_1, target_x_2, target_x_3, target_x_4; // target position in x
extern float target_z_1, target_z_2, target_z_3, target_z_4; // target position in z

extern float x_dis, z_dis; // how much to move

extern float relative_z; // relative height to hold

void end_walk(){


    
}