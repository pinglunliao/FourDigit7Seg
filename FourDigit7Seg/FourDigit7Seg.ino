/*
 * Random String & Numbers for 4-Digit 7-segment LED Display
 * 4-Digit 7-segment LED Display Type: HS420561K
 * Bipolar junction transistor Type: 2N2222
 * 
 * References: 
 * 1. http://coopermaa2nd.blogspot.tw/2011/01/arduino-lab15.html
 * 2. http://learn.parallax.com/4-digit-7-segment-led-display-arduino-demo
 * 3. http://samuelmh.com/arduino/arduino-smh_7sd/
 */

/*
 * A 7 SEGEMENT DISPLAY:
 *  This is the layout of a S.S.D.
 *        a
 *     +-----+
 *     |     |
 *   f |  g  | b
 *     +-----+
 *   e |     | c
 *     |     |
 *     +-----+  0
 *        d     dp
 *
 */
 
// 4-Digit 7-segment LED Display Pins
#define ASeg 5
#define BSeg 7
#define CSeg 4
#define DSeg 11
#define ESeg 10
#define FSeg 3
#define GSeg 6
#define DpSeg 2

// Bipolar junction transistor Pins
#define CA1 13
#define CA2 12
#define CA3 9
#define CA4 8

// define the LED digit pins
byte segs[8] = { ASeg, BSeg, CSeg, DSeg, ESeg, FSeg, GSeg, DpSeg };

// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                Mapping to       a,b,c,d,e,f,g,dp of Seven-Segment LED
byte numbers[10][8] = { { 1,1,1,1,1,1,0,0 },  // = 0
                        { 0,1,1,0,0,0,0,0 },  // = 1
                        { 1,1,0,1,1,0,1,0 },  // = 2
                        { 1,1,1,1,0,0,1,0 },  // = 3
                        { 0,1,1,0,0,1,1,0 },  // = 4
                        { 1,0,1,1,0,1,1,0 },  // = 5
                        { 1,0,1,1,1,1,1,0 },  // = 6
                        { 1,1,1,0,0,0,0,0 },  // = 7
                        { 1,1,1,1,1,1,1,0 },  // = 8
                        { 1,1,1,1,0,1,1,0 }   // = 9
                             }; 

// define the LED digit patterns, from A - Z
// 1 = LED on, 0 = LED off, in this order:
//                Mapping to       a,b,c,d,e,f,g,dp of Seven-Segment LED
byte letters[27][8] = { { 1,1,1,0,1,1,1,0 },   // = A
                        { 0,0,1,1,1,1,1,0 },   // = B
                        { 1,0,0,1,1,1,0,0 },   // = C
                        { 0,1,1,1,1,0,1,0 },   // = D
                        { 1,0,0,1,1,1,1,0 },   // = E
                        { 1,0,0,0,1,1,1,0 },   // = F
                        { 1,0,1,1,1,1,0,0 },   // = G
                        { 0,1,1,0,1,1,1,0 },   // = H
                        { 0,1,1,0,0,0,0,0 },   // = I
                        { 0,1,1,1,1,0,0,0 },   // = J
                        { 0,1,0,1,1,1,1,1 },   // = K
                        { 0,0,0,1,1,1,0,0 },   // = L
                        { 1,1,1,0,1,1,0,1 },   // = M
                        { 0,0,1,0,1,0,1,0 },   // = N
                        { 1,1,1,1,1,1,0,0 },   // = O
                        { 1,1,0,0,1,1,1,0 },   // = P
                        { 1,1,1,0,0,1,1,0 },   // = Q
                        { 0,0,0,0,1,0,1,0 },   // = R
                        { 1,0,1,1,0,1,1,0 },   // = S
                        { 0,0,0,1,1,1,1,0 },   // = T
                        { 0,1,1,1,1,1,0,0 },   // = U
                        { 0,0,1,1,1,0,0,0 },   // = V
                        { 1,1,1,1,0,0,1,1 },   // = W
                        { 0,0,1,1,0,0,1,1 },   // = X
                        { 0,1,1,1,0,1,1,0 },   // = Y
                        { 1,1,0,1,1,0,1,0 },   // = Z
                        { 0,0,0,0,0,0,0,0 }    // = ' ' (white space)
                             }; 

