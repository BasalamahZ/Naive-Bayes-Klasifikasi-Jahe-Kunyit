#include "HX711.h"  //You must have this library in your arduino library folder
#define CLK  2
#define DOUT 3

HX711 scale;
float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;

void setup(){
 Serial.begin(9600);  
 Serial.println("Press T to tare");
 scale.begin(DOUT, CLK);
 scale.set_scale(calibration_factor); //Adjust to this calibration factor
 scale.tare(); 
}

void loop() {
 units = scale.get_units(), 5;
 if (units < 0){
   units = 0.00;
 }
 Serial.print("Weight: ");
 Serial.print(units); //displays the weight in 4 decimal places only for calibration
 Serial.println("grams");
 if(Serial.available()){
   char temp = Serial.read();
   if(temp == 't' || temp == 'T')
     scale.tare();  //Reset the scale to zero      
 }
} 
