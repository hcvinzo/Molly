#include <CheapStepper.h>
#include <IRremote.h>

// Remote Control Button Codes
// These codes specific to remote control 
// You should upload the RemoteTest.ino file to the Arduino and get the codes of the buttons from the Serial Monitor
#define SPD_BTN_1 12
#define SPD_BTN_2 24
#define SPD_BTN_3 94
#define SPD_BTN_4 8
#define SPD_BTN_5 28
#define SPD_BTN_6 90
#define SPD_BTN_7 66
#define SPD_BTN_8 82
#define SPD_BTN_9 74
#define DIR_CW_BTN 67
#define DIR_CCW_BTN 64
#define PWR_BTN 69
#define ACC_BTN 9
#define DEC_BTN 21

// Signal pin of the IR sensor. 
// If you connected to different pin, you musts change the number below
#define RECV_PIN 3

// Motor driver connection pins
// If you connected to different pins then replace the values below
#define MOTOR_PIN_1 4
#define MOTOR_PIN_2 5
#define MOTOR_PIN_3 6
#define MOTOR_PIN_4 7

// Minimum RPM value
const int MIN_RPM = 6;
// Maximum rpm value
const int MAX_RPM = 24;

// Initiate IR reciever
IRrecv irrecv(RECV_PIN);

// Initilize motor
CheapStepper stepper(MOTOR_PIN_1,MOTOR_PIN_2,MOTOR_PIN_3,MOTOR_PIN_4); 
// hold motors direction. 
boolean moveClockwise = true;
// Hold the motor is running or not
boolean isMotorRunning = false;

// current RPM of the motor
int currentRpm = 12;

void setup() {
  // begin serial communication
  // Baud rate on the Serial Monitor must be set to 9600
  Serial.begin(9600);
  // Enable the IR reciever
  irrecv.enableIRIn();
  // Default rpm of the motor
  stepper.setRpm(currentRpm);
}

void loop() {   

  // Keep motor running if it's ON
  if(isMotorRunning) {
    stepper.run();
    int stepsLeft = stepper.getStepsLeft();
    if (stepsLeft == 0){
      stepper.newMoveDegrees(moveClockwise,5);
    }
  }

  // Handle remote control buttons
  if (irrecv.decode()) {      
      switch(irrecv.decodedIRData.command)
      {
        // Speed Buttons
        case SPD_BTN_1:
          setSpeed(6);
          break;
        case SPD_BTN_2:
          setSpeed(8);
          break;          
        case SPD_BTN_3:
          setSpeed(10);
          break;          
        case SPD_BTN_4:
          setSpeed(12);
          break;          
        case SPD_BTN_5:
          setSpeed(14);
          break;          
        case SPD_BTN_6:
          setSpeed(16);
          break;          
        case SPD_BTN_7:
          setSpeed(18);
          break;          
        case SPD_BTN_8:
          setSpeed(20);
          break;          
        case SPD_BTN_9:
          setSpeed(24);
          break;     
        case ACC_BTN:
          incSpeed();
          break;    
        case DEC_BTN:
          decSpeed();
          break;                                    
        // Direction
        case DIR_CW_BTN:
          moveClockwise = true;
          break;
        case DIR_CCW_BTN:
          moveClockwise = false;
          break;         
        case PWR_BTN:
          stopMotor();
          break;
      }
      irrecv.resume(); // Receive the next value
  }
}
// Sets the speed of the motor
// And starts to motor if stopped
void setSpeed(int speed){
  if(speed>MAX_RPM)
    speed=MAX_RPM;
  if(speed<MIN_RPM)
    speed=MIN_RPM;    
  stepper.setRpm(speed);
  currentRpm = speed;
  startMotor();
}

// Increases motor speed by two
void incSpeed(){
  setSpeed(currentRpm+2);
}

// Decreases motor speed by two
void decSpeed(){
  setSpeed(currentRpm-2);
}

// Starts the motor
void startMotor(){
  if(!isMotorRunning){
    stepper.newMoveDegrees(moveClockwise, 5);
    isMotorRunning=true;
  }
}

// stops the motor
void stopMotor(){
  isMotorRunning = false;
  // turn the pins off
  digitalWrite(MOTOR_PIN_1, 0);
  digitalWrite(MOTOR_PIN_2, 0);
  digitalWrite(MOTOR_PIN_3, 0);
  digitalWrite(MOTOR_PIN_4, 0);
}
