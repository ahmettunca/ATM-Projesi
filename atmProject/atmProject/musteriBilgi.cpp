#include "musteriBilgi.h"




musteriBilgi::musteriBilgi(std::string hangiMusteri)
{
	this->bakiye = 0;
	std::string bilgiler[6];
	dosyasi = "musteri" + hangiMusteri + ".txt";

	std::ifstream bilgiAl;
	bilgiAl.open(dosyasi.c_str());
	for (int i = 0; i<6; i++) {
		getline(bilgiAl, bilgiler[i]);
	}
	
	this->ad = bilgiler[0];
	this->soyad = bilgiler[1];
	this->adres = bilgiler[2];
	std::stringstream donusturucu;
	donusturucu << bilgiler[3];
	donusturucu >> this->musteriHizmetNo;
	donusturucu.clear();
	donusturucu << bilgiler[4];
	donusturucu >> this->sifre;
	donusturucu.clear();
	donusturucu << bilgiler[5];
	donusturucu >> this->bakiye;
	bilgiAl.close();
}


musteriBilgi::~musteriBilgi()
{
}

void musteriBilgi::setSifre(int sifre)
{
	this->sifre = sifre;
}

void musteriBilgi::setAd(std::string ad)
{
	this->ad = ad;
}

void musteriBilgi::setSoyad(std::string soyad)
{
	this->soyad = soyad;
}

void musteriBilgi::setAdres(std::string adres)
{
	this->adres = adres;
}

void musteriBilgi::setMusteriHizmetNo(int hizmetno)
{
	this->musteriHizmetNo = hizmetno;
}

void musteriBilgi::setBakiye(double bakiye)
{
	this->bakiye = bakiye;
}

void musteriBilgi::duzenlemeyiKaydet()
{
	std::ofstream duzenleme;
	duzenleme.open(dosyasi.c_str());
	duzenleme << this->ad<<std::endl << this->soyad << std::endl << this->adres << std::endl << this->musteriHizmetNo 
		<< std::endl << this->sifre << std::endl << this->bakiye << std::endl;
	duzenleme.close();

}

std::string musteriBilgi::getAd()
{
	return this->ad;
}

std::string musteriBilgi::getSoyad()
{
	return this->soyad;
}

std::string musteriBilgi::getAdres()
{
	return this->adres;
}

int musteriBilgi::getSifre()
{
	return this->sifre;
}

int musteriBilgi::getMusteriHizmetNo()
{
	return this->musteriHizmetNo;
}

double musteriBilgi::getBakiye()
{
	return this->bakiye;
}

