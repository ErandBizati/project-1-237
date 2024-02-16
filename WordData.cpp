/********************************************************
/ *    File:    WordData.cpp            			*
/ *    Prepared by: Dr. Spiegel         			*
/ *    Description:  // Add it          			*
 /********************************************************/

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

// Overloaded stream insertion operator for WordData class
std::ostream& operator<<(std::ostream& os, const WordData& wd) {
    os << std::setw(20) << std::left << wd.word << std::setw(5) << std::left << wd.count;
    return os;
}

void WordData::increment() {
    ++count; // Increment the word's count by one
}

bool WordData::matches(const std::string& otherWord) const {
    return word == otherWord; // Return true if the words match
}

