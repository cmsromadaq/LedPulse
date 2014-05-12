/*
Led pulser V0.1
Code to remotely pilot a pulsed led driver at a fixed frequency
 */

// Pin 13 has also a LED connected on most Arduino boards.
int led = 13;
int status = 0;
int freq=0;
int npulses=0;

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  Serial.setTimeout(10000);
  Serial.println("LED Pulser V0.1"); 
  Serial.println("Type a freq in Hz (integer value 1-500) or 0 to stop pulsing");  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  if (freq>0)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(100);               // send a pulse of 100usec
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(1000/freq);               // repetition rate 25Hz
    npulses++;
    if ((npulses%100)==0)
    {
      Serial.print("#pulses sent: "); Serial.println(npulses,DEC); 
    }
  }
}

// serialEvent occurs whenever a new data comes in the
// hardware serial RX. Catches frequency from serial connection
void serialEvent()
{
  if (Serial.available() > 0) {
    // sentence:
    int val = Serial.parseInt(); 
    if (Serial.read() == '\n') {
        val=constrain(val,0,500); //constrain value up to 500Hz
        freq=val;
        Serial.print("Frequency has been set to ");
        Serial.print(freq,DEC);
        Serial.println(" Hz. Resetting pulser");
        npulses=0;
    }
  }  
}



