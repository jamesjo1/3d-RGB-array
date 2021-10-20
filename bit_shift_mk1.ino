int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off
int incomingByte = 0;
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
  leds = 255; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  //leds = 255; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
 //updateShiftRegister();
  //delay(500);
  /*
  for (int i = 0; i < 8; i++) // Turn all the LEDs ON one by one.
  {
    bitSet(leds, i);    // Set the bit that controls that LED in the variable 'leds'
    if (i > 0) {
      bitClear(leds, i-1);
    }
    Serial.println(leds);
    updateShiftRegister();
    delay(500);
  }
  */
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte != 10) {
      if (incomingByte <= 303) {
        leds = 255 - (incomingByte - 48);
      } else {
        Serial.println("too large didnt work");
      }
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte);
      Serial.print("leds = ");
      Serial.println(leds);
      updateShiftRegister();
      delay(500);
    }
  }
}
/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
