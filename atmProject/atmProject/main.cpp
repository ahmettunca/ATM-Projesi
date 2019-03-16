#include "kullanilan.h"



//main fonksiyon-----------------------
int main() {
	int secim;
	bool kontrol = true;
	while (kontrol) {
		system("cls");
		std::cout << "\tLUTFEN KULLANICI TIPINI\n\t\tBELIRLEYINIZ" << endl
			<< "[1]BANKACI" << endl
			<< "[2]MUSTERI" << endl
			<< "[3]IPTAL" << endl;

		cin >> secim;
		switch (secim) {

		case 1:admin_Kontrol(); admin_Islemleri(); break;	//þifreyi doðru girmiþse program kapanmayacaðý için admin islemlerine yönlenicek

		case 2:{
			
			short sayac=3;
			string hizmetNo;
			string hangiMusteri;
			bool dogrulama;
			
			system("cls");
			cout << "8 Haneli Musteri Hizmet No yu giriniz : " << endl
				<< "--------\r";
			cin >> hizmetNo;
			dosyaAra(hizmetNo, dogrulama, hangiMusteri);
			if (!dogrulama) { cout << "Girdiginiz Hesab Numarasi Bulunmamaktadir. Tekrar Deneyiniz"; _sleep(1500); break; }
			int sifre;
			musteriBilgi girisYapti(hangiMusteri);
			while (1) {
				cout << "4 Haneli Sifreyi Giriniz : " << endl << "----\r";
				cin >> sifre;
				if (sifre != girisYapti.getSifre()) {
					sayac--;
					if (sayac == 0) {
						cout << "Hesabiniz Bloke Oldu Banka Ile Temasa Gecin" << endl;
						dogrulama = false;
						break;
					}
					cout << "Yanlis Sifre Girildi. Kalan Hak: " << sayac << endl;
				}
				else {
					cout << "Basari Ile Giris Yapildi.";
					dogrulama = true;
					break;
				}
				
			}
			_sleep(1500);
			if (!dogrulama) {

			}
			girisYapti.menu();
		}break;

		case 3: kontrol = false; break;

		default: cout << "Yanlis Islem Yapildi. Tekrar Deneyiniz." << endl;
		}
	}

	system("PAUSE");
	return 0;
}
//--------------------------------------------------------------------------------------------------




//verilen 2 string türünde parametrenin ayný olup olmadýðýný kontrol eder 0 veya 1 döndürür.
bool strKrslstr(std::string str1, std::string str2) {
	if (str1.length() != str2.length())
		return false;
	else {
		for (int i = 0; i < str1.length(); i++) {
			if (str1[i] != str2[i])
				return false;
		}
		return true;
	}

}
//-----------------------------------------------------------------

//Admin girisini kontrol eder
bool admin_Kontrol() {
	bool deneme = true;
	string gParola;			//Gerçek parola;
	string dParola;			//Kullanýcýnýn gireceði parola
	fstream dosya;
	dosya.open("admin.txt", ios::in);
	dosya >> gParola;		//admin.txt içerisinden admin parolasýný aldým.

	cout << "Admin Parolasini Giriniz:";
	while (1) {	//bu döngü ile eðer yanlýþ parola girilirse 1 hak daha veriyorum.	

		cin >> dParola;

		if (strKrslstr(gParola, dParola)) {					//kullanilan.h içerisindeki fonksiyon ile 2 string i karsilaþtýrýyor.
			cout << "Basari Ile Giris Yapildi" << endl;
			_sleep(2000);
			break;
		}

		else {

			if (deneme == false) {							//eðer kullanýcý 2. hakkýnýda yanlýþ kullanmýþsa programý kapatýyor.
				cout << "Uzgunum Yetkisiz Girmeye Calistiginiz Icin Program Kapaniyor";
				_sleep(3000);
				exit(EXIT_SUCCESS);
			}

			cout << "Giris Basarisiz. Sadece 1 Deneme Hakkiniz Var : ";
			deneme = false;
		}
	}
	return true;

}
//----------------------------------------------------------------

