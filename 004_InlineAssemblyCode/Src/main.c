
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void inlineAssemblyOne();
void inlineAssemblyTwo();
void inlineAssemblySix();
void inlineAssemblySeven();


int main(void)
{
	inlineAssemblySeven();


	//inlineAssemblySix();

	for(;;);
}


void inlineAssemblyOne(){

	//Store two memory address into two registers, read those memory address then sum them storing the answer in a register and then
	//store it into memory.


	__asm volatile("LDR R1, =#0x20001000"); //LOAD 0X20001000 	in R1
	__asm volatile("LDR R2, =#0X20001004");

	__asm volatile("LDR R0, [R1]");  //  Load into R0 from the memory location that is stored in R1
	__asm volatile("LDR R1, [R2]");  //  Load into R0 from the memory location that is stored in R1

	__asm volatile("ADD R0, R0,R1"); //  ADD operation, the first R0 is where the result will be allocated, then R0 and R1 are the operands.
	__asm volatile("STR R0, [R2]"); // Storeback,

	// LDR is used to load something from memory into a register, and STR is used to store something from a register to a memory address.


}

void inlineAssemblyTwo(){

	//Move value from a variable or immediate value to a register

	int mem1 = 2;
	int mem2 = 3;

	__asm volatile ("MOV R0, %0": : "r"(mem1));
	__asm volatile ("MOV R1, %0": : "r"(mem2));


	__asm volatile("MOV R0, %0": : "i"(0x02)); 		// I means immediate value

}


void inlineAssemblythree(){

	//Move from special register to register and move from a register to special register
	// This instructions needs PAL access


	// Special registers = APSR , IPSR , EPSR , IEPSR , IAPSR , EAPSR , PSR , MSP , PSP , PRIMASK , BASEPRI ,
	//  BASEPRI_MAX , FAULTMASK , or CONTROL

	// MRS special reg -> reg
	// MSR reg -> special reg


	//read CONTROL and store it in control_reg

	int control_reg;
	__asm volatile ("MRS %0, CONTROL":"=r"(control_reg));

}

void inlineAssemblyFour(){

	// Copy var1 value to var2

	int var1 = 20, var2;

	__asm volatile("MOV %0 ,%1": "=r"(var2): "r"(var1));

}


void inlineAssemblyFive(){

	// Copy the content of a pointer into another variable

	int p1, *p2;

	p2 = (int*)0x20000008;

	__asm volatile("LDR %0, [%1]":"=r"(p1): "r"(p2)); // p1 = *p2


}

void inlineAssemblySix(){

	// Change the value of a memory address


	int *var = (int *) 0x20001004;	// create a pointer to the 0x20001004 position of the memory
	*var = (int) 20;						// change the value of the memory position of the pointer to 20
}



void inlineAssemblySeven(){

	// Store 2 numbers in memory, copy to register, sum them and store it answer back in memory

	int *var1 = (int *) 0x20001000,*var2 = (int *) 0x20001004;
	*var1 = (int) 3;
	*var2 = (int) 4;

	__asm volatile ("LDR R1 , [%0]"::"r"(var1));
	__asm volatile ("LDR R2 , [%0]"::"r"(var2));

	__asm volatile ("ADD R0, R1, R2");
	__asm volatile ("STR R0, [%0]":"=r"(var1));



}























