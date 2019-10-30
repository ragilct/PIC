/*
Project: Diode and Transistor Tester
Internal Oscillator @ 4MHz, MCLR Enabled, PWRT Enabled, WDT OFF
Copyright @ Rajendra Bhatt
November 9, 2010
*/
// LCD module connections
sbit LCD_RS at RC4_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D4 at RC0_bit;
sbit LCD_D5 at RC1_bit;
sbit LCD_D6 at RC2_bit;
sbit LCD_D7 at RC3_bit;
sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;
// End LCD module connections
sbit TestPin1 at RA0_bit;
sbit TestPin2 at RA1_bit;
sbit TestPin3 at RA2_bit;
sbit Detail at RA4_bit;
sbit SelectButton at RA5_bit;
// Define Messages
char message1[] = "Diode Tester";
char message2[] = "BJT Tester";
char message3[] = "Result:";
char message4[] = "Short";
char message5[] = "Open ";
char message6[] = "Good ";
char message7[] = "BJT is";
char *type = "xxx";
char *BE_Info = "xxxxx";
char *BC_Info = "xxxxx";
unsigned int select, test1, test2, update_select, detail_select;
unsigned int BE_Junc, BC_Junc, EB_Junc, CB_Junc;
void debounce_delay(void){
Delay_ms(200);
}
void main() {
ANSEL = 0b00000000; //All I/O pins are configured as digital
CMCON0 = 0x07 ; // Disbale comparators
PORTC = 0;
PORTA = 0;
TRISC = 0b00000000; // PORTC All Outputs
TRISA = 0b00111000; // PORTA All Outputs, Except RA3 (I/P only)
Lcd_Init();                      // Initialize LCD
Lcd_Cmd(_LCD_CLEAR);             // CLEAR display
Lcd_Cmd(_LCD_CURSOR_OFF);        // Cursor off
Lcd_Out(1,2,message1);           // Write message1 in 1st row
select = 0;
test1 = 0;
test2 = 0;
update_select = 1;
detail_select = 0;
do {
if(!SelectButton){
debounce_delay();
update_select = 1;
switch (select) {
case 0 : select=1;
break;
case 1 : select=0;
break;
} //case end
}

if(select == 0){   // Diode Tester
if(update_select){
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,2,message1);
Lcd_Out(2,2,message3);
update_select=0;
}
TRISA = 0b00110100; // RA0 O/P, RA2 I/P
TestPin1 = 1;
test1 = TestPin3 ; // Read I/P at RA2
TestPin1 = 0;
TRISA = 0b00110001; // RA0 I/P, RA2 O/P
TestPin3 = 1;
test2 = TestPin1;
TestPin3 = 0;

if((test1==1) && (test2 ==1)){
Lcd_Out(2,10,message4);
}
if((test1==1) && (test2 ==0)){
Lcd_Out(2,10,message6);
}
if((test1==0) && (test2 ==1)){
Lcd_Out(2,10,message6);
}
if((test1==0) && (test2 ==0)){
Lcd_Out(2,10,message5);
}

}  // End if(select == 0)

if(select && !detail_select){     // Transistor Tester
if(update_select){
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,2,message2);
update_select = 0;
}
// Test for BE and BC Junctions of NPN
TRISA = 0b00110101; // RA0, RA2 I/P, RA1 O/P
TestPin2 = 1;
BE_Junc = TestPin1 ; // Read I/P at RA0
BC_Junc = TestPin3;   // Read I/P at RA2
TestPin2 = 0;

// Test for EB and CB Junctions of PNP
TRISA = 0b00110110; // RA0 O/P, RA1/RA2 I/P
TestPin1 = 1;
EB_Junc = TestPin2;
TestPin1 = 0;
TRISA = 0b00110011; // RA0 O/P, RA1/RA2 I/P
TestPin3 = 1;
CB_Junc = TestPin2;
TestPin3 = 0;

if(BE_Junc && BC_Junc && !EB_Junc && !CB_Junc){
Lcd_Out(2,2,message3);
Lcd_Out(2,10,message6);
type = "NPN";
BE_info = "Good ";
BC_info = "Good ";
}
else
if(!BE_Junc && !BC_Junc && EB_Junc && CB_Junc){
Lcd_Out(2,2,message3);
Lcd_Out(2,10,message6);
type = "PNP";
BE_info = "Good ";
BC_info = "Good ";
}
else {
Lcd_Out(2,2,message3);
Lcd_Out(2,10,"Bad ");
type = "Bad";
}
}
if(select && !Detail){
debounce_delay();
switch (detail_select) {
case 0 : detail_select=1;
break;
case 1 : detail_select=0;

break;

} //case end
update_select = 1;
}

if(detail_select && update_select){

// Test for BE Junction open
if(!BE_Junc && !EB_Junc){
BE_info = "Open ";
}
// Test for BC Junction open
if(!BC_Junc && !CB_Junc){
BC_info = "Open ";
}
// Test for BE Junction short
if(BE_Junc && EB_Junc){
BE_info = "Short";
}

// Test for BC Junction short
if(BC_Junc && CB_Junc){
BC_info = "Short";
}
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"Type:");
Lcd_Out(1,7,type);
Lcd_Out(2,1,"BE:");
Lcd_Out(2,4,BE_info);
Lcd_Out(2,9,"BC:");
Lcd_Out(2,12,BC_info);
update_select = 0;
}       // End if (detail_select)

} while(1);
}
