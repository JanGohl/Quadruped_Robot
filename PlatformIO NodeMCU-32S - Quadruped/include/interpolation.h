#include <Arduino.h>
 
extern float interpolation_rate_pos; // interpolation on positions
extern float interpolation_rate_ang; // interpolation on angles

extern float set_yaw;   //
extern float set_pitch; // output level
extern float set_roll;  //
 
extern float target_yaw;   //
extern float target_pitch; // targeted level
extern float target_roll;  //

extern float set_x_1, set_x_2, set_x_3, set_x_4; // 
extern float set_y_1, set_y_2, set_y_3, set_y_4; // output position in xyz
extern float set_z_1, set_z_2, set_z_3, set_z_4; //

extern float target_x_1, target_x_2, target_x_3, target_x_4; // 
extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in xyz
extern float target_z_1, target_z_2, target_z_3, target_z_4; //

void interpolation(){

    set_yaw += ( target_yaw - set_yaw ) / interpolation_rate_ang;
    set_pitch += ( target_pitch - set_pitch ) / interpolation_rate_ang;
    set_roll += ( target_roll - set_roll ) / interpolation_rate_ang;

    set_x_1 += ( target_x_1 - set_x_1 ) / interpolation_rate_pos;
    set_y_1 += ( target_y_1 - set_y_1 ) / interpolation_rate_pos;
    set_z_1 += ( target_z_1 - set_z_1 ) / interpolation_rate_pos;

    set_x_2 += ( target_x_2 - set_x_2 ) / interpolation_rate_pos;
    set_y_2 += ( target_y_2 - set_y_2 ) / interpolation_rate_pos;
    set_z_2 += ( target_z_2 - set_z_2 ) / interpolation_rate_pos;

    set_x_3 += ( target_x_3 - set_x_3 ) / interpolation_rate_pos;
    set_y_3 += ( target_y_3 - set_y_3 ) / interpolation_rate_pos;
    set_z_3 += ( target_z_3 - set_z_3 ) / interpolation_rate_pos;

    set_x_4 += ( target_x_4 - set_x_4 ) / interpolation_rate_pos;
    set_y_4 += ( target_y_4 - set_y_4 ) / interpolation_rate_pos;
    set_z_4 += ( target_z_4 - set_z_4 ) / interpolation_rate_pos;

}