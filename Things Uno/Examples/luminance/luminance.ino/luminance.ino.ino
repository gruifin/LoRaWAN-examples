float VoutArray[] =  { 0.0011498,  0.0033908,   0.011498, 0.041803,0.15199,     0.53367, 1.3689,   1.9068,  2.3};
float  LuxArray[] =  { 1.0108,     3.1201,   9.8051,   27.43,   69.545,   232.67,  645.11,   73.52,  1000};

int ledPin = 13;
int luminancePin = A2;
float sensorVoltage;
float luminance;

void setup() {
  
  //Enable this code if you're connecting the board to your pc, for smooth reading

  while(!SerialUSB) {
   ;
  }
  delay(1500); 
  
  pinMode(ledPin, OUTPUT);
  }

void loop() 
{
  sensorVoltage = analogRead(luminancePin) * (3.0 / 1023.0);
  luminance = FmultiMap(sensorVoltage, VoutArray, LuxArray, 9);
  SerialUSB.print("sensorVoltage = ");
  SerialUSB.print(sensorVoltage);
  SerialUSB.print(" luminance value = ");
  SerialUSB.println(luminance);
  delay(400);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}
  
float FmultiMap(float val, float * _in, float * _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

