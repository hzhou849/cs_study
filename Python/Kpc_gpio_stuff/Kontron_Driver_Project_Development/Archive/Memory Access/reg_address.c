/* Register access embedded with BASE address and OFFset address 
 from: https://www.linuxquestions.org/questions/programming-9/accessing-register-values-in-c-321431/
*/
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm/io.h>
#include "rtc-reg.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

int main()
{
  int mem;
  char status;
  char *mmStatus;
  void *statusAdr;

  /* Open /dev/mem */
  if ((mem = open ("/dev/mem", O_RDONLY | O_SYNC)) == -1)
    fprintf(stderr, "Cannot open /dev/mem\n"), exit(1);

  /* open RTC_STATUS_REG */
  if ((mmStatus = (char *)mmap(0, MAP_SIZE, PROT_READ, MAP_SHARED, mem, RTC_STATUS_REG & ~MAP_MASK)) == NULL)
    fprintf(stderr, "Cannot open Memory Map\n"), exit(1);
  statusAdr = mmStatus + (RTC_STATUS_REG & MAP_MASK);

  while(1)
  {
    status = *((volatile unsigned char *)statusAdr);

    if ((status&01) == 0)
      break;
  }

  /* close all registers */
  if (munmap(mmStatus, MAP_SIZE) == -1)
    fprintf(stderr, "Cannot close Memory Map"), exit(1);

  /* close /dev/mem */
  close(mem);

  return 0;
}
