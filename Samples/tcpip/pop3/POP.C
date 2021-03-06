/*
   Copyright (c) 2015, Digi International Inc.

   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
/*******************************************************************************
        pop.c

        A simple program that will connect to a POP3 server and download
        e-mail form it, optionally deleting the messages after they have
        been read.
*******************************************************************************/

/***********************************
 * Configuration                   *
 * -------------                   *
 * All fields in this section must *
 * be altered to match your local  *
 * network settings.               *
 ***********************************/

#class auto


/***********************************
 * Configuration                   *
 * -------------                   *
 * All fields in this section must *
 * be altered to match your local  *
 * network settings.               *
 ***********************************/

/*
 * Pick the predefined TCP/IP configuration for this sample.  See
 * LIB\TCPIP\TCP_CONFIG.LIB for instructions on how to set the
 * configuration.
 */
#define TCPCONFIG 1


/*
 * POP3 settings
 */

/*
 *	Enter the name of your POP3 server here.
 */
#define POP_HOST	"mail.domain.com"

/*
 * This is the username and password for the account on the
 * pop3 server.  These names must not change until complete.
 */
#define POP_USER	"myname"
#define POP_PASS	"secret"

/* Uncomment this to show extra debug output */
//#define POP_DEBUG

/* comment this out to delete the messages off the server after they are read */
#define POP_NODELETE

/********************************
 * End of configuration section *
 ********************************/
 
#memmap xmem
#use "dcrtcp.lib"
#use "pop3.lib"

/*
 * 	This is the no POP_PARSE_EXTRA calling style.
 */
int n;
int storemsg(int num, char *buf, int len)
{
#GLOBAL_INIT
	{
		n = -1;
	}

	if(n == -1) {
		n = num;
		printf("RECEIVING MESSAGE <%d>\n", n);
	}

	if(n != num) {
		n = num;
		printf("RECEIVING MESSAGE <%d>\n", n);		
	}
	
	printf("MSG_DATA> '%s'\n", buf);

	return 0;
}

void main()
{
	static long address;
	static int retval;
	
	sock_init();
	// Wait for the interface to come up
	while (ifpending(IF_DEFAULT) == IF_COMING_UP) {
		tcp_tick(NULL);
	}

	pop3_init(storemsg);

	printf("Resolving name...\n");
	address = resolve(POP_HOST);
	printf("Calling pop3_getmail()...\n");
	pop3_getmail(POP_USER, POP_PASS, address);

	printf("Entering pop3_tick()...\n");
	while((retval = pop3_tick()) == POP_PENDING)
		continue;

	if(retval == POP_SUCCESS)
		printf("POP was successful!\n");
	if(retval == POP_TIME)
		printf("POP timed out!\n");
	if(retval == POP_ERROR)
		printf("POP returned a general error!\n");
		
	printf("All done!\n");
}