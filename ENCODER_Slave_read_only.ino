/*#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x3f,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack
*/

// what to do with incoming data
volatile byte command = 0;
volatile byte outbyte = 0; 
volatile byte inbyte = 0; 



// usually the rotary encoders three pins have the ground pin in the middle
enum PinAssignments {
  encoderPinA = 18,   // rigth
  encoderPinB =19,   // left
  clearButton1 = 20,    // another two pins
  encoderPinC = 7,   // rigth
  encoderPinD = 8,   // left
  clearButton2 = 9   // another two pins
  
};
static int count1=0;
static int getdir1=0;
static int count2=0;
static int getdir2=0;
static int dataval=0;

void setup (void)
{
  /*
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  */
  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  pinMode(clearButton1, INPUT);
 // turn on pullup resistors
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);
  digitalWrite(clearButton1, HIGH);


  pinMode(encoderPinC, INPUT); 
  pinMode(encoderPinD, INPUT); 
  pinMode(clearButton2, INPUT);
 // turn on pullup resistors
  digitalWrite(encoderPinC, HIGH);
  digitalWrite(encoderPinD, HIGH);
  digitalWrite(clearButton2, HIGH);
  
    Serial.begin(9600);  // output
  
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(SS, INPUT);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  //digitalWrite(MISO,LOW);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);
   
}  // end of setup

// SPI interrupt routine
ISR (SPI_STC_vect)
{
    inbyte = SPDR;
    
  switch (command)
  {
  // no command? then this is the command
  case 0:
    command = inbyte;
    SPDR = outbyte;
    break;   
  case 1:
    outbyte=count1;

    break;
  case 2:
    outbyte=count2;

    break;
  default:

    break;

  } // end of switch

         
}  // end of interrupt service routine (ISR) SPI_STC_vect

/*
void update_lcd(int vlaues){

    lcd.home (); // set cursor to 0,0
    lcd.print("ENC1:"); 
    lcd.print(count1);
    lcd.setCursor (0,1);        // go to start of 2nd line
    //lcd.print(millis());
    lcd.print("ENC2:"); 
    lcd.print(count2);

}
*/
void loop (void)
{

   int clrval1=0,A=0,B=0;
   int clrval2=0,C=0,D=0;
   
  if (digitalRead (SS) == HIGH)
    command = 0;
  /*-----SPI command switch ------------------------------------------
  if (dataval==0 && command>0 ){

    switch (command){
  
        case 0:
         command=0;
         dataval=0;
        break;
        
        case 1: 
          outbyte=count1;
               command=0;
                  Serial.println(count1);
        break;
        
        case 2:
          outbyte=count2;
              command=0;
     Serial.println(count2);
        break;

        default:
              dataval=0;
              command=0;
        break;
        
      }
  }
Serial.print(
   ---------------------------------------------------*/

    /*------rotary encoder--------------------------------------*/

    Serial.print(count1);
    Serial.print(" ");
    Serial.print(count2);

        Serial.print(" ");
    Serial.print(C);

        Serial.print(" ");
    Serial.print(D);
    Serial.println();
    
    
           clrval1=digitalRead(clearButton1) ;
            A=digitalRead(encoderPinA);
            B=digitalRead(encoderPinB);

            
            if ( A && !B && getdir1 ){
                count1=count1+1;
                A=0;B=0;getdir1=0;
            }
            else if( !A && B && getdir1){
                count1=count1-1;
                A=0;B=0;getdir1=0;
            }
            else if(!A && !B){
                //ready to step, next get dir
                getdir1=1;
            }
            else if(A && B){
                getdir1=0;               
            }
            else{
                count1=count1;
                A=0;B=0;                
            }

            if(clrval1==0)
              count1=0;
             
            A=0;B=0;   

// second encoder


            clrval2=digitalRead(clearButton2) ;
            C=digitalRead(encoderPinC);
            D=digitalRead(encoderPinD);

            
            if ( C && !D && getdir2 ){
                count2=count2+1;
                C=0;D=0;getdir2=0;
            }
            else if( !C && D && getdir2){
                count2=count2-1;
                C=0;D=0;getdir2=0;
            }
            else if(!C && !D){
                //ready to step, next get dir
                getdir2=1;
            }
            else if(C && D){
                getdir2=0;               
            }
            else{
                count2=count2;
                C=0;D=0;                
            }

            if(clrval2==0)
              count2=0;
             
            C=0;D=0;   




}  // end of loop



