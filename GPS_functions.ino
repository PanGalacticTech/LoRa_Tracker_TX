/*
     GPS Functions




*/

//GPSlocationData gpsPacket;


//void GPSdataPackage(){    // function to package GPS data into packets for LoRa transmission


//gpsPacket = {GPS.latitudeDegrees, GPS.longitudeDegrees, GPS.altitude};

/*
  gpsPacket.GPSlatitudeDeg = GPS.latitudeDegrees;
  gpsPacket.GPSlongitudeDeg = GPS.longitudeDegrees;
  gpsPacket.GPSaltitude = GPS.altitude;
*/


//}




void GPSsetup() {

  Serial.println("SkyTracker GPS Initilize.");

  delay(4000);


  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);

}




void GPSread_andParse() {

  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if ((c) && (GPSECHO)) {
    Serial.write(c);
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
}




int shift = 10000;  // controls the precision of the decimal points for latitude & longitude printouts


void sortGPSData() {  // Function sorts data for easier processing later

  latitudePre =  (int16_t)GPS.latitude;

  latitudePost = (int16_t)((GPS.latitude * shift) - latitudePre * shift);

  longitudePre =  (int16_t)GPS.longitude;

  longitudePost = (int16_t)((GPS.longitude * shift) - longitudePre * shift);



  latitudeDegPre =  (int16_t)GPS.latitudeDegrees;

  latitudeDegPost = (int16_t)((GPS.latitudeDegrees * shift) - latitudeDegPre * shift);

  longitudeDegPre =  (int16_t)GPS.longitudeDegrees;

  longitudeDegPost = (int16_t)((GPS.longitudeDegrees * shift) - longitudeDegPre * shift);

  if ( longitudeDegPost < 0) {
    longitudeDegPost =  longitudeDegPost * -1;    // invert to fix negative decimals
  }


  altitudePre =   (int16_t)GPS.altitude;
  altitudePost =   (int16_t)((GPS.altitude * 10) - altitudePre * 10);

  altitudeKmPre =  (int16_t)(GPS.altitude / 1000);
  altitudeKmPost = (int16_t)((GPS.altitude * (shift / 1000)) - altitudeKmPre * (shift / 1000) );

  speedConversion(GPS.speed);

}







void speedConversion (float speedInput) {            // Speed input in Knots


  // all maths here------

  speedKnotsPre = (int16_t)speedInput;
  speedKnotsPost = (int16_t)((speedInput * 100) - speedKnotsPre * 100);



  float speedCalc;   // Working float value for doing calculations

  ///speed values for printouts

  speedCalc = (speedInput * (1.852 / 3600 * 1000)); // meters per second

  speedmsPre = (int16_t)speedCalc;
  speedmsPost = (int16_t)((speedCalc * shift) - speedmsPre * shift);



  speedCalc  = (speedInput * 1.852);                           // Kilometers Per Hour

  speedkmhPre = (int16_t)speedCalc;
  speedkmhPost = (int16_t)((speedCalc * shift) - speedkmhPre * shift);



  speedCalc = (speedInput * 1.15077945);                         // Miles Per Hour

  speedmphPre = (int16_t)speedCalc;
  speedmphPost = (int16_t)((speedCalc * shift) - speedmphPre * shift);




}


/*



void  GPSserialPrint() {    // Prints out the main body of GPS data in easy to read format

  //Serial Print Data


  char buffer [64];                                       // must be large enough for your whole string!  // Way around printf not being avaiable for whatever reason


  // These Variables Print all the time

  //     Serial.printf("Time: %2i:&2i:%2i.%4i  ", GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds);       // Print Time
  sprintf (buffer, "Time: %02i:%02i:%02i", GPS.hour, GPS.minute, GPS.seconds );       //                   //GPS.milliseconds
  Serial.println(buffer);

  //      Serial.printf("  Date: %2i/%2i/20%2i ", GPS.day, GPS.month, GPS.year);                                // Print Date
  sprintf (buffer, "Date: %02i/%02i/20%02i", GPS.day, GPS.month, GPS.year);
  Serial.println(buffer);

  //    Serial.printf("Fix: %i  | Satellites: %i " , GPS.fix, GPS.satellites);                                           // GPS Stats
  sprintf (buffer, "Fix: %i  |  Satellites: %i " , GPS.fix, GPS.satellites);
  Serial.println(buffer);
  //

  // These variables only print if GPS lock is avaliable

  if (GPS.fix) {

    sortGPSData();                                                                                                                                             // Function to repackage data into more easily digestable parcels

    //    Serial.printf("Coordinates: %i %c, %i %c " , GPS.latitude, GPS.lat, GPS.longitude, GPS.lon);                          // Location Data
    sprintf (buffer, "Coordinates: %i.%i %c %i.%i %c " ,   latitudePre, latitudePost, GPS.lat, longitudePre,  longitudePost, GPS.lon);
    Serial.println(buffer);

    //    Serial.printf("Coordinates: %i %c, %i %c " , GPS.latitude, GPS.lat, GPS.longitude, GPS.lon);                          // Location Data
    sprintf (buffer, "Degrees: %i.%i, %i.%i " ,   latitudeDegPre, latitudeDegPost, longitudeDegPre, longitudeDegPost);
    Serial.println(buffer);



    //    Serial.printf("Altitude: %i %c, %i %c " , GPS.latitude, GPS.lat, GPS.longitude, GPS.lon);                        // Altitude
    sprintf (buffer, "Altitude: %i.%i m ASL  %i.%i km" ,  altitudePre, altitudePost, altitudeKmPre, altitudeKmPost);
    Serial.println(buffer);


    //    Serial.printf("Altitude: %i %c, %i %c " , GPS.latitude, GPS.lat, GPS.longitude, GPS.lon);                        // Speed
    sprintf (buffer, "Speed: %i.%i knots   %i.%i m/s   %i.%i km/h  %i.%i mph" , speedKnotsPre, speedKnotsPost, speedmsPre, speedmsPost, speedkmhPre, speedkmhPost, speedmphPre, speedmphPost);
    Serial.println(buffer);


    //GPSserialTestPrint();   // Test printout uncomment if unrequired
  }



  Serial.println(" ");
  Serial.println(" ");

}











void GPSserialTestPrint() {               // Used to directly print variables from the GPS library to compare to calculated figures for testing > Not needed unless experiencing math errors & testing



  /*
        // For testing
        Serial.print(GPS.latitude, 4);
        Serial.print("    ");
        Serial.println(GPS.longitude, 4);
        Serial.println(" ");
  */
  /*
        // For testing
        Serial.print(GPS.latitudeDegrees, 4);
        Serial.print("    ");
        Serial.println(GPS.longitudeDegrees, 4);
        Serial.println(" ");
  */

  /*
    Serial.println(" ");
    Serial.println(GPS.altitude, 4);
    Serial.println(" ");
  */
  /*
        Serial.println(" ");
        Serial.println(GPS.speed, 2);
        Serial.println(" ");
  */

/*

}


*/
