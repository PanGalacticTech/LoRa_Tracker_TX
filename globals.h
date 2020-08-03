/*  Global Variables
 * 
 * 
 * 
 */

// Public Variables


// LoRa Packets

char callSign[] = {"SKY1"};

// These variables are packaged to send using LoRa library


char loraBuffer[64];   // buffer to write char string into for transmission


struct GPSlocationData{

float GPSlatitudeDeg;
float GPSlongitudeDeg;
float GPSaltitude;

  
};




int counter = 0;                      // Variable to number transmissions






//const char degreeMark = 176;   // when sprintf this value it prints a degree symbol // sprintf("%1cC)
const int degreeMark = 176;   // when sprintf this value it prints a degree symbol // sprintf("%1cC)

//"(char)247" degree symbol?


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~BME280~~~~~~~~~~~~~~~~~~~~~~~
float pressure = 0;
float humd;
float temp;
float altitude; 


float tempOffset = 2.50;   // Fudge value for temp offset. More testing to find a better solution or closer offset. Probably between 2.00 and 3.00 for now


bool notFirstTime = false;
bool firstTime = true;

int CO2;   // Buffer for CO2
int flipData = 0;

float last_humd;
float last_temp;








 // "Private" variables for GPS values

 // GPS Veriables - used to convert Floats to ints to use with sprintf

// Direct conversions from library

int16_t longitudePre;    // pre decimal point
int16_t longitudePost;   // post decimal point

int16_t latitudePre;
int16_t latitudePost;

int16_t longitudeDegPre;    // pre decimal point
int16_t longitudeDegPost;   // post decimal point

int16_t latitudeDegPre;
int16_t latitudeDegPost;

int16_t altitudePre;                  // Altitude is only in m so can just be cast to an int
int16_t altitudePost;

// calculated values and conversions

int16_t altitudeKmPre;
int16_t altitudeKmPost;


int16_t  speedKnotsPre;
int16_t  speedKnotsPost;


int16_t  speedmsPre;
int16_t  speedmsPost;

int16_t speedkmhPre;
int16_t speedkmhPost;

int16_t speedmphPre;
int16_t speedmphPost;


int16_t headingPre;
int16_t headingPost;
