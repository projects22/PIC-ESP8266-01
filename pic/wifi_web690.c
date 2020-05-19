
// WiFi WEB 
// Enter your SSID, PASSWORD and domain.
// XC8 on MPLABX.
// pic16f690
   
#include <htc.h>
#include <xc.h>
#include <stdio.h>
#include <stdarg.h>

#pragma config WDTE=OFF, BOREN=OFF, FOSC=HS, CP=OFF, CPD=OFF    //MCLRE=OFF, 

#define _XTAL_FREQ 8000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
#define switch RA2
#define input RB4

//prototypes
void putch(char data);

void main(void)
{
  	char * d1;
		
	// PIC I/O init
	TRISA2 = 1;		//RA2 switch
	TRISB4 = 1;		//RB4 input
	WPUA2 = 1;		//pull-up
	WPUB4 = 1;		//pull-up
	TRISB5 = 1;		//Rx
	TRISB7 = 1;		//Tx
	ANSEL = 0;			//digital port
	ANSELH = 0;
	ANS8 = 1;	//analogue chan 8
		
    	//ADC
    ADCON1 = 0B1010000;		// Fosc/16.
	ADCON0 = 0B10100000;	// ref=Vdd, right just, AN8, AD off 
		//UART
//	TXSTA = 0B0010
	TXEN = 1; 
	SYNC = 0;
	SPEN = 1;  //Serial Port Enable bit	
	CREN = 1;	//receive enabled
	BRGH = 1;
	SPBRG = 51;	//baud rate 9600bps
    
            printf("AT+RST\r\n");   //reset ESP
		    __delay_ms(1000);
		    printf("AT+CWMODE=%d\r\n", 1);  //station mode
		    __delay_ms(1000);
		    printf("AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n");   //enter your router SSID, PASSWORD
			__delay_ms(10000);
			
	while(1){
		
				//start ADC conversion
			ADON = 1;
			GO_DONE = 1;
		    
			__delay_ms(1);
			if(input) {d1 = "OFF";}else{d1 = "ON";}
                //count the bytes in the data to be sent
            unsigned char cc1 = printf("GET /a1.php?v1=%i&v2=%i&v3=%s HTTP/1.1\r\n", ADRESH, ADRESL, d1);
			unsigned char cc2 = printf("HOST: domain.co.uk\r\n\r\n");   //enter your domain
            cc2 += cc1;
         
            printf("AT+CIPSTART=\"TCP\",\"domain.co.uk\",%d\r\n", 80);   //enter your domain
		    __delay_ms(1000);
		    printf("AT+CIPSEND=%i\r\n", cc2);
		    __delay_ms(2000);
            cc1 = printf("GET /a1.php?v1=%i&v2=%i&v3=%s HTTP/1.1\r\n", ADRESH, ADRESL, d1);
            cc1 = printf("HOST: domain.co.uk\r\n\r\n");   //enter your domain
            __delay_ms(20000);
            __delay_ms(20000);
            __delay_ms(20000);

	
	}	
}

void putch(char data)
{
while( ! TXIF)
continue;
TXREG = data;
}

