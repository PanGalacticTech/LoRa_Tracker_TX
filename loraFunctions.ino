/*   All Lora Functions




*/



float txFrequency = 434.500;     // Tx Frequency in MHz   (*E6)

long txHz;                          // Tx Frequency in Hz

long MHz = 1000000;                    // conversion from Hz to MHz




void loraSetup() {

  Serial.println("LoRa Transmitter");

  txHz = txFrequency * MHz;

  if (!LoRa.begin(txHz)) {                             // sets TX frequency 434.500    E6 = translate to MHz
    Serial.println("Starting LoRa failed!");
    delay(5000);
    Serial.print("...");
    delay(1000);
    Serial.println("Restarting");
    ESP.restart();
    //  while (1);
  }



}






void loraSendPacket() {


  // send packet
  LoRa.beginPacket();

  LoRa.print(callSign);
  LoRa.print(" ");
  LoRa.print(counter);
  LoRa.print(" ");

  LoRa.print("GPS Data");

  LoRa.endPacket();


}
