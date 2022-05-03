
int Enable1 = 3;
int PWM1 = 5;
int DIR1 = 6;
int Enable2 = 9;
int PWM2 = 10;
int DIR2 = 11;

char data;
/*
void drive_forward();
void turn_left();
void turn_right();
void motor_stop();
void serialEvent();
*/
void setup() {
  pinMode(PWM1, OUTPUT);
  pinMode(Enable1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(Enable2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  
  digitalWrite(Enable1, HIGH);
  digitalWrite(Enable2, HIGH);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(Enable1, LOW);
  digitalWrite(Enable2, LOW);
  
 switch(data) {
    case '0' :
      analogWrite(PWM1, 0);
      analogWrite(PWM2, 0);
      break;
    case '1' :
      digitalWrite(DIR1, HIGH);
      digitalWrite(DIR2, HIGH);
      analogWrite(PWM1, 128);
      analogWrite(PWM2, 128);
      break;
    case '2' :
      digitalWrite(DIR1, HIGH);
      digitalWrite(DIR2, LOW);
      analogWrite(PWM1, 128);
      analogWrite(PWM2, 0);
      break;
    case '3' :
      digitalWrite(DIR1, LOW);
      digitalWrite(DIR2, HIGH);
      analogWrite(PWM1, 0);
      analogWrite(PWM2, 128);
      break;

      default :
        break;
  }
}

/*void drive_forward() {
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW); 
}

void turn_left() {
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW);
}

void turn_right() {
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
}

void motor_stop(){
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], LOW);
}*/

void serialEvent() {
  data = Serial.read();
  Serial.println(data);
}
