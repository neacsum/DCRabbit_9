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
/**************************************************************************
	board_id.c

	This sample program is for the Smart Star series controllers.
	
	This program will detect the controller type that you have (via product
	ID) and will display that information in the STDIO window. Here's the
	controllers product information. 

	Board Setup:
	------------------------
	1. Connect a +24v power source to the backplane PWR connector
	   as follows:

	   PS     	Backplane
	   --			-----------------
	   +24v		+RAW Terminal  
	   GND      GND Terminal


	Product ID     Product Description
	---------- 		-------------------
	0x0501			SR9110...18MHz Smart Star
	0x0502			SR9100...25Mhz Smart Star, no ethernet
	0x0C00			SR9150...22MHz SmartStar CPU, ethernet
	0x0C01			SR9160...22MHz SmartStar CPU, no ethernet
			 
**************************************************************************/

///////////////////////////////////////////////////////////////////////////

void main()
{
	auto char * ptr[5];
	auto int i;

	ptr[2] = "SR9100...25Mhz Smart Star, no ethernet";
	ptr[0] = "SR9150...22MHz SmartStar CPU, ethernet";
	ptr[1] = "SR9160...22MHz SmartStar CPU, no ethernet";
	ptr[3] = "SR9110...18MHz Smart Star";

	/*
	 *  It used to be that the last digit was enough to tell all models
	 *  apart. However, now 0x0C01 and 0x501 exist.  So use a switch
	 *  statment.
	 */
	switch( _BOARD_TYPE_ )
	{
		case SR9100 :	i = 2;	break;
		case SR9110 :	i = 3;	break;
		case SR9150 :	i = 0;	break;
		case SR9160 :	i = 1;	break;

		default :
				printf("\n\n\rNote: Invalid controller BOARD_ID detected!!!");
				exit(2);
	}

	// display controller information in the STDIO window	
	printf("\n\n\rController is a %s\n", ptr[i]);

}


	