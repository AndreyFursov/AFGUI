/*
Fursov Andrey, 2013
TNKernel v2.6 by Yury Tyemkin



*/

/*============================================================================

*===========================================================================*/
#include "globals.h"


#include <string.h>
#include <stdio.h>

#include "tn_task_usart.h"


#include "at26df.h"
#include "crcm.h"
#include "uartdrv.h"




//----------- Tasks ----------------------------------------------------------
// 0 - max priority,  30 - min priority
//#define  TASK_xxx_PRIORITY		11

// stack size
//#define  TASK_xxx_STK_SIZE		32

//-------- stack -----------------------
 


//-------- Semaphores -----------------------

//-------- Events -----------------------

//------- Queues ----------------------------


//------- Memory pools ----------------------------


//------------ Non OS globals ---------------



//************************************************************
// LOCAL VARIABLES



//************************************************************
// LOCAL PROTOTYPES




//************************************************************
// MAIN
//************************************************************
//----------------------------------------------------------------------------
int main(void)

 {
	tn_arm_disable_interrupts();

	HardwareInit();
	
			
	tn_start_system(); //-- Never returns

   return 1;
}


//----------------------------------------------------------------------------
void  tn_app_init()
{
	//--- gui
	appGUI_task_create();

   //--- Task USART
	uart_task_create();
	

}

