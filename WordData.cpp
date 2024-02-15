/********************************************************
 *    File:    WordData.cpp            			*
 *    Prepared by: Dr. Spiegel         			*
 *    Description:  // Add it          			*
 ********************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "WordData.h"

using namespace std;


WordData::WordData(string wrd, int cnt)
{
	setWordData(wrd, cnt);	
}

void WordData::setWord(string wrd)
{
	word = wrd;
}

void WordData::setCount(int cnt)
{
	count = cnt;
}

void WordData::setWordData(string wrd, int cnt)
{
	setWord(wrd);
	setCount(cnt);
}

string WordData::getWord() const
{
	return(word);
}

int WordData::getCount() const
{
	return(count);
}

WordData& WordData::operator++()	// preincrement
{	setCount(getCount()+1);
	return(*this);
}

WordData WordData::operator++(int)	// postincrement
{	WordData temp;
	setCount(getCount()+1);
	return(temp);
}

* << operator
  Parameters: output (ostream), word (worddata object)
  Goal: Overloaded output operator for class worddata
------------------------------*/
                    //import/export  			//import
ostream &operator<< (ostream &output, const WordData &word)
{
	output << setw(20) << left << word.getWord() <<
	setw(5) << left << word.getCount() << endl;
	return output;
}