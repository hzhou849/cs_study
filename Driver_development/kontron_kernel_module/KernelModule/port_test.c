/* read write to port */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <inttypes.h>


#define BASEPORT 0x20C
#define DATA_REGISTER_OFFSET 0
#define STATUS_REGISTER_OFFSET 1
#define COMMAND_REGISTER_OFFSET 1

#define CMD_GET_FAN_RPM 0x15

int main()
{

	unsigned int data1 =0;
	unsigned int data2 =0;

	// get access to port
	if (ioperm(BASEPORT, 32, 1)) {perror("ioperm"); exit(1);}

	//set data signal for port to 0x1d
	outb(0x00, BASEPORT+1);

	//100ms sleep
	usleep(100000);

	// send command
// static u32 ite8516k_send_cmd (u8 cmd)
// {
// 	int timeout = 10000;
	
// 	if (!ite8516k_wait_ibf())
// 		return ITE8516K_IOCMD_ERROR;
	
// 	while ((inb(ite8516k_baddr + ITE8516K_REG_STATUS) & ITE8516K_STATUS_BMODE) && (timeout))
// 	{
// 		outb(0x00, ite8516k_baddr+ITE8516K_REG_CMD);
// 		if (!ite8516k_wait_ibf())
// 			return ITE8516K_IOCMD_ERROR;
		
// 		inb(ite8516k_baddr + ITE8516K_REG_DATA);
// 		timeout--;
// 	}

// 	if (!timeout)
// 		return ITE8516K_IOCMD_ERROR;
	
// 	outb(cmd, ite8516k_baddr + ITE8516K_REG_CMD);

// 	return 0;
// }
	//s
	printf("status: %x\n", inb(BASEPORT+1));
	printf("status: %d\n", inb(BASEPORT));
	outb(0x00, BASEPORT+1);
	outb(0x1d, BASEPORT+0);

	data1 = inb(BASEPORT+1);
	data2 = inb(BASEPORT);

	printf("status_post: %x\n", inb(BASEPORT+1));
	printf("Status_post2 %d\n", inb(BASEPORT));

	//terminate ports
	if (ioperm(BASEPORT,32, 0)) {perror("ioperm"); exit(1);}
	exit (0);
}