
//#include "Def.h"
#include "stdio.h"
#include "UartCtrl.h"
#include "def.h"
#include "uart.h"
#include "motor.h"

#include "PID.h"
 


uint8_t getUartData = FALSE;

uint8_t g_u8RecData[RXBUFSIZE]  = {0};

//volatile uint32_t g_u32comRbytes = 0;
//volatile uint32_t g_u32comRhead  = 0;
//volatile uint32_t g_u32comRtail  = 0;
volatile uint32_t g_u32comLength = 0;

void setupUART()
{
	/* Enable peripheral clock */
	CLK_EnableModuleClock(UART0_MODULE);
	/* Peripheral clock source */
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UARTSEL_HIRC, CLK_CLKDIV_UART(1));
	/* Set PD multi-function pins for UART0 RXD, TXD */
	SYS->P1_MFP &= ~(SYS_MFP_P51_Msk | SYS_MFP_P50_Msk);
  SYS->P1_MFP |= (SYS_MFP_P51_UART0_RXD | SYS_MFP_P50_UART0_TXD);
	
	//SYS->P0_MFP = SYS_MFP_P00_TXD | SYS_MFP_P01_RXD;
	
	/* Reset UART module */
	SYS_ResetModule(UART0_RST);

	/* Configure UART0 and set UART0 Baudrate */
	UART_Open(UART0, 115200);
}


/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void UART_HANDLE()
{
    uint8_t u8InChar=0xFF;
    uint32_t u32IntSts= UART0->INTSTS;

    if(u32IntSts & UART_INTSTS_RDAINT_Msk) {

        /* Get all the input characters */
        while(UART_IS_RX_READY(UART)) {
            /* Get the character from UART Buffer */
            u8InChar = UART_READ(UART);           /* Rx trigger level is 1 byte*/

						//printf("%c", u8InChar);
            /* Check if buffer full */
            if(g_u32comLength < RXBUFSIZE) {
                /* Enqueue the character */
                g_u8RecData[g_u32comLength] = u8InChar;
								g_u32comLength++;
                //g_u32comRtail = (g_u32comRtail == (RXBUFSIZE-1)) ? 0 : (g_u32comRtail+1);
                //g_u32comRbytes++;
            }
						if(u8InChar == '\n')
						{
							
								getUartData = TRUE;
								g_u32comLength = 0;
						}
        }
    }
		
//		if(u32IntSts & UART_ISR_THRE_INT_Msk) {
//        uint16_t tmp;
//        tmp = g_u32comRtail;
//        if(g_u32comRhead != tmp) {
//            u8InChar = g_u8RecData[g_u32comRhead];
//            UART_WRITE(UART,u8InChar);
//            g_u32comRhead = (g_u32comRhead == (RXBUFSIZE-1)) ? 0 : (g_u32comRhead+1);
//            g_u32comRbytes--;
//        }
//    }
		
		
}


/*---------------------------------------------------------------------------------------------------------*/
/*  UART Function Test                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void UART_NVIC_INIT()
{
    
    /* Enable Interrupt and install the call back function */
   // UART_ENABLE_INT(UART, (UART_IER_RDA_IEN_Msk | UART_IER_THRE_IEN_Msk | UART_IER_RTO_IEN_Msk));
	  UART_ENABLE_INT(UART, UART_INTEN_RDAIEN_Msk);
    NVIC_EnableIRQ(UART0_IRQn);
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART_IRQHandler(void)
{
    UART_HANDLE();
}

void CommandProcess(void)
{
	int command;
	char mode;
	// Read incoming control messages
	//if (Serial_available() >= 2)
	if(getUartData == TRUE)
	{
		char start=g_u8RecData[0];//UART_READ(UART);//Serial_read();
		if (start == '@') 
		{// Start of new control message
			printf("@HOOK \n");
			//int command = UART_READ(UART);//Serial_read(); // Commands
			command = g_u8RecData[1];
			mode = g_u8RecData[2];
			if (command == 's')
			{
					printf("@s ok \n");
					// 's'tream output control
					
					if (mode == 's') 
					{// 's'tart stream
						//stream_mode = STREAM_START;
						Motor_Start();
					}
					else if (mode == 'p') 
					{// 'p'ause stream
						//stream_mode = STREAM_PAUSE;
						Motor_Stop();
					}
			}
//		else 
//		{ 
//			if (report_format == REPORT_FORMAT_TEXT) {
//			printf("Unknown command.\n");
//		}
		} // Skip character
		
		getUartData = FALSE;	//标记接收完成
	}
}
