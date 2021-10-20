/*
 
 All the resources for this project:
 https://randomnerdtutorials.com/
 
*/

int redPin = 8;     // Red RGB pin -> D3
int greenPin = 9;   // Green RGB pin -> D5




void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(5000);
  digitalWrite(redPin, 255);
  delay(75);
  digitalWrite(redPin, 0);
  delay(5000);
    
    /*
    digitalWrite(redPin, 0);
    digitalWrite(greenPin, 0);
    delay(1000);
    digitalWrite(redPin, 255);
    delay(10);
    digitalWrite(greenPin, 255);
    delay(90);
    digitalWrite(redPin,0);
    delay(10);
    digitalWrite(greenPin,0);
    delay(100);
    */
}
