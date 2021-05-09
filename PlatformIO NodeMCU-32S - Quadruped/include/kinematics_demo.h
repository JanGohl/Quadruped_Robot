#include <Arduino.h>

extern float interpolation_rate_pos; // interpolation on positions
extern float interpolation_rate_ang; // interpolation on angles

extern float target_yaw;   //
extern float target_pitch; // targeted level
extern float target_roll;  //

extern float target_x_1, target_x_2, target_x_3, target_x_4; // 
extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in xyz
extern float target_z_1, target_z_2, target_z_3, target_z_4; //

extern int kins; // kinematic demo stage

extern float timer_k; // timer kinematics demo
extern float dtimer_k; // delta timer kinematics demo

extern int mode; // what to do

void kinematics_demo(){

    interpolation_rate_pos = 35;
    interpolation_rate_ang = 35;

    dtimer_k = ( micros() - timer_k );
    timer_k = micros(); 

    //if( !kins or dtimer_k > 1000000 ) kins++;
    
    //
        kins++;
    //

    switch( kins ){

        case 1:
            delay(500);
            target_pitch = 20;
            break;

        case 2:
            delay(500);
            target_pitch = 0;
            break;

        case 3:
            delay(500);
            target_pitch = -20;
            break;

        case 4:
            delay(500);
            target_pitch = 0;
            break;
        
        case 5:
            delay(500);
            target_yaw = 30;
            break;

        case 6:
            delay(500);
            target_yaw = 0;
            break;

        case 7:
            delay(500);
            target_yaw = -30;
            break;

        case 8:
            delay(500);
            target_yaw = 0;
            break;

        case 9:
            delay(500);
            target_roll = 30;
            break;

        case 10:
            delay(500);
            target_roll = 0;
            break;

        case 11:
            delay(500);
            target_roll = -30;
            break;

        case 12:
            delay(500);
            target_roll = 0;
            break;

        case 13:
            delay(500);
            target_z_1 += 50;
            target_z_2 += 50;
            target_z_3 += 50;
            target_z_4 += 50;
            break;

        case 14:
            delay(500);
            target_z_1 -= 50;
            target_z_2 -= 50;
            target_z_3 -= 50;
            target_z_4 -= 50;
            break;

        case 15:
            delay(500);
            target_z_1 -= 50;
            target_z_2 -= 50;
            target_z_3 -= 50;
            target_z_4 -= 50;
            break;

        case 16:
            delay(500);
            target_z_1 += 50;
            target_z_2 += 50;
            target_z_3 += 50;
            target_z_4 += 50;
            break;
        
        case 17:
            delay(500);
            target_x_1 += 65;
            target_x_2 += 65;
            target_x_3 += 65;
            target_x_4 += 65;
            break;

        case 18:
            delay(500);
            target_x_1 -= 65;
            target_x_2 -= 65;
            target_x_3 -= 65;
            target_x_4 -= 65;
            break;

        case 19:
            delay(500);
            target_x_1 -= 65;
            target_x_2 -= 65;
            target_x_3 -= 65;
            target_x_4 -= 65;
            break;

        case 20:
            delay(500);
            target_x_1 += 65;
            target_x_2 += 65;
            target_x_3 += 65;
            target_x_4 += 65;
            break;

        case 21:
            delay(500);
            target_y_1 += 50;
            target_y_2 += 50;
            target_y_3 += 50;
            target_y_4 += 50;
            break;

        case 22:
            delay(500);
            target_y_1 -= 50;
            target_y_2 -= 50;
            target_y_3 -= 50;
            target_y_4 -= 50;
            break;

        case 23:
            delay(500);
            target_y_1 -= 50;
            target_y_2 -= 50;
            target_y_3 -= 50;
            target_y_4 -= 50;
            break;

        case 24:
            delay(500);
            target_y_1 += 50;
            target_y_2 += 50;
            target_y_3 += 50;
            target_y_4 += 50;
            break;

        case 25:
            kins = 0;
            mode = 0;
            //
                mode = 8;
            //
            break;
        
    }

}