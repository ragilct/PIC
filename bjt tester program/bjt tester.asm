
_debounce_delay:

;bjt tester.c,39 :: 		void debounce_delay(void){
;bjt tester.c,40 :: 		Delay_ms(200);
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_debounce_delay0:
	DECFSZ     R13+0, 1
	GOTO       L_debounce_delay0
	DECFSZ     R12+0, 1
	GOTO       L_debounce_delay0
	DECFSZ     R11+0, 1
	GOTO       L_debounce_delay0
	NOP
;bjt tester.c,41 :: 		}
	RETURN
; end of _debounce_delay

_main:

;bjt tester.c,42 :: 		void main() {
;bjt tester.c,43 :: 		ANSEL = 0b00000000; //All I/O pins are configured as digital
	CLRF       ANSEL+0
;bjt tester.c,44 :: 		CMCON0 = 0x07 ; // Disbale comparators
	MOVLW      7
	MOVWF      CMCON0+0
;bjt tester.c,45 :: 		PORTC = 0;
	CLRF       PORTC+0
;bjt tester.c,46 :: 		PORTA = 0;
	CLRF       PORTA+0
;bjt tester.c,47 :: 		TRISC = 0b00000000; // PORTC All Outputs
	CLRF       TRISC+0
;bjt tester.c,48 :: 		TRISA = 0b00111000; // PORTA All Outputs, Except RA3 (I/P only)
	MOVLW      56
	MOVWF      TRISA+0
;bjt tester.c,49 :: 		Lcd_Init();                      // Initialize LCD
	CALL       _Lcd_Init+0
;bjt tester.c,50 :: 		Lcd_Cmd(_LCD_CLEAR);             // CLEAR display
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;bjt tester.c,51 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);        // Cursor off
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;bjt tester.c,52 :: 		Lcd_Out(1,2,message1);           // Write message1 in 1st row
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message1+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,53 :: 		select = 0;
	CLRF       _select+0
	CLRF       _select+1
;bjt tester.c,54 :: 		test1 = 0;
	CLRF       _test1+0
	CLRF       _test1+1
;bjt tester.c,55 :: 		test2 = 0;
	CLRF       _test2+0
	CLRF       _test2+1
;bjt tester.c,56 :: 		update_select = 1;
	MOVLW      1
	MOVWF      _update_select+0
	MOVLW      0
	MOVWF      _update_select+1
;bjt tester.c,57 :: 		detail_select = 0;
	CLRF       _detail_select+0
	CLRF       _detail_select+1
