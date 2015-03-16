/* ###################################################################
**     Filename    : main.c
**     Project     : PESampleCode
**     Processor   : MK22FN512VLH12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-15, 13:04, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "pin_mux.h"
#include "FX1.h"
#include "WAIT1.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "BitIoLdd1.h"
#include "SCL1.h"
#include "BitIoLdd2.h"
#include "FRTOS1.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
char *task1name = "Task1";
char *task2name = "Task2";

/*!
 * This task is made to stress the printf functionality
 * @param pvParameters
 */
void TestPrint(void *pvParameters)
{
	int16_t X,Y,Z;
	uint8_t status;
	uint8_t whoAmI;
	bool enableState;
	int32_t delay=100;
	int32_t getFlag = 0;
	if( strcmp((char*)pvParameters,task1name) == 0)
	{
		delay = 100;
		getFlag = 1;
	}
	if( strcmp((char*)pvParameters,task2name) == 0)
	{
		delay = 500;
	}
	status = FX1_Init();
	if(status)
	{
		printf("problem init FX1\r\n");
	}

	status = FX1_isEnabled(&enableState);
	if(status)
	{
		printf("problem with FX1\r\n");
	}
	else
	{
		printf("enableState: %d\r\n",enableState);
	}

	FX1_CalibrateZ1g();

	status =  FX1_WhoAmI(&whoAmI);
	if(status)
	{
		printf("problem with FX1\r\n");
	}
	else
	{
		printf("whoami: %X\r\n",whoAmI);
	}

	for(;;)
	{
		X = FX1_GetX();
		Y = FX1_GetY();
		Z = FX1_GetZ();

		printf("%d %d %d\r\n", X,Y,Z);
		vTaskDelay(delay);
	}
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
//  xTaskCreate(TestPrint, task1name, 512, task1name, 3, NULL);
  xTaskCreate(TestPrint, task2name, 512, task2name, 2, NULL);

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
