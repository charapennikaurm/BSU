#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;



struct RRecord
{
	bool operator <= (RRecord const& r) const
	{
		if (number < r.number) return true;
		else if (number > r.number) return false;
		/*if (fUchastok < r.fUchastok) return true;
		else if (fUchastok > r.fUchastok) return false;
		if (fDetail < r.fDetail) return true;
		else if (fDetail > r.fDetail) return false;*/
		return true;
	}

	friend ifstream& operator >> (ifstream& fi, RRecord& rec)
	{
		fi.read((char*)& rec, sizeof(rec));
		return fi;
	}

	friend ofstream& operator << (ofstream& fo, RRecord const& aRec)
	{
		fo.write((char*)& aRec, sizeof(aRec));
		return fo;
	}

	friend fstream& operator >> (fstream& fi, RRecord& rec)
	{
		fi.read((char*)& rec, sizeof(rec));
		return fi;
	}


	friend fstream& operator << (fstream& fo, RRecord const& aRec)
	{
		fo.write((char*)& aRec, sizeof(aRec));
		return fo;
	}

	int number;
	char dest[15];//пункт назначени€
	double dep_time, arr_time;
	int free_seat;
	char company[20];
};

struct RRecordCompany
{
	friend ifstream& operator>>(ifstream& fi, RRecordCompany& rec)
	{
		fi.read((char*)& rec, sizeof(rec));
		return fi;
	}
	friend  ofstream& operator <<(ofstream& fout, RRecordCompany const& rec)
	{
		fout.write((char*)& rec, sizeof(rec));
		return fout;
	}
	int  num;
	char company[20];
};

struct KRecordTxt
{
	KRecordTxt(RRecord& aRec) : r(aRec) { }
	RRecord& r;
	friend istream& operator >> (istream& fi, KRecordTxt& aRec)
	{
		std::string s;
		if (getline(fi, s))
		{
			istringstream ss(s);
			string sf;
			getline(ss, sf, ';');
			aRec.r.number = stoi(sf);
			getline(ss, sf, ';');
			strcpy(aRec.r.dest, sf.c_str());
			getline(ss, sf, ';');
			aRec.r.dep_time = stof(sf);
			getline(ss, sf, ';');
			aRec.r.arr_time = stof(sf);
			getline(ss, sf, ';');
			aRec.r.free_seat = stoi(sf);
			getline(ss, sf, ';');
			strcpy(aRec.r.company, sf.c_str());
		}
		return fi;
	}
	friend ostream& operator << (ostream& fo, KRecordTxt const& rec)
	{
		fo << rec.r.number << " " << rec.r.dest << " " << fixed << setprecision(2) << rec.r.dep_time
			<< " " << rec.r.arr_time << " " << rec.r.free_seat << " " << rec.r.company;
		return fo;
	}
};
//-------------------
struct KRecordCompanyTxt
{
	KRecordCompanyTxt(RRecordCompany& aRec) :r(aRec) {}
	friend ostream& operator <<(ostream& out, KRecordCompanyTxt const& rec)
	{
		out << rec.r.num << ";" << rec.r.company ;
		return out;
	}
	friend istream& operator >> (istream& in, KRecordCompanyTxt & aRec)
	{
		string s;
		if (getline(in, s))
		{
			istringstream ss(s);
			string sf;
			getline(ss, sf, ';');
			aRec.r.num = stoi(sf);
			getline(ss, sf, ';');
			strcpy(aRec.r.company, sf.c_str());
		}
		return in;
	}
	RRecordCompany & r;
};

void FFileToScreen(char* aFileName)
{
	cout << endl << "Output on display: " << endl;
	RRecord r;
	ifstream fi(aFileName, ios::binary);
	while (fi >> r)
		cout << KRecordTxt(r) << endl;
	cout << endl;
	fi.close();
}

void FBinToTxtFile(char* aFileNameBin, char* aFileNameTxt)
{
	ifstream fi(aFileNameBin, ios::binary);
	ofstream fOut(aFileNameTxt);
	RRecord rec;
	KRecordTxt rOut(rec);
	while (fi >> rec)
		fOut << rOut << endl;
}

void BinToTxtFile(char* aFileNameBin, char* aFileNameTxt)
{
	ifstream fi(aFileNameBin, ios::binary);
	ofstream fOut(aFileNameTxt);
	RRecordCompany rec;
	KRecordCompanyTxt rOut(rec);
	while (fi >> rec)
		fOut << rOut << endl;
}

bool FTxtToBinFile(char* aFileNameTxt, char* aFileNameBin)
{
	bool b = false;
	ofstream fo(aFileNameBin, ios::binary);
	ifstream fi(aFileNameTxt);
	if (fi)
	{
		RRecord rec;
		KRecordTxt rIn(rec);
		while (fi >> rIn)
			fo << rec;
		b = true;
	}
	return b;
}

