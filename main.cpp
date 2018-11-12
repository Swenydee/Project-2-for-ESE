/*	Filename: main.cpp
Author: Michael Galle
Date: Nov 2017
Details: Testing mainline for Windows sound API
*/


#include <stdio.h>
#include <windows.h>
#include "sound.h"
#include "queues.h"
#include "messages.h"
#include "menus.h"
#include "RS232Comm.h"

#define BUFSIZE 140			

extern short* iBigBuf;			// buffer
extern long  lBigBufSize;		// total number of samples


int	main(int argc, char *argv[])
{
	short* iBigBufNew = (short*)malloc(lBigBufSize*sizeof(short));		// buffer used for reading recorded sound from file
	int selection = 0;
	int recExit = 0;
	int mainExit = 0;
	int playExit = 0;
	int subExit = 0;
	char save = NULL;
	char replay = NULL;
	char c = NULL;	// used to flush extra input
	char * messageOut = (char *)malloc(140 * sizeof(char));
	strcpy_s(messageOut, BUFSIZE, "");
	char msgIn[BUFSIZE];							// Received message

	initPort();										// Initialize the port

	//create a pointer for the file
	FILE* f;
	errno_t err;

	
	do {
		printf("\nPlease enter the number corresponding to the menu option you would like:\n1)Record\n2)Playback\n3)Send\n4)Recieve\n5)Exit\n");
		scanf_s("%i", &selection);
		switch (selection) {
		case 1:
			do {
				subExit = recordMen(iBigBuf, lBigBufSize, iBigBufNew, messageOut);
				if (subExit == 1)
					mainExit = 1;
			} while (subExit == 0);
			break;
		case 2:
			do {
				subExit = playMen(iBigBuf, lBigBufSize);
				if (subExit == 1)
					mainExit = 1;
			} while (subExit == 0);
			break;
		case 3:
			do {
				subExit = sendMen(messageOut, BUFSIZE);
				if (subExit == 1)
					mainExit = 1;
			} while (subExit == 0);
			break;
		case 4:
			inputFromPort(msgIn, BUFSIZE);					// Receive string from port
			printf("\nMessage Received: %s\n\n", msgIn);	// Display message from port
			purgePort();
			break;
		case 5:
			mainExit = 1;
			break;
		}
		subExit = 0;
	} while (mainExit != 1);

	

	// save audio recording  
	//printf("Would you like to save your audio recording? (y/n): "); 
	//scanf_s("%c", &save);
	//while ((c = getchar()) != '\n' && c != EOF) {}							// Flush other input
	//if ((save == 'y') || (save == 'Y')) {
	//	/* Open input file */
	//	if ((err = fopen_s(&f, "C:\\myfiles\\recording.dat", "wb")) != 0) {
	//		printf("unable to open %s\n", "C:\\myfiles\\recording.dat");
	//		return 0;
	//	}
	//	printf("Writing to sound file ...\n");
	//	fwrite(iBigBuf, sizeof(short), lBigBufSize, f);
	//	fclose(f);
	//}
	//	
	//	// replay audio recording from file -- read and store in buffer, then use playback() to play it
	//	printf("Would you like to replay the saved audio recording from the file? (y/n): ");
	//	scanf_s("%c", &replay);
	//	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	//	if ((replay == 'y') || (replay == 'Y')) {
	//		/* Open input file */
	//		if ((err = fopen_s(&f, "C:\\myfiles\\recording.dat", "wb")) != 0) {
	//			printf("unable to open %s\n", "C:\\myfiles\\recording.dat");
	//			return 0;
	//		}
	//		printf("Reading from sound file ...\n");
	//		fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
	//		fclose(f);

	//		InitializePlayback();
	//		printf("\nPlaying recording from saved file ...\n");
	//		PlayBuffer(iBigBufNew, lBigBufSize);
	//		ClosePlayback();
	//	}
	printf("\n");
	system("pause");
	return(0);
}