// Default: 1ms 
int delay_time = 1;

const int DEMO_CNT = 3;
char demoLetters[4] = { ' ', ' ', ' ', ' ' };
int demoNumbers[4] = { 0, 0, 0, 0 };

void setup() {
  pinMode(ASeg, OUTPUT);
  pinMode(BSeg, OUTPUT);
  pinMode(CSeg, OUTPUT);
  pinMode(DSeg, OUTPUT);
  pinMode(ESeg, OUTPUT);
  pinMode(FSeg, OUTPUT);
  pinMode(GSeg, OUTPUT);
  pinMode(DpSeg, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  pinMode(CA3, OUTPUT);
  pinMode(CA4, OUTPUT);
}
 
void loop() {
  unsigned long startTime;

  clearSreeen(1000);
  for (unsigned int cnt = 0; cnt < DEMO_CNT; cnt++) {
    rndNumbers();
    startTime = millis();
    for (unsigned long elapsed=0; elapsed < 1000; elapsed = millis() - startTime) {
      // Multiplexing for displaying the 4-digits (Right-to-Left)
      for(int i = 0; i < 4; i++) {
        prtNumber(i, demoNumbers[i]);
        delay(delay_time);
      }
    }    
  }

  clearSreeen(1000);
  for (unsigned int cnt = 0; cnt < DEMO_CNT; cnt++) {
    rndLetters();
    unsigned long startTime = millis();
    for (unsigned long elapsed=0; elapsed < 1000; elapsed = millis() - startTime) {
      // Multiplexing for displaying the 4-digits (Right-to-Left)
      for(int i = 0; i < 4; i++) {
        prtChar(i, demoLetters[i]);
        delay(delay_time);
      }
    }
  }
}

void pickDigit(int x) {
  digitalWrite(CA1, LOW);
  digitalWrite(CA2, LOW);
  digitalWrite(CA3, LOW);
  digitalWrite(CA4, LOW);
 
  switch(x) {
    case 0: digitalWrite(CA1, HIGH); break;
    case 1: digitalWrite(CA2, HIGH); break;
    case 2: digitalWrite(CA3, HIGH); break;
    case 3: digitalWrite(CA4, HIGH); break;    
  }
}

void prtNumber(int d, byte number) {
   pickDigit(d);
   displayNumbers(number);  
} 

void displayNumbers(byte number) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segs[i], numbers[number][i]);
  }
}

void prtChar(int d, char ch) {
  pickDigit(d);
  int chIndex = 0;

  if( 65 <= ch && ch <= 90 )  // Upper letter
    chIndex = ch - 65;
  else if( 97 <= ch && ch <= 122 )  // Lower letter
    chIndex = ch - 97;
  else
    chIndex = 26;  // white space

  for (int i = 0; i < 8; i++) {
    digitalWrite(segs[i], letters[chIndex][i]);
  }
}

void rndNumbers() {
  for(int i = 0; i < 4; i ++)
    demoNumbers[i] = random(0, 9);
}

void rndLetters() {
    for(int i = 0; i < 4; i ++)
      demoLetters[i] = random('A', 'Z');
}

void clearSreeen(int delayTime) {
  unsigned long startTime = millis();
  for (unsigned long elapsed=0; elapsed < delayTime; elapsed = millis() - startTime) {
    // Multiplexing for displaying the 4-digits (Right-to-Left)
    for(int i = 0; i < 4; i++) {
      prtChar(i, demoLetters[26]);
      delay(delay_time);
    }
  }
}
