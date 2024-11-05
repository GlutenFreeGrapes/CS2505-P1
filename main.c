#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "mesa.h"

/**
	argc = number of arguments
	argv = the actual arguments
		argv[0] = the name of your executable
		argv[1] = the first argument to your executable on the command line
		argv[2] = the second argument to your executable
		etc.
*/
int main(int argc, char* argv[])
{
	if ( argc != 3 )
	{
		fprintf( stderr, "Usage: %s <input-file> <output-file>\n", argv[0] );
		exit(1);
	}

	//open input and output files here
	FILE* in;
	in = fopen(argv[1], "r");
	FILE* out;
	out = fopen(argv[2], "w");

	//-------------------------------

	//get data from input file in a format you can use it for the first set
	//HINT: what functions are you creating in other files?

	unsigned int size = 0;
	unsigned int minLength = 0;
	unsigned int minHeight = 0;
	unsigned int* array = create_array(in, &size);
	read_data(in, array, size);
	//--------------------------------

	int set = 1;

	while( !feof(in) )
	{
		//print header for each Mesa in output file
		fprintf(out,"Set %d\n", set );
		for ( int i = 0; i < 55; i++)
			fputs("-", out);
		fputs("\n", out);
		//-----------------------------------------

		
		//find the largest Mesa
		struct Mesa maxMesa = find_mesa(in, array, size, &minLength, &minHeight);

		//------------------------
		
		//print all necessary information about the minimum length and height of the Mesas
		//print the largest Mesa if there is a valid one
		//otherwise, print that there is no valid Mesa
		//(see the examples in the assignment spec)
		fprintf(out, "Min Length: %u  Min Height: %u",minLength, minHeight);
		display_data(out, size, array);
		display_mesa(out, maxMesa);

		//------------------------
		

		//clean up any memory used for the first iteration
		free_memory(array);
		//------------------------

		set++;
		//get data from input file in a format you can use it for the next set
		//HINT: what functions are you creating in other files?
		if (!feof(in))
		{
			array = create_array(in, &size);
			read_data(in, array, size);
		}

		//------------------------
	}

	//clean up memory for the last iteration
	free_memory(array);
	
	//-----------------------


	//close input and output files here
	fclose(in);
	fclose(out);

	//-----------------------

	return 0;
}