void musteriBilgi::musteriBilgiYaz() {
	std::cout << "[1]Ad: " << ad << std::endl << "[2]Soyad: " << soyad << std::endl << "[3]Adres: " << adres << std::endl
		<< "[4]MusteriHizmetNo: " << musteriHizmetNo << std::endl << "[5]Sifre: " << sifre << std::endl << "[6]Bakiye: " << bakiye << std::endl;
}

 void musteriBilgi::menu() {
	 while (1) {
		 system("cls");
		 std::cout << "[1]Para Yatirma" << std::endl
			 << "[2]Para Cekme" << std::endl
			 << "[3]Fatura Odeme" << std::endl
			 << "[4]Havale" << std::endl
			 << "[5]Bakiye Goruntuleme" << std::endl
			 << "[6]Cikis" << std::endl;
		 short secim;
		 std::cin >> secim;
		 switch (secim) {

		  // Para Yatýrma iþlemleri yapýlýyor....
		 case 1: {
			 system("cls");
			 double neKadar;
			 std::cout << "Yatirmak Istediginiz Tutari Giriniz : " << std::endl << "\t.00TL\r";
			 std::cin >> neKadar;
			 if (neKadar < 1) {
				 cout << "1 TL Altinda Para Yatirilamaz.";
				 _sleep(1500);
				 break;
			 }
			 std::cout << "Islemi Onayliyor musunuz." << std::endl << "[1]Evet\t[2]Hayir" << std::endl;
			 short secim;
			 std::cin >> secim;
			 if (secim == 1) {
				 paraYatirma(neKadar);
				 std::cout << "Isleminiz Basari ile Gerceklesmistir.";
			 }
			 else if (secim == 2) break;
			 else
				 std::cout << "Yanlis Islem Yapildi";
			 _sleep(1500);
		 }break;

		 //Para Cekme Islemleri Yapiliyor.
		 case 2: {
			 system("cls");
			 double neKadar;
			 std::cout << "Miktari Giriniz:" << std::endl << "\t.00TL\r";
			 std::cin >> neKadar;
			 if (neKadar < 1) {
				 cout << "1 TL Altinda Para Cekilemez.";
				 break;
			 }
			 std::cout << "Bakiyenizden " << neKadar << ",00TL Para Cekimi Yapilacak OnayLiyor musunuz?" << std::endl << "[1]EVET\t[2]Hayir" << std::endl;
			 int secim;
			 std::cin >> secim;

			 if (secim == 1) {
				 bool tamam;
				 tamam = paraCekme(neKadar);
				 if (tamam)
					 std::cout << "Isleminiz Basari Ile Gerceklestirildi.";
				 else
					 std::cout << "Yetersiz Bakiye...";
				 _sleep(1500); break;
			 }
			 else if (secim == 2)
				 break;
			 else {
				 std::cout << "Yanlis Islem"; _sleep(1000);
			 }
		 }break;

		 //fatura ödeme iþlemleri yapýlýyor..
		 case 3: {
			 system("cls");
			 bool tamam;
			 tamam = faturaOde();
			 if (tamam)
				 std::cout << "Isleminiz Basariyla Gerceklesmistir.";
			 else
				 std::cout << "Menuye Donduruluyorsunuz."; 
			 _sleep(1500);
		 }break;
		 
		 //Havale Ýslemleri yapýlýyor...
		 case 4: {
			 system("cls");
			 std::string yatiranNo;
			 std::string yatirilanNo;
			 string aciklama;
			 bool dogrulama;
			 std::cout << "Musteri Hizmet Numaranizi Giriniz :" << std::endl << "--------\r";
			 std::cin >> yatiranNo;
			 std::cout << "Yatirilicak Kisinin Hizmet No'sunu Giriniz : " << std::endl << "--------\r";
			 std::cin >> yatirilanNo;
			 if (!yatiranNo.compare(yatirilanNo)) { cout << "2 ayni Hizmet No Girdiniz Tekrar Deneyiniz."; _sleep(1500); break; }
			 dogrulama = strKrslstr(yatiranNo, intToStr(this->musteriHizmetNo));
			 if (!dogrulama) { cout << "Hizmet Numaranizi Yanlis Girdiniz."; _sleep(1500); break; }
			 string kacinciKayit;
			 dosyaAra(yatirilanNo, dogrulama, kacinciKayit);
			 if (!dogrulama) { cout << "Verilen Hizmet Numarasinda Birisi yoktur.."; _sleep(1500); break; }
			 double HavaleMiktari;
			 cout << "Havale Miktarini Giriniz : " << endl << "\t.00TL\r";
			 cin >> HavaleMiktari;
			 cout << "En fazla 20 Karakter Olacak Sekilde Aciklama Giriniz : ";
			 string temp;		// girileni gecici olrk bir str ye atayýp onun ilk 20 karakterini aldým.
			 cin.get();
			 getline(cin, temp);
			 aciklama = temp.substr(0, 20);
			 cout << "Islemi Yapmak Istediginize Emin misiniz :  [1]Evet\t[2]GERI" << endl;
			 short secim;
			 cin >> secim;
			 if (secim == 1) {
				 dogrulama = havale(yatirilanNo, kacinciKayit, HavaleMiktari);
				 if (dogrulama) { cout << "Isleminiz Basari Ile Gerceklesti"; havaleKayit(yatirilanNo, HavaleMiktari, aciklama); }
			 }
			 else if (secim == 2)
				 cout << "Islem Iptal Ediliyor.";
			 else
				 cout << "Yanlis Islem. Isleminiz Iptal Ediliyor.";
			 _sleep(1500);
		 }break;

		 //Bakiye Goruntuleme....
		 case 5: {system("cls"); std::cout << getBakiye() << ",00 TL" << std::endl << "Geri Donmek Icin Herhangi Bir Tusa Basiniz :"; _getch(); break; }
		 
		 //ÇIKIÞ
		 case 6:std::cout << "Cikis Yapiliyor..."; _sleep(1000); exit(EXIT_SUCCESS);
		 }
	 }
 }

 bool musteriBilgi::paraCekme(double neKadar){
	 if (bakiye < neKadar)
		 return false;
	 setBakiye(bakiye - neKadar);
	 duzenlemeyiKaydet();
	 paraIslemleriKayit("Para Cekme", neKadar);
	 return true;
 
 }

 void musteriBilgi::paraYatirma(double neKadar){
	 setBakiye(neKadar + bakiye);
	 duzenlemeyiKaydet();
	 paraIslemleriKayit("Para Yatirma", neKadar);
 }

 bool musteriBilgi::faturaOde() {
	 std::cout << "Odeme Yapmak Istediginiz Fatura Turunu Giriniz." << std::endl
		 << "[1]Elektrik" << std::endl
		 << "[2]Su" << std::endl
		 << "[3]A.D.S.L Internet" << std::endl
		 << "[4]Geri" << std::endl;
	 int secim;
	 std::cin >> secim;
	 switch (secim) {

	 //Elektrik Faturasi icin islemler
	 case 1: {
		std::cout << "Odeme Miktarini Giriniz." << std::endl << "\t.00TL\r"; 
		double sayi; 
		std::cin >> sayi; 
		if (sayi < 1) {
			cout << "1 TL Altinda Fatura Odenemez.";
			return false;
		}
		if (sayi > bakiye) {
			std::cout << "Bakiyeniz Yetersiz."; _sleep(1500);
			return false;
		}
		std::cout << "Elektrik Faturasi Olarak " << sayi << ",00TL Odenecek Onayliyor Musunuz" << std::endl << "[1]EVET\t[2]Hayir"; 
		int secim; 
		std::cin >> secim; 
		if (secim == 1) {
			this->bakiye -= sayi;
			faturaIslemKayit("elektrik", sayi);
			
			return true;
		}
		else if (secim == 2) 
			return false; 
		else{
			std::cout << "Yanlis Islem"; _sleep(1000); return false;
			}
	 }break;

     //Su Faturasý Ýþlemleri
	 case 2: {
		 std::cout << "Odeme Miktarini Giriniz." << std::endl << "\t,00TL\r"; 
		 double sayi; 
		 std::cin >> sayi;
		 if (sayi < 1) {
			 cout << "1 TL Altinda Fatura Odenemez.";
			 return false;
		 }
		 if (sayi > bakiye) {
			 std::cout << "Bakiyeniz Yetersiz."; _sleep(1500);
			 return false;
		 }
		 std::cout << "Su Faturasi Olarak " << sayi << ",00TL Odenecek Onayliyor Musunuz" << std::endl << "[1]EVET\t[2]Hayir";
		 int secim; std::cin >> secim; 
		 if (secim == 1) { 
			 this->bakiye -= sayi;
			 faturaIslemKayit("Su", sayi);
			 return true;
		 }
		 else if (secim == 2) 
			 return false; 
		 else { 
			 std::cout << "Yanlis Islem"; _sleep(1000); 
			 return false; 
		 }
	 }break;

	 //A.D.S.L. Fatura Ýþlemleri
	 case 3: {
		 std::cout << "Odeme Miktarini Giriniz." << std::endl << "\t,00TL\r"; 
		 double sayi; 
		 std::cin >> sayi;
		 if (sayi < 1) {
			 cout << "1 TL Altinda Fatura Odenemez.";
			 return false;
		 }
		 if (sayi > bakiye) {
			 std::cout << "Bakiyeniz Yetersiz."; _sleep(1500);
			 return false;
		 }
		 std::cout << "A.D.S.L. Internet Faturasi Olarak " << sayi << ",00TL Odenecek Onayliyor Musunuz" << std::endl << "[1]EVET\t[2]Hayir";
		 int secim;
		 std::cin >> secim; 
		 if (secim == 1) { 
			 this->bakiye -= sayi;
			 faturaIslemKayit("ADSL", sayi);
			 return true;
		 }
		 else if (secim == 2) 
			 return false; 
		 else { 
			 std::cout << "Yanlis Islem"; _sleep(1000);
			return false; 
		 }
	 }break;


	 case 4: return false; break;
	 default: std::cout << "Yanlis Islem Secildi. "; _sleep(1500); return false;
	 }

 }

 bool musteriBilgi::havale(std::string yatirilanNo, std::string kacinciKayit,double havaleMiktari) {
	 if (havaleMiktari <= 0) {
		 cout << "Sadece 1 TL ve Uzeri Havale Edilebilir ";
			 return false;
	 }
	 if (bakiye > havaleMiktari) {
		 this->bakiye -= havaleMiktari;
		 musteriBilgi yatirilan(kacinciKayit);
		 double yeniBakiye = yatirilan.getBakiye() + havaleMiktari;
		 yatirilan.setBakiye(yeniBakiye);
		 yatirilan.duzenlemeyiKaydet();
		 this->duzenlemeyiKaydet();
		 return true;
	 }
	 else
	 {
		 cout << "Bakiyeniz Yetersiz Islem Yapilamadi." << endl;
		 return false;
	 }
 }

 void musteriBilgi::faturaIslemKayit(std::string hangiFatura, double sayi) {
	
	 string dosyahangiFatura = hangiFatura + ".txt";
	 std::ofstream kaydet;
	 kaydet.open(dosyahangiFatura.c_str(), std::ios::app);
	 kaydet << this->musteriHizmetNo << " Hizmet No'lu Musteri " << sayi << ".00TL Tutarýnda " << hangiFatura << " Fatura Odemesi Yapmistir." << std::endl
		 << "Onceki Bakiye:" << this->bakiye+sayi << ".00TL" << "\t Kalan Bakiye: " << this->bakiye << ".00 TL" << std::endl << std::endl;
	 kaydet.close(); 
	 duzenlemeyiKaydet();
 }

 void musteriBilgi::paraIslemleriKayit(std::string islem, double neKadar)
 {
	 std::ofstream LogKaydet;
	 LogKaydet.open("ParaCekme-Yatirma.txt", ios::app);
	 LogKaydet << this->musteriHizmetNo << " Hizmet No'lu Musteri " << neKadar << ".00TL" << " Tutarinda " << islem << " Islemi Yapmistir." << std::endl
		 << "Onceki Bakiye: " << this->bakiye - neKadar << ".00TL\t" << "Bakiye: " << this->bakiye << ".00TL" << std::endl << std::endl;
	 LogKaydet.close();
 }

 void musteriBilgi::havaleKayit(std::string yatirilanNo, double neKadar,string aciklama) {
	 ofstream kayit;
	 kayit.open("havale.txt", ios::app);
	 kayit << getMusteriHizmetNo() << " Hizmet No'lu Musteri " << yatirilanNo << " Hizmet No'lu Musteri Hesabina " << neKadar << ".00TL Havale Gerceklestirdi." << endl
		 << "Aciklama : " << aciklama << endl << endl << endl;
	 kayit.close();

 }
