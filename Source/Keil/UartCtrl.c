//#include <stdio.h>
//#include "Def.h"
#include "stdio.h"
#include "UartCtrl.h"
#include "mini51series.h"
#include "uart.h"


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
	CLK_EnableModuleClock(UART_MODULE);
	/* Peripheral clock source */
	CLK_SetModuleClock(UART_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));
	/* Set PD multi-function pins for UART0 RXD, TXD */
	SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
  SYS->P1_MFP |= (SYS_MFP_P12_RXD | SYS_MFP_P13_TXD);
	
	//SYS->P0_MFP = SYS_MFP_P00_TXD | SYS_MFP_P01_RXD;
	
	/* Reset UART module */
	SYS_ResetModule(UART_RST);

	/* Configure UART0 and set UART0 Baudrate */
	UART_Open(UART0, 115200);
}


/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void UART_HANDLE()
{
    uint8_t u8InChar=0xFF;
    uint32_t u32IntSts= UART->ISR;

    if(u32IntSts & UART_ISR_RDA_INT_Msk) {

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
							//标志接收完成
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
	  UART_ENABLE_INT(UART, UART_IER_RDA_IEN_Msk);
    NVIC_EnableIRQ(UART_IRQn);
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
	// Read incoming control messages
	//if (Serial_available() >= 2)
	if(getUartData == TRUE)
	{
		char start=g_u8RecData[0];//UART_READ(UART);//Serial_read();
		if (start == '@') {// Start of new control message
		
			//int command = UART_READ(UART);//Serial_read(); // Commands
			int command = g_u8RecData[1];
			if (command == 'h') {//Hook AHRS Stack Device
				// Read ID
				char id[2];
				//id[0] = UART_READ(UART);//GetChar();
				//id[1] = UART_READ(UART);//GetChar();
				id[0] = g_u8RecData[2];
				id[1] = g_u8RecData[3];
				// Reply with synch message
				printf("@HOOK");
				//Serial_write(id, 2);
			}
			else if (command == 'v') {//Check Version
				//CheckVersion();
				printf("version\n");
			}
			else if (command == 'c') {// A 'c'calibration command
				//SensorCalibration();
			}
			else if (command == 'b') {// 'b'lock erase flash
				//FlashControl();
			}
			else if (command == 'p') {// Set 'p'id command
			//	SetPID();
			}
//			else if (command == 'm') {// Set report 'm'ode
//				char mode = GetChar();
//				if (mode == 'e') {// Report AHRS by 'e'uler angle
//					report_mode = REPORT_AHRS_EULER;
//				}
//				else if (mode == 'q') {// Report // Report AHRS by 'q'quaternion
//					report_mode = REPORT_AHRS_QUATERNION;
//				}
//				else if (mode == 'r') {// Report sensor 'r'aw data
//					report_mode = REPORT_SENSORS_RAW;
//				}
//				else if (mode == 'c') {// Report sensor 'c'alibrated data
//					report_mode = REPORT_SENSORS_CALIBRATED;
//				}
//				else if (mode == 'm') {// Report 'm'otor power distribution
//					report_mode = REPORT_MOTOR_POWER;
//				}
//				else if (mode == 'v') {// Report 'v'elocity
//					report_mode = REPORT_VELOCITY;
//				}
//				else if (mode == 's') {// Report 's'tatus
//					report_status();
//				}
//				else if (mode == 'p') {// Report controller 'p'id
//					char type = GetChar();
//					if (type == 'p') // 'p'id
//						report_mode = REPORT_PID;
//					else if (type == 'r') //'r'ate pid
//						report_mode = REPORT_RATE_PID;
//					else if (type == 'a') //'a'ltitude hold pid
//						report_mode = REPORT_ALTHOLD_PID;
//				}
//			}
//			else if (command == 'f') {// Set report 'f'ormat
//				char format = GetChar();
//				if (format == 'b') {// Report 'b'inary format
//					report_format = REPORT_FORMAT_BINARY;
//				}
//				else if (format == 't') {// Report 't'ext format
//					report_format = REPORT_FORMAT_TEXT;
//				}
//			}
//			else if (command == 's') {// 's'tream output control
//				char mode = GetChar();
//				if (mode == 's') {// 's'tart stream
//					stream_mode = STREAM_START;
//				}
//				else if (mode == 'p') {// 'p'ause stream
//					stream_mode = STREAM_PAUSE;
//				}
//				else if (mode == 't') {// 't'oggle stream
//					if(stream_mode==STREAM_START)
//						stream_mode = STREAM_PAUSE;
//					else
//						stream_mode = STREAM_START;
//				}
//			}
//		}
//		else { 
//			if (report_format == REPORT_FORMAT_TEXT) {
//			printf("Unknown command.\n");
//			}
			} // Skip character
		
			getUartData = FALSE;	//接收完成
	}
}
