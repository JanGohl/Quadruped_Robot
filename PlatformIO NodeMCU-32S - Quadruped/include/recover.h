#include <Arduino.h>

extern int recs; // recover stage

extern bool recn; // if recovery is needed

extern float target_x_1, target_x_2, target_x_3, target_x_4; // 
extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in xyz
extern float target_z_1, target_z_2, target_z_3, target_z_4; //

extern float set_yaw;   //
extern float set_pitch; // output level
extern float set_roll;  //
 
extern float target_yaw;   //
extern float target_pitch; // targeted level
extern float target_roll;  //

extern int trot; // trotting cycle
extern int etgs; // end trotting gate stage
extern int etws; // end trotting walk stage
 
extern int tur; // turning cycle
extern int ets; // end turning stage
 
extern int sitr; // side trotting
extern int ests; // end side trotting stage

extern int wal; // walking stage
extern int ews; // end walking stage

extern float relative_z;

void recover(){

    recs++;

    target_yaw = 0;
    target_pitch = 0;
    target_roll = 0;

    set_yaw = 0; 
    set_pitch = 0;
    set_roll = 0;

    switch( recs ){

        case 1:
            target_x_1 = 0;
            target_x_2 = 0;
            target_x_3 = 0;
            target_x_4 = 0;

            target_y_1 = 0;
            target_y_2 = 0;
            target_y_3 = 0;
            target_y_4 = 0;

            target_z_1 = 0;
            target_z_2 = 0;
            target_z_3 = 0;
            target_z_4 = 0;
            break;

        case 2:
            target_z_2 = -250;
            target_z_4 = -250;
            break;

        case 3:
            target_z_1 = -250;
            target_z_3 = -250;
            break;

        case 4:
            target_z_1 = relative_z;
            target_z_2 = relative_z;
            target_z_3 = relative_z;
            target_z_4 = relative_z;
            break;

        case 5:
            recs = 0;
            recn = 0;

            trot = 0;
            etgs = 10;
            etws = 10;

            tur = 0;
            ets = 10;

            sitr = 0;
            ests = 10;

            wal = 0;
            ews = 10;
            break;

    }
    
}