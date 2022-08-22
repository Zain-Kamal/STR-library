#include <list>
#include <string>
#include <cstring>
#include <iostream>
#pragma once

class STR {

private:

	std::list<char>* strng;
	unsigned int size;
	void init() {
		strng = new std::list<char>;
		size = 0;
	};

public:

	//The big 5
	STR() { //Default constructor
		init();
	}
	STR(const STR& s) { //Copy constructor
		init();
		size = s.size;
		for (auto& x : (*s.strng)) { //Deep copy using iterators
			strng->push_back(x);
		}
	}
	STR(STR && s) : strng{s.strng}, size{ s.size } { //Move constructor
		s.strng = nullptr;
		s.size = 0;
	}
	STR& operator=(const STR& s) { //Copy assignment operator
		STR copy = s;
		std::swap(*this, copy);
		return *this;
	}
	STR& operator=(STR&& s) { //Move assignment operator
		std::swap(*strng, *s.strng);
		std::swap(size, s.size);
		return *this;
	}
	~STR() { //Destructor
		strng->clear();
		delete strng;
	}

	//Other assignment operators
	STR& operator=(const std::string & s) {
		this->clear();
		size = s.size();
		for (int i = 0; i < s.size(); i++) {
			strng->push_back(s[i]);
		}
		return *this;
	}
	STR& operator=(const char c) { //
		this->clear();
		size = 1;
		strng->push_back(c);
	}

	//Storage size related functions
	void clear() { //erase the content inside the object
		strng->clear();
		size = 0;
	}
	bool empty() { //check whether the object is empty or not
		return size == 0;
	}
	int length() { //return the size of the object
		return size;
	}
	char operator[] (int n) { //provide a way to use the STR library with indeces
		int temp = 0;
		if (n < 0 || n >= size)
			std::cout << "The value entered is not within acceptable range";
		for (auto itr = strng->begin(); itr != strng->end(); itr++, temp++) {
			if (temp == n)
				return *itr;
		}
	}

	//Inserting and removing elements
	void push_back(const STR& s) { //insert item at the back (copy)
		size += s.size;
		for (auto x : *s.strng) {
			strng->push_back(x);
		}
	}
	void push_back(STR&& s) { //insert item at the back (move)
		size += s.size;
		for (auto x : *s.strng) {
			strng->push_back(std::move(x));
		}
	}
	void push_back(const char& c) {
		strng->push_back(c);
	}
	void push_back(char&& c) {
		strng->push_back(c);
	}
	void push_back(const std::string& s) {
		size += s.size();
		for (auto x : s) {
			strng->push_back(x);
		}
	}
	void push_back(std::string&& s) {
		size += s.size();
		for (auto x : s) {
			strng->push_back(x);
		}
	}
	void push_front(const STR& s) { //insert item at the back (copy)
		size += s.size;
		for (auto x : *s.strng) {
			strng->push_front(x);
		}
	}
	void push_front(STR&& s) { //insert item at the back (move)
		size += s.size;
		for (auto x : *s.strng) {
			strng->push_front(x);
		}
	}
	void pop_back() { //removing the last character of the string
		size--;
		strng->pop_back();
	}
	void pop_front() { //remove the first character of the string
		size--;
		strng->pop_front();
	}

	//Arithmetic operators
	STR& operator+(const STR& s) {
		STR temp;
		temp.push_back(*this);
		temp.push_back(s);
		return temp;
	}
	STR& operator+(const std::string& s) {
		STR temp;
		temp.push_back(*this);
		temp.push_back(s);
		return temp;
	}
	STR& operator+(const char c) {
		STR temp;
		temp.push_back(*this);
		temp.push_back(c);
		return temp;
	}

	//Input/Output stream
	friend std::ostream& operator<<(std::ostream& os, const STR& s) {
		for (auto x : *s.strng) {
			os << x;
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, STR& s) {
		s.clear();
		std::string* temp = new std::string;
		is >> *temp;
		s.push_back(*temp);
		delete temp;
		return is;
	}

	//Some other functions
	int find(const std::string& s) { //searches a STR object for the first occurence of a particular substring
		if (s.size() > size || s.size() == 0)
			return -1;
		bool found = false;
		int index = -1, i = 0, j = 0;
		for (auto itr = strng->begin(); itr != strng->end() || i < s.size(); itr++, j++) {
			if (s[i] == *itr) {
				found = true;
				index = j;
				i++;
			}
			else if (s[i] != *itr && found) {
				found = false;
				i--;
			}
		}
		if (found)
			return index - s.size() + 1;
		else
			return -1;
	}
	int find(const STR& s) { //searches a STR object for the first occurence of a particular subSTR
		if (s.size > size || s.size == 0)
			return -1;
		bool found = false;
		int index = -1, j = 0;
		for (auto itr = strng->begin(), i = s.strng->begin(); itr != strng->end() || i != strng->end(); itr++, j++) {
			if (*i == *itr) {
				found = true;
				index = j;
				i++;
			}
			else if (*i != *itr && found) {
				found = false;
				i--;
			}
		}
		if (found)
			return index - s.size + 1;
		else
			return -1;
	}
	STR& substr(unsigned int expr1, unsigned int expr2) { //returns a particular subSTR of a STR object
		STR temp;
		if (expr2 >= this->size)
			std::cout << "The value entered is not within acceptable range";
		for (int i = expr1; i < expr2; i++) {
			temp.push_back((*this)[i]);
		}
		return temp;
	}
	STR& swap(STR& s) { //swap two STR objects and return the value of the object acting as an argument
		std::swap(*this, s);
		return *this;
	}
	int find_first_of(const STR& s) { //return first occurence of any charcater of s in the calling object
		int i = 0;
		for (auto itr = strng->begin(); itr != strng->end(); itr++, i++) {
			for (auto jtr = s.strng->begin(); jtr != s.strng->end(); jtr++) {
				if (*itr == *jtr)
					return i;
			}
		}
		return -1;
	}
	int find_last_of(const STR& s) { //return last occurence of any charcater of s in the calling object
		int i = size;
		for (auto itr = strng->rbegin(); itr != strng->rend(); itr++, i--) {
			for (auto jtr = s.strng->begin(); jtr != s.strng->end(); jtr++) {
				if (*itr == *jtr)
					return i;
			}
		}
		return -1;
	}
	int find_first_not_of(const STR& s) { //return first occurence of any character not of s in the calling object
		int i = 0;
		for (auto itr = strng->begin(); itr != strng->end(); itr++, i++) {
			for (auto jtr = s.strng->begin(); jtr != s.strng->end(); jtr++) {
				if (*itr != *jtr)
					return i;
			}
		}
		return -1;
	}
	int find_last_not_of(const STR& s) { //return last occurence of any charcater not of s in the calling object
		int i = size;
		for (auto itr = strng->rbegin(); itr != strng->rend(); itr++, i--) {
			for (auto jtr = s.strng->begin(); jtr != s.strng->end(); jtr++) {
				if (*itr != *jtr)
					return i;
			}
		}
		return -1;
	}
};

