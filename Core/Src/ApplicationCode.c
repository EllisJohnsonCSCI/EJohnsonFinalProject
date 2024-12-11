/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 *      Adjusted by: Ellis
 */

#include "ApplicationCode.h"

/* Static variables */
uint8_t screenCount = 0;

extern void initialise_monitor_handles(void); 
extern TIM_HandleTypeDef htim6;

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS


/* GENERAL */

void ApplicationInit(void){
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS

	#if USE_INTERRUPT_FOR_BUTTON == 1
	buttonInitInterrupt();
	#endif

	#if USE_INTERRUPT_FOR_TIMER == 1
	timerInit();
	#endif
}


/* LCD */

void LCD_Visual_Demo(void){
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void){
	LCD_Clear(0,LCD_COLOR_GREEN);

	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}


// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void){
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init      
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;

}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler(){
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universal interrupt guard
	bool isTouchDetected = false;

	static uint32_t count;
	count = 0;
	while(count == 0){
		count = STMPE811_Read(STMPE811_FIFO_SIZE);
	}

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}

	/* - ACTION TO EXECUTE DUE TO INTERRUPT - */

	switch(screenCount){
	// SCREEN 1 -> 2
	case 0:
		//Check if pressing in range of button
		//if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 70, 160, 100, 100)){
			// Doesn't work so just ignore button
		//}
		screenCount = 1;
		screen2();
		break;

	// PLAYING GAME (moving block from side to side)
	case 1:
		// Determine if it is pressed or unpressed
		if(isTouchDetected) // Touch has been detected
		{
			printf("\nPressed");
			// May need to do numerous retries?
			DetermineTouchPosition(&StaticTouchData);
			/* Touch valid */
			printf("\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);

			// Check which side of screen is pressed
			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 0, 0, 125, 320)){
				// Pressing on left
				LCD_Clear(0, LCD_COLOR_RED);
			}
			else if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 125, 0, 125, 320)){
				// Pressing on right
				LCD_Clear(0, LCD_COLOR_GREEN);
			}
		}
		else{
			/* Touch not pressed */
			printf("\nNot pressed \n");
			screen2();
		}

		break;

	// Consider third screen if we include menu/replay button

	default:
		break;
	}


	/* - I think everything below here is just taking care of interrupt bits - */

	STMPE811_Write(STMPE811_FIFO_STA, 0x01);
	STMPE811_Write(STMPE811_FIFO_STA, 0x00);

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS


/* BUTTON */

#if USE_INTERRUPT_FOR_BUTTON == 0
void buttonInit(){
	Button_Init();
}

void executeButtonPollingRoutine(){
	if(Button_IsPressed()){
		//activateGreenLED();
	}
	else{
		//deactivateGreenLED();
	}
}
#endif

#if USE_INTERRUPT_FOR_BUTTON == 1
void buttonInitInterrupt(){
	Button_InterruptInit();
}
#endif

void EXTI0_IRQHandler(){
	IRQ_DisableInterrupt(EXTI0_IRQ_NUMBER);

	addSchedulerEvent(ROTATE_BLOCK_EVENT);
	LCD_Clear(0, LCD_COLOR_RED);

	ClearPendingEXTIInterrupt(BUTTON_PIN);
	IRQ_EnableInterrupt(EXTI0_IRQ_NUMBER);
}

/* TIMER */

void timerInit(){
	Timer_Init();
}

void TIM6_IRQHandler(void){
	HAL_TIM_IRQHandler(&htim6);

	LCD_Clear(0, LCD_COLOR_GREEN);
	HAL_Delay(5000);
	LCD_Clear(0, LCD_COLOR_WHITE);
}
