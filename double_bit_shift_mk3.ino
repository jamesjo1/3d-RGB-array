int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off
byte leds2 = 0;
int incomingByte = 0;

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

String inputValue;
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  leds = 0; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  recvWithEndMarker();
  inputValue = showNewData();
  if (inputValue != "a"){
    leds = inputValue.substring(0,3).toInt();
    leds2 = inputValue.substring(4,7).toInt();
    Serial.println(leds);
    Serial.println(leds2);
    updateShiftRegister();  
  }
  delay(500);
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, 255 - leds);
   shiftOut(dataPin, clockPin, LSBFIRST, 255 - leds2);
   digitalWrite(latchPin, HIGH);
}

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 // if (Serial.available() > 0) {
 while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }
}

String showNewData() {
 if (newData == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChars);
 newData = false;
 return receivedChars;
 }
 return "a";
}
