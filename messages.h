/* messages.h : Header file for messages.cpp
*				By: Kevin MacIntosh
*				Based off code provided by: Michael Galle
*/
#pragma once

 // function that counts the number of quotes in the file. Takes in: file pointer. Returns: the number of quotes in the file.
int quoteCounter(FILE * file);

// function that finds the location of the first letter of each quote using the offset from the start of the file. Takes in: file pointer, number of quotes. Returns: an array of the offsets.
long int * quoteIndexer(FILE * file, int quoteCount);

// function that determines the length of each quote. Takes in: file pointer, the number of quotes and the quote index. Returns: an array of quote lengths that matches the index array.
int * getQuoteLength(FILE * file, int quoteCount, long int * quoteIndex); 

// Function that randomly retrieves a message from the file and saves it to the buffer (szBuf) adding and string terminator to the end. 
// Takes in: file pointer, the number of quotes, the quote index and the quote lengths. Returns: 0 if it succeeds or non-zero if it fails
int GetMessageFromFile(FILE * file, char szBuf[], int iLen, int numQuotes, long int * quoteIndex, int * quoteLength); 

// wrapper that gets a random quote from the file
void randomQuote(char *messageOut, int bufSize);
