#pragma once
#include<iostream>
#include<fstream>
#include<string>
#pragma warning(disable: 4996)

using namespace std;

struct message {
	char text[20];
	message() {};
	message(string s) {
		if (s.length() > 20) {
			cout << "Message creating error";
			return;
		}
		strcpy(text, s.c_str());
	}

	char* get_text() {
		return text;
	}

	friend ostream& operator <<(ostream& out, message& m) {
		out.write((char*)&m, sizeof(m));
		return out;

	}

	friend istream& operator >>(istream& in, message& m) {
		in.read((char*)&m, sizeof(m));
		return in;
	}
};