;bjt tester.c,58 :: 		do {
L_main1:
;bjt tester.c,59 :: 		if(!SelectButton){
	BTFSC      RA5_bit+0, 5
	GOTO       L_main4
;bjt tester.c,60 :: 		debounce_delay();
	CALL       _debounce_delay+0
;bjt tester.c,61 :: 		update_select = 1;
	MOVLW      1
	MOVWF      _update_select+0
	MOVLW      0
	MOVWF      _update_select+1
;bjt tester.c,62 :: 		switch (select) {
	GOTO       L_main5
;bjt tester.c,63 :: 		case 0 : select=1;
L_main7:
	MOVLW      1
	MOVWF      _select+0
	MOVLW      0
	MOVWF      _select+1
;bjt tester.c,64 :: 		break;
	GOTO       L_main6
;bjt tester.c,65 :: 		case 1 : select=0;
L_main8:
	CLRF       _select+0
	CLRF       _select+1
;bjt tester.c,66 :: 		break;
	GOTO       L_main6
;bjt tester.c,67 :: 		} //case end
L_main5:
	MOVLW      0
	XORWF      _select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main70
	MOVLW      0
	XORWF      _select+0, 0
L__main70:
	BTFSC      STATUS+0, 2
	GOTO       L_main7
	MOVLW      0
	XORWF      _select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main71
	MOVLW      1
	XORWF      _select+0, 0
L__main71:
	BTFSC      STATUS+0, 2
	GOTO       L_main8
L_main6:
;bjt tester.c,68 :: 		}
L_main4:
;bjt tester.c,70 :: 		if(select == 0){   // Diode Tester
	MOVLW      0
	XORWF      _select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main72
	MOVLW      0
	XORWF      _select+0, 0
L__main72:
	BTFSS      STATUS+0, 2
	GOTO       L_main9
;bjt tester.c,71 :: 		if(update_select){
	MOVF       _update_select+0, 0
	IORWF      _update_select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main10
;bjt tester.c,72 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;bjt tester.c,73 :: 		Lcd_Out(1,2,message1);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message1+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,74 :: 		Lcd_Out(2,2,message3);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message3+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,75 :: 		update_select=0;
	CLRF       _update_select+0
	CLRF       _update_select+1
;bjt tester.c,76 :: 		}
L_main10:
;bjt tester.c,77 :: 		TRISA = 0b00110100; // RA0 O/P, RA2 I/P
	MOVLW      52
	MOVWF      TRISA+0
;bjt tester.c,78 :: 		TestPin1 = 1;
	BSF        RA0_bit+0, 0
;bjt tester.c,79 :: 		test1 = TestPin3 ; // Read I/P at RA2
	MOVLW      0
	BTFSC      RA2_bit+0, 2
	MOVLW      1
	MOVWF      _test1+0
	CLRF       _test1+1
;bjt tester.c,80 :: 		TestPin1 = 0;
	BCF        RA0_bit+0, 0
;bjt tester.c,81 :: 		TRISA = 0b00110001; // RA0 I/P, RA2 O/P
	MOVLW      49
	MOVWF      TRISA+0
;bjt tester.c,82 :: 		TestPin3 = 1;
	BSF        RA2_bit+0, 2
;bjt tester.c,83 :: 		test2 = TestPin1;
	MOVLW      0
	BTFSC      RA0_bit+0, 0
	MOVLW      1
	MOVWF      _test2+0
	CLRF       _test2+1
;bjt tester.c,84 :: 		TestPin3 = 0;
	BCF        RA2_bit+0, 2
;bjt tester.c,86 :: 		if((test1==1) && (test2 ==1)){
	MOVLW      0
	XORWF      _test1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main73
	MOVLW      1
	XORWF      _test1+0, 0
L__main73:
	BTFSS      STATUS+0, 2
	GOTO       L_main13
	MOVLW      0
	XORWF      _test2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main74
	MOVLW      1
	XORWF      _test2+0, 0
L__main74:
	BTFSS      STATUS+0, 2
	GOTO       L_main13
L__main69:
;bjt tester.c,87 :: 		Lcd_Out(2,10,message4);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message4+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,88 :: 		}
L_main13:
;bjt tester.c,89 :: 		if((test1==1) && (test2 ==0)){
	MOVLW      0
	XORWF      _test1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main75
	MOVLW      1
	XORWF      _test1+0, 0
L__main75:
	BTFSS      STATUS+0, 2
	GOTO       L_main16
	MOVLW      0
	XORWF      _test2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main76
	MOVLW      0
	XORWF      _test2+0, 0
L__main76:
	BTFSS      STATUS+0, 2
	GOTO       L_main16
L__main68:
;bjt tester.c,90 :: 		Lcd_Out(2,10,message6);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message6+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,91 :: 		}
L_main16:
;bjt tester.c,92 :: 		if((test1==0) && (test2 ==1)){
	MOVLW      0
	XORWF      _test1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main77
	MOVLW      0
	XORWF      _test1+0, 0
L__main77:
	BTFSS      STATUS+0, 2
	GOTO       L_main19
	MOVLW      0
	XORWF      _test2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main78
	MOVLW      1
	XORWF      _test2+0, 0
L__main78:
	BTFSS      STATUS+0, 2
	GOTO       L_main19
L__main67:
;bjt tester.c,93 :: 		Lcd_Out(2,10,message6);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message6+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,94 :: 		}
L_main19:
;bjt tester.c,95 :: 		if((test1==0) && (test2 ==0)){
	MOVLW      0
	XORWF      _test1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main79
	MOVLW      0
	XORWF      _test1+0, 0
L__main79:
	BTFSS      STATUS+0, 2
	GOTO       L_main22
	MOVLW      0
	XORWF      _test2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main80
	MOVLW      0
	XORWF      _test2+0, 0
L__main80:
	BTFSS      STATUS+0, 2
	GOTO       L_main22
L__main66:
;bjt tester.c,96 :: 		Lcd_Out(2,10,message5);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message5+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,97 :: 		}
L_main22:
;bjt tester.c,99 :: 		}  // End if(select == 0)
L_main9:
;bjt tester.c,101 :: 		if(select && !detail_select){     // Transistor Tester
	MOVF       _select+0, 0
	IORWF      _select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main25
	MOVF       _detail_select+0, 0
	IORWF      _detail_select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main25
L__main65:
;bjt tester.c,102 :: 		if(update_select){
	MOVF       _update_select+0, 0
	IORWF      _update_select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main26
;bjt tester.c,103 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;bjt tester.c,104 :: 		Lcd_Out(1,2,message2);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message2+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,105 :: 		update_select = 0;
	CLRF       _update_select+0
	CLRF       _update_select+1
;bjt tester.c,106 :: 		}
L_main26:
;bjt tester.c,108 :: 		TRISA = 0b00110101; // RA0, RA2 I/P, RA1 O/P
	MOVLW      53
	MOVWF      TRISA+0
;bjt tester.c,109 :: 		TestPin2 = 1;
	BSF        RA1_bit+0, 1
;bjt tester.c,110 :: 		BE_Junc = TestPin1 ; // Read I/P at RA0
	MOVLW      0
	BTFSC      RA0_bit+0, 0
	MOVLW      1
	MOVWF      _BE_Junc+0
	CLRF       _BE_Junc+1
;bjt tester.c,111 :: 		BC_Junc = TestPin3;   // Read I/P at RA2
	MOVLW      0
	BTFSC      RA2_bit+0, 2
	MOVLW      1
	MOVWF      _BC_Junc+0
	CLRF       _BC_Junc+1
;bjt tester.c,112 :: 		TestPin2 = 0;
	BCF        RA1_bit+0, 1
;bjt tester.c,115 :: 		TRISA = 0b00110110; // RA0 O/P, RA1/RA2 I/P
	MOVLW      54
	MOVWF      TRISA+0
;bjt tester.c,116 :: 		TestPin1 = 1;
	BSF        RA0_bit+0, 0
;bjt tester.c,117 :: 		EB_Junc = TestPin2;
	MOVLW      0
	BTFSC      RA1_bit+0, 1
	MOVLW      1
	MOVWF      _EB_Junc+0
	CLRF       _EB_Junc+1
;bjt tester.c,118 :: 		TestPin1 = 0;
	BCF        RA0_bit+0, 0
;bjt tester.c,119 :: 		TRISA = 0b00110011; // RA0 O/P, RA1/RA2 I/P
	MOVLW      51
	MOVWF      TRISA+0
;bjt tester.c,120 :: 		TestPin3 = 1;
	BSF        RA2_bit+0, 2
;bjt tester.c,121 :: 		CB_Junc = TestPin2;
	MOVLW      0
	BTFSC      RA1_bit+0, 1
	MOVLW      1
	MOVWF      _CB_Junc+0
	CLRF       _CB_Junc+1
;bjt tester.c,122 :: 		TestPin3 = 0;
	BCF        RA2_bit+0, 2
;bjt tester.c,124 :: 		if(BE_Junc && BC_Junc && !EB_Junc && !CB_Junc){
	MOVF       _BE_Junc+0, 0
	IORWF      _BE_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main29
	MOVF       _BC_Junc+0, 0
	IORWF      _BC_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main29
	MOVF       _EB_Junc+0, 0
	IORWF      _EB_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main29
	MOVF       _CB_Junc+0, 0
	IORWF      _CB_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main29
L__main64:
;bjt tester.c,125 :: 		Lcd_Out(2,2,message3);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message3+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,126 :: 		Lcd_Out(2,10,message6);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message6+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,127 :: 		type = "NPN";
	MOVLW      ?lstr4_bjt_32tester+0
	MOVWF      _type+0
;bjt tester.c,128 :: 		BE_info = "Good ";
	MOVLW      ?lstr5_bjt_32tester+0
	MOVWF      _BE_Info+0
;bjt tester.c,129 :: 		BC_info = "Good ";
	MOVLW      ?lstr6_bjt_32tester+0
	MOVWF      _BC_Info+0
;bjt tester.c,130 :: 		}
	GOTO       L_main30
L_main29:
;bjt tester.c,132 :: 		if(!BE_Junc && !BC_Junc && EB_Junc && CB_Junc){
	MOVF       _BE_Junc+0, 0
	IORWF      _BE_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main33
	MOVF       _BC_Junc+0, 0
	IORWF      _BC_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main33
	MOVF       _EB_Junc+0, 0
	IORWF      _EB_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main33
	MOVF       _CB_Junc+0, 0
	IORWF      _CB_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main33
L__main63:
;bjt tester.c,133 :: 		Lcd_Out(2,2,message3);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message3+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,134 :: 		Lcd_Out(2,10,message6);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message6+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,135 :: 		type = "PNP";
	MOVLW      ?lstr7_bjt_32tester+0
	MOVWF      _type+0
;bjt tester.c,136 :: 		BE_info = "Good ";
	MOVLW      ?lstr8_bjt_32tester+0
	MOVWF      _BE_Info+0
;bjt tester.c,137 :: 		BC_info = "Good ";
	MOVLW      ?lstr9_bjt_32tester+0
	MOVWF      _BC_Info+0
;bjt tester.c,138 :: 		}
	GOTO       L_main34
L_main33:
;bjt tester.c,140 :: 		Lcd_Out(2,2,message3);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      _message3+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,141 :: 		Lcd_Out(2,10,"Bad ");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      10
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr10_bjt_32tester+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,142 :: 		type = "Bad";
	MOVLW      ?lstr11_bjt_32tester+0
	MOVWF      _type+0
;bjt tester.c,143 :: 		}
L_main34:
L_main30:
;bjt tester.c,144 :: 		}
L_main25:
;bjt tester.c,145 :: 		if(select && !Detail){
	MOVF       _select+0, 0
	IORWF      _select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main37
	BTFSC      RA4_bit+0, 4
	GOTO       L_main37
L__main62:
;bjt tester.c,146 :: 		debounce_delay();
	CALL       _debounce_delay+0
;bjt tester.c,147 :: 		switch (detail_select) {
	GOTO       L_main38
;bjt tester.c,148 :: 		case 0 : detail_select=1;
L_main40:
	MOVLW      1
	MOVWF      _detail_select+0
	MOVLW      0
	MOVWF      _detail_select+1
;bjt tester.c,149 :: 		break;
	GOTO       L_main39
;bjt tester.c,150 :: 		case 1 : detail_select=0;
L_main41:
	CLRF       _detail_select+0
	CLRF       _detail_select+1
;bjt tester.c,152 :: 		break;
	GOTO       L_main39
;bjt tester.c,154 :: 		} //case end
L_main38:
	MOVLW      0
	XORWF      _detail_select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main81
	MOVLW      0
	XORWF      _detail_select+0, 0
L__main81:
	BTFSC      STATUS+0, 2
	GOTO       L_main40
	MOVLW      0
	XORWF      _detail_select+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main82
	MOVLW      1
	XORWF      _detail_select+0, 0
L__main82:
	BTFSC      STATUS+0, 2
	GOTO       L_main41
L_main39:
;bjt tester.c,155 :: 		update_select = 1;
	MOVLW      1
	MOVWF      _update_select+0
	MOVLW      0
	MOVWF      _update_select+1
;bjt tester.c,156 :: 		}
L_main37:
;bjt tester.c,158 :: 		if(detail_select && update_select){
	MOVF       _detail_select+0, 0
	IORWF      _detail_select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main44
	MOVF       _update_select+0, 0
	IORWF      _update_select+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main44
L__main61:
;bjt tester.c,161 :: 		if(!BE_Junc && !EB_Junc){
	MOVF       _BE_Junc+0, 0
	IORWF      _BE_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main47
	MOVF       _EB_Junc+0, 0
	IORWF      _EB_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main47
L__main60:
;bjt tester.c,162 :: 		BE_info = "Open ";
	MOVLW      ?lstr12_bjt_32tester+0
	MOVWF      _BE_Info+0
;bjt tester.c,163 :: 		}
L_main47:
;bjt tester.c,165 :: 		if(!BC_Junc && !CB_Junc){
	MOVF       _BC_Junc+0, 0
	IORWF      _BC_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main50
	MOVF       _CB_Junc+0, 0
	IORWF      _CB_Junc+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L_main50
L__main59:
;bjt tester.c,166 :: 		BC_info = "Open ";
	MOVLW      ?lstr13_bjt_32tester+0
	MOVWF      _BC_Info+0
;bjt tester.c,167 :: 		}
L_main50:
;bjt tester.c,169 :: 		if(BE_Junc && EB_Junc){
	MOVF       _BE_Junc+0, 0
	IORWF      _BE_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main53
	MOVF       _EB_Junc+0, 0
	IORWF      _EB_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main53
L__main58:
;bjt tester.c,170 :: 		BE_info = "Short";
	MOVLW      ?lstr14_bjt_32tester+0
	MOVWF      _BE_Info+0
;bjt tester.c,171 :: 		}
L_main53:
;bjt tester.c,174 :: 		if(BC_Junc && CB_Junc){
	MOVF       _BC_Junc+0, 0
	IORWF      _BC_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main56
	MOVF       _CB_Junc+0, 0
	IORWF      _CB_Junc+1, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main56
L__main57:
;bjt tester.c,175 :: 		BC_info = "Short";
	MOVLW      ?lstr15_bjt_32tester+0
	MOVWF      _BC_Info+0
;bjt tester.c,176 :: 		}
L_main56:
;bjt tester.c,177 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;bjt tester.c,178 :: 		Lcd_Out(1,1,"Type:");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr16_bjt_32tester+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,179 :: 		Lcd_Out(1,7,type);
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      7
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _type+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,180 :: 		Lcd_Out(2,1,"BE:");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr17_bjt_32tester+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,181 :: 		Lcd_Out(2,4,BE_info);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      4
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _BE_Info+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,182 :: 		Lcd_Out(2,9,"BC:");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr18_bjt_32tester+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,183 :: 		Lcd_Out(2,12,BC_info);
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      12
	MOVWF      FARG_Lcd_Out_column+0
	MOVF       _BC_Info+0, 0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;bjt tester.c,184 :: 		update_select = 0;
	CLRF       _update_select+0
	CLRF       _update_select+1
;bjt tester.c,185 :: 		}       // End if (detail_select)
L_main44:
;bjt tester.c,187 :: 		} while(1);
	GOTO       L_main1
;bjt tester.c,188 :: 		}
	GOTO       $+0
; end of _main
