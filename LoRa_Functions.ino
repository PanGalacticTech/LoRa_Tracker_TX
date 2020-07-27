




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



void loraBuildPacket(){


sprintf(loraBuffer, "%i.%i,%i.%i,%i.%i,%i.%i", latitudeDegPre, latitudeDegPost, longitudeDegPre, longitudeDegPost, altitudePre, altitudePost , speedkmhPre, speedkmhPost);      // "Basic Data String"


  
}




void loraSendPacket() {

  char buffer2 [8];
  // send packet
  LoRa.beginPacket();

  LoRa.print(callSign);
  LoRa.print(" ");
  LoRa.print(counter);
  LoRa.print(" ");
  LoRa.print(loraBuffer);
 // LoRa.print("");

  //  LoRa.print(GPS.longitudeDegrees);
  // LoRa.print(",");
  //  LoRa.print(GPS.altitude);
  // LoRa.print(",");

  LoRa.endPacket();




  sprintf(buffer2, "LoRa Packet %i Sent", counter);
  Serial.println(buffer2);
  Serial.println(" ");
  counter++;

}
