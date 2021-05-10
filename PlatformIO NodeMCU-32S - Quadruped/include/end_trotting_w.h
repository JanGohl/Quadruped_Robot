#include <Arduino.h>

extern int trot; // current pair of legs in trotting
extern int etws; // end trotting walk stage

extern bool trotting_w_f; // if end of trotting walk is necessary

extern float target_x_1, target_x_2, target_x_3, target_x_4; //  target position in x
extern float target_z_1, target_z_2, target_z_3, target_z_4; //  target position in z

extern float relative_z; // relative height to hold

extern float x_dis, z_dis; // how much to move

extern float static_stab_x; // how much moving body by trotting 

void end_trotting_w(){ 

    etws++;

    switch( etws ){

        case 1:
            switch( trot ){

                case 1:
                    target_x_2 -= x_dis;
                    target_x_3 -= x_dis;

                    target_z_2 -= z_dis;
                    target_z_3 -= z_dis;
                    break;

                case 2:                
                    target_x_1 -= x_dis;
                    target_x_4 -= x_dis;

                    target_z_1 = relative_z;
                    target_z_4 = relative_z;
                    break;

                case 3:
                    target_x_1 -= x_dis;
                    target_x_4 -= x_dis;

                    target_z_1 -= z_dis;
                    target_z_4 -= z_dis;
                    break;

                case 4:
                    target_x_2 -= x_dis;
                    target_x_3 -= x_dis;

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
            static_stab_x = 0;
            trotting_w_f = 0;
            etws = 0; 
            break;

    }

    trot = 0;

}