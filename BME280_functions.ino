



/////////////////////////// BME280  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\




void readBME280() {





  pressure = (bme280.readFloatPressure() / 100); //  I dont know why this is divided by 100 but okay

  humd =  bme280.readFloatHumidity() ;

  if (BME_HIGHT) {
    altitude = bme280.readFloatAltitudeMeters();
  }
  else {
    altitude = bme280.readFloatAltitudeFeet();
  }


  if (TEMP_TYPE) {                              // if temp type true = degC
    temp = (bme280.readTempC() - tempOffset);  // offset value a fudge for now

  } else {
    temp = (bme280.readTempF(), 2);

  }
}





void BME280setup() {
  // set BME280 I2C address.
  bme280.setI2CAddress(I2CADDR);

  if (bme280.beginI2C() == false) { // Begin communication over I2C
    Serial.println("The BME280 did not respond. Please check wiring.");
    Serial.println("...");
    delay(500);
  }
  else  {
    detected_BME280 = true;
    Serial.println(F("Detected BME280"));
    Serial.println("...");
    delay(500);
  }
}







int16_t tempPre;
int16_t tempPost;

int16_t pressurePre;
int16_t pressurePost;

int16_t BMEaltitudePre;
int16_t BMEaltitudePost;

int16_t humidityPre;
int16_t humidityPost;



void BME280serialPrint() {

  char buffer [64];

  sortBMEdata();


  //    Serial.printf("Altitude: %i %c, %i %c " , GPS.latitude, GPS.lat, GPS.longitude, GPS.lon);                        // Speed
  sprintf (buffer, "Temp: %i.%i %1cC  Pressure: %i.%i hPa  Altitude: %i.%i m  Humidity %i.%i %%" , tempPre, tempPost, degreeMark, pressurePre, pressurePost, altitudePre, altitudePost,  humidityPre, humidityPost);
  Serial.println(buffer);


// Test Output for direct printing sensor variables
/*

  Serial.print(F("\t"));
  Serial.print(temp, 2);
  Serial.print(F("\t  "));
  Serial.print(pressure, 1);   // (value, no of .Points);
  Serial.print(F("\t     "));
  Serial.print(altitude, 1);
  Serial.print(F("\t   "));
  Serial.print(humd, 1);                  // (value, no of .Points);


  Serial.print(F("\n"));

*/

  Serial.println(" ");
  Serial.println(" ");


}






void sortBMEdata() {


  tempPre =  (int16_t)temp;

  tempPost = (int16_t)((temp * 100) - tempPre * 100);



  pressurePre =  (int16_t)pressure;

  pressurePost = (int16_t)((pressure * 100) - pressurePre * 100);



  altitudePre =  (int16_t)altitude;

  altitudePost = (int16_t)((altitude * 10) - altitudePre * 10);



  humidityPre =  (int16_t)humd;

  humidityPost = (int16_t)((humd * 10) - humidityPre * 10);


}
