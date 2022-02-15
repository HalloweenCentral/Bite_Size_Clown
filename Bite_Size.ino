// Change 8 or 9 depending on which pins you attach each to, Stick to digital pins.
# define PinMotor      8
# define PinSensor       9
boolean deviceOn = false;
void setup() {
  Serial.begin(115200);
  pinMode(PinSensor, INPUT_PULLUP);
  Serial.println("waiting for trigger");
  digitalWrite (PinMotor,    LOW);
  pinMode(PinMotor, OUTPUT);


}
// -----------------------------------------------------------------------------
struct Timer {
  byte           pin;
  unsigned long  duration;
  bool           on;
};

Timer timers [] = {
  { PinMotor, 13000 },
  // Currently his motor will go for 13 seconds. The arduino counts in milliseconds, so if you need to change time replace 13000 with whatever time you want in milliseconds.

};

#define N_TIMERS    (sizeof(timers)/sizeof(Timer))

// -----------------------------------------------------------------------------
void loop() {
  static unsigned long msecLst;
  unsigned long msec = millis ();

  // Enable timed outputs
  //You may need to change LOW to HIGH depending on the sensor. Most go LOW when activated, so try that first. Some do go HIGH, however.
  if ((digitalRead(PinSensor) == LOW) && (deviceOn == false))  {
    Serial.println("Triggered");
    deviceOn = true;
    msecLst = msec;
    for (unsigned n = 0; n < N_TIMERS; n++)  {
      timers [n].on = true;
      digitalWrite (timers [n].pin, HIGH);
    }
  }

  // Turn off timed outputs when duration expired
  Timer *t = timers;
  for (unsigned n = 0; n < N_TIMERS; n++, t++)  {
    if (t->on && (msec - msecLst) > t->duration)  {
      digitalWrite (t->pin, LOW);
      t->on = false;
      deviceOn == false;
      Serial.println("waiting for trigger");
    }
  }



}