bool TxtToBinFile(char* aFileNameTxt, char* aFileNameBin)
{
	bool b = false;
	ofstream fo(aFileNameBin, ios::binary);
	ifstream fi(aFileNameTxt);
	if (fi)
	{
		RRecordCompany rec;
		KRecordCompanyTxt rIn(rec);
		while (fi >> rIn)
			fo << rec;
		b = true;
	}
	return b;
}

//compare дл€ qsort
int fcmp(const void* p1, const void* p2)
{
	return *(int*)p1 - *(int*)p2;
}

void SortT(char* file_name1)
{
	ifstream fi1(file_name1);
	int i = 0;
	string str;
	while (getline(fi1, str)) ++i;
	fi1.close();
	fi1.open(file_name1);
	RRecord* mas = new RRecord[i];
	for (int j = 0; j < i; j++)
	{
		getline(fi1, str, ';');
		mas[j].number = stoi(str);
		getline(fi1, str, ';');
		strcpy(mas[j].dest, str.c_str());
		getline(fi1, str, ';');
		mas[j].dep_time = stof(str);
		getline(fi1, str, ';');
		mas[j].arr_time = stof(str);
		getline(fi1, str);
		mas[j].free_seat = stoi(str);
		//getline(fi2, str);
		//getline(fi1, str);
	}
	qsort(mas, i, sizeof(RRecord), fcmp);
	fi1.close();
	ofstream fout(file_name1);
	for (int j = 0; j < i; ++j)
	{
		fout << mas[j].number << ";" << mas[j].dest << ";" << fixed << setprecision(2) << mas[j].dep_time
			<< ";" << mas[j].arr_time << ";" << mas[j].free_seat << endl;
	}
}

void SortC(char* filename)
{
	ifstream file1(filename,ios::binary);
	RRecordCompany r1, r2, minC;
	
	int minCI;
	int i, j;
	int stroki = 0;
	string str;
	while (file1.read((char*)&r1,sizeof(r1)))
	{
		++stroki;
	}
	//file.seekp(0, ios::beg);
	file1.close();
	fstream file(filename, ios::binary | ios::in | ios::out);
	for (i = 0; i < stroki; ++i)
	{
		streampos xPos = sizeof(RRecordCompany) * i;
		file.seekp(xPos,ios::beg);
		file.read((char*)& r1, sizeof(RRecordCompany));
		minC = r1;
		minCI = i;
		for (j = i + 1; j < stroki; ++j)
		{
			file.read((char*)& r2, sizeof(RRecordCompany));
			if (r2.num < minC.num)
			{
				minCI = j;
				minC = r2;
			}
		}
		xPos = sizeof(RRecordCompany) * minCI;
		file.seekp(xPos,ios::beg);
		file.write((char*)& r1, sizeof(RRecordCompany));
		xPos = sizeof(RRecordCompany) * i;
		file.seekp(xPos);
		file.write((char*)& minC, sizeof(RRecordCompany));
	}
	file.close();
}

