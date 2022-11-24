// load cell
#include "HX711.h"  //You must have this library in your arduino library folder
#define CLK  2
#define DOUT 3
// LCS3200
#define s0 8       //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define PUSHBUTTON 7
#define out 12

HX711 scale;
float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;
double data = 0;

void setup(){
 pinMode(s0,OUTPUT);    //pin modes
 pinMode(s1,OUTPUT);
 pinMode(s2,OUTPUT);
 pinMode(s3,OUTPUT);
 pinMode(PUSHBUTTON,INPUT);
 pinMode(out,INPUT);
 Serial.begin(9600);  
 Serial.println("Press T to tare");
 scale.begin(DOUT, CLK);
 scale.set_scale(calibration_factor); //Adjust to this calibration factor
 scale.tare(); 
 digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
 digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
}

void loop() {
//  Serial.println();
  int val = digitalRead(PUSHBUTTON);
//  Serial.println(val);
 if (val) {
 
   units = scale.get_units(), 5;
   if (units < 0){
     units = 0.00;
   }
//   if(units != 0.00){
   Serial.print(units); //displays the weight in 4 decimal places only for calibration
   Serial.print(",");
   if(Serial.available()){
     char temp = Serial.read();
     if(temp == 't' || temp == 'T')
       scale.tare();  //Reset the scale to zero      
   }
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");    
   delay(20);
   Serial.println();
   delay(2000);

  }
}
