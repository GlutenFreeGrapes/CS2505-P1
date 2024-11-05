#include "array.h"

unsigned int* create_array( FILE* in, unsigned int *size )
{
	fscanf(in, "%u", size);	// scans the first unsigned int from the file into size
	unsigned int* array = malloc(*size * sizeof(int));	// dynamically allocate array given size
	return array;	// return pointer to the array
}

unsigned int* free_memory( unsigned int* pointer )
{
	free(pointer);	// free up pointer memory
	pointer = NULL;	// null out pointer
	return pointer;	// return nulled-out pointer
}

void read_data( FILE* in, unsigned int *data, unsigned int count )
{
	for ( unsigned int i=0; i<count; i++ )
		fscanf(in, "%u", &data[i]);
	/*get rid of the newline -- the * indicates to ignore this
	field that was read in via fscanf*/
	fscanf(in, "%*c" ); 
}

void display_data( FILE* out, unsigned int count, unsigned int* data )
{
	fprintf(out, "\n");	// line break at beginning

	// header row
	if (count<10)	// if 10 values in the array --> 10 header columns
	{
		for (unsigned int column = 0; column < count; column++)
		{
			fprintf(out, "\t%d",column);
		}
	}
	else	// otherwise make appropriate number of header columns
	{
		for (int column = 0; column < 10; column++)
		{
			fprintf(out, "\t%d",column);
		}
	}

	// output numbers in all complete rows
	for (unsigned int row = 0; row < (count/10); row++)	// iterate through all complete rows
	{
		fprintf(out, "\n%d",row);	// line break and row numbers for each row
		for (unsigned int column = 0; column < 10; column++)	// iterate through that row
		{
			fprintf(out,"\t%d",data[(row*10)+column]);	// add tabs between numbers
		}
	}

	// place remaining digits
	if (count % 10 > 0)	// if there are still numbers left to paste in
	{
		fprintf(out, "\n%d",(count/10));	// make new row
		for (unsigned int column = 0; column < count%10; column++)	//iterate through remaining numbers
		{
			fprintf(out, "\t%u", data[count - (count%10) + column]);//paste numbers with tabs in between
		}
	}
	fprintf(out, "\n");	// line break at end
}
