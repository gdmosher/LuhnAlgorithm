/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 27, 2014, 8:35 AM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global Constants

//Function Prototypes
char rndDgit();
void prpLuhn(char[],int);
void Luhn(char[],int);
bool DEBUG = true;

int main(int argc, char** argv) {
    //Set the random number seed
    /*if (!DEBUG)*/ srand(static_cast<unsigned int>(time(0)));		// test 174 094 8824 w/o srand
															// example  799 273 9871 Lehr + wiki
											// freeformatter example	4556 7375 8689 985x
    const int SIZE=12;			// only used for prpLuhn
	char crdCard[20];			// handles 19 digit cards and null term
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit"<<endl;
    prpLuhn(crdCard,SIZE-2);
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
	cout << crdCard << endl;

    //Exit Stage Right
//	cout << "Press <Enter> to continue...";
	system("pause");
    return 0;
}
void Luhn(char cc[], int n){
	int sumLuhn = 0, tmpLuhn, chkLuhn;
	for (int i = n - 3; i >= 0; i--){			// only supports cards with even number of digits
		if ((i+n) % 2) {							// odd numbered digits, now supports odd numbered digit cards
			tmpLuhn = (((int)cc[i]) - 48) * 2;
			cout << "dbl " << tmpLuhn << "\t";
		}
		else {
			tmpLuhn = (((int)cc[i]) - 48);
			cout << "    " << tmpLuhn << "\t";
		}
		if (tmpLuhn > 9) { tmpLuhn -= 9; }
		cout << tmpLuhn << endl;
		sumLuhn += tmpLuhn;
	}
//	chkLuhn = (10 - (sumLuhn % 10)) % 10;		// second % 10 is in case the chkLuhn is 0	THIS LINE WORKS AS ALTERNATE
	chkLuhn = (9 * sumLuhn) % 10;
	cout << "sumLuhn = " << sumLuhn << "   chkLuhn = " << chkLuhn << endl;
	cc[n-2] = chkLuhn + 48;
	cc[n - 1] = 0;
}

void prpLuhn(char cc[],int n){
    //Create a random cc in prep for Luhn checksum
    for(int i=0;i<n;i++){
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



