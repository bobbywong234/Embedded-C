/*
 * String
 *
 *  Created on: Jun 10, 2021
 *      Author: bobby
 */

#ifndef STRING_
#define STRING_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* StringBuilder(int size){
   char* string = (char*)malloc(size * sizeof(char));
   return string;
}

void StrAppend(char input, char* output){
	bool flag = true;
	int i = -1;
	while(flag){
		if(output[++i] == '\0'){
			output[i] = input;
			flag = false;
		}
	}
}

int* partialMatch(char* subStr){
	bool flag = true;
	int i = -1;
	int* pattern=(int*)malloc(sizeof(int));
	pattern[0] =0;
	while(flag){
		if(subStr[++i] == '\0'){
			flag = false;
			continue;
		}
		int partialMatchNumber = 0;
		for(int prefix=0;prefix<=i-1;prefix++){
			partialMatchNumber = 0;
			for(int partial =0;partial<=prefix;partial++){
				if(subStr[partial] == subStr[i-prefix+partial]){
					partialMatchNumber ++;
				}
			}
			if(partialMatchNumber != 0)
			 pattern[i]=partialMatchNumber;
		}
	}
	return pattern;
}

/*
int* next(char* subStr){
	int i=1,j=0;
	int* partialMatch = (int*)malloc(sizeof(int));
	partialMatch[1] = 0;
    while(subStr[i] != '\0'){
    	if(j==0||subStr[i-1] == subStr[j-1]){
    		i++;j++;
    		if(subStr[i-1]!=subStr[j-1]) {
    			partialMatch = (int*)realloc(partialMatch,(i+1)*sizeof(int));
    			partialMatch[i] = j;
    		}
    		else{
    			partialMatch = (int*)realloc(partialMatch,(i+1)*sizeof(int));
    			partialMatch[i] = partialMatch[j];
    		}
    	}
    	else
    		j=partialMatch[j];
    }
    return partialMatch;
}*/

int* next(char* subStr,int depth){
	int i=1,j=0;
	int* partialMatch = (int*)malloc(2*sizeof(int));
	partialMatch[1] = 0;
	while(i<=depth){
	    if(j==0||subStr[i-1] == subStr[j-1]){
	    	i++;j++;
	    	if(subStr[i-1]!=subStr[j-1]) {
	    		partialMatch = (int*)realloc(partialMatch,(i+1)*sizeof(int));
	    		partialMatch[i] = j;
	    	}
	    	else{
	    		partialMatch = (int*)realloc(partialMatch,(i+1)*sizeof(int));
	    		partialMatch[i] = partialMatch[j];
	    	}
	    }
	    else
	    	j=partialMatch[j];
	}
	return partialMatch;
}

bool KMP(char* mainStr, char* subStr){
	bool isMatched = false;
	bool flag = true;
	int index = 0;
	int depth = 0;
	int* pattern;
	while(flag){
		if(mainStr[index] == '\0'){
			flag = false;
			continue;
		}
		int subIndex=0;
		bool subFlag;
		int partial =0;
		while(subFlag){
			if(subIndex >= depth){
				pattern = next(subStr,++depth);
			}

			if(subStr[subIndex] == '\0' ){
				subFlag = false;
				if(partial == subIndex){
					flag = false;
					isMatched = true;
					printf("%i\n",index);
				}
				continue;
			}

			if(subStr[subIndex] != mainStr[subIndex+index]){
				partial-=pattern[subIndex+1];
				break;
			}else
				partial++;

			subIndex++;
		}
		if(partial == 0)
			index++;
		else
			index += partial;
	}
	return isMatched;
}

#endif /* STRING_ */
