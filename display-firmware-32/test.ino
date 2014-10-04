#include "application.h"

#include "Adafruit_mfGFX.h"   // Core graphics library
#include "RGBmatrixPanel.h" // Hardware-specific library
#include "math.h"

SYSTEM_MODE(MANUAL);

//#include "spark_disable_wlan.h"
//#include "spark_disable_cloud.h"



#if defined(SPARK)
 #define CLK D6
 #define OE  D7
 #define LAT A3
 #define A   A0
 #define B   A1
 #define C   A2
#else
 #define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
 #define LAT A3
 #define OE  9
 #define A   A0
 #define B   A1
 #define C   A2
#endif



// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false, 2);

// 32x32
//RGBmatrixPanel matrix(A, B, C, A4, CLK, LAT, OE, true, 2);


#define MILLISECONDS_BETWEEN_MESSAGES 5000

//about one 3 letter word per second
#define PIXELS_PER_CHARACTER 12.0
#define SECONDS_PER_CHARACTER ((1.0/5.0) * 1000.0)

//const char *msgText;
String *msgText;
int msgIndex = -1;
int xpos = 0;
int msgLen;
int textMin;
uint8_t pixelDelay = SECONDS_PER_CHARACTER / PIXELS_PER_CHARACTER;


//
//#define NUM_MESSAGES 2
//const char *messages[NUM_MESSAGES] = {
//    "Hi Dave!",
//    NULL
//};
//uint16_t colors[NUM_MESSAGES] = {
//    matrix.Color333(3,3,3),
//    matrix.Color333(1,3,3)
//};
//
//uint8_t fontSizes[NUM_MESSAGES] = { 2, 2 };
//


//void motdHandler(const char *event, const char *data)
//{
//    Serial.print("GOT ");
//    Serial.println(event);
//    Serial.println(data);
//
//    if (strcmp(event, "rgb_motd") == 0) {
//        messages[0] = data;
//    }
//    else if (strcmp(event, "rgb_bus_times") == 0) {
//        if (data == NULL) {
//            messages[1] = "No buses...";
//        }
//        else {
//            Serial.println("GOT BUS TIMES");
//            Serial.println(data);
//            messages[1] = data;
//        }
//
//    }
//    else if (strncmp(event, "Input", 5) == 0) {
//        messages[0] = data;
//        msgIndex = 0;
//        resetMessage();
//    }
////    else if (strncmp(event, "Temperature", ) == 0) {
////        messages[1] = (new String(String("It's ") + String(data) + String(" outside")))->c_str();
////    }
//}

void setup() {
    Serial.begin(115200);

    matrix.begin();
    matrix.setRotation(5);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(0, 0);   // start at top left, with one pixel of spacing

    //matrix.setTextWrap(false);
    //matrix.swapBuffers(false);

//    resetMessage();

//        Spark.subscribe("rgb_motd", motdHandler, MY_DEVICES);
//        Spark.subscribe("rgb_bus_times", motdHandler, MY_DEVICES);
//        Spark.subscribe("Input", motdHandler, MY_DEVICES);

//    WiFi.on();
//    Spark.connect();
}

//uint8_t resubscribe = 1;
uint16_t color = 0;

