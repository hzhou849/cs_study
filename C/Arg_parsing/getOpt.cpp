/*
 * getopt c++
 *
 * used to create argument handling flags options 
 * 
 * example:
 * getopt [-dmp] [-s name] -f name file [file...]
 * 
 * requires two external variables:
 * 
 *
 * 	1) extern char *optarg: 
 *		- used when parsing options that take a name as a parameter
		(ie. the -s <name> and -f <name>)
		- contains a pointer to that parameter

 * 
 *  2)extern int optind;
 *  - is the current index into the main function's argument list.
 *  - used to find arguments after all the option processing is done.
 * 
 * 
 * 
 * usage: getopt(argc, argv, "df:mps:")
 * 	* flag that requires an extra parameter ie '-f' and '-s'
 *    is suffixed by a : colon
 * 
 *
 * example of command line parsing via getopt
 * usage of app: getopt [-dmp] -f fname [-s sname] name [name..] 
 * 
 * sample:
 *  ./main dp -f test -s "more stuff" blah						
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int debug = 0;

int main (int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int mflag=0, pflag=0, fflag=0;
	char *sname = "default_sname", *fname;
	static char usage[] = "usage: %s [-dmp] -f fname [-s sname] name [name...]\n";
	static char sample[] = "./main dp -f test -s \"more stuff\" blah\n";

	while ((c = getopt(argc, argv, "df:mps:")) != -1)
		switch (c) {
			case 'd':
				debug = 1;
				
				break;
			case 'm':
				mflag = 1;
				
				break;
			case 'p':
				pflag = 1;
				
				break;
			case 'f':
				fflag = 1;
				
				fname = optarg;
			case 's':
				sname = optarg;
				break;

			case '?':
				err = 1;
				break;

		}
	if ( fflag ==0 ) {  		// -f was mandatory
		fprintf(stderr, "%s: missing -f option \n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		fprintf(stderr, sample, argv[0]);
		exit(1);
	} else if ((optind+1) > argc) {
		/*need at lease one argument (change +1 to +2 for two etc..)*/
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	/* see what we have */
	printf("debug = %d\n", debug);
	printf("pflag = %d\n", pflag);
	printf("mflag = %d\n", mflag);
	printf("fname = \"%s\"\n", fname);
	printf("fname = \"%s\"\n", sname);

	// these are the arguments after the command-line options
	if (optind <argc)
		for (; optind < argc; optind++)
			printf("argument: \"%s\"\n", argv[optind]);

}


