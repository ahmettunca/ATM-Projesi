//bu sayfayý kütüphane dosyalarýný ve kullanýlan fonksiyonlarý bir yerde tutmak amacýyla oluþturdum.
#ifndef _kullanilan_h
#define _kullanilan_h



#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <sstream>		//int'i stringe ve sting'i int'e çevirmek için gerekli kütüphane.
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