//admin Islemlerini Yapan Fonksiyon
void admin_Islemleri() {
	bool kontrol = true;        //kullanicinin geri-iptal vs. gibi secimlerinin kontrolünü yapacak deðiþken.
	srand(time(NULL));
	while (kontrol) {
		system("cls");				//bu komut,komut ekranýnýn temizlenmesini saðlýyor.
		std::cout << "\t***ADMIN***" << std::endl
			<< "[1] Kullanici Hesabi Olusturma" << std::endl
			<< "[2] Kullanici Hesap Duzelt" << std::endl
			<< "[3] Para Cekme" << std::endl
			<< "[4] Para Yatirma" << std::endl
			<< "[5]GERI" << std::endl;
		short secim;
		cin >> secim;
		switch (secim) {

			//hesab oluþturan kýsým
		case 1: {
			system("cls");
			short secim2;
			int hizmetNo;
			int sifre;
			string ad;
			string soyad;
			string adres;

			//musteri hizmet no belirleme
			cout << "8 Haneli Musteri Numarasini Giriniz" << endl
				<< "--------\r";
			cin >> hizmetNo;


			//sifre olusturma
			sifre = 1000 + rand() % 8999;
			cout << "4 Haneli Sifreniz : " << sifre << endl;


			//diðer bilgileri alma
			cout << "***KULLANICI***" << endl
				<< "Adi:";
			cin >> ad;
			cout << "Soyadi:";
			cin >> soyad;
			cout << "Adresi:";
			cin >> adres;


			cout << "[1]Kaydet\t"
				<< "[2]Geri" << endl;
			cin >> secim2;
			if (secim2 == 2)
				break;


			//txt ye kayit islemleri yapiliyor...
			if (txtKaydet(ad, soyad, adres, hizmetNo, sifre))
				cout << "Kayit Basariyla Tamamlandi...";
			else
				cout << "Kayit Basarisiz...";

			_sleep(3000);
			break;
		}

				//Hesabý düzenleyen kýsým
		case 2: {
			bool tekrar;
			string hangiMusteri;
			do {
				tekrar = false;
				system("cls");
				string hizmetNo;
				bool musteriVarmi = false;
				cout << "Bilgileri Duzenlenecek Olan Musterinin Hizmet No'sunu giriniz : ";
				cin >> hizmetNo;

				dosyaAra(hizmetNo, musteriVarmi, hangiMusteri);//girdiði hizmetno yu dosyalarda aratýcam eðer varsa kacýncý musteri olduðunu bana 'hangiMusteri'
															   //deðiþkeninin içerisine atarak getirecek.
				if (!musteriVarmi) {
					cout << "Musteri Bulanamadi. Tekrar Arama Yapmak Istiyorsaniz 1'e basiniz. Geri Donmek icin Herhangi Bir Tusa Basiniz.";
					char devammi;
					cin >> devammi;
					if (devammi==1)
						tekrar = true;
					else tekrar = false;

				}
				else {
					musteriBilgi musteri(hangiMusteri);
					cout << "Hangisini Degismek Istiyorsunuz: " << endl;
					musteri.musteriBilgiYaz();
					cout << "[7]Geri" << endl;
					short hangisi;
					cin >> hangisi;
					switch (hangisi) {
					case 1: {cout << "Yeni Degeri Giriniz: "; string yeniad; cin >> yeniad; musteri.setAd(yeniad); musteri.duzenlemeyiKaydet(); }break;
					case 2: {cout << "Yeni Degeri Giriniz: "; string yenisoyad; cin >> yenisoyad; musteri.setSoyad(yenisoyad); musteri.duzenlemeyiKaydet(); }break;
					case 3: {cout << "Yeni Degeri Giriniz: "; string yeniadres; cin >> yeniadres; musteri.setAdres(yeniadres); musteri.duzenlemeyiKaydet(); }break;
					case 4: {cout << "Bu deger degistirilemez" << endl; }break;
					case 5: {cout << "Yeni Degeri Giriniz: "; int yenisifre; cin >> yenisifre; musteri.setSifre(yenisifre); musteri.duzenlemeyiKaydet(); }break;
					case 6: {cout << "Bakiyeyi Buradan Degisemezsiniz. "; }break;
					case 7:break;
					default:cout << "Yanlis Islem Secildi" << endl;
					}
					cout << "Isleminiz uygulaniyor.";
					_sleep(2000);
				}
			} while (tekrar);

		}break;
			//para cekme
		case 3: {
			system("cls");
			string hizmetNo;
			bool varmi;
			string kacinciKayit;
			cout << "Para Cekilecek Olan Hesabin Hizmet Numarasini Giriniz :" << endl << "--------\r";
			cin >> hizmetNo;
			dosyaAra(hizmetNo, varmi, kacinciKayit);
			if (varmi) {
				musteriBilgi musteri(kacinciKayit);
				double neKadar;
				cout << "Cekilecek Miktari Giriniz:" << endl << "\t.00TL\r";
				cin >> neKadar;
				if (neKadar < 0) { cout << "Yanlis Miktar Girildi."; _sleep(1500); break; }
				cout << "Islemi Onayliyor Musunuz: [1]Evet\t[2]Hayir" << endl;
				int secim;
				cin >> secim;
				if (secim == 1) { bool dogrulama = musteri.paraCekme(neKadar); if (!dogrulama) { cout << "Islem Basarisiz. Bakiyenizi Kontrol ediniz"; _sleep(1500); break; } cout << "Isleminiz Basari Ile Tamamlandi." << endl; }
				else if (secim == 2) { cout << "Geri Donduruluyorsunuz." << endl; }
				else { cout << "Yanlis Islem Geri Donduruluyorsunuz." << endl; }
			}
			else
				cout << "Boyle Bir Hesab Bulunmamaktadir.";
			_sleep(1500);

		}break;
			//para Yatirma
		case 4: {
			system("cls");
			string hizmetNo;
			bool varmi;
			string kacinciKayit;
			cout << "Para Yatirilacak Olan Hesabin Hizmet Numarasini Giriniz :" << endl << "--------\r";
			cin >> hizmetNo;
			dosyaAra(hizmetNo, varmi, kacinciKayit);
			if (varmi) {
				musteriBilgi musteri(kacinciKayit);
				double neKadar;
				cout << "Yatirilacak Miktari Giriniz:" << endl << "\t.00TL\r";
				cin >> neKadar;
				if (neKadar < 0) { cout << "Yanlis Miktar Girildi."; _sleep(1500); break; }
				cout << "Islemi Onayliyor Musunuz: [1]Evet\t[2]Hayir" << endl;
				int secim;
				cin >> secim;
				if (secim == 1) { musteri.paraYatirma(neKadar); cout << "Isleminiz Basari Ile Tamamlandi." << endl; }
				else if (secim == 2) { cout << "Geri Donduruluyorsunuz." << endl; }
				else { cout << "Yanlis Islem Geri Donduruluyorsunuz." << endl; }
			}
			else
				cout << "Boyle Bir Hesab Bulunmamaktadir.";
			_sleep(1500);
		}break;

		case 5: kontrol = false; break;
		default: cout << "Yanlis Islem Sectiniz. Tekrar Deneyiniz."; _sleep(1500);

		}
	}
}
//----------------------------------------------------------------


