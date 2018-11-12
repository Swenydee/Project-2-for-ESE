#include <stdio.h> 
#include <windows.h>					// Contains WAVEFORMATEX structure
#include <mmsystem.h>					
#include <math.h>
#include <time.h>
#include "sound.h"
#include "queues.h"
#include "messages.h"
#include "menus.h"
#include "RS232Comm.h"

int playMen(short * iBigBuf, long lBigBufSize) {
	int exit = 0;
	int playSel = 0;

	printf("\nPlease choose one of the options below:\n1)Play from buffer.\n2)Save from buffer.\n3)Go back.\n4)Exit.\n");
	scanf_s("%i", &playSel);
	switch (playSel) {
	case 1:
		// playback recording 
		printf("\nPlaying recording from buffer\n");
		PlayBuffer(iBigBuf, lBigBufSize);
		ClosePlayback();
		break;
	case 2:
		// save recording
		break;
	case 3:
		// return 2, which causes the previous menu to display
		exit = 2;
		break;
	case 4:
		// return 1, which exits the program
		exit = 1;
		break;
	}
	return(exit);
}

int recordMen(short* iBigBuf, long  lBigBufSize, short* iBigBufNew, char * message) {
	int menselect = 0;
	char c = NULL;
	int rate = 8000;
	int recTime = 1;
	int exit = 0;
	while ((c = getchar()) != '\n' && c != EOF) {}							// Flush other input

	printf("\nPlease choose one of the options below:\n1)Set recording length.\n2)Set sample rate\n3)Begin recording.\n4)Go back.\n5)Exit.\n");
	scanf_s("%i", &menselect);
	switch (menselect) {
	case 1:
		// get the number of seconds to record from the user
		while ((c = getchar()) != '\n' && c != EOF) {}							// Flush other input
		printf("\nEnter the number of seconds that you want to record: ");
		scanf_s("%i", &recTime);
		break;
	case 2:
		// get the sample rate from the user
		printf("\nPlease enter the desired sample rate (8 or 16 kHz): ");
		scanf_s("%i", &rate);
		break;
	case 3:
		// start recording
		lBigBufSize = recTime * rate;
		iBigBufNew = (short*)malloc(lBigBufSize * sizeof(short));
		// initialize playback and recording
		InitializePlayback(rate);
		InitializeRecording(rate);
		RecordBuffer(iBigBuf, lBigBufSize);
		CloseRecording();
		break;
	case 4:
		// return 2, which causes the previous menu to display
		exit = 2;
		break;
	case 5:
		// return 1, which exits the program
		exit = 1;
		break;
	}
	return(exit);
}

int sendMen(char * messageOut, int bufSize) {
	int choice = 0;
	int exit = 0;
	char c = NULL;

	printf("\nWould you likie to send a:\n1)Text message.\n2)Audio message.\n3)Go back.\n4)Exit.\n");
	scanf_s("%i", &choice);
	switch (choice) {
	case 1: // text message either from user or from the file
		printf("Would you like to:\n1)Create your own message.\n2)Send a random fortune.\n");
		scanf_s("%i", &choice);
		switch (choice) {
			case 1: // get a message from the user
				while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
				printf("Type your message below (max 140 characters):\n");
				scanf_s("%c", messageOut);
				while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
				break;
			case 2: // pull a quote from the file
				randomQuote(messageOut, bufSize);
				break;
		}
		if (strcmp(messageOut, "") == 0) { // do something else to test???
			printf("\nNo message to send, please enter a message first.\n");
		}
		else {
			outputToPort(messageOut, strlen(messageOut) + 1);			// Send string to port - include space for '\0' termination
			Sleep(1000);
		}
		break;
	case 2:
		// for audio 
		break;
	case 3:
		exit = 2; // set the returned value to go back to the previous menu
		break;
	case 4:
		exit = 1; // set the return value to exit the program
		break;
	}
	return(exit);
}