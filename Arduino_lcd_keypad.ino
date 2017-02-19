#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27,20,4);

int sayac;
char array_tc[13];
const byte SATIR = 4; 
const byte SUTUN= 3; 

char keys[SATIR][SUTUN] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};



byte rowPins[SATIR] = { 9, 8, 7, 6 };
byte colPins[SUTUN] = { 12, 11, 10 }; 


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, SATIR, SUTUN );


void setup(){
  
  lcd.init();                      
  lcd.backlight();
 
  sayac=0; 
  
  lcd.begin(16,2);
  lcd.print("TC KIMLIK NO GIR");
  lcd.setCursor(sayac+3, 1); 
  lcd.blink();

  Serial.begin(9600);
     
}


void loop()
{
 
 char key = kpd.getKey();

  if(key){
   switch (key) {
   case '#':
        if (sayac  == 11 ) {
          array_tc[12] = 0x0D; 
          array_tc[0] = 0x02; 
          Serial.print(array_tc); 
          lcd.clear();
          lcd.print("   GONDERILDI   ");
          delay(1000);
          lcd.clear();
          lcd.print("TC KIMLIK NO GIR");
          sayac =0;  
          lcd.setCursor(sayac+3, 1); 
          memset(array_tc, 0, sizeof(array_tc));
        }
        break;
   case '*':
        lcd.clear();
        sayac=0;
        lcd.print("TC KIMLIK NO GIR");
        memset(array_tc, 0, sizeof(array_tc));
        lcd.setCursor(sayac+3, 1); 
        break;
   default:
       if (sayac  < 11 ) {
         lcd.setCursor(sayac+3, 1); 
         array_tc[sayac+1]=key;
         lcd.print(key);  
         //Serial.print(sayac);
         sayac++; 
       }
    } //case 
  } // if
}
