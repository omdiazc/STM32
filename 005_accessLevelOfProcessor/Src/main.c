

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void changeAccessLevel();
void generate_interrupt();

int main(void)
{
	changeAccessLevel();

	generate_interrupt();
	for(;;);
}

void changeAccessLevel(){

	__asm volatile("MRS R0 , CONTROL"); // store control in R0
	__asm volatile("ORR R0, R0, #0X01");// negates R0
	__asm volatile("MSR CONTROL, R0");// store R0 in control

}


void generate_interrupt(){
	//this method needs PAL mode

	int *pSTIR 		= (int *) 0xE000EF00;
	int *pISER0 	= (int *) 0xE000E100;

	//Enable IRQ3 interrupt
	*pISER0 |= (1<<3);

	*pSTIR  =	(3 & 0x1FF);


}

void HardFault_Handler(void){
	// Called when a HardFault happen

	printf("HARD FAULT DETECTED \n");
	while(1);

}
