/*****************************************************************************
 * desCrack2.c                                                               *
 *                           Brute Force attack against DES                  *
 *                                                                           *
 *  THIS IS UNSUPPORTED FREE SOFTWARE. USE AND DISTRIBUTE AT YOUR OWN RISK.  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 *   REVISION HISTORY:                                                       *
 *                                                                           *
 *   Version 1.0:  Initial release                                           *
 *                                                                           *
 *****************************************************************************/
#include "des.h"
#include "desCrack2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static bool output[64];
static bool testValue[56];
//given plaintext converted to boolean array, this is the input for encryption every round
static bool input[64] = {0,1,0,0,1,1,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1};
//Given ciphertext converted to boolean array, output will be compared to this to check the key
static bool ciphertext[64] = {0,1,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,0,1,1,0,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1};

static char keyword[] = "AAAAAAA";
static int exitvar = 0;

int main(void)
	{
		int a;							//added to keep the command window open
		//****************************************

		testKeyZero();					//calls the method to brute force the key

		//****************************************
		scanf("%d", &a);				//added to keep the command window open
		printf("You entered: %d\n", a);	//added to keep the command window open
		return 0;
	}

/*
 * Checks to see if the text encrypted with the guessed key is equal to the known ciphertext
 */
int checkEquality(bool outpt[64], bool answer[64])
{
	int i, check;
	check = 1;
	for(i=0; i<64 && check; i++)
	{
		if(outpt[i] != answer[i])
			check = 0;
	}
	return check;
}

/*
* This is the method that does the bulk of the work. It checks all possible letters in the last position of the string (xxxxxxZ)
* and tries to encrpyt the message with each generated string, it will exit and print what the key is when it is found.
*/
void testKeySix(void)
{
	int i, j;
	char temp[8];
	strcpy(temp, keyword);
	temp[6]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[6]++;
		//printf("%s\n", temp); //used this for debugging purposes
		
		//*******************
		// This is where the program converts the string key to a boolean array which is used as the key in DES
		// A separate function call would've probably been a little nicer to work with
		{
			int i, j, k;
			for(i=0; i <7; i++)
			{
				for(j = 7; j >= 0; --j)
				{
					k =(i+1)*8-1-j;
					testValue[k] = ((temp[i] & (1 << j)) ? 1 : 0);
				}
			}
			EncryptDES(testValue, output, input, 0);
			if(checkEquality(output, ciphertext) != 0)
			{
				printf("%s is the key.\n", temp);
				exitvar = 10;
			}
		}

		//*******************
	}
}

/*
*	This function checks all values in position 5 of the key string (xxxxxZx) and checks every value in the last position
*	for each value in this position
*/
void testKeyFive(void)
{
	int i;
	char temp[8];
	strcpy(temp, keyword);
	temp[5]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[5]++;
		strcpy(keyword, temp);
		testKeySix();

	}
}

/*
*	This function checks all values in position 4 of the key string (xxxxZxx) and checks every value in the following positions
*	as well
*/
void testKeyFour(void)
{
	int i;
	char temp[8];
	strcpy(temp, keyword);
	temp[4]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[4]++;
		strcpy(keyword, temp);
		testKeyFive();
	}
}

/*
*	This function checks all values in position 3 of the key string (xxxZxxx) and checks every value in the following positions
*	as well
*/
void testKeyThree(void)
{
	int i;
	char temp[8];
	strcpy(temp, keyword);
	temp[3]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[3]++;
		strcpy(keyword, temp);
		testKeyFour();
	}
}

/*
*	This function checks all values in position 2 of the key string (xxZxxxx) and checks every value in the following positions
*	as well
*/
void testKeyTwo(void)
{
	int i;
	char temp[8];
	strcpy(temp, keyword);
	temp[2]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[2]++;
		strcpy(keyword, temp);
		testKeyThree();
	}
}

/*
*	This function checks all values in position 1 of the key string (xZxxxxx) and checks every value in the following positions
*	as well
*/
void testKeyOne(void)
{
	int i;
	char temp[8];
	strcpy(temp, keyword);
	temp[1]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[1]++;
		strcpy(keyword, temp);
		testKeyTwo();
	}
}

/*
*	This function checks all values in position 0 of the key string (Zxxxxxx) and checks every value in the following positions
*	as well
*/
void testKeyZero(void)
{
	int i;
	char temp[8];
	strcpy(temp, "AAAAAAA");
	temp[0]--;
	for(i = 0; i < 26 && exitvar != 10; i++)
	{
		temp[0]++;
		strcpy(keyword, temp);
		testKeyOne();
	}
}


