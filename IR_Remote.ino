//IR_Remote
unsigned long irCodes[] = {
0x41BEB04F,//right
0x41BED02F,//up
0x41BE40BF,//left
0x41BE609F,//down
0x41BEC03F,//enter
0x41BEF00F,//exit
0x41BE20DF,//slide show
0x41BE30CF,//menu
0x41BE906F,//rotate
0x41BE50AF,//zoom
0x41BE10EF,//pluse 
0x41BE708F//minus

//viso TV
//0x20DF10EF,  //tv power  
//0x20DF40BF,  //volume up
//0x20DFC03F,  //volume down 
//0x20DFF40B,  //source input 
//0x20DFC23D,  //menu 
//0x20DF00FF,  //channle up 
//0x20DF807F,  //channle down 
//0x20DF38C7,  //last 
//0x20DF58A7,  //input hdmi
//0x20DF6B94,  //input tv 
//0x20DF8A75,  //input av 
//0x20DF5AA5,  //input componint 
//0x20DFFF00  //unknow
//1 20DF8877
//2 20DF48B7
//3 20DFC837
//4 20DF28D7
//5 20DFA857
//6 20DF6897
//7 20DFE817
//8 20DF18E7
//9 20DF9867
//0 20DF08F7
};

//ir led must be connected to pin 3
#include <IRremote.h>
IRsend irsend;
int sendLight = 13;
int buttons[] = {2,4,5,6,7,8,9,10,11,12};
int buttonCount = 0;

void setup()
{
  pinMode(sendLight,OUTPUT);
  
  buttonCount = sizeof(buttons) / sizeof(int);  
  for (int i = 0; i < buttonCount; i++) 
  {
    pinMode (buttons[i], INPUT_PULLUP);
  }
  
  delay(2000);
  Serial.begin(9600);
  Serial.println(F("ready"));
}

bool readButton(int inputPin)
{
  return digitalRead(inputPin) == LOW;
}

void send(int codeIndex)
{
  digitalWrite(sendLight,HIGH);
  for (int i = 0; i < 2; i++) 
  {
    irsend.sendNEC(irCodes[codeIndex], 32);    
  }  
  digitalWrite(sendLight,LOW);
}

void loop()
{   
  for (int i = 0; i < buttonCount; i++) 
  {      
    if(readButton(buttons[i]))
    {
        Serial.print(buttons[i]);
        Serial.print(' ');
        send(i);      
    }
    delay(10);
  }
}
