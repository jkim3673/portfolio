const int ledPin = 8;

char data;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(data) {
    case '0' :
      digitalWrite(ledPin, LOW);
      break;
    case '1' :
      digitalWrite(ledPin, HIGH);
      break;

      default :
        break;
  }
}

void serialEvent() {
  data = Serial.read();
  Serial.println(data);
}
