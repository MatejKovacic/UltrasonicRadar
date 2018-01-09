/*  UltrasonicRadar
*   Arduino firmware for implementation of traffic radar with ultrasonic distance sensor.
*   
*   Wiring
*   ======
*   Ultrasonic sensor - Arduino Nano:
*   VCC  --- 5V
*   Trig --- D3
*   Echo --- D4
*   GND  --- GND
*/ 

const int trigger_pin = 3;   // trigger pin from ultrasonic sensor
const int echo_pin = 4;      // echo pin from ultrasonic sensor

// Define duration, distance, time and speed variables:
long duration1;
long duration2;
int distance1;
int distance2;
float traveled_distance;
unsigned long time1;
unsigned long time2;
float elapsed_time;
float measured_speed;

void setup() {
  pinMode(trigger_pin, OUTPUT);     // set the trigger_pin as an output
  pinMode(echo_pin, INPUT);         // set the echo_pin as an input
  Serial.begin(9600);               // start the serial communication
  Serial.println("Ultrasonic radar");
}

void loop() {
  // First ultrasonic measurement...
  time1 = millis();
  digitalWrite(trigger_pin, LOW);   // clear the trigger_pin
  delayMicroseconds(2);
  
  // Set the trigger_pin on HIGH state for 10 micro seconds:
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  
  // Read the echo_pin and return the sound wave travel time in microseconds:
  duration1 = pulseIn(echo_pin, HIGH);
  // Calculate the distance:
  distance1 = duration1*0.034/2;

  delay(200);


  // Second ultrasonic measurement...
  time2 = millis();
  // Set the trigger_pin on HIGH state for 10 micro seconds:
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  
  // Read the echo_pin and return the sound wave travel time in microseconds:
  duration2 = pulseIn(echo_pin, HIGH);
  // Calculate the distance:
  distance2 = duration2*0.034/2;  
  
 
  // Compute traveled distance, elapsed time and speed:
  traveled_distance = distance1-distance2;
  elapsed_time = time2-time1;
  measured_speed = traveled_distance/elapsed_time*36;

  // Print speed only if object final distance is less than 0.5 m away...
  if (distance2<50)
  {
    if ((fabs(traveled_distance) > 1.0))  // Print speed only if object moves for at least 1 cm...
    {
      // Print current distance of a object
      Serial.print("Objekt je oddaljen ");
      Serial.print(distance2);

      // Print if object is approaching or moving away
      if (measured_speed > 0)
      {
        Serial.print("cm, in se približuje s hitrostjo ");
      }
      else
      {
        Serial.print("cm, in se oddaljuje s hitrostjo ");
      }
      // Print speed of an object
      Serial.print(fabs(measured_speed));
      Serial.println(" km/h.");
    }
  }
}
