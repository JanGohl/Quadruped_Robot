#include <Arduino.h>

extern int sitr; // side trotting

extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in y
extern float target_z_1, target_z_2, target_z_3, target_z_4; // target position in z

extern float y_dis, z_dis; // how much to move

extern float relative_z;

void side_trotting(){

    if( !sitr ){

        target_y_1 += y_dis;
        target_y_4 += y_dis;

        target_z_1 -= z_dis;
        target_z_4 -= z_dis;

    } 
    switch( sitr ){

        case 1:
            target_z_1 = relative_z;
            target_z_2 = relative_z;
            target_z_3 = relative_z;
            target_z_4 = relative_z;
            break;

        case 2:
            target_y_1 -= y_dis;
            target_y_2 += y_dis;
            target_y_3 += y_dis;
            target_y_4 -= y_dis;

            target_z_2 -= z_dis;
            target_z_3 -= z_dis;
            break;

        case 3:
            target_z_1 = relative_z;
            target_z_2 = relative_z;
            target_z_3 = relative_z;
            target_z_4 = relative_z;
            break;

        case 4:
            target_y_1 += y_dis;
            target_y_2 -= y_dis;
            target_y_3 -= y_dis;
            target_y_4 += y_dis;
            
            target_z_1 -= z_dis;
            target_z_4 -= z_dis;
            break;

    }

    sitr++;
    sitr %=5;

    if( !sitr ) sitr++;
    
}