//bu sayfay� k�t�phane dosyalar�n� ve kullan�lan fonksiyonlar� bir yerde tutmak amac�yla olu�turdum.
#ifndef _kullanilan_h
#define _kullanilan_h



#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <sstream>		//int'i stringe ve sting'i int'e �evirmek i�in gerekli k�t�phane.
#include <time.h>
#include "musteriBilgi.h"

using namespace std;

bool admin_Kontrol();
void admin_Islemleri();
bool strKrslstr(std::string str1, std::string str2);
bool txtKaydet(string &, string&, string &, int &, int &);
bool dosyaAra(string, bool &, string &);
string intToStr(int);




#endif // !"kullanilan.h"


