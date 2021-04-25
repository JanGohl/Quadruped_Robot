#include <Arduino.h>
#include <LSM6.h>
#include <Wire.h>
#include <Kalman.h>

extern LSM6 imu;

extern Kalman kalmanX;
extern Kalman kalmanY;

extern float timer; // timer
extern float dtimer; // delta timer

extern float yaw;   //
extern float pitch; // real level
extern float roll;  //

extern float target_yaw;   //
extern float target_pitch; // targeted level
extern float target_roll;  //

#define pi 3.1415926535897932384626433832795

static float x_acc; // 
static float y_acc; // Accelerometer data
static float z_acc; //  

static float pitch_acc; // pitch derived from acc
static float roll_acc;  // roll derived from acc

static float x_gyr; //
static float y_gyr; // Gyroscope data
static float z_gyr; //

void angles(){

    imu.read();
    
    x_acc = imu.a.x * 0.061 / 1000; //
    y_acc = imu.a.y * 0.061 / 1000; // Accelerometer values
    z_acc = imu.a.z * 0.061 / 1000; // 

    x_gyr = imu.g.x * 8.750 / 1000; // 
    y_gyr = imu.g.y * 8.750 / 1000; // Gyroscope values
    z_gyr = imu.g.z * 8.750 / 1000; // 

    pitch_acc = atan2( x_acc, z_acc ) * 180 / pi;
    roll_acc = atan2( y_acc, z_acc ) * 180 / pi;

    dtimer = ( micros() - timer ) / 1000000;
    timer = micros(); 

    yaw = z_gyr;                                          //
    pitch = kalmanX.getAngle( pitch_acc, y_gyr, dtimer ); // Calculating filterd angles
    roll = kalmanY.getAngle( roll_acc, y_gyr, dtimer );   //

    //target_yaw = yaw;
    //target_pitch = pitch;
    //target_roll = roll;

}