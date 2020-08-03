




/*   All Lora Functions




*/



float txFrequency = 434.500;     // Tx Frequency in MHz   (*E6)

long txHz;                          // Tx Frequency in Hz

long MHz = 1000000;                    // conversion from Hz to MHz




void loraSetup() {

  Serial.println("SkyTracker LoRa Transmitter Starting...");

  txHz = txFrequency * MHz;

  if (!LoRa.begin(txHz)) {                             // sets TX frequency 434.500    E6 = translate to MHz
    Serial.println("Starting LoRa failed!");
    delay(5000);
    Serial.print("...");
    delay(1000);
    Serial.println("Restarting");
    //   ESP.restart();
    //  while (1);
  }

  Serial.println("SkyTracker LoRa Transmitter Initilised.");

}



void loraBuildPacket() {

  // *        [$][CallSign],[PacketType(counter)],[GPS.latitude],[GPS.longitude],[GPS.altitude]
  //Bytes     1     5           3             4(float)    4(float)

 char packetBuffer[82];
 Serial.println(latitudeDegPre);            // This makes no sense and is annoying AF but no data gets loaded into string if these lines are not here
 Serial.println(" ");                           // This makes literally no sense, I dont get it whatsoever.

  sprintf(packetBuffer, "%s,%i,%i.%i,%i.%i,%i.%i,%i.%i,%i.%i", callSign, counter, latitudeDegPre, latitudeDegPost, longitudeDegPre, longitudeDegPost, altitudePre, altitudePost , speedkmhPre, speedkmhPost, headingPost, headingPre);      // "Basic Data String"

  //nmeaChecksum(loraBuffer);

sprintf(loraBuffer, "%s*%i", packetBuffer, nmeaChecksum(packetBuffer));




}




void loraSendPacket() {

  char buffer2 [8];
  // send packet
  LoRa.beginPacket();
  // LoRa.print("$");

  LoRa.print(loraBuffer);
  // LoRa.print("*");
  LoRa.endPacket();




  sprintf(buffer2, "LoRa Packet %i Sent:", counter);
  Serial.println(buffer2);
  Serial.println(loraBuffer);
  Serial.println(" ");
  txLED.callBlink();
  counter++;

}
