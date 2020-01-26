/*
  Ultrasonic Sensor HC-SR04
  Angle of 15degs
  Range 2cm to 400cm
  Accurate 3mm
  15ma current
*/

int trigPin;
int echoPin;
bool isMetric;


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;//do nothing
  }
}


/*
 Note: multiple sensors may use array of structures
 ultrasound pins trigPin and echoPin
 metric true = centemeters for distance calculation
 metric false = inches 
 repeat will force multiple pings and average results
 to improve accuracy
*/

long  UPing(int trig, int echo, bool metric, int repeat) {
  
  int _trig;
  int _echo;
  int _repeat;
  bool _metric;
  long _duration;
  long _distance;
  
  _trig = trig;
  _echo = echo;
  _repeat = repeat;
  _metric = metric;
  _duration = 0;
  _distance = 0;
  
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);

  for (int x = 0; x < _repeat; x++)
  {
    digitalWrite(_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(_trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(_trig, LOW);
    //total for all repeats
    _duration += pulseIn(_echo, HIGH);//time to return in microseconds
  }
  //average the time and one way so divide by 2
  _duration = _duration / 2;
  _duration = _duration / _repeat;

//test for out of sensor parameters
  if (_distance < 0 || _distance > 11600) {
    _distance = -1.0;
    return _distance;
  }
//calculate cm or in
  if (_metric)
  {
    _distance = _duration / 29; //centimeters

  } else {

    _distance = _duration / 74; //inches
  }
  return _distance;
}

void loop() {

  long distance;
  trigPin = 7;
  echoPin = 8;
  isMetric = true;

  distance = UPing(trigPin, echoPin, isMetric, 3);
  Serial.print(String(distance));
  if(isMetric) { 
    Serial.print("cm");
    } else {
    Serial.print("in");
  }
  Serial.println();
}
