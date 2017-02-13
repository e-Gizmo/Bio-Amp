//***********************************************************************************//
//    ECG Monitor Using gizDuino and Bio-Amp DEMO CODE                     //
//                                                                                   //
//  This sketch is used to connect the e-Gizmo Bio-Amp kit interface with gizDuino   //
// microcontroller(Arduino Compatible) through Bluetooth wireless communication to   //
// send signal data in Bluetooth terminal/Graphics app  display by using your        //
// Smart/Android phone.                                                              //
//                                                                                   //
// Bluetooth Terminal/Graphics app                                                   //
// https://play.google.com/store/apps/details?id=com.emrctn.BluetoothGraphics&hl=en  //
//                                                                                   //
//                                                                                   //
//                                                                                   //
//                    Created by e-Gizmo Mechatronix Central                         //
//         September 3, 2016                                   //
//                     http://www.e-gizmo.com                              //
//                                                                                   //
//***********************************************************************************//


float data1=1.25;

#define RATE 3      // specify sampling rate in ms. Set to 3ms in this example
#define SR 62.5*RATE


void setup() {

  Serial.begin(115200);   // Set up Serial for 115.2 kbaud speed

  //Timer 1
  // Timer 1 interrupt service is used exclusively for data acquisition in order 
  // to achieve a uniform sample rate
  // That means you cannot not use functions and libraries that also uses timer1 
  // like the servo library
  
   // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = SR;            // set to run at above specified sampling rate
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}



void loop() {

// This sample program is interrupt driven, it automatically
// send the sampled Bio-Amp ADC converted signal to the serial port.

}

void readADC()
{

  data1= (analogRead(A0)*0.00488); // Sample Bio-Amp analog signal
}

// Timer 1 interrupt, automatically serviced every RATE ms.

ISR(TIMER_COMPA_vect) 
{
  //Serial printing for 1 value (data1 variables)
  Serial.print("E");
  readADC();
  Serial.print(data1);
  Serial.print ("\n");
}
