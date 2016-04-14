int moisturePin = A0;
float Moisture;

pinMode(moisturePin, INPUT);

// moisture::air        = 0
// moisture::soil       = 20 +/-
// moisture::humid soil = 580 +/-
// moisture::water      = 940 +/-

moisture = analogRead(moisturePin);
