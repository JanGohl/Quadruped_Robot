#include <Arduino.h>
#include <ESP32Servo.h> 
#include <LSM6.h>
#include <Wire.h>
#include <Kalman.h>
#include <PID_v1.h>
#include <HardwareSerial.h>
#include "kinematics.h"
#include "interpolation.h"
#include "angles.h"
#include "serial_comunication.h"
#include "PID_controll.h"
#include "position_check.h"

#include "stand_up.h"
#include "trotting_g.h"
#include "trotting_w.h"
#include "end_trotting_g.h" 
#include "end_trotting_w.h"
#include "turn.h"
#include "end_turning.h"
#include "side_trotting.h"
#include "end_side_trotting.h"
#include "recover.h"
#include "walk.h"
#include "end_walk.h"
#include "kinematics_demo.h"

// for necessary stuff

Servo hip1;
Servo hip2;
Servo hip3;
Servo hip4;
Servo shoulder1;
Servo shoulder2;
Servo shoulder3;
Servo shoulder4;
Servo knee1;
Servo knee2;
Servo knee3;
Servo knee4;

LSM6 imu;

Kalman kalmanX;
Kalman kalmanY;

float timer; // timer
float dtimer; // delta timer

float timer_k; // timer kinematics demo
float dtimer_k; // delta timer kinematics demo

HardwareSerial serial(2);

// PID controller 1 - roll

    float Pk1 = 2; //
    float Ik1 = 5; // 
    float Dk1 = 1; //

    double Setpoint1; // target for PID controller
    double Input1;    // input for PID controller 
    double Output1;   // output of PID controller 

    PID pid_roll( &Input1, &Output1, &Setpoint1, Pk1, Ik1, Dk1, DIRECT );

// PID contorller 2 - pitch

    float Pk2 = 2; // 
    float Ik2 = 5; //
    float Dk2 = 1; //

    double Setpoint2; // target for PID controller
    double Input2;    // input for PID controller 
    double Output2;   // output of PID controller 

    PID pid_pitch( &Input2, &Output2, &Setpoint2, Pk2, Ik2, Dk2, DIRECT ); 

float relativ_yaw;   //
float relativ_pitch; // relativ level 
float relativ_roll;  // 

float yaw;   //
float pitch; // real level
float roll;  //

float set_yaw;   //
float set_pitch; // output level
float set_roll;  //

float target_yaw;   //
float target_pitch; // targeted level
float target_roll;  //

float x_1, x_2, x_3, x_4; // 
float y_1, y_2, y_3, y_4; // real position in xyz
float z_1, z_2, z_3, z_4; //

float set_x_1, set_x_2, set_x_3, set_x_4; // 
float set_y_1, set_y_2, set_y_3, set_y_4; // output position in xyz
float set_z_1, set_z_2, set_z_3, set_z_4; //

float target_x_1, target_x_2, target_x_3, target_x_4; // 
float target_y_1, target_y_2, target_y_3, target_y_4; // target position in xyz
float target_z_1, target_z_2, target_z_3, target_z_4; //

float interpolation_rate_pos; // interpolation on positions
float interpolation_rate_ang; // interpolation on angles

float error_val_x = 2.5; // how much error for leg position in x axis is allowd
float error_val_y = 2.5; // how much error for leg position in y axis is allowd
float error_val_z = 2.5; // how much error for leg position in z axis is allowd

float error_val_Y = 2.5; // how much error for leg angle in yaw is allowd
float error_val_P = 2.5; // how much error for leg angle in pitch is allowd
float error_val_R = 2.5; // how much error for leg angle in roll is allowd

float static_stab_x; // how much moving body by trotting 


// for bug... features

int mode; // what to do
/*
    0 - stand by, hold pos
    1 - stand up
    2 - trotting gate 
    3 - trotting gate with x move
    4 - turn
    5 - side trotting
    6 - walking
    7 - kinematics demo
*/

float relative_z; // relative height to hold 

float x_dis, y_dis, z_dis; // how much to move

int trot; // trotting cycle
int etgs; // end trotting gate stage
int etws; // end trotting walk stage

int tur; // turning cycle
int ets; // end turning stage

int sitr; // side trotting
int ests; // end side trotting stage

int wal; // walking stage
int ews; // end walking stage

bool trotting_g_f; // if end of trotting gate is necessary
bool trotting_w_f; // if end of trotting walk is necessary

bool turning_f; // if end of turning is necessary

bool side_trotting_f; // if end of side trotting is  necessary

bool walking_f; // if end of walking is necessary

