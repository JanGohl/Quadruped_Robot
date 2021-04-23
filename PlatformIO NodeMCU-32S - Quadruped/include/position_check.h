#include <Arduino.h>

extern float yaw;   //
extern float pitch; // real level
extern float roll;  //

extern float relativ_yaw;   //
extern float relativ_pitch; // relativ level
extern float relativ_roll;  //

extern float set_x_1, set_x_2, set_x_3, set_x_4; // 
extern float set_y_1, set_y_2, set_y_3, set_y_4; // real position in xyz
extern float set_z_1, set_z_2, set_z_3, set_z_4; //

extern float target_x_1, target_x_2, target_x_3, target_x_4; // 
extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in xyz
extern float target_z_1, target_z_2, target_z_3, target_z_4; //

extern float interpolation_rate_pos; // interpolation on positions
extern float interpolation_rate_ang; // interpolation on angles

extern float error_val_x; // how much error for leg position in x axis is allowd
extern float error_val_y; // how much error for leg position in y axis is allowd
extern float error_val_z; // how much error for leg position in z axis is allowd

extern float error_val_Y; // how much error for leg angle in yaw is allowd
extern float error_val_P; // how much error for leg angle in pitch is allowd
extern float error_val_R; // how much error for leg anglen roll is allowd

bool position_check(){

    // leg
    if( set_x_1 < target_x_1 - error_val_x or set_x_1 > target_x_1 + error_val_x 
     or set_x_2 < target_x_2 - error_val_x or set_x_2 > target_x_2 + error_val_x 
     or set_x_3 < target_x_3 - error_val_x or set_x_3 > target_x_3 + error_val_x 
     or set_x_4 < target_x_4 - error_val_x or set_x_4 > target_x_4 + error_val_x 
    ) return 0;

    // leg
    if( set_y_1 < target_y_1 - error_val_y or set_y_1 > target_y_1 + error_val_y 
     or set_y_2 < target_y_2 - error_val_y or set_y_2 > target_y_2 + error_val_y 
     or set_y_3 < target_y_3 - error_val_y or set_y_3 > target_y_3 + error_val_y 
     or set_y_4 < target_y_4 - error_val_y or set_y_4 > target_y_4 + error_val_y 
    ) return 0;

    // leg
    if( set_z_1 < target_z_1 - error_val_z or set_z_1 > target_z_1 + error_val_z 
     or set_z_2 < target_z_2 - error_val_z or set_z_2 > target_z_2 + error_val_z 
     or set_z_3 < target_z_3 - error_val_z or set_z_3 > target_z_3 + error_val_z 
     or set_z_4 < target_z_4 - error_val_z or set_z_4 > target_z_4 + error_val_z 
    ) return 0;

    // leg 4
    //if( yaw < relativ_yaw - error_val_Y or yaw > relativ_yaw + error_val_Y
    // or pitch < relativ_pitch - error_val_P or pitch > relativ_pitch + error_val_P
    // or roll < relativ_roll - error_val_R or roll > relativ_roll + error_val_R
    //) return 0;
    
    return 1;

}