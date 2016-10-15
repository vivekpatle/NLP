/**
	All the necessary header file added.  
**/
#include<iostream>
#include<fstream>
#include<string.h>
#include <cstring>

using namespace std;
/**
	A function for checking the string and counting the number of string having same pattern.
**/
int *partialMatchTable(string p, int l[]) {
	int m = p.length();
	l[0] = 0;
	int i = 0;
	for (int j = 1; j < m; j++) {
		if (p[i] == p[j]) {
			l[j] = i + 1;
			i++;
		}	else {
			while (i > 0) {
				i = l[i - 1];
				if (p[i] == p[j]) {

					l[j] = i + 1;
					i++;
					break;
				}
			}
			if (i == 0) {
				l[j] = i;
			}
		}
	}
	return l;
}
/**
	Function for searching the string with target string.
**/
int search (string text, string p, int f[]) {
	int k = text.length();
	int m = p.length();
	int i = 0;
	int j = 0;
	int flag = 0;
	while (j < k) {
		if (p[i] == text[j]) {
			i++;
			j++;
			if (i == m) {
				flag = 1;
				break;
			}
		} else if (p[i] != text[j] && i == 0) {
			j++;
			if (j == k) flag = 0;
		} else if (p[i] != text[j]) {
			i = f[i - 1];
		}
	}
	return flag;
}
/**
	KMP algorithm implemented. 
**/
char KMP(string text, string p) {
	char a = 'a';
	int f[p.length()];
	int *final;
	final = partialMatchTable(p, f);
	int s = search(text, p, final);
	if (s == 1) a = 'b';
	return a;
}
/**
	Dictionary search basically for finding the probability of the string in the target string.
**/
void DictionarySearch(string filename, string partialMatchTable) {
	ifstream object1;
	object1.open(filename.c_str());
	if (!object1.is_open()) {
		cout << "Error"<<endl;
	}
	char letter;
	int i = 0;
	int char_count = 0;
	float word_match_count = 0;
	float word_count = 0;
	char word[20];
	int char_position = 0;
	while (object1.get(letter)) {
		char_count++;
		if (letter == ' ' || letter == '\n' || letter == '.' || letter == ',' || letter == '"') {
			word_count++;
			string word1 = string(word);
			char a = KMP(word1, partialMatchTable);
			if (a == 'b') {
				word_match_count++;
				cout << partialMatchTable + " Found in " + string (word) + " at position "<<endl;
				cout << char_position << endl;
			}
			i = 0;
			for (int j = 0; j < 20; j++) {
				word[j] = '\0';
			}
		} else {
			if (i == 0) {
				char_position = char_count;
			}
			word[i] = letter;
			i++;
		}
	}
	cout << "The probability of finding " << partialMatchTable << " is " << word_match_count / word_count << endl;
	cout << endl;
}
/**
	For counting the number of paragraph.
**/
void para_count(string filename) {
	ifstream myfile;
	int count = 1;
	myfile.open(filename.c_str());
	if (!myfile.is_open()) {
		cout << "error";
	}
	char word;
	while (myfile.get(word)) {
		if (word == '\n') {
			count++;
		}
	}
	cout << "The number of paragraphs in the text are: " << count << endl;
	cout << endl;
	myfile.close();
}
/**
	Main function for the execution of the program.
**/
int main() {
	int choice;
	char n = '\0';
	string filename;
	while (n != 'n') {
		cout << "1. To find number of paragraphs in the text" << endl;
		cout << "2. To find a particular string in the text " << endl;
		cout << "Enter the filename along with its extension: ";
		cin >> filename;
		cout << endl;
		cout << "Enter your choice--> ";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			para_count(filename);
			break;
		}
		case 2:
		{
			string partialMatchTable;
			char option = '\0';
			cout << endl;
			cout << "Enter the patern you want to search for: ";
			cin >> partialMatchTable;
			DictionarySearch(filename, partialMatchTable);
			break;
		}
		default:
			cout << "Enter a valid choice!" << endl;
			break;
		}
		cout << "Do you want to continue? y or n -> ";
		cin >> n;
	}
}
