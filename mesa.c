#include "mesa.h"

struct Mesa find_mesa(FILE* in, unsigned int *numbers, unsigned int count, unsigned int *length, unsigned int *height)
{
	fscanf(in, "%u %u", length, height);    // scan minimum height and length from the input file
    unsigned int currentHeight = 0;         // height of current mesa
    unsigned int currentBeginning = 0;      // beginning of current mesa
    unsigned int currentWeight = 0;         // weight of current mesa

    unsigned int maxHeight = 0;             // height of maximum mesa
    unsigned int maxBeginning = 0;          // beginning of maximum mesa
    unsigned int maxEnd = 0;                // end of maximum mesa
    unsigned int maxWeight = 0;             // weight of maximum mesa
    
    for (unsigned int i = 0; i < count; i++)    // iterate through all arrays
    {
        if (i==0)   // for the first item
        {
            currentHeight = numbers[0];     // current height set to first item
            currentWeight = currentHeight;  // current weight is just current height because there is only 1 length
            maxHeight = currentHeight;      // max height is also current height
            maxWeight = currentHeight;      // max weight is also current weight
        }
        else
        {
            if (numbers[i] == currentHeight)    // if the mesa remains unbroken
            {
                currentWeight += currentHeight; // increase weight accordingly
                if ((currentWeight > maxWeight) && (currentHeight >= *height) && ((i-currentBeginning+1) >= *length))   // if mesa is larg
                {
                    maxBeginning = currentBeginning;    // beginning of the max mesa is current beginning
                    maxEnd = i;                         // end of the max mesa is current index
                    maxWeight = currentWeight;          // weight of the max mesa is current weight
                    maxHeight = currentHeight;          // height of the max mesa is current height
                }
            }
            else
            {
                currentHeight = numbers[i];             // current height changes to a new number
                currentWeight = currentHeight;          // current weight changes to the new height
                currentBeginning = i;                   //  current beginning is now the beginning of a new mesa
            }
        }
    }

    // make a new mesa and set values to the maximum mesa values
    struct Mesa m;
    m.start = maxBeginning;
    m.end = maxEnd;
    m.height = maxHeight;
    m.weight = maxWeight;
    if ((maxHeight >= *height) && ((maxEnd-maxBeginning+1) >= *length)) // if height of the mesa is at least minimum height and length is at least minimum length
    {
        m.valid = true; // mesa is valid
    }
    else
    {
        m.valid = false;// mesa is invalid
    }
    return m;   // return mesa
}

void display_mesa(FILE* out, struct Mesa m)
{
    if (m.valid)    // only prints out statistics if the largest mesa was found
        fprintf(out, "Start\tEnd\tHeight\tWeight\n%d\t\t%d\t%d\t\t%d\n\n", m.start, m.end, m.height, m.weight);
    else            // otherwise, don't print anything
        fprintf(out, "No valid mesa found.\n\n");
}