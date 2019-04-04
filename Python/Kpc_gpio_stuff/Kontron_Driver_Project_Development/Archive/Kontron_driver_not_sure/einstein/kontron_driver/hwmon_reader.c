I’m hoping to get some information about the “host” CPU interface to access the board status and GPIO on the KTQM87 boards via the onboard ITE8516 embedded controller.  In particular, we were wondering if you have any written documentation that describes any of the following:
 
•        the I/O base address (0x020c) used to access hardware
•        the commands used to access firmware version information (0x01, 0x02)
•        the commands used to access the temperature (0x20) and fan speed (0x1d)
•        the commands used to access voltage measurements
•        the commands used to control GPIO pin direction (0x31), read input pins (0x32), and set output pins (0x33)

prototype code to read hwmon from ubuntu device files
 
---
//To read the 12v level – input should be “0”
int voltageRead(int input)
{
                char value[3];
               char path[BUFFER_SIZE];
                int fd;
 
// open the voltage port
                snprintf(path, BUFFER_SIZE, "/sys/class/hwmon/hwmon2/device/in%d", input);
                fd = open(path, O_RDONLY);
                if (fd == -1)
                {
                     fprintf(stderr, "Failed to open 12V for reading!\n");
                     close(fd);
                     return(-1);
                }
 
// read the value
                if (read(fd, value, 3) == -1)
                {
                                fprintf(stderr, "Failed to read 12V value!\n");
                                close(fd);
                                return(-1);
                }
 
// close the file handle and return the value that was read
                close(fd);
                return(atoi(value));
}
---
 
Give this a try and see how it works…
 
--mark