
/*
 *  Data Types for Parsing
 * 
 * 
 * 
 */

/*

  uint8_t hour;          ///< GMT hours
  uint8_t minute;        ///< GMT minutes
  uint8_t seconds;       ///< GMT seconds
  uint16_t milliseconds; ///< GMT milliseconds
  uint8_t year;          ///< GMT year
  uint8_t month;         ///< GMT month
  uint8_t day;           ///< GMT day

  nmea_float_t latitude;  ///< Floating point latitude value in degrees/minutes
                          ///< as received from the GPS (DDMM.MMMM)
  nmea_float_t longitude; ///< Floating point longitude value in degrees/minutes
                          ///< as received from the GPS (DDDMM.MMMM)

 Fixed point latitude and longitude value with degrees stored in units of
    1/10000000 of a degree. See pull #13 for more details:
    https://github.com/adafruit/Adafruit-GPS-Library/pull/13 
  int32_t latitude_fixed;  ///< Fixed point latitude in decimal degrees.
                           ///< Divide by 10000000.0 to get a double.
  int32_t longitude_fixed; ///< Fixed point longitude in decimal degrees
                           ///< Divide by 10000000.0 to get a double.

  nmea_float_t latitudeDegrees;  ///< Latitude in decimal degrees
  nmea_float_t longitudeDegrees; ///< Longitude in decimal degrees
  nmea_float_t geoidheight;      ///< Diff between geoid height and WGS84 height
  nmea_float_t altitude;         ///< Altitude in meters above MSL
  nmea_float_t speed;            ///< Current speed over ground in knots
  nmea_float_t angle;            ///< Course in degrees from true north
  nmea_float_t magvariation; ///< Magnetic variation in degrees (vs. true north)
  nmea_float_t HDOP; ///< Horizontal Dilution of Precision - relative accuracy
                     ///< of horizontal position
  nmea_float_t VDOP; ///< Vertical Dilution of Precision - relative accuracy
                     ///< of vertical position
  nmea_float_t PDOP; ///< Position Dilution of Precision - Complex maths derives
                     ///< a simple, single number for each kind of DOP
  char lat = 'X';    ///< N/S
  char lon = 'X';    ///< E/W
  char mag = 'X';    ///< Magnetic variation direction
  bool fix;          ///< Have a fix?
  uint8_t fixquality;    ///< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
  uint8_t fixquality_3d; ///< 3D fix quality (1, 3, 3 = Nofix, 2D fix, 3D fix)
  uint8_t satellites;    ///< Number of satellites in use

  uint16_t LOCUS_serial;  ///< Log serial number
  uint16_t LOCUS_records; ///< Log number of data record
  uint8_t LOCUS_type;     ///< Log type, 0: Overlap, 1: FullStop
  uint8_t LOCUS_mode;     ///< Logging mode, 0x08 interval logger
  uint8_t LOCUS_config;   ///< Contents of configuration
  uint8_t LOCUS_interval; ///< Interval setting
  uint8_t LOCUS_distance; ///< Distance setting
  uint8_t LOCUS_speed;    ///< Speed setting
  uint8_t LOCUS_status;   ///< 0: Logging, 1: Stop logging
  uint8_t LOCUS_percent;  ///< Log life used percentage




  */