void loop() {
    //WiFi_Status_TypeDef status = WiFi.status();

/*
    if (resubscribe && (WiFi.status() == WIFI_ON)) {
        Spark.subscribe("rgb_motd", motdHandler, MY_DEVICES);
        Spark.subscribe("rgb_bus_times", motdHandler, MY_DEVICES);
        Spark.subscribe("Temperature", motdHandler, MY_DEVICES);

        resubscribe = 0;
    }
*/

xpos = matrix.width();
//uint16_t color = matrix.Color444(255, 0, 0);

//for(int x = 0; x < 2; x++ ) {
//    matrix.fillScreen(0);
//
//    for(int y = 0; y < 32; y++ ) {
//        //matrix.setCursor(4, 4);   // start at top left, with one pixel of spacing
//        //matrix.print(String(x) + " " + String(y));
//        matrix.drawPixel(x, y, color);
//        //matrix.swapBuffers(false);
//
////        if ((x % 4 == 0) && (y % 4 == 0)) {
////            Serial.println("x: " + String(x) + " y" + String(y));
////            delay(25);
////        }
//        delay(250);
//    }
//}
//
//
//for(int x = 30; x < 32; x++ ) {
//    matrix.fillScreen(0);
//
//    for(int y = 0; y < 32; y++ ) {
//        //matrix.setCursor(4, 4);   // start at top left, with one pixel of spacing
//        //matrix.print(String(x) + " " + String(y));
//        matrix.drawPixel(x, y, color);
//        //matrix.swapBuffers(false);
//
////        if ((x % 4 == 0) && (y % 4 == 0)) {
////            Serial.println("x: " + String(x) + " y" + String(y));
////            delay(25);
////        }
//        delay(250);
//    }
//}

    color++;
    if (color >= 255) {
        color = 0;
    }

    //not 444, not 888
    uint16_t colorVal = matrix.Color333(0, color, 0);

    matrix.fillScreen(0);
    for(int x = 0; x < 32; x++ ) {
        for(int y = 0; y < 32; y++ ) {

            colorVal = matrix.Color333(x, y, 0);
            matrix.drawPixel(x, y, colorVal);
            //delay(10);
        }
    }
    delay(5 * 1000);

    int counter = 0;
    for(int counter = 0; counter < 32768;counter++) {
        matrix.fillScreen(counter);
        delay(100);
    }


//    for(uint8_t r = 0;r<255;r++) {
//        for(uint8_t g = 0;g<255;g++) {
//            for(uint8_t b = 0;b<255;b++) {

                   //colorVal = matrix.Color333(r, 0, b);
//                   matrix.fillScreen(colorVal);
//                   delay(100);
//
////             }
//        }
//    }


    //end of loop

}



////
////  Update our message params, coordinates, sizes, etc.
////
//void resetMessage() {
//    //if we're out of bounds or the message is empty...
//    if ((msgIndex < 0) || (msgIndex >= NUM_MESSAGES) || (messages[msgIndex] == NULL))
//    {
//        Serial.println("resetting message counter to 0");
//        msgIndex = 0;
//    }
//
//    xpos = matrix.width();
//
//    //grab the raw char array of our message
//    //msgText = messages[msgIndex];
//
//
//    //figure out how many pixels long it is
//    msgLen = strlen(messages[msgIndex]);
//    textMin = msgLen * -12;
//    Serial.println("message length was " + String(msgLen));
//    Serial.println("textMin was " + String(textMin));
//
//    //Serial.println(*msgText);
//
//
//    // size 1 == 8 pixels high
//    // size 2 == ?
//    matrix.setTextSize(fontSizes[msgIndex]);
//    matrix.setTextColor(colors[msgIndex]);
//
//
//}
//
//void updateMarqueeText() {
//
//    //roll back to the first message
//    if ((msgIndex < 0) || (msgIndex >= NUM_MESSAGES) || (messages[msgIndex] == NULL))
//    {
//        Serial.println("updateMarqueeText msgIndex was below zero, or >= NUM_MESSAGES");
//        resetMessage();
//        delay(MILLISECONDS_BETWEEN_MESSAGES);
//    }
//
//    matrix.fillScreen(0);
//    matrix.setCursor(xpos, 0);   // start at top left, with one pixel of spacing
//    matrix.print(messages[msgIndex]);
//
//    if ((--xpos) < textMin) {
//        Serial.println("xpos "+String(xpos)+" was beyond textMin");
//        msgIndex++;
//        resetMessage();
//        delay(MILLISECONDS_BETWEEN_MESSAGES);
//    }
//
//    // Update display
//    matrix.swapBuffers(false);
//    delay(pixelDelay);
//}