//void SortBuble(char* file_name2) {
//	fstream fi(file_name2, ios::binary | ios::binary | ios::out);
//	RRecord rec;
//	int n = 0;
//	while (fi >> rec){n++;}
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n - i - 1; j++) {
//			if (rec.number >) {
//				
//			}
//		}
//	}
//}

void BinMerge(char* aFileName, char* bFileName, char* resFile)
{
	ifstream fi1(aFileName, ios::binary);
	ifstream fi2(bFileName, ios::binary);
	ofstream fo(resFile, ios::binary);
	RRecordCompany recC;
	vector<RRecordCompany> vc;
	RRecord rec;
	vector<RRecord> v;
	while (fi1 >> rec)
	{
		v.push_back(rec);
	}
	while (fi2 >> recC)
	{
		vc.push_back(recC);
	}
	int j = 0;
	int i = 0;
metka1: 
	if ((i < v.size() )&& (j < vc.size()))
	{
		if (v[i].number == vc[j].num)
		{
			strcpy(v[i].company, vc[j].company);
			fo << v[i];
			i++;
			j++;
			goto metka1;
		}
		else if (v[i].number > vc[j].num)
		{
			j++;
			goto metka1;
		}
		else if (v[i].number < vc[j].num)
		{
			strcpy(v[i].company, "UNDEF");
			fo << v[i];
			i++;
			goto metka1;
		}
	}
			else if (i < v.size())
	{
		while (i < v.size())
		{
			strcpy(v[i].company, "UNDEF");
			fo << v[i];
			++i;
		}
	}
}


void SortAndMerge(char* file_name1, char* file_name2, char* new_file_name)//сортировка файла
{
	ifstream fi0(file_name1);
	ifstream fi2(file_name2);
	int i = 0;
	string str;
	while (getline(fi0, str)) ++i;
	ifstream fi1(file_name1);
	RRecord* mas = new RRecord[i];
	for (int j = 0; j < i; j++)
	{
		getline(fi1, str, ';');
		mas[j].number = stoi(str);
		getline(fi1, str, ';');
		strcpy(mas[j].dest, str.c_str());
		getline(fi1, str, ';');
		mas[j].dep_time = stof(str);
		getline(fi1, str, ';');
		mas[j].arr_time = stof(str);
		getline(fi1, str);
		mas[j].free_seat = stoi(str);
		getline(fi2, str, ';');
		getline(fi2, str);
		strcpy(mas[j].company, str.c_str());
		//getline(fi2, str);
		//getline(fi1, str);
	}
	qsort(mas, i, sizeof(RRecord), fcmp);
	ofstream fout(new_file_name);
	for (int j = 0; j < i; ++j)
	{
		fout << mas[j].number << ";" << mas[j].dest << ";" << fixed << setprecision(2) << mas[j].dep_time
			<< ";" << mas[j].arr_time << ";" << mas[j].free_seat << ";" << mas[j].company << endl;
	}
}

int FreeSpaces(char* filename, char* depar, double t)
{
	ifstream fi(filename);
	int res = -1;
	RRecord rec;
	while (fi >> rec)
	{
		if ((!strcmp(depar, rec.dest)) && abs((t - rec.dep_time)) < 0.001)
		{
			res = rec.free_seat;
		}
	}
	return res;
}

void MaxFlightTime(char* filename)
{
	double max = 0;
	int num;
	string destin;
	ifstream fi(filename);
	RRecord rec;
	while (fi >> rec)
	{
		if ((rec.arr_time - rec.dep_time) > max)
		{
			num = rec.number; destin = rec.dest; max = rec.arr_time - rec.dep_time;
		}
	}
	cout << "Number: " << num << ". Destination: " << destin << endl;
}

void Update(char* file_name, int num)
{
	/*double x, y;
	cout << "¬ведите врем€ вылета и врем€ прибыти€";
	cin >> x >> y;
	ifstream fi(file_name, ios::binary);
	vector<RRecord> vec;
	RRecord rec;
	while (fi >> rec)
	{
		if (rec.number==num)
		{
			rec.dep_time = x;
			rec.arr_time = y;
			vec.push_back(rec);

		}
		else
		vec.push_back(rec);
	}
	ofstream fo(file_name, ios::binary);
	for (int i = 0; i < vec.size(); ++i)
	{
		fo << vec[i];
	}
	return;*/
	ifstream fi(file_name, ios::binary);
	RRecord rec;
	double x, y;
	cout << "¬ведите врем€ вылета и врем€ прибыти€";
	cin >> x >> y;
	int n = 0;
	while (fi >> rec)
	{
		if (rec.number == num)
			break;
		++n;
	}
	fi.close();
	fstream fo(file_name, ios::in | ios::out, ios::binary);
	streampos xPos = (n * sizeof(RRecord));
	fo.seekp(xPos, ios::beg);
	rec.dep_time = x;
	rec.arr_time = y;
	fo.write((char*)& rec, sizeof(rec));
}

void DeleteWB(char* fname)
{
	ifstream fi(fname, ios::binary);
	vector<RRecord> vec;
	RRecord rec;
	while (fi >> rec)
	{
		if (strcmp(rec.dest, "Warszaw") && strcmp(rec.dest, "Berlin"))
		{
			vec.push_back(rec);
		}
	}
	ofstream fo(fname, ios::binary);
	for (int i = 0; i < vec.size(); ++i)
	{
		fo << vec[i];
	}
	return;
}

void SwapMSC(char* fname)
{
	ifstream fi(fname, ios::binary);
	vector<RRecord> vec;
	RRecord rec;
	while (fi >> rec)
	{
		vec.push_back(rec);
	}
	int num1 = -1, num2 = -1;
	for (int i = 0; i < vec.size(); ++i)
	{
		if (num1 == -1 && !strcmp(vec[i].dest, "Moscow")) { num1 = i; }
		else if (!strcmp(vec[i].dest, "Moscow")) { num2 = i; }
	}
	if (num2 != -1 && num1 != -1)
		swap(vec[num1], vec[num2]);
	ofstream fo(fname, ios::binary);
	for (int i = 0; i < vec.size(); ++i)
	{
		fo << vec[i];
	}
	return;
}

int destcmp(const void* p1, const void* p2)
{
	return strcmp(((RRecord*)p1)->dest, ((RRecord*)p2)->dest);
}

void SortByDestination(char* fname)
{
	ifstream fi(fname, ios::binary);
	vector<RRecord> vec;
	RRecord rec;
	while (fi >> rec)
	{
		vec.push_back(rec);
	}
	vector<RRecord>::iterator it;
	it = vec.begin();
	ofstream fo(fname, ios::binary);
	qsort(&vec[0], vec.size(), sizeof(RRecord), destcmp);
	for (int i = 0; i < vec.size(); ++i)
	{
		fo << vec[i];
	}
	return;
}