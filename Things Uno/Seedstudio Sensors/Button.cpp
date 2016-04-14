int buttonPin = 4;

pinMode(buttonPin, INPUT);

While(digitalRead(buttonPin)){
    // <do something while button is pressed>
} else {
    // <do something while button is not pressed>
}