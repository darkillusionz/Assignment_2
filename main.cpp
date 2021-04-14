#include <Arduino.h>



//Circuit:
//-LEDs between D1, D2, D3 and GND
//Button between D0 and GND
//-Pot resistor leads (Outer) between 3.3vdc and GND, Pot wiper (Center lead) to A0
 int potresis = A0;
 int inpin = D0;
 int Led1 = D1;
 int Led2 = D2;
 int Led3 = D3;
 int inputValue = 0;
 int outputValue = 0;
 int buttonState = 0;

 int led1brightness = 0;
 int led2brightness = 0;
 int led3brightness = 0;
 

void setup() {
  pinMode(D0, INPUT_PULLUP); //button on pin D0
  pinMode(Led1, OUTPUT); //led1 on D1
  pinMode(Led2, OUTPUT); //led2 on D2
  pinMode(Led3, OUTPUT); //led3 on D3
  Serial.begin(9600);
}


void loop(){
  //Potentiometer control, values from 0 --> 100
  
  int inputValue = analogRead(potresis); //read the value from the potentiometer
  Serial.print("Input: "); //print "Input"
  Serial.println(inputValue); //print inputValue
  int outputValue = map(inputValue, 0, 1023, 0, 100); //Convert from 0-1023 proportional to the number of a number of from 0 to 100
  Serial.print("Output: "); //print "Output"
  Serial.println(outputValue); //print outputValue
  delay(1000);

  //General program for the button and lights - synergy

  
  buttonState = digitalRead(inpin);

  if(buttonState != 0)
  {
    digitalWrite(Led1, HIGH); //leds to max if button is held down
    digitalWrite(Led2, HIGH);
    digitalWrite(Led3, HIGH);
  }

  else
  {
    //General program for the synergy between the lights and the potentiometer

    if(outputValue < 34 && outputValue != 0)
    {

      led1brightness = map(outputValue, 0, 34, 1, 100); //turn Led1 on depending on the potentio-values
      analogWrite(D1, led1brightness);

    } 
    else if(outputValue >= 34 && outputValue < 67){

      led2brightness = map(outputValue, 34, 67, 1, 100);
      analogWrite( D2 , led2brightness); //turn LED2 on depending on the potentio-values
      }

    else if(outputValue >= 67){
      led3brightness = map(outputValue, 67, 100, 1, 100);
      analogWrite(D3, led3brightness); //turn Led3 on depending on potentio-values
    }
    else{
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
    }
  }
  

}