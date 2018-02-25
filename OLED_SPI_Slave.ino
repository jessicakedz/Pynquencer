
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



// what to do with incoming data
volatile byte command = 0;
volatile byte dispword = 0;
volatile byte outbyte = 0; 
volatile byte inbyte = 0; 

volatile byte page = 0;
volatile byte instrument = 0;

void setup (void)
{
  Serial.begin(9600);  // output
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(SS, INPUT);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  //digitalWrite(MISO,LOW);
  digitalWrite(SS,LOW);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

  display.setTextSize(3);
  display.setTextColor(WHITE,BLACK); // the "BLACK" will clear old text underneath
  display.clearDisplay();
  // write out instrument names instead of of some number
  display.setCursor(0,0);
  display.println("Unknown");
  display.setCursor(0,40);
  display.println("Page: U");
    display.display();
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
    dispword=command;
    SPDR = outbyte;
    break;   
  case 1:
    outbyte=14;

    break;
  case 2:
    outbyte=24;

    break;
  default:

    break;

  } // end of switch

         
}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{

 /* Serial.print("CMD:");
  Serial.print(command, DEC);
  Serial.print(" page:");
  Serial.print(page, DEC);
  Serial.print(" instr:");
  Serial.println(instrument, DEC);
  */
    
  if (digitalRead (SS) == HIGH)
    command = 0;

  // received some valid numbers, change the display
  if (dispword != 0) {
    page = (dispword&0x0F);
    instrument = (dispword&0xF0)>>4;
    dispword = 0;
     display.clearDisplay();
     
  display.setCursor(0,0);
  display.println("Unknown");
  display.setCursor(0,40);
  display.println("Page: U");
  display.setCursor(0,0);
    switch (instrument){
        case 1:
            display.println("Kick   ");
         break;
        case 2:
            display.println("HIHat  ");
         break;
        case 3:
            display.println("Snare  ");
         break;
        case 4:
            display.println("Chord1 ");
         break;
        case 5:
            display.println("Chord2 ");
         break;
        case 14:
            display.println("PGM    ");
         break;
         case 15:
            display.println("RUN    ");
         break;
         default:
         break;      
    }

    display.setCursor(0,40);
    
    switch (page){
        case 1:
            display.println("Page: 1");
         break;
        case 2:
            display.println("Page: 2");
         break;
        case 3:
            display.println("Page: 3");
         break;
        case 4:
            display.println("Page: 4");
         break;

         default:
       
         break;      
    }
    display.display();
  }

}  // end of loop


