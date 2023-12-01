/**************************************************************************************************
 Name        : Mini_Project3.c
 Author      : Amira Atef Ismaeil El Komy
 Description : Fan Controller
 Date        : 15/10/2023
 **************************************************************************************************/

#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void){
	LCD_init();
	LM35_init();
	DcMotor_Init();
	DcMotor_State state;
	uint8 temp =LM35_getTemperature();
	while(1){
		if(temp >=120){
			state = CLOCKWISE;
			DcMotor_Rotate(state, 100);
		}
		else if(temp >=90){
			state = CLOCKWISE;
			DcMotor_Rotate(state, 75);
		}
		else if(temp >=60){
			state = CLOCKWISE;
			DcMotor_Rotate(state, 50);
		}
		else if(temp >=30){
			state = CLOCKWISE;
			DcMotor_Rotate(state, 25);
		}
		else {
			state = STOP;
			DcMotor_Rotate(state, 0);
		}
		if(state == STOP){
			LCD_displayStringRowColumn(0, 4,"FAN is OFF");
		}
		else if(state == CLOCKWISE){
			LCD_displayStringRowColumn(0, 4,"FAN is ON 	");
		}
		LCD_displayStringRowColumn(1, 4,"Temp = ");
		LCD_intgerToString(temp);
		LCD_displayString(" C   ");
		temp =LM35_getTemperature();
	}
	return 0;
}
