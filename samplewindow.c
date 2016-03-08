#include <stdio.h> 
#include <stdlib.h>
#include "samplewindow.h"

#define WINDOW_SIZE		60
#define TRANSFORMER_RATIO		0.05 //ratio of .05 volts per amp
#define THRESHOLD		10 //Threshold of change in calculated power, in terms of watts. Useful if returning boolean on event detected



int samplewindow(int *buffer, int currentsample){

		static int i = 0;
		static int old_avg = 0;
		static int current_avg = 0;
		const int *int_buffer = malloc(currentsample * WINDOW_SIZE * sizeof(int)); //can edit to use external or internal buffer depending on requirements
		
		
		buffer[i] = currentsample;
		i++;
		if (i >= WINDOW_SIZE){
			i = 0;
		
		
			int j, temp;
		
			for (j=0; j < WINDOW_SIZE; j++){
				buffer[j] += temp;
			}
			old_avg = current_avg;
			current_avg = (temp/WINDOW_SIZE)*TRANSFORMER_RATIO;
		
		}
				
		return current_avg; 

}

