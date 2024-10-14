#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // กำหนดรอบการหมุนของมอเตอร์
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() { //งค่าเซอร์โวมอเตอร์ให้หมุนไปที่มุม 115 องศา และอ่านค่าระยะทางจากเซ็นเซอร์อัลตราโซนิกหลายครั้งเพื่อเก็บค่าเริ่มต้น

  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() { //เตรียมตัวแปรสำหรับเก็บค่าระยะทางด้านซ้ายและขวา และหน่วงเวลา 40 มิลลิวินาทีก่อนการทำงานถัดไป
 int distanceR = 0;
 int distanceL =  0;
 delay(40);

 if(distance<=15) //ควบคุมการเคลื่อนที่ของหุ่นยนต์ โดยใช้ข้อมูลระยะทางจากเซ็นเซอร์ อัลตราโซนิก เพื่อตัดสินใจว่าหุ่นยนต์ควรจะหยุด,ถอยหลัง หรือเลี้ยวไปทางซ้ายหรือขวาเมื่อพบสิ่งกีดขวางที่ระยะทางใกล้
 {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}
   //หันจากซ้าย
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}
   //หันจากซ้าย
int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}
  //อ่านค่าจาก ultra sonic sensor ถ้าค่าอ่านได้เป็น 0 (ไม่มีการตรวจจับ) เเละจะตั้งค่าเป็น 250 เซนติเมตร
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
  //หยุด
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  //เดินหน้า
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // ค่อย ๆ เพิ่มความเร็วขึ้น เพื่อไม่ให้แบตเตอรี่หมดเร็วเกินไป
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}
  //ถอยหลัง
void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // ค่อย ๆ เพิ่มความเร็วขึ้น เพื่อไม่ให้แบตเตอรี่หมดเร็วเกินไป
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  
  //หันหน้าทางขวา
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 //หันหน้าทางซ้าย
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
