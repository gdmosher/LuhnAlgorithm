/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 27, 2014, 8:35 AM
 * Extended by Gordon Mosher 2015-0322
 */

//System Libraries
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>				// I used a couple deprecated c functions like strncpy() and strcat()
#undef _CRT_SECURE_NO_WARNINGS
//#include <cstdlib>
#include <ctime>
//#include <string>
using namespace std;

//Global Constants


enum CrdCard { AmericanExpress, Visa, MasterCard, Discover, ALL };	// ALL must be last!!
																	// it is used as a bound for rand() below

//Function Prototypes
char rndDgit();
void prpLuhn(char[],int);
void Luhn(char[], int);
void genCC(char[], int, CrdCard);
bool validCC(char[]);
void flipDigit(char[]);
bool DEBUG = true;
bool DEBUGrandom = false;
bool LuhnDEBUG = false;
bool genCCDEBUG = true;				// turn this on to see numbers as they are generated
bool flipDEBUG = false;
#define MAXFIELDSIZE 20

int main(int argc, char** argv) {
    //Set the random number seed
    if (!DEBUGrandom) srand(static_cast<unsigned int>(time(0)));		// test 174 094 8824 w/o srand
															// example  799 273 9871 Lehr + wiki
											// freeformatter example	4556 7375 8689 985x
//    const int SIZE=12;			// only used for prpLuhn
	char crdCard[MAXFIELDSIZE] = "";			// handles 19 digit cards and null term
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit"<<endl;
    prpLuhn(crdCard,11-1);
//	if (DEBUG) strcpy_s(crdCard, "455673758689985");
//	if (DEBUG) strcpy_s(crdCard, "7992739871");	
	int size = 2 + strlen(crdCard);
	cout << "Card length w/ chkLuhn and null term = " << size << endl;
	//Output the preLuhn credit card
    cout<<crdCard<<endl;
    //Now create a function that fills the last digit
    //using the Luhn Algorithm
    cout<<"The random number with Luhn Encoding, Output Here!"<<endl;
	Luhn(crdCard, size);
	cout << crdCard << endl << endl;
	// 2016-0322 new code to test validation
	int validCount = 0, invalidCount = 0;
	for (int i = 0; i < 2E3; i++) {
/*		genCC(crdCard, 0, AmericanExpress);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
		genCC(crdCard, 0, Visa);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
		genCC(crdCard, 16, Visa);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
		genCC(crdCard, 0, MasterCard);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
		genCC(crdCard, 0, Discover);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
*/
	}
	validCount = 0; invalidCount = 0;
	for (int i = 0; i < 1E4; i++) {
		CrdCard ccToMake = static_cast<CrdCard>(rand() % ALL);
		genCC(crdCard, 0, ccToMake);
		flipDigit(crdCard);
		validCC(crdCard) ? validCount++ : invalidCount++;
	}
	cout << "Valid = " << validCount << ", Invalid = " << invalidCount << ", Ratio = " << (validCount*100.0 / (validCount + invalidCount)) << endl;
    //Exit Stage Right
//	cout << "Press <Enter> to continue...";
	system("pause");
    return 0;
}
char* PAX[] = { "34", "37" };		// array of prefixes and valid lengths for certain cards
int	  SAX[] = { 15 };
char* PVI[] = { "4" };
int	  SVI[] = { 13, 14, 15, 16 };
char* PMC[] = { "51", "52", "53", "54", "55" };
int	  SMC[] = { 16, 17, 18, 19 };
char* PDI[] = { "6011", "622126", 
						"622127",			// ... and the rest :)
						"622925", "644", "645", "646", "647", "648", "649", "65" };
