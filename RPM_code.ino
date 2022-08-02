/* This code is tweaked by Navanudi LLP. The source Code is by miliohm.com.*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

float rpm1 = 0;
float rpm2 = 0;

int pid;
unsigned long millisBefore;
volatile int holes1;
volatile int holes2;

int page_counter=1 ;
int up = 8;               //Up button
int down = 10;           //Down button

boolean current_up = LOW;          
boolean last_up=LOW;            
boolean last_down = LOW;
boolean current_down = LOW;

boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Speed Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Test");
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), count1, FALLING);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
  delay(1000);
  lcd.clear();
}

void loop()
{
  
  if (millis() - millisBefore > 1000) {
    rpm1 = (holes1 / 12.0)*60;
    holes1 = 0;
    rpm2 = (holes2 / 12.0)*60;
    holes2 = 0;
    millisBefore = millis();
  }
  delay(100);



current_up = debounce(last_up, up);         
current_down = debounce(last_down, down);   



    if (last_up== LOW && current_up == HIGH){  
      lcd.clear();                       
      if(page_counter <2){              
      page_counter= page_counter +1;   
      
      }
      else{
      page_counter= 2;  
      }
  }
  
    last_up = current_up;


    if (last_down== LOW && current_down == HIGH){ 
      lcd.clear();                         
      if(page_counter >1){              
      page_counter= page_counter -1;   
      
      }
      else{
      page_counter= 1;  
      }
  }
    
    last_down = current_down;


  switch (page_counter) {
   
    case 1:{  
      lcd.setCursor(0, 0);
      lcd.print("Motor 1 : ");
      lcd.print(rpm1);
      lcd.print("    ");
    }
    break;

    case 2: { 
      lcd.setCursor(0, 0);
      lcd.print("Motor 2 : ");
      lcd.print(rpm2);
      lcd.print("    ");
    }
    break;
    
  }
  
}


void count1() {
  holes1++;
}

void count2() {
  holes2++;
}
