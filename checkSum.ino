
/*


  Implementing NMEA Checksum

*/





int checksum(const char *s) {
  int c = 0;

  while (*s)
    c ^= *s++;

  return c;
}







int nmeaChecksum(char *nmea_data) {
  int crc = 0;
  int i;

  // the first $ sign and the last two bytes of original CRC + the * sign
  for (i = 1; i < strlen(nmea_data) - 3; i ++) {
    crc ^= nmea_data[i];
  }
  Serial.print("CheckSum CRC: ");
  Serial.println(crc);
  return crc;
}