int	  SDI[] = { 16 };
void genCC(char cc[], int size, CrdCard ccType) {
	char* prefix;
	int len;
	switch (ccType) {
	case AmericanExpress:	// 15
		prefix = PAX[rand() % (sizeof(PAX)/sizeof(PAX[0]))];
		if (size == 0) { size = SAX[rand() % (sizeof(SAX) / sizeof(SAX[0]))]; }
		strncpy(cc, prefix, MAXFIELDSIZE);
		//		strcat(cc, "0000000000"); strcat(cc, "123");
		prpLuhn(cc, size-1);
		//		cout << cc << endl;
		Luhn(cc, size+1);
		if (genCCDEBUG) cout << cc << endl;
		break;
	case Visa:
		prefix = PVI[rand() % (sizeof(PVI) / sizeof(PVI[0]))];
		if (size == 0) { size = SVI[rand() % (sizeof(SVI) / sizeof(SVI[0]))]; }
		strncpy(cc, prefix, MAXFIELDSIZE);
		//		strcat(cc, "0000000000"); strcat(cc, "123");
		prpLuhn(cc, size - 1);
		//		cout << cc << endl;
		Luhn(cc, size + 1);
		if (genCCDEBUG) cout << cc << endl;
		break;
	case MasterCard:
		prefix = PMC[rand() % (sizeof(PMC) / sizeof(PMC[0]))];
		if (size == 0) { size = SMC[rand() % (sizeof(SMC) / sizeof(SMC[0]))]; }
		strncpy(cc, prefix, MAXFIELDSIZE);
		//		strcat(cc, "0000000000"); strcat(cc, "123");
		prpLuhn(cc, size - 1);
		//		cout << cc << endl;
		Luhn(cc, size + 1);
		if (genCCDEBUG) cout << cc << endl;
		break;
	case Discover:
		prefix = PDI[rand() % (sizeof(PDI) / sizeof(PDI[0]))];
		if (size == 0) { size = SDI[rand() % (sizeof(SDI) / sizeof(SDI[0]))]; }
		strncpy(cc, prefix, MAXFIELDSIZE);
		//		strcat(cc, "0000000000"); strcat(cc, "123");
		prpLuhn(cc, size - 1);
		//		cout << cc << endl;
		Luhn(cc, size + 1);
		if (genCCDEBUG) cout << cc << endl;
		break;
	}
}

bool validCC(char cc[]) {		// only validates digits given to checkdigit
	bool retval = false;		// does not check for valid prefixes or lengths
	int len = strlen(cc);
	char hold = cc[len-1];
	cc[len-1] = 0;
	Luhn(cc, len+1);
	cc[len-1] == hold ? retval=true : retval=false;
	return (retval);
}

void flipDigit(char cc[]) {		// should cause a 90% failure with a mod 10 checkdigit
	int len = strlen(cc);		// because we are not blocking the 10% chance of
	int i = rand() % (len);		// flipping back to the same digit
//	i = len - 1;				// otherwise we could attain a %100 failure rate!!
//	cout << i << endl;
//	if (i == len-1) cout << "Flipping the checkdigit." << endl;
	cc[i] = rndDgit();
//	cc[6] = '7';
//	cc[7] = '8';
	if (flipDEBUG) cout << cc << endl;
	return;
}

void Luhn(char cc[], int n){				// n includes the null term for some reason
	int sumLuhn = 0, tmpLuhn, chkLuhn;
	for (int i = n - 3; i >= 0; i--){			// only supports cards with even number of digits
		if ((i+n) % 2) {							// odd numbered digits, now supports odd numbered digit cards
			tmpLuhn = (((int)cc[i]) - 48) * 2;
			if (LuhnDEBUG) cout << "dbl " << tmpLuhn << "\t";
		}
		else {
			tmpLuhn = (((int)cc[i]) - 48);
			if (LuhnDEBUG) cout << "    " << tmpLuhn << "\t";
		}
		if (tmpLuhn > 9) { tmpLuhn -= 9; }
		if (LuhnDEBUG) cout << tmpLuhn << endl;
		sumLuhn += tmpLuhn;
	}
//	chkLuhn = (10 - (sumLuhn % 10)) % 10;		// second % 10 is in case the chkLuhn is 0	THIS LINE WORKS AS ALTERNATE
	chkLuhn = (9 * sumLuhn) % 10;
	if (LuhnDEBUG) cout << "sumLuhn = " << sumLuhn << "   chkLuhn = " << chkLuhn << endl;
	cc[n-2] = chkLuhn + 48;
	cc[n - 1] = 0;
}

void prpLuhn(char cc[],int n){				// n does not include the checksum digit
    //Create a random cc in prep for Luhn checksum
	int i = strlen(cc);	// keep what's already in there
    for(;i<n;i++){		// can be used to strip off the chkDigit!!
        cc[i]=rndDgit();
    }
    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}

char rndDgit(){
    return rand()%10+48;
}



