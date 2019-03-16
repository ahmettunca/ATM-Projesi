#ifndef _musteriBilgi_h
#define _musteriBilgi_h



#include "kullanilan.h"
#include "musteriIslem.h"
//Struct Yapýlarý c++ ta daha geliþmiþtir class ile kullanýlýþ þekli aynýdýr 3-4 tane farký vardýr.
//Burada class yapýsýný kullanmayý seçtim. çünkü class verileri heap'te tutulur. 
class musteriBilgi:private musteriIslem
{
private:
	std::string dosyasi;
	std::string ad;
	std::string soyad;
	std::string adres;
	int musteriHizmetNo;
	int sifre;
	double bakiye;

public:
	musteriBilgi(std::string hangiMusteri);
	~musteriBilgi();
	void setAd(std::string ad);
	void setSoyad(std::string soyad);
	void setAdres(std::string adres);
	void setSifre(int sifre);
	void setMusteriHizmetNo(int hizmetno);
	void setBakiye(double bakiye);
	std::string getAd();
	std::string getSoyad();
	std::string getAdres();
	int getSifre();
	int getMusteriHizmetNo();
	double getBakiye();
	void duzenlemeyiKaydet();
	void musteriBilgiYaz();
	bool paraCekme(double neKadar);
	void paraYatirma(double neKadar);
	void menu();
	bool faturaOde();
	bool havale(std::string yatirilanNo, std::string kacinciKayit, double havaleMiktari);
	void faturaIslemKayit(std::string hangiFatura, double sayi);
	void paraIslemleriKayit(std::string islem, double neKadar);
	void havaleKayit(std::string yatirilanNo, double neKadar, std::string aciklama);
};

#endif // !_musteriBilgi_h