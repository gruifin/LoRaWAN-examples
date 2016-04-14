int luminancePin = A0;
float sensorVoltage;
float ligthlevel;

pinMode(ligthPin, INPUT);

ligthlevel = analogRead(ligthPin) * (5.0 / 1023.0)

