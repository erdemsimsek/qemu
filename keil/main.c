#include <stdint.h>

// Macro Definitions
#define HWREG(x)														(*((volatile uint32_t *)(x)))

// Constants
#define DATA_SIZE			(4u)

// Refer for datasheet: https://www.ti.com/lit/ds/symlink/lm3s811.pdf?&ts=1590054582270
// Datasheet page: 380

// UART Register ADDR				
#define UART0_DR_ADDR												(0x4000c000u)
#define UART0_INT_MASKED_STATUS_ADDR				(0x4000C040u)
#define UART0_INT_CLEAR_ADDR								(0x4000C044u)
#define UART0_INT_MASK_ADDR									(0x4000C038u)

// UART FLAGS				
#define UART0_RX_INT_FLAG										(0x00000010u)
#define UART0_TX_INT_FLAG										(0x00000020u)
#define UART0_RX_INT_ENABLE_FLAG						(0x00000010u)
#define UART0_TX_INT_ENABLE_FLAG						(0x00000020u)

// Static Global Variables
static uint8_t gs_data[DATA_SIZE];
				
void send (uint8_t data){
	
	
	HWREG(UART0_DR_ADDR) = data;
	
	while(!(HWREG(UART0_INT_MASKED_STATUS_ADDR) & UART0_TX_INT_FLAG));
	HWREG(UART0_INT_CLEAR_ADDR) = UART0_TX_INT_FLAG;
}


uint8_t receive(){

	volatile uint8_t data;

	// Wait for interrupt
	while(!(HWREG(UART0_INT_MASKED_STATUS_ADDR) & UART0_RX_INT_FLAG));
	
	// Read data
	data = HWREG(UART0_DR_ADDR);
	
	// Clear received interrupt
	HWREG(UART0_INT_CLEAR_ADDR) = UART0_RX_INT_FLAG;
	HWREG(UART0_DR_ADDR) = 0;
	
	return data;
}



int main ( void )
{
	uint8_t rx;
	uint8_t index;
	
	HWREG(UART0_INT_MASK_ADDR) = UART0_RX_INT_ENABLE_FLAG | UART0_TX_INT_ENABLE_FLAG;

#if 1
	
	
	for(index = 0; index < DATA_SIZE; index++){
		gs_data[index] = receive();
	}
	
	while(1){
		for(index = 0; index < DATA_SIZE; index++){
			send(gs_data[index]);
		}
	}
#else	
	
	rx = receive();
	
	while(1){
		
		send(rx);
	}
	
#endif	

  return(0);
}
