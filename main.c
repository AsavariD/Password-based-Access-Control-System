#include <p18f4580.h>
#include <stdio.h>
#include <string.h>

#define r1 PORTBbits.RB7
#define r2 PORTBbits.RB6
#define r3 PORTBbits.RB5
#define r4 PORTBbits.RB4

#define c1 PORTBbits.RB3
#define c2 PORTBbits.RB2
#define c3 PORTBbits.RB1
#define c4 PORTBbits.RB0

#define rs PORTDbits.RD0
#define en PORTDbits.RD1

#define ledRed PORTDbits.RD6
#define ledGreen PORTDbits.RD7

#define in1 PORTDbits.RD2
#define in2 PORTDbits.RD3

void delay(int time) {
    int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 100; j++);
    }
}

void lcd_cmd(int cmd) {
    PORTC = cmd;
    rs = 0;
    en = 1;
    delay(10);
    en = 0;
}

void lcd_data(int data) {
    PORTC = data;
    rs = 1;
    en = 1;
    delay(10);
    en = 0;
}

void lcd_init() {
    char intro[] = "Enter password: ";
    int i;
    lcd_cmd(0x0f);
    lcd_cmd(0x38);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    for (i = 0; intro[i] != '\0'; i++) {
        lcd_data(intro[i]);
        delay(5);
    }
    lcd_cmd(0xc0);
}

void noAttemptsMessage(){
	char error[] = "No attempts left";
    char wait[] = "Wait 10s";
    int j;
    in1 = in2 = 0;
	ledGreen = ledRed = 0;
	lcd_cmd(0x01);
	for(j=0;error[j]!='\0';j++){
		lcd_data(error[j]);
	}
	delay(100);
	lcd_cmd(0x01);
	for(j=0;wait[j]!='\0';j++){
		lcd_data(wait[j]);
	}
	delay(50);
	lcd_cmd(0xc0);
	for(j=10; j>=0; j--){
		lcd_data(j+'0');
		delay(100);
		lcd_cmd(0xc0);
	}
	lcd_init();
	
}

void main() {
    int i = 0, j;
    char pwd[] = "1234";
    char user_pwd[5] = {0};
    int attempts = 3;

    TRISB = 0x0f;
    TRISC = 0x00;
    TRISD = 0x00;
    ADCON1 = 0x0f;

    lcd_init();

    while (1) {
        r1 = 1;
        r2 = r3 = r4 = 0;
        if (c1 == 1) {
            lcd_data('7');
            user_pwd[i++] = '7';
            while (c1 == 1);
            delay(10);
        }
        if (c2 == 1) {
            lcd_data('8');
            user_pwd[i++] = '8';
            while (c2 == 1);
            delay(10);
        }
        if (c3 == 1) {
            lcd_data('9');
            user_pwd[i++] = '9';
            while (c3 == 1);
            delay(10);
        }

        r2 = 1;
        r1 = r3 = r4 = 0;
        if (c1 == 1) {
            lcd_data('4');
            user_pwd[i++] = '4';
            while (c1 == 1);
            delay(10);
        }
        if (c2 == 1) {
            lcd_data('5');
            user_pwd[i++] = '5';
            while (c2 == 1);
            delay(10);
        }
        if (c3 == 1) {
            lcd_data('6');
            user_pwd[i++] = '6';
            while (c3 == 1);
            delay(10);
        }

        r3 = 1;
        r1 = r2 = r4 = 0;
        if (c1 == 1) {
            lcd_data('1');
            user_pwd[i++] = '1';
            while (c1 == 1);
            delay(10);
        }
        if (c2 == 1) {
            lcd_data('2');
            user_pwd[i++] = '2';
            while (c2 == 1);
            delay(10);
        }
        if (c3 == 1) {
            lcd_data('3');
            user_pwd[i++] = '3';
            while (c3 == 1);
            delay(10);
        }

        r4 = 1;
        r1 = r2 = r3 = 0;
        if (c1 == 1) {
            lcd_cmd(0x01);
            lcd_init();
            ledGreen = ledRed = 0;
            in1 = in2 = 0;
            while (c1 == 1);
            delay(10);
        }
        if (c2 == 1) {
            lcd_data('0');
            user_pwd[i++] = '0';
            while (c2 == 1);
            delay(10);
        }

        if (c3 == 1) {
            user_pwd[4] = '\0';

            if (strcmp(user_pwd, pwd) == 0) {
                ledGreen = 1;
                ledRed = 0;
                in1 = 1;
                in2 = 0;
                attempts = 3;
            } else {
            	attempts--;
                ledGreen = 0;
                ledRed = 1;
            	in1 = in2 = 0;
            }
            for (j = 0; j < 5; j++) {
                user_pwd[j] = '\0';
            }
            i=0;
            while(c3 == 1);
            delay(10);

       }
       
       if(attempts == 0){
				noAttemptsMessage();
				attempts = 3;	       
       		}
       }
}