int recs; // recover stage
bool recn; // if recovery is needed

int kins; // kinematic demo stage

void setup() {

    Serial.begin(115200);

    //
        mode = 1;
        interpolation_rate_pos = 5;
        interpolation_rate_ang = 5;
        x_dis = 50;
        z_dis = 50;
        relative_z = 177;
        //target_pitch = 20;
        //target_roll = -20;
        //set_ = 20;
        //target_y_1 = 50;
        //target_y_2 = 50;
        //target_y_3 = 50;
        //target_y_4 = 50;
        //target_yaw = 20;
    
    //

    serial.begin( 115200 );

    // Servos setup
    hip1.attach(15);
    hip2.attach(13);
    hip3.attach(18);
    hip4.attach(33);
    shoulder1.attach(2);
    shoulder2.attach(12);
    shoulder3.attach(5);
    shoulder4.attach(32);
    knee1.attach(4);
    knee2.attach(14);
    knee3.attach(23);
    knee4.attach(25);
    
    // I2C imu setup
    Wire.begin();
    while( !imu.init() ){}  
    imu.enableDefault();

    x_acc = imu.a.x * 0.061 / 1000; //
    y_acc = imu.a.y * 0.061 / 1000; // Accelerometer values
    z_acc = imu.a.z * 0.061 / 1000; // 
    
    pitch_acc = atan2( x_acc, z_acc ) * 180 / pi;
    roll_acc = atan2( y_acc, z_acc ) * 180 / pi;

    kalmanX.setAngle( roll_acc );
    kalmanY.setAngle( pitch_acc );

    pid_roll.SetMode(AUTOMATIC);
    pid_roll.SetOutputLimits( -20, 20 );
    pid_roll.SetSampleTime(10);

    pid_pitch.SetMode(AUTOMATIC);
    pid_pitch.SetOutputLimits( -20, 20 );
    pid_pitch.SetSampleTime(10);

    delay(30000);

}

void loop() {
    
    delay(10);

    Serial.print(target_z_1);
    Serial.print(" ");
    Serial.print(target_z_2);
    Serial.print(" ");
    Serial.print(target_z_3);
    Serial.print(" ");
    Serial.print(target_z_4);
    Serial.print(" ");
    Serial.print(target_pitch);
    Serial.print("\n");

    //if( serial.available() && !recn && !kins ){
    //
    //    if( trotting_g_f && position_check() ) end_trotting_g();
    //    if( trotting_w_f && position_check() ) end_trotting_w();
    //    
    //    if( turning_f && position_check() ) end_turning();
    //
    //    if( side_trotting_f && position_check() ) end_side_trotting();    
    //
    //    if( walking_f && position_check() ) end_walk();
    //
    //    if( !trotting_g_f && !trotting_w_f && !turning_f && !side_trotting_f && !walking_f ) serial_comunication_RX();
    //
    //}

    if( position_check() && !etgs && !etws && !ets && !ests && !ews && !recn){
        
        switch( mode ){
        
            case 1: stand_up(); break;
            case 2: trotting_g(); break;
            case 3: trotting_w(); break;
            case 4: turn(); break;
            case 5: side_trotting(); break;
            case 6: walk(); break;
            case 7: kinematics_demo(); break;
            //
                case 8:
                target_z_1--;
                target_z_2--;
                target_z_3--;
                target_z_4--;
                interpolation_rate_pos = 1;
                if( target_z_1 == 0 && target_z_2 == 0 && target_z_3 == 0 && target_z_4 == 0 ) mode = 0;
            //
        }
    
    }

    //angles();
    //if( !recn ) PID_controll();
    interpolation();


    //if( pitch > 99 or pitch < -99 or roll > 99 or roll < -99 ) recn = 1;
    //if( recn && ( position_check() or !recs ) ) recover(); 

    kinematics(1, set_yaw, set_pitch, set_roll, set_x_1 + Output2 + static_stab_x, set_y_1 + Output1, set_z_1);
    kinematics(2, set_yaw, set_pitch, set_roll, set_x_2 + Output2 + static_stab_x, set_y_2 + Output1, set_z_2);
    kinematics(3, set_yaw, set_pitch, set_roll, set_x_3 + Output2 + static_stab_x, set_y_3 + Output1, set_z_3);
    kinematics(4, set_yaw, set_pitch, set_roll, set_x_4 + Output2 + static_stab_x, set_y_4 + Output1, set_z_4);


}

// change values = in main and in standup
// change in position check 
// change body len in kinematics.h 
