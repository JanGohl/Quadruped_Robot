#include <Arduino.h>

extern int sitr; // side trotting
extern int ests; // end side trotting stage

extern bool side_trotting_f; // if end of side trotting is  necessary

extern float target_y_1, target_y_2, target_y_3, target_y_4; // target position in y
extern float target_z_1, target_z_2, target_z_3, target_z_4; // target position in z

extern float y_dis, z_dis; // how much to move

extern float relative_z; // relative height to hold

void end_side_trotting(){

    ests++;

    switch( ests ){

    case 1:
        switch( sitr ){

            case 1:
                target_y_2 -= y_dis;
                target_y_3 -= y_dis;

                target_z_2 -= z_dis;
                target_z_3 -= z_dis;
                break;

            case 2:
                target_y_1 -= y_dis;
                target_y_4 -= y_dis;

                target_z_1 = relative_z;
                target_z_4 = relative_z;
                break;

            case 3:
                target_y_1 -= y_dis;
                target_y_4 -= y_dis;

                target_z_2 -= z_dis;
                target_z_3 -= z_dis;
                break;

            case 4:
                target_y_2 -= y_dis;
                target_y_3 -= y_dis;

                target_z_2 = relative_z;
                target_z_3 = relative_z;
                break;

        }
        break;

    case 2:
        target_z_1 = relative_z;
        target_z_2 = relative_z;
        target_z_3 = relative_z;
        target_z_4 = relative_z;
        break;

    case 3:
        side_trotting_f = 0;
        ests = 0;
        break;

    }

    sitr = 0;
}