//text e kayýt iþlemlerini yapan fonksiyon.
bool txtKaydet(string &ad, string &soyad, string &adres, int &hizmetNo, int &sifre) {

	//txt den kacinci musteri olduðunu aldýk çünkü ona göre ismi farklý olan txt kaydedicez örn: musteri1.txt , musteri2.txt
	ifstream kacinciMusteri;
	kacinciMusteri.open("musteri_sayi.txt");
	if (kacinciMusteri.fail())
		return false;
	string s_mustSayi;
	int i_mustSayi;
	getline(kacinciMusteri, s_mustSayi);
	stringstream donusturucu;
	donusturucu << s_mustSayi;
	donusturucu >> i_mustSayi;
	kacinciMusteri.close();
	ofstream musteriArttir;
	musteriArttir.open("musteri_sayi.txt");
	musteriArttir << (i_mustSayi + 1);
	musteriArttir.close();


	//txt kaydýna geçiyoruz.
	string isim = "musteri" + s_mustSayi + ".txt";
	ofstream kayit;
	kayit.open(isim.c_str());
	if (kayit.fail())
		return false;
	kayit << ad << endl << soyad << endl << adres << endl << hizmetNo << endl << sifre << endl << 0;
	kayit.close();
	return true;
}
//-----------------------------------------------------------------------------------------------------

//bu fonksiyon kayitlarda bu hizmet no'lu biri olup olmadýðýný kontrol eder ve ayrýca bu fonksiyonu çaðýrmadan önce
//hangiMusteri için kullanýlmayan bir string deðiþkeni oluþturup parametre olarak verirsek fonksiyon görevi bittiðinde o deðiþkenin içerisine
//bu hizmet No lu müþterinin kaçýncý kayýtta olduðunu yazacaktýr.
bool dosyaAra(string hizmetNo, bool &varmi, string& hangiMusteri) {
	varmi = false;
	string musteriSayi;
	int i_musteriSayi;
	ifstream kacMusteriVar;
	kacMusteriVar.open("musteri_sayi.txt");
	getline(kacMusteriVar, musteriSayi);
	kacMusteriVar.close();

	stringstream donustur;
	donustur << musteriSayi;
	donustur >> i_musteriSayi;
	string sayi;
	for (int i = 1; i < i_musteriSayi; i++) {
		stringstream donustur;
		donustur << i;
		donustur >> sayi;

		string dosya = "musteri" + sayi + ".txt";

		string satir;
		ifstream bulucu;
		bulucu.open(dosya.c_str());
		for (int j = 0; j < 6; j++) {
			getline(bulucu, satir);
			if (j == 3) {
				if (strKrslstr(hizmetNo, satir)) {
					varmi = true;
					break;
				}
			}
		}
		bulucu.close();
		if (varmi) {
			hangiMusteri = sayi;
			break;
		}
	}
	if (varmi == false)
		return false;
	return true;
}


//verilen int deðeri string e dönüþtürür.
string intToStr(int sayi) {
	string str_sayi;
	stringstream donusturucu;
	donusturucu << sayi;
	donusturucu >> str_sayi;
	return str_sayi;

}

	
