/*
 *  Copyright 2011 Chen-Hsiung Liu, Lung-Sheng Chien, Cheng-Hung Lin,and Shih-Chieh Chang
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../include/PFAC_P.h"

#define  PFAC_TABLE_MAP( i , j )   (i)*CHAR_SET + (j)

PFAC_status_t  PFAC_CPU(char *input_string, int input_size,
    int *PFAC_table,
    int num_finalState, int initial_state,
    int *match_result)
{
    int start;
    int pos; // position to read input for the thread
    int state;
    int inputChar;
    int match_pattern = 0;

    if ( num_finalState > initial_state ){
        return PFAC_STATUS_INTERNAL_ERROR ;
    }

    // initialize match result on CPU
    for (pos = 0; pos < input_size; pos++) {
        match_result[pos] = 0;
    }

    for (start=0; start < input_size; start++) {
    	
        state = initial_state;
        pos = start;
        while ( (pos < input_size) ) {
            // read input character
            inputChar =(unsigned char)input_string[pos];
            
            state = PFAC_table[ PFAC_TABLE_MAP(state,inputChar)];

            if ( TRAP_STATE == state ){ break ; }

            // output match pattern
            if(state <= num_finalState ){
                match_pattern = state;
                match_result[start] = match_pattern;
            }

            pos = pos + 1;
        }
    }

    return PFAC_STATUS_SUCCESS ;

}
