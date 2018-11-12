/* messages.cpp :	Source code for retrieving and collecting data from a file in the format of messages
*					By: Kevin MacIntosh
*					Based off code provided by: Michael Galle
*/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "messages.h"

// function that counts the number of quotes in the file. Takes in: file pointer. Returns: the number of quotes in the file.
int quoteCounter(FILE * file){

	int count = 0; //declare and initialize conut

	// search for two % in a row, increase counter when they are reached. Repeat until the end of the file.
	while (!feof(file))  {
		if (fgetc(file) == '%') {
			if (fgetc(file) == '%') {
				count++;
			}
		}
	}

	return(count); // return the number of quotes
}

// function that finds the location of the first letter of each quote using the offset from the start of the file. Takes in: file pointer, number of quotes. Returns: an array of the offsets.
long int * quoteIndexer(FILE * file, int numQuotes){

	//declare and initialize the variables
	char temp;
	int count = 0;
	long int * quoteIndex = (long int *)malloc(sizeof(long int)*numQuotes);

	fseek(file, 0, 0); // return to the start of the file
	
	// Until the end of the file is reached, search for two consecutive %, then set the offse of the next character as the start of a quote
	while (!feof(file)) {
		if (fgetc(file) == '%') {
			if (fgetc(file) == '%') {
				quoteIndex[count] = ftell(file); // add the offset of the character to the array
				count++; // increase the location in the index
			}
		}
	}//end while
	return(quoteIndex); // return the index array
}

// function that determines the length of each quote. Takes in: file pointer, the number of quotes and the quote index. Returns: an array of quote lengths that matches the index array.
int * getQuoteLength(FILE * file, int numQuotes, long int * quoteIndex) {
	// declare and initialize variables 
	int count = 1;
	long int temp = 0;
	int curIndex = 0;
	int * quoteLengths = (int *)malloc(numQuotes * sizeof(int));

	
	fseek(file, 0, 0);//return to the start of the file

	// until the end of the file is reached, jump to the start of each quote using the quote index, then count the characters in the quote up to 140 characters. 
	while (!feof(file)) {
		fseek(file, quoteIndex[curIndex], 0);// jump to the start of a quote
			
			// check characters one at a time for two consecutive % or 140 characters is reached or end of file is reached, meaning that is the end of the quote.
			for (count = 1; count <= 140; count++) {
				if (fgetc(file) == '%' && fgetc(file) == '%') { // double % reached
					quoteLengths[curIndex] = count - 1; // set the currentcount minus one as the length
					count = 141; // set count to exit loop
				}
				else if (count == 140) { // 140 characters reached
					quoteLengths[curIndex] = count + 3; // set current count plus 3 as length
				}
				else if (feof(file)) { // end of file is reached
					quoteLengths[curIndex] = count - 1; // set the currentcount minus one as the length
					count = 141; // set count to exit loop
				} // end if else
			}  //end for    
			
			curIndex++; //go to the next index
		}//end while

	return(quoteLengths); // return the array of quote lengths
}

// Function that randomly retrieves a message from the file and saves it to the buffer (szBuf) adding and string terminator to the end. 
// Takes in: file pointer, the number of quotes, the quote index and the quote lengths. Returns: 0 if it succeeds or non-zero if it fails
int GetMessageFromFile(FILE * file, char szBuf[], int iLen, int numQuotes, long int * quoteIndex, int * quoteLength) {

	//declare and initialize variables
	int ran = 0;
	int quoteLocation = 0;
	int count = 0;
	
	quoteLocation = rand() % (numQuotes - 1); // randomly generate a number between 0 and the number of quotes minus one using the time.

	// if the random number is outside of the range of the quotes, return that the function failed and exit function
	if (quoteLocation < 0 || quoteLocation >(numQuotes - 1))
		return(1); // return a fail state

	fseek(file, quoteIndex[quoteLocation], 0); // jump to the location of the first character in the quote

	// fill the buffer with the quote
	while (count < quoteLength[quoteLocation]) {
		szBuf[count] = fgetc(file); // put characters one by one into the buffer
		count++; // increase the count
	} // end while

	szBuf[quoteLength[quoteLocation]] = '\0'; // add the string terminator to the end of the message

	return(0); // return a success state
} //end function

void randomQuote(char *messageOut, int bufSize) {

	int iLen;
	int numQuotes;
	long int * quoteIndex;
	int * quoteLength;
	int success = 0;

	//create a pointer for the file
	FILE * file;
	errno_t err;

	//If there is an error, display an error message, else continue 
	if ((err = fopen_s(&file, "FortuneCookies.txt", "r")) != 0)
		printf("File was not opened\n");
	else {
		srand(time(NULL)); // seed the random generator

		numQuotes = quoteCounter(file); //call the function to count the number of quotes in the file

										// initialize quote index and length arrays based on the number of quotes in the file
		quoteIndex = (long int *)malloc(numQuotes);
		quoteLength = (int *)malloc(numQuotes);

		quoteIndex = quoteIndexer(file, numQuotes); // call the function to index the location of the first letter of each quote

		quoteLength = getQuoteLength(file, numQuotes, quoteIndex); // call the function that determines the length of each quote and stores them in an array that matches with the index array

		success = GetMessageFromFile(file, messageOut, bufSize, numQuotes, quoteIndex, quoteLength);
	}
}