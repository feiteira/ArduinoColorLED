#define DEBUG 0

#define MAX_BRIGHT 100

int ledR= 16;// the PWM pin the LED is attached to
int ledG= 14;// the PWM pin the LED is attached to
int ledB= 12;// the PWM pin the LED is attached to

const int RGB_VALUES [] = {0,86,172,255};

int COLOR_CIRCLE[1024][3];

int in = A0;

int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by


void init_circle(){
  // 0 - 341 yellow - red
  for(int i = 0; i < 342; i++){
    COLOR_CIRCLE[i][0] = 255; 
    COLOR_CIRCLE[i][1] = 255 - (256 * i) / 342; 
    COLOR_CIRCLE[i][2] = 0; 
  }
  // 342 - 682 red - blue
  int i;
  for(int j = 342; j < 682; j++){
    i = j - 342;
    COLOR_CIRCLE[j][0] = 255 - (256 * i) / 342; 
    COLOR_CIRCLE[j][1] = 0; 
    COLOR_CIRCLE[j][2] = (256 * i) / 342; 
  }
  // 682 - 853 blue - green
  for(int j = 682; j < 854; j++){
    i = j - 682;
    COLOR_CIRCLE[j][0] = 0; 
    COLOR_CIRCLE[j][1] = (256 * i) / 172; 
    COLOR_CIRCLE[j][2] = 255 - (256 * i) / 172; 
  }
  // 854 - 1023
  for(int j = 854; j < 1024; j++){
    i = j - 854;
    COLOR_CIRCLE[j][0] = (256 * i) / 170; 
    COLOR_CIRCLE[j][1] = 255; 
    COLOR_CIRCLE[j][2] = 0; 
  }
  
}

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
 // pinMode(in, INPUT);
  Serial.begin(9600);
  init_circle();
}

void setColor(int r,int g, int b){
   analogWrite(ledR, r);
   analogWrite(ledG, g);
   analogWrite(ledB, b);
}
void setColorPos(int pos,int bright){
   pos = pos % 1024;
   analogWrite(ledR, (COLOR_CIRCLE[pos][0] * bright) / 255);
   analogWrite(ledG, (COLOR_CIRCLE[pos][1] * bright) / 255);
   analogWrite(ledB, (COLOR_CIRCLE[pos][2] * bright) / 255);

}

int counter = 0;

void loop() {
  ++counter;  
  brightness = brightness + fadeAmount;
  int val = analogRead(in);    
  Serial.println(val);
  if(val == 1024){
        setColorPos(counter,MAX_BRIGHT);
  }else{
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= MAX_BRIGHT) {
      fadeAmount = -fadeAmount;
    }
    setColorPos(val,brightness);
  }
  
  // wait for 30 milliseconds to see the dimming effect
  delay(25);
}
