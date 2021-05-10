#include <Arduino.h>
#include <ESP32Servo.h> 
#include <LSM6.h>
#include <Wire.h>

extern Servo hip1;
extern Servo hip2;
extern Servo hip3;
extern Servo hip4;
extern Servo shoulder1;
extern Servo shoulder2;
extern Servo shoulder3;
extern Servo shoulder4;
extern Servo knee1;
extern Servo knee2;
extern Servo knee3;
extern Servo knee4;

extern float x_1, x_2, x_3, x_4; // 
extern float y_1, y_2, y_3, y_4; // real position in xyz
extern float z_1, z_2, z_3, z_4; //

#define pi 3.1415926535897932384626433832795
#define upper_leg_len 125
#define lower_leg_len 125
#define hip_offset 80 // hip axis to ground contact distance
#define body_wid 47.7 // middle to hip axis distance / 2
#define body_len 150 // centre to shoulder axis distance / 2

static float hip_angle; 
static float hip_angle2;
static float y_base_len; // base of hip triangle
static float shoulder_angle;
static float shoulder_angle_offset_x_move;
static float knee_angle;
static float yaw_angle_now;
static float yaw_angle_wanted;
static float radius_from_centre;
static float pitch_angle;
static float leg_angle_pitch;
static float real_foot_angle_pitch; // where is the actual contact
static float leg_len_diff_pitch; // leg len - virtual leg len
static float body_len_diff_pitch; // body len - virtual body len
static float roll_angle;
static float leg_angle_roll;
static float real_foot_angle_roll; // where is the actual contact
static float leg_len_diff_roll; // leg len - virtual leg len
static float body_len_diff_roll; // body len - virtual body len

void kinematics( int leg, float yaw, float pitch, float roll, float x, float y, float z ){
    
    // leg: 1 - front left, 2 - front right, 3 - back left, 4 - back right

    x *= -1;

    // rotation axis

    // yaw calc
    switch( leg ){
        case 1:
            x -= body_len;
            y -= ( body_wid + hip_offset );
            break;
        case 2:
            x -= body_len;
            y += ( body_wid + hip_offset );
            break;
        case 3:
            x += body_len;
            y -= ( body_wid + hip_offset );
            break;
        case 4:
            x += body_len;
            y += ( body_wid + hip_offset );
            break;
    }
    yaw_angle_now = atan( y / x );
    radius_from_centre = y / sin( yaw_angle_now );
    yaw_angle_wanted = yaw_angle_now + ( pi / 180 * yaw );
    x = radius_from_centre * cos( yaw_angle_wanted );
    y = radius_from_centre * sin( yaw_angle_wanted );
    switch( leg ){
        case 1:
            x += body_len;
            y += ( body_wid + hip_offset );
            break;
        case 2:
            x += body_len;
            y -= ( body_wid + hip_offset );
            break;
        case 3:
            x -= body_len;
            y += ( body_wid + hip_offset );
            break;
        case 4:
            x -= body_len;
            y -= ( body_wid + hip_offset );
            break;
    }

    // pitch calc
    if( leg == 1 || leg == 2 ) pitch *= -1;
    else x *= -1;
    pitch_angle = ( pi / 180 ) * pitch;
    leg_len_diff_pitch = z - sin( pitch_angle ) * body_len;
    body_len_diff_pitch = cos( pitch_angle ) * body_len;
    if( !leg_len_diff_pitch ) leg_len_diff_pitch = 1;
    real_foot_angle_pitch = atan( ( ( body_len_diff_pitch - body_len ) * -1 + x ) / leg_len_diff_pitch );
    z = leg_len_diff_pitch / cos( real_foot_angle_pitch );
    leg_angle_pitch = real_foot_angle_pitch + pitch_angle;
    x = sin( leg_angle_pitch ) * z;
    z *= cos( leg_angle_pitch ); 
    if( leg == 3 || leg == 4 ) x *= -1;

    // roll calc
    if( leg == 1 || leg == 3 ) y *= -1;
    else roll *= -1;
    roll_angle = ( pi / 180 ) * roll;
    leg_len_diff_roll = z - sin( roll_angle ) * body_wid;
    if( !leg_len_diff_roll ) leg_len_diff_roll = 1;
    body_len_diff_roll = cos( roll_angle ) * body_wid;
    real_foot_angle_roll = atan( ( ( body_len_diff_roll - body_wid ) * -1 + hip_offset - y ) / leg_len_diff_roll );
    z = leg_len_diff_roll / cos( real_foot_angle_roll );
    leg_angle_roll = real_foot_angle_roll + roll_angle;
    y = sin( leg_angle_roll ) * z - hip_offset;
    z *= cos( leg_angle_roll );

    // translation axis
    
    // hip angle calc
    y_base_len = y + hip_offset;
    hip_angle = atan( y_base_len / z );
    hip_angle2 = asin( hip_offset / ( y_base_len / sin( hip_angle ) ) );
    hip_angle += pi - pi / 2 - hip_angle2;
    hip_angle *= 180 / pi;
    z = hip_offset / tan( hip_angle2 );

    // z height for x move calc
    shoulder_angle_offset_x_move = atan( x / z); 
    z /= cos( shoulder_angle_offset_x_move ); 
    shoulder_angle_offset_x_move *= 180 / pi;

    // shoulder angle calc
    shoulder_angle = z * z + upper_leg_len * upper_leg_len - lower_leg_len * lower_leg_len;
    shoulder_angle /= ( 2 * z * upper_leg_len ); 
    shoulder_angle = acos( shoulder_angle );
    shoulder_angle *= 180 / pi; // total angle in degrees
    
    // knee angle calc
    knee_angle = 180 - shoulder_angle * 2;
 
    // writing to servos 
    switch( leg ){

        case 1:
            hip1.write( hip_angle );
            shoulder1.write( shoulder_angle - shoulder_angle_offset_x_move ); // - shoulder_angle_offset_x_move
            knee1.write( knee_angle );
            x_1 = x;
            y_1 = y;
            z_1 = z;
            break;

        case 2:
            hip2.write( 180 - hip_angle );
            shoulder2.write( 180 - shoulder_angle + shoulder_angle_offset_x_move ); // + shoulder_angle_offset_x_move
            knee2.write( 180 - knee_angle ); 
            x_2 = x;
            y_2 = y;
            z_2 = z; 
            break;

        case 3:
            hip3.write( 180 - hip_angle );
            shoulder3.write( shoulder_angle - shoulder_angle_offset_x_move ); // - shoulder_angle_offset_x_move
            knee3.write( knee_angle );
            x_3 = x;
            y_3 = y;
            z_3 = z;
            break;

        case 4:
            hip4.write( hip_angle );
            shoulder4.write( 180 - shoulder_angle + shoulder_angle_offset_x_move ); // + shoulder_angle_offset_x_move
            knee4.write( 180 - knee_angle );
            x_4 = x;
            y_4 = y;
            z_4 = z;
            break;
            
    }
    
}