/*******************************************DRONE BASIC MOVEMENTS**********************************************/
/* 
 * File:   DRONE_Movements
 * Author: SoftwareTeam@BreakingPoint
 *
 */

//Assmue drone is quadCopter -> has 4 engines {M1,M2,M3,M4}   

                                         M2       M1
                                            DRONE
                                         M4       M3 

 /****************************************************************************************************************/  
void Drone_Move_Forward() {
    // Increase speed of motors on the back side
    increase_motor_speed(M3);
    increase_motor_speed(M4);
    
    // Decrease speed of motors on the front side
    decrease_motor_speed(M1);
    decrease_motor_speed(M2);
}
void Drone_Move_Backward() {
    // Increase speed of motors on the front side
    increase_motor_speed(M1);
    increase_motor_speed(M2);
    
    // Decrease speed of motors on the back side
    decrease_motor_speed(M3);
    decrease_motor_speed(M4);
}

void Drone_Move_Left() {
    // Increase speed of motors on the right side
    increase_motor_speed(M1);
    increase_motor_speed(M3);
    
    // Decrease speed of motors on the left side
    decrease_motor_speed(M2);
    decrease_motor_speed(M4);
}
void Drone_Move_Right() {
    // Increase speed of motors on the left side
    increase_motor_speed(M2);
    increase_motor_speed(M4);
    
    // Decrease speed of motors on the right side
    decrease_motor_speed(M1);
    decrease_motor_speed(M3);
}

void Drone_Move_Up() {
    // Increase speed of motors responsible for upward movement
    increase_motor_speed(M1);
    increase_motor_speed(M2);
    increase_motor_speed(M3);
    increase_motor_speed(M4);
}
void Drone_Move_Down() {
    // Decrease speed of motors responsible for downward movement
    decrease_motor_speed(M1);
    decrease_motor_speed(M2);
    decrease_motor_speed(M3);
    decrease_motor_speed(M4);
}

void Drone_Rotate_Clockwise() {
    // Increase speed of motors responsible for clockwise rotation
    increase_motor_speed(M2);
    increase_motor_speed(M3);
    
    // Decrease speed of motors responsible for counterclockwise rotation
    decrease_motor_speed(M1);
    decrease_motor_speed(M4);
}
void Drone_Rotate_Counterclockwise() {
    // Increase speed of motors responsible for counterclockwise rotation
    increase_motor_speed(M1);
    increase_motor_speed(M4);
    
    // Decrease speed of motors responsible for clockwise rotation
    decrease_motor_speed(M2);
    decrease_motor_speed(M3);
}

