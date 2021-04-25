#include <Arduino.h>
#include <HardwareSerial.h>

extern HardwareSerial serial;

extern int mode;
extern int trot;

extern float yaw;   //
extern float pitch; // real level
extern float roll;  //

extern float relativ_yaw;   //
extern float relativ_pitch; // relativ level
extern float relativ_roll;  //

extern float interpolation_rate_pos; // interpolation on positions
extern float interpolation_rate_ang; // interpolation on angles

extern float x_dis, y_dis, z_dis; // how much to move

extern float relative_z; // relative height to hold 

extern bool trotting_g_f; // if end of trotting gate is necessary
extern bool trotting_w_f; // if end of trotting walk is necessary

extern bool turning_f; // if end of turning is necessary

extern bool side_trotting_f; // if end of side trotting is necessary

extern bool walking_f; // if end of walking is necessary

static char rx[73]; // recived data
static char tx[26]; // transmited data

void serial_comunication_RX(){

    for( int i = 0; i < serial.available(); i++) rx[i] = serial.read();

    // if trotting than trotting_w_f or trotting_g_f on 1
    
    sscanf( rx, "%d|%f|%f|%f|%f|%f|%f|%f|%f", 
          &mode, &interpolation_rate_pos, &interpolation_rate_ang,
          &relativ_yaw, &relativ_pitch, &relativ_roll,
          &x_dis, &y_dis, &z_dis );

    switch( mode ){

        case 2: trotting_g_f = 1; break;
        case 3: trotting_w_f = 1; break;
        case 4: turning_f = 1; break;
        case 5: side_trotting_f = 1; break;
        case 6: walking_f = 1; break;
        
    }

}

void serial_comunication_TX(){
    
    sprintf( tx, "%f|%f|%f", yaw, pitch, roll );
    serial.print( tx );

}