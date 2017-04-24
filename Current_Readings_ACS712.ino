/*
Measuring AC Current Using ACS712
*/
const int sensorIn = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module


double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
double power = 0;
double powerWh = 0;



void setup(){ 
 Serial.begin(9600);
}

void loop(){
 
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 power = 220 * AmpsRMS;
 powerWh = (power / 3600) + powerWh;
 
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");

 Serial.print(power);
 Serial.println(" Watts");

 Serial.print(powerWh);
 Serial.println(" Units");
 
 

}

float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }