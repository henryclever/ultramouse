//Inputs 0 and 1 are used for communication with the Ping Sensors

//arduino pins connected to the 4 inputs of the BCD Decoder
int ledA = 2;
int ledB = 3;
int ledC = 4;
int ledD = 5;

//arduino pins connected to the 2 transistors of the display to run the common cathodes
int ledY = 6;
int ledX = 7;

// this constant won't change.  It's the pin number of the Ping sensor's output:
const int pingPinX = 8;
const int pingPinY = 9;

//arduino pins hacking into the mouse board
int msensorY1 = 10;
int msensorY2 = 11;
int msensorX2 = 12;
int msensorX1 = 13;

//arduino pins connected to the clicker inputs. Pins 14 and 17 are not used.
int clickpinX1 = 15;
int clickpinX2 = 16;
int clickpinY2 = 18;
int clickpinY1 = 19;

//These are other variables
int initialize = 50;
int upX2 = 50;
int downX2 = 50;
int upY2 = 50;
int downY2 = 50;
int upX, downX, upY, downY, displayX, displayY, point1X, point2X, point3X, point4X, point5X, point6X, point7X, point8X, point1Y, point2Y, point3Y, point4Y, point5Y, point6Y, point7Y, point8Y;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  //Let the arduino know which pins go where
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  
  pinMode(ledX, OUTPUT);
  pinMode(ledY, OUTPUT);
 
  pinMode(msensorX1, OUTPUT);
  pinMode(msensorX2, OUTPUT);
  pinMode(msensorY1, OUTPUT);
  pinMode(msensorY2, OUTPUT);
  
  pinMode(clickpinX1, INPUT);
  pinMode(clickpinX2, INPUT);
  pinMode(clickpinY1, INPUT);
  pinMode(clickpinY2, INPUT);
 
}

void loop()
{
  
    
//Here is the BCD Decoder Code. It uses pins 2, 3, 4, 5 for the decoder and 6, 7 for the two common cathodes

   //This sets the Display to a middle number of 5 upon startup
  if(initialize == 50){initialize++; displayX=5; displayY=5;}
  
   // establish variables for duration of the ping, and the distance result in inches and centimeters:
  long inchesX, cmX, inchesY, cmY;
 
  int constant = 0;
    //This reads the clickers for adjusting the range and display
    downX=digitalRead(clickpinX1);
    upX=digitalRead(clickpinX2);
    downY=digitalRead(clickpinY1);
    upY=digitalRead(clickpinY2);
  
    //This is for clicking the X range down
    if(downX==HIGH && downX2==50){displayX--; if(displayX < 1){displayX=1;} downX2++; delay(1);}
    else if(downX==LOW){downX2=50;}
    
    //This is for clicking the X range up
    if(upX==HIGH && upX2==50){displayX++; if(displayX > 9){displayX=9;} upX2++; delay(1);}
    else if(upX==LOW){upX2=50;}
  
    //This is for clicking the Y range down
    if(downY==HIGH && downY2==50){displayY--; if(displayY < 1){displayY = 1;} downY2++; delay(1);}
    else if(downY==LOW){downY2=50;}
  
    //This is for clicking the Y range up
    if(upY==HIGH && upY2==50){displayY++; if(displayY > 9){displayY = 9;} upY2++; delay(1);}
    else if(upY==LOW){upY2=50;}
    

//Here is the Ping Ultrasonic Code. It uses pin 8 for the x directions
    pinMode(pingPinX, OUTPUT);
    digitalWrite(pingPinX, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPinX, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPinX, LOW);
    pinMode(pingPinX, INPUT);
    unsigned long durationX = pulseIn(pingPinX, HIGH);
    if(durationX > 4000){durationX=4000;}
    delayMicroseconds(4000-durationX);
 
//Here is the Ping Ultrasonic Code. It uses pin 9 for the y directions   
    pinMode(pingPinY, OUTPUT);
    digitalWrite(pingPinY, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPinY, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPinY, LOW);
    pinMode(pingPinY, INPUT);
    unsigned long durationY = pulseIn(pingPinY, HIGH);
    if(durationY > 4000){durationY=4000;}
    delayMicroseconds(4000-durationY);
    
    // convert the time into a distance
    inchesX = microsecondsToInches(durationX);
    cmX = microsecondsToCentimeters(durationX);
  
 //This is for the PS2 mouse hack
    //various x ranges
     if(displayX==1){point1X=100; point2X=845; point3X=855; point4X=865; point5X=935; point6X=945; point7X=955; point8X=3000;}
else if(displayX==2){point1X=100; point2X=805; point3X=820; point4X=845; point5X=955; point6X=970; point7X=985; point8X=3000;}
else if(displayX==3){point1X=100; point2X=775; point3X=800; point4X=825; point5X=975; point6X=1000; point7X=1025; point8X=3000;}
else if(displayX==4){point1X=100; point2X=725; point3X=775; point4X=825; point5X=975; point6X=1025; point7X=1075; point8X=3000;}
else if(displayX==5){point1X=100; point2X=650; point3X=725; point4X=800; point5X=1000; point6X=1075; point7X=1150; point8X=3000;}
else if(displayX==6){point1X=100; point2X=600; point3X=700; point4X=800; point5X=1000; point6X=1100; point7X=1200; point8X=3000;}
else if(displayX==7){point1X=100; point2X=525; point3X=650; point4X=775; point5X=1025; point6X=1150; point7X=1275; point8X=3000;}
else if(displayX==8){point1X=100; point2X=475; point3X=625; point4X=775; point5X=1025; point6X=1175; point7X=1325; point8X=3000;}
else if(displayX==9){point1X=100; point2X=400; point3X=575; point4X=750; point5X=1050; point6X=1225; point7X=1400; point8X=3000;}


    //this moves the cursor in the x-direction at various speeds
    int count=1;
    
    while(durationX >= point1X && durationX < point2X && count <= 3)
     {digitalWrite(msensorX2, HIGH); delayMicroseconds(100); digitalWrite(msensorX1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX2, LOW); delayMicroseconds(100); digitalWrite(msensorX1, LOW); delayMicroseconds(100); count++;}
      
    while(durationX >= point2X && durationX < point3X && count <= 2)
     {digitalWrite(msensorX2, HIGH); delayMicroseconds(100); digitalWrite(msensorX1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX2, LOW); delayMicroseconds(100); digitalWrite(msensorX1, LOW); delayMicroseconds(100); count++;}
      
    while(durationX >= point3X && durationX < point4X && count <= 1)
     {digitalWrite(msensorX2, HIGH); delayMicroseconds(100); digitalWrite(msensorX1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX2, LOW); delayMicroseconds(100); digitalWrite(msensorX1, LOW); delayMicroseconds(100); count++;}
      
    while(durationX >= point4X && durationY < point5X && count <= 1)
     {delayMicroseconds(400); count++;}
  
    while(durationX >= point5X && durationX < point6X && count <= 1)
     {digitalWrite(msensorX1, HIGH); delayMicroseconds(100); digitalWrite(msensorX2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX1, LOW); delayMicroseconds(100); digitalWrite(msensorX2, LOW); delayMicroseconds(100); count++;}
     
    while(durationX >= point6X && durationX < point7X && count <= 2)
     {digitalWrite(msensorX1, HIGH); delayMicroseconds(100); digitalWrite(msensorX2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX1, LOW); delayMicroseconds(100); digitalWrite(msensorX2, LOW); delayMicroseconds(100); count++;}
      
    while(durationX >= point7X && durationX < point8X && count <= 3)
     {digitalWrite(msensorX1, HIGH); delayMicroseconds(100); digitalWrite(msensorX2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorX1, LOW); delayMicroseconds(100); digitalWrite(msensorX2, LOW); delayMicroseconds(100); count++;}
    
   //various X ranges
     if(displayY==1){point1Y=100; point2Y=845; point3Y=855; point4Y=865; point5Y=935; point6Y=945; point7Y=955; point8Y=3000;}
else if(displayY==2){point1Y=100; point2Y=805; point3Y=820; point4Y=845; point5Y=955; point6Y=970; point7Y=985; point8Y=3000;}
else if(displayY==3){point1Y=100; point2Y=775; point3Y=800; point4Y=825; point5Y=975; point6Y=1000; point7Y=1025; point8Y=3000;}
else if(displayY==4){point1Y=100; point2Y=725; point3Y=775; point4Y=825; point5Y=975; point6Y=1025; point7Y=1075; point8Y=3000;}
else if(displayY==5){point1Y=100; point2Y=650; point3Y=725; point4Y=800; point5Y=1000; point6Y=1075; point7Y=1150; point8Y=3000;}
else if(displayY==6){point1Y=100; point2Y=600; point3Y=700; point4Y=800; point5Y=1000; point6Y=1100; point7Y=1200; point8Y=3000;}
else if(displayY==7){point1Y=100; point2Y=525; point3Y=650; point4Y=775; point5Y=1025; point6Y=1150; point7Y=1275; point8Y=3000;}
else if(displayY==8){point1Y=100; point2Y=475; point3Y=625; point4Y=775; point5Y=1025; point6Y=1175; point7Y=1325; point8Y=3000;}
else if(displayY==9){point1Y=100; point2Y=400; point3Y=575; point4Y=750; point5Y=1050; point6Y=1225; point7Y=1400; point8Y=3000;}

     
   //various mouse movement speeds
    count=1;
    
    while(durationY >= point1Y && durationY < point2Y && count <= 3)
     {digitalWrite(msensorY2, HIGH); delayMicroseconds(100); digitalWrite(msensorY1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY2, LOW); delayMicroseconds(100); digitalWrite(msensorY1, LOW); delayMicroseconds(100); count++;}
      
    while(durationY >= point2Y && durationY < point3Y && count <= 2)
     {digitalWrite(msensorY2, HIGH); delayMicroseconds(100); digitalWrite(msensorY1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY2, LOW); delayMicroseconds(100); digitalWrite(msensorY1, LOW); delayMicroseconds(100); count++;}
      
    while(durationY >= point3Y && durationY < point4Y && count <= 1)
     {digitalWrite(msensorY2, HIGH); delayMicroseconds(100); digitalWrite(msensorY1, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY2, LOW); delayMicroseconds(100); digitalWrite(msensorY1, LOW); delayMicroseconds(100); count++;}
      
    while(durationY >= point4Y && durationY < point5Y && count <= 1)
     {delayMicroseconds(400); count++;}
  
    while(durationY >= point5Y && durationY < point6Y && count <= 1)
     {digitalWrite(msensorY1, HIGH); delayMicroseconds(100); digitalWrite(msensorY2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY1, LOW); delayMicroseconds(100); digitalWrite(msensorY2, LOW); delayMicroseconds(100); count++;}
     
    while(durationY >= point6Y && durationY < point7Y && count <= 2)
     {digitalWrite(msensorY1, HIGH); delayMicroseconds(100); digitalWrite(msensorY2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY1, LOW); delayMicroseconds(100); digitalWrite(msensorY2, LOW); delayMicroseconds(100); count++;}
      
    while(durationY >= point7Y && durationY < point8Y && count <= 3)
     {digitalWrite(msensorY1, HIGH); delayMicroseconds(100); digitalWrite(msensorY2, HIGH); delayMicroseconds(100);
      digitalWrite(msensorY1, LOW); delayMicroseconds(100); digitalWrite(msensorY2, LOW); delayMicroseconds(100); count++;}
   

 //multiplex the display. An extra set of 'plexes' is added to slow down the movement of the cursor. Delays factor in the delay of the sensors.
 if(durationX < 3000 && durationY < 3000){digitalWrite(ledX, LOW); Display(displayY); digitalWrite(ledY, HIGH);}
 else{digitalWrite(ledY, LOW); Display(constant); digitalWrite(ledX, LOW);}
 delay(8);

 if(durationX < 3000 && durationY < 3000){digitalWrite(ledY, LOW); Display(displayX); digitalWrite(ledX, HIGH);}
 else{digitalWrite(ledY, LOW); Display(constant); digitalWrite(ledX, LOW);}
 delay(8);
    
 if(durationX < 3000 && durationY < 3000){digitalWrite(ledX, LOW); Display(displayY); digitalWrite(ledY, HIGH);}
 else{digitalWrite(ledY, LOW); Display(constant); digitalWrite(ledX, LOW);}
 delay(8);
 
 if(durationX < 3000 && durationY < 3000){digitalWrite(ledY, LOW); Display(displayX); digitalWrite(ledX, HIGH);}
 else{digitalWrite(ledY, LOW); Display(constant); digitalWrite(ledX, LOW);}
    
 
  //  Serial.print(durationX);
  //  Serial.print(" x-microseconds, ");
  //  Serial.print(durationY);
  //  Serial.print(" y-microseconds ");
  //  Serial.println();
}


//This function converts microseconds to inches
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second).  This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
long microsecondsToInches(long microseconds){return microseconds / 74 / 2;}

//This function converts microseconds to centimeters
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
long microsecondsToCentimeters(long microseconds){return microseconds / 29 / 2;}

//This function converts a digit into a Base 2 code for the BCD decoder
void Display(int n) {
  if (n == 0) {digitalWrite(ledA, LOW); digitalWrite(ledB, LOW); digitalWrite(ledC, LOW); digitalWrite(ledD, LOW);}
  else if (n == 1) {digitalWrite(ledA, HIGH); digitalWrite(ledB, LOW); digitalWrite(ledC, LOW); digitalWrite(ledD, LOW);}
  else if (n == 2) {digitalWrite(ledA, LOW); digitalWrite(ledB, HIGH); digitalWrite(ledC, LOW); digitalWrite(ledD, LOW);}
  else if (n == 3) {digitalWrite(ledA, HIGH); digitalWrite(ledB, HIGH); digitalWrite(ledC, LOW); digitalWrite(ledD, LOW);}
  else if (n == 4) {digitalWrite(ledA, LOW); digitalWrite(ledB, LOW); digitalWrite(ledC, HIGH); digitalWrite(ledD, LOW);}
  else if (n == 5) {digitalWrite(ledA, HIGH); digitalWrite(ledB, LOW); digitalWrite(ledC, HIGH); digitalWrite(ledD, LOW);}
  else if (n == 6) {digitalWrite(ledA, LOW); digitalWrite(ledB, HIGH); digitalWrite(ledC, HIGH); digitalWrite(ledD, LOW);}
  else if (n == 7) {digitalWrite(ledA, HIGH); digitalWrite(ledB, HIGH); digitalWrite(ledC, HIGH); digitalWrite(ledD, LOW);}
  else if (n == 8) {digitalWrite(ledA, LOW); digitalWrite(ledB, LOW); digitalWrite(ledC, LOW); digitalWrite(ledD, HIGH);}
  else if (n == 9) {digitalWrite(ledA, HIGH); digitalWrite(ledB, LOW); digitalWrite(ledC, LOW); digitalWrite(ledD, HIGH);}
}

