#include <Arduino.h>
#include <PID_v1.h>

extern float relativ_yaw;   //
extern float relativ_pitch; // relativ level 
extern float relativ_roll;  // 

extern float yaw;   //
extern float pitch; // real level
extern float roll;  //

// PID controller 1 - roll

    extern float Pk1; //
    extern float Ik1; // 
    extern float Dk1; //

    extern double Setpoint1; // target for PID controller
    extern double Input1;    // input for PID controller 
    extern double Output1;   // output of PID controller 

    extern PID pid_roll;

// PID contorller 2 - pitch

    extern float Pk2; // 
    extern float Ik2; //
    extern float Dk2; //
 
    extern double Setpoint2; // target for PID controller
    extern double Input2;    // input for PID controller 
    extern double Output2;   // output of PID controller 
 
    extern PID pid_pitch; 

void PID_controll(){

    Setpoint1 = relativ_roll;
    Input1 = roll;
    pid_roll.Compute();

    Setpoint2 = relativ_pitch;
    Input2 = pitch;
    pid_pitch.Compute();

}