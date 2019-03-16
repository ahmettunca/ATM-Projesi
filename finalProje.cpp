#include <stdio.h>
#include <iostream>
#include <locale.h> 
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <math.h>
using namespace std;
char * strcat(char * dest,const char * src);
int index = 0;
//Admin �ifresini global olarak tan�mlad�k.
char * adminPassword = "5666ab";
int ilk_musteri_Numara = 20089999;
void kullaniciSec();
void adminGiris();
void clrscr();
void verileriBelgeyeKaydet(int);
void musteriBulunamadiKontrol(int id);
void HataliSecim();
int yeniKullaniciArtir();
void bakiyeCheck(int, float, int);
void paraYatir(int id, int tip);
void paraCek(int id, int tip);
void havaleYap(int id);
void faturaOde(int id);
void bakiyeGoruntule(int id);
void islemTamam(int id, int tip);
void islemleriGoster(int id);
int kullaniciSayisiBul();
void mustNoKontrol(int id);
void kullaniciHesapOlustur();
void veriyiDiziyeAktar();
char * satirdanVeriAl(char * veriYolu, int index);
void kullaniciHesapDuzelt(int secim);
int kullaniciBul(int hesapNO);
const int kullaniciSayisi = 100;
/*M��terileri tutaca��m�z bir struct tan�mlad�k. Bu struct istenildi�i gibi 100 kullan�c� bar�nd�rabilen bir struct.*/
struct musteri {
  int musteriHesapNO;
  int sifre;
  float bakiye = 0.0;
  char ad[20];
  char soyad[20];
  char adres[250];
  int bloke = 0;
}
musteriler[kullaniciSayisi];
main() {
   /*Program dilini T�rk�e yap�yoruz.*/
  setlocale(LC_ALL, "Turkish");
  /*Global index de�i�kenine sayi.txt'den ald���m�z kullan�c� say�s�n� at�yoruz. Bundan sonra atayaca��m�z elemanlar� dizinin
  ka��nc� s�ras�na ataca��m�z� bu sayede bilebiliyoruz.*/
  index = kullaniciSayisiBul();
  /*Daha �nceki verileri diziye aktar�yoruz.*/
  veriyiDiziyeAktar();
  kullaniciSec();
}
void adminSifreGiris() {
  clrscr();
  char adminSifre[6];
  /*Admin �ifresini do�ru girene kadar sormaya devam edecek bir d�ng�
  tan�mlad�k.*/
  while (true) {
    printf("�ifreyi giriniz: ");
    scanf("%s", & adminSifre);
    if (strcmp(adminPassword, adminSifre) == 0)
      break;
    else
      printf("\n**��FRE YANLI� TEKRAR G�R�N�Z!**\n");
  }
  adminGiris();
}
void adminGiris() {
  clrscr();
  int secim, id, hesapNo;
  printf("*** Admin ***\n[1]Kullan�c� Hesap Olu�tur\n[2]Kullan�c� Hesap D�zelt\n[3]Para �ekme\n[4]Para Yat�rma\n[5]�IKI�\nSe�iminiz:");
  scanf("%d", & secim);
  /*Kullan�c�n�n se�ti�i i�leme g�re switch-case yard�m�yla y�nlendiriyoruz.*/
  switch (secim) {
  case 1:
    kullaniciHesapOlustur();
    break;
  case 2:
    int secim2, mustNo;
    printf("\nD�zenlemek istedi�iniz m��teri numaras�: \n");
    scanf("%d", & mustNo);
    /*mustNoKontrol yard�m�yla girilen m��teri numaras� sistemde kay�tl� m� de�il mi ��renebiliyoruz.*/
    mustNoKontrol(mustNo);
    break;
  case 3:
    printf("\nPara �ekmek �stedi�iniz Hesap Numaras�n� Giriniz: ");
    scanf("%d", & hesapNo);
    id = kullaniciBul(hesapNo);
    /*hesapNo'yu kullan�c�Bul fonksiyonuna g�ndererek b�yle bir kullan�c� var m� anlayabiliyoruz.
	E�er 404 geldiyse b�yle bir kullan�c� bulunmuyordur.*/
    if(id==404)
    {
    	printf("\n**BU NUMARAYA A�T B�R KULLANICI BULUNMAMAKTADIR. ANA EKRANA D�NMEK ���N ENTER'A BASINIZ**\n");
    	getch();
		adminGiris(); 	
    }
    /*Para �ek metoduna kullan�c� id'sini ver tip = 1 g�nderiyoruz. 1 admin oldu�umuzu belli ediyor.*/
    paraCek(id, 1);
    break;
  case 4:
    printf("Para Yat�rmak �stedi�iniz Hesap Numaras�n� Giriniz: ");
    scanf("%d", & hesapNo);
    if(id==404)
    {
    	printf("\n**BU NUMARAYA A�T B�R KULLANICI BULUNMAMAKTADIR. ANA EKRANA D�NMEK ���N ENTER'A BASINIZ**\n");
    	getch();
		adminGiris(); 	
    }    id = kullaniciBul(hesapNo);
    paraYatir(id, 1);
    break;
  case 5:
    kullaniciSec();
    break;
    /*E�er yaz�lan se�imler d���nda bir se�im yap�ld�ysa tekrar soruyor.*/
  default:
    printf("\n**YANLI� SE��M YAPTINIZ. TEKRAR SE��N�Z! DEVAM ETMEK ���N ENTER'A BASINIZ.**\n");
    getch();
    adminGiris();
    break;
  }
}
/*Bu metod yard�m�yla ekranda �imdiye kadar yaz�lan yaz�lar� temizleyebiliyoruz.*/
void clrscr() {
  system("@cls||clear");
}
void kullaniciSec() {
  clrscr();
  int secim;
  printf("L�TFEN KULLANICI T�P�N� BEL�RLEY�N�Z:\n[1]BANKACI\n[2]M��TER�\nSe�iminiz: ");
  scanf("%d", & secim);
  if (secim == 1) {
    adminSifreGiris();
  } else if(secim == 2){
    clrscr();
    int hesapNo, sifre, id = 404, hak = 3;
    while (true) {
      printf("M��teri numaras�n� giriniz: ");
      scanf("%d", & hesapNo);
      /*Girilen m��teri numaras� var m� yok mu kontrol ediyoruz.*/
      id = kullaniciBul(hesapNo);
      if (id == 404) {
        printf("**BU M��TER� NUMARASINA A�T B�R M��TER� YOK!**\n");
      } else
        break;
    }
    while (true) {
      printf("�ifrenizi giriniz: ");
      scanf("%d", & sifre);
      /*�ifre ve hesapNo e�le�iyorsa  giri� yapabiliyor*/
      if (hesapNo == musteriler[id].musteriHesapNO && sifre == musteriler[id].sifre)
        break;
        /*Her yanl�� girdi�inde 3 hakk�ndan 1 hak eksiliyor. 3 yanl��ta ise bloke oluyor.*/
      else
        printf("�ifre yanl�� girildi!\n\n%d\n\nHakk�n�z Kald�!\n", --hak);
      if (hak == 0) {
        printf("%d NOLU M��TER� HESABINIZ BLOKE OLMU�TUR.\n\nL�TFEN BANKANIZ �LE �LET���ME GE��N�Z!\n", musteriler[id].musteriHesapNO);
        musteriler[id].bloke = 1;
        /*verileriBelgeyeKaydet metodu yard�m�yla bloke durumunu .txt'ye kaydediyoruz.*/
        verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
        break;
      }
    }
    if (musteriler[id].bloke == 1) {
      printf("\n**HESABINIZ BLOKE OLMU�TUR. BANKA �LE �LET���ME GE��N�Z.\nANA EKRANA D�NMEK ���N ENTER'A BASINIZ...**\n");
      getch();
      kullaniciSec();
      clrscr();
    } else {
    	/*E�er ad�mlar ba�ar�yla ge�ildiyse ana ekrana girebiliyor.*/
      printf("HO�GELD�N %s %s!", musteriler[id].ad, musteriler[id].soyad);
      islemleriGoster(kullaniciBul(hesapNo));
    }
  }
  else{
  	kullaniciSec();
  }
}
/*kullaniciBul metodu yard�m�yla girilen hesap numaras�n�n dizideki index'ini bulabiliyoruz.
E�er kullan�c� yoksa 404 d�n�yor.*/
int kullaniciBul(int hesapNO) {
  int id = 404;
  for (int i = 0; i < kullaniciSayisi; i++) {
    if (musteriler[i].musteriHesapNO == hesapNO) {
      id = i;
    }
  }
  return id;
}
/*T�m kullan�c� i�lemlerinin g�sterildi�i metod.
Burda paraYatir, paraCek gibi metodlarda 2 de�erini 
g�ndermemizin sebebi kullan�c� oldu�umuzu belli etmek amac�yla.
Bu sayede admin ve kullan�c� ayn� para �ekme metodunu kullanabiliyor.
��lem bitince geri d�n��lerde e�er 1 ise admin ekran�na, e�er 2 ise
kullan�c� ekran�na d�n�yor.*/
void islemleriGoster(int id) {
  clrscr();
  int secim;
  printf("[1]PARA YATIRMA\t[4]FATURA �DEME\n[2]PARA �EKME\t[5]BAK�YE G�R�NT�LEME\n[3]HAVALE\nSe�iminiz: ");
  scanf("%d", & secim);
  switch (secim) {
  case 1:
    paraYatir(id, 2);
    break;
  case 2:
    paraCek(id, 2);
    break;
  case 3:
    havaleYap(id);
    break;
  case 4:
    faturaOde(id);
    break;
  case 5:
    bakiyeGoruntule(id);
    break;
  default:
    printf("\n**YANLI� SE��M YAPTINIZ TEKRAR SE��N�Z.**\n");
    islemleriGoster(id);
    break;
  }
}
void paraYatir(int id, int tip) {
  /*Ekranda yazan yaz�lar temizleniyor.*/
  clrscr();
  float miktar;
  printf("%s %s Ad�na Yat�r�lacak Miktar� giriniz: ", musteriler[id].ad, musteriler[id].soyad);
  scanf("%f", & miktar);
  /*Para yat�r�lan kullan�ya para yat�r�yor ve yat�r�lan para kadar yat�ran kullan�cadan
  para eksiltiyor.*/
  musteriler[id].bakiye = musteriler[id].bakiye + miktar;
  /*Veriler belgeye kaydediliyor.*/
  verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
  /*��lem bitince i�lemTamam ekran�na giriyor ve beraberinde tip de�erinide g�nderiyor.
  Tip de�eri bu ekrana admin hesab�ndan veya kullan�c� hesab�ndan gelmesine g�re de�i�iklik g�sterir.*/
  islemTamam(id, tip);
}
void paraCek(int id, int tip) {
  clrscr();
  float miktar;
  printf("Miktar� giriniz: ");
  scanf("%f", & miktar);
  /*Yeterli miktarda bakiye var m� kontrol ediliyor. E�er yoksa a�a��daki i�lemler
  ger�ekle�tirilmiyor.*/
  bakiyeCheck(id, miktar, tip);
  /*Kullan�c�dan �ekilen miktar eksiltiliyor.*/
  musteriler[id].bakiye = musteriler[id].bakiye - miktar;
  /*Veriler belgeye kaydediliyor.*/
  verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
  islemTamam(id, tip);
}
void havaleYap(int id) {
  clrscr();
  int hizmetNo, hesapNo, secim, id2;
  float miktar;
  hizmetNo = musteriler[id].musteriHesapNO;
  char aciklama[20];
  printf("Havale Yap�lacak Kullan�c� Hesap Numaras� Giriniz:  ");
  scanf("%d", & hesapNo);
  printf("A��klama Giriniz:  ");
  getc(stdin);
  gets(aciklama);
  printf("Havale Miktar�n� Giriniz:  ");
  scanf("%f", & miktar);
  /*Bakiye kontrol edilir. E�er yetersizse a�a��da ad�mlar ger�ekle�tirilmez.*/
  bakiyeCheck(id, miktar, 2);
  printf("%d Nolu Kullan�c�ya %f TL G�nderilecek Onayl�yor Musunuz? \n[1]EVET\n[2]HAYIR\nSe�iminiz: ", hesapNo, miktar);
  scanf("%d", &secim);
  /*E�er kullan�c� onayl�yor ise*/
  if (secim == 1) {
    /*1. kullan�c�dan miktar d���lecek ve 2. kullan�c�ya miktar eklenecek.
	Daha sonras�nda iki kullan�c�da ayr� ayr� .txt dosyalar�na tekrar kay�t
	olacaklard�r.*/
    musteriler[id].bakiye -= miktar;
    id2 = kullaniciBul(hesapNo);
    musteriler[id2].bakiye += miktar;
    verileriBelgeyeKaydet(musteriler[id2].musteriHesapNO);
    verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
    islemTamam(id, 2);
  } else {
    islemleriGoster(id);
  }
}
void faturaOde(int id) {
  clrscr();
  int secim;
  float miktar;
  char * firmaAdi;
  /*Kullan�c�dan se�im yapmas� istenir ve se�im pointer char'a atan�r.*/
  printf("\n[1]Elektrik\n[2]Su\n[3]A.D.S.L. �nternet\n[4]Geri\nSe�iminiz:");
  scanf("%d", & secim);
  if (secim == 1) {
    firmaAdi = "Elektrik";
  } else if (secim == 2) {
    firmaAdi = "Su";
  } else if (secim == 3) {
    firmaAdi = "A.D.S.L. �nternet";
  } else if (secim == 4) {
    islemleriGoster(id);
  } else {
  	/*Yanl�� bir se�im yap�ld�ysa i�lem ba�tan yap�l�r.*/
    printf("\n**YANLI� SE��M YAPTINIZ TEKRAR SE��N�Z!**\n");
    faturaOde(id);
  }
  printf("�deme Miktar�n� Giriniz: ");
  scanf("%f", & miktar);
  bakiyeCheck(id, miktar, 2);
  /*�demenin bir �zeti yaz�l�r.*/
  printf("%s Faturas� Olarak Hesab�n�zdan %.2f. �deme Yap�lacakt�r.\nOnayl�yor musunuz?\n[1]EVET\n[2]HAYIR\nSe�iminiz:", firmaAdi, miktar);
  scanf("%d", & secim);
  if (secim == 1) {
  	/*Miktar hesaptan d���l�r ve .txt dosyas�na kay�t edilir.*/
    musteriler[id].bakiye -= miktar;
    verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
    islemTamam(id, 2);
  } else {
    faturaOde(id);
  }
}
/*Kullan�c� bakiyesini bu metod yard�m�yla g�r�nt�leyebilir.*/
void bakiyeGoruntule(int id) {
  /*Not defterindeki veriler �al��ma an�nda y�netici taraf�ndan
   elle bir de�i�iklik  yap�lma ihtimaline kar�� tekrar diziye aktar�l�r.*/
  veriyiDiziyeAktar();
  clrscr();
  printf("Bakiyeniz:%.2fTL", musteriler[id].bakiye);
  islemTamam(id, 2);
}
/*E�er i�lem tamamsa ve gelen tip 1 ise admin ekran�na geri d�n�l�r.
E�er 2 ise giri� yap�lan kullan�c�n�n ekran�na tekrar id g�nderilerek
geri d�ner.*/
void islemTamam(int id, int tip) {
  int secim;
  /*Tip 1 ise i�lemi yapan admindir ve admin ekran�na d�ner.*/
  if (tip == 1) {
    printf("\n**ISLEMINIZ TAMAMLANDI!**\n[1]ANA MENU\n[2]�IKI�\nSe�iminiz: ");
    scanf("%d", & secim);
    switch (secim) {
    case 1:
      adminGiris();
      break;
    case 2:
      kullaniciSec();
      /*Se�im yanl�� ise metod ba��na tekrar d�ner.*/
    default:
      printf("\n**YANLI� SE��M YAPTINIZ TEKRAR SE��N�Z.**\n");
      islemTamam(id, tip);
      break;
    }
  }
  /*Tip 2 ise kullan�c� ekran�na d�ner.*/
  if (tip == 2) {
    printf("\n**ISLEMINIZ TAMAMLANDI!**\n[1]ANA MENU\n[2]BAK�YE G�R�NT�LEME\n[3]�IKI�\nSe�iminiz: ");
    scanf("%d", & secim);
    switch (secim) {
    case 1:
      islemleriGoster(id);
      break;
    case 2:
      bakiyeGoruntule(id);
      break;
    case 3:
      kullaniciSec();
      break;
    default:
      printf("\n**YANLI� SE��M YAPTINIZ TEKRAR SE��N�Z.**\n");
      islemTamam(id, tip);
      break;
    }
  }
}
/*Bu metod yard�m�yla kullan�c� hesab� olu�turulabilir.*/
void kullaniciHesapOlustur() {
  clrscr();
  char temp[1], sifre, basamak, sayac, sifre_yedek;
  int hesapNo_int;
  /*Kullan�c� say�s� bul metodu sayi.txt'den ka� kullan�c� oldu�unu
  al�r ve ilk kullan�c�ya o kadar say� ekler. B�ylelikle yeni
  eklenecek kullan�n�n m��teri numaras� otomatik olarak atanacakt�r.*/
  hesapNo_int = 20090000+kullaniciSayisiBul();
  printf("M��teri Hizmet No: %d\n", hesapNo_int);
  musteriler[index].musteriHesapNO = hesapNo_int;
  printf("4 haneli �ifre: ");
  scanf("%d", & musteriler[index].sifre);
  printf("Ad�:");
  /*Kullan�c�n�n girdi�i ad verisini gets yard�m�yla alarak
  bo�luklarla beraber al�yoruz(Kullan�c� 2 isimli olabilir.)*/
  getc(stdin);
  gets(musteriler[index].ad);
  printf("Soyad�:");
  gets(musteriler[index].soyad);
  printf("Adresi:");
  gets(musteriler[index].adres);
  /*Giri� bittikten sorna verileri .txt dosyas�na kaydediyoruz.*/
  verileriBelgeyeKaydet(hesapNo_int);
  /*Bu metod yard�m�yla sayi.txt'deki sayac� 1 art�r�yoruz ve b�ylece
  sistemde kay�tl� kullan�c� say�s�n� g�ncellemi� oluyoruz.*/
  yeniKullaniciArtir();
  /*index ise s�radaki kullan�n�n dizideki hangi indexe kay�t olaca��n� belirler.*/
  ++index;
  int secim;
  printf("\n**KULLANICI BA�ARIYLA OLU�TURULDU!**\n\n[1]ADMIN ANA EKRAN\n[2]YEN� KULLANICI OLU�TUR\n[3]�IKI�\nSe�iminiz: ");
  /*Kullan�c�n�n se�imine g�re yanl�� bir se�im girilmedi�i takdirde sonsuz d�ng�den ��kacak ve
  kullan�c�n�n i�lemini ger�ekle�tirecektir.*/
  while (true) {
    scanf("%d", & secim);
    if (secim == 1 || secim == 2 || secim == 3) {
      break;
    } else {
      printf("YANLI� SE��M. TEKRAR SE��N�Z.\n");
    }
  }
  if (secim == 1) {
    adminGiris();
  } else if (secim == 2) {
    kullaniciHesapOlustur();
  } else if (secim == 3) {
    kullaniciSec();
  }
}
/*Bu metod yard�m�yla kullan�c� hesaplar� d�zeltilebilecektir.*/
void kullaniciHesapDuzelt(int secim) {
  int secim2;
  /*�lk ba�ta kullan�c� hesab� bloke mi de�il mi kontro ledilir ve uyar� verilir. E�er
  bloke olmu� ise admin .txt dosyas�ndan bloke durumunu 1'den 0'a getirebilir.*/
  if (musteriler[secim].bloke == 1) {
    printf("**HESAP BLOKE OLMU�. Y�netici C:\\'den a�abilir.");
  }
  /*Kullan�c� bilgilerinin bir �zeti yaz�l�r.*/
  printf("M��teri Numaras�: %d\n�ifre: %d\nAd: %s\nSoyad: %s\nAdres:%s\n",musteriler[secim].musteriHesapNO,musteriler[secim].sifre,musteriler[secim].ad,musteriler[secim].soyad,musteriler[secim].adres);
  printf("\n�ifre:");
  scanf("%d", & musteriler[secim].sifre);
  printf("Ad:");
  getc(stdin);
  gets(musteriler[secim].ad);
  printf("Soyad:");
  gets(musteriler[secim].soyad);
  printf("Adres:");
  gets(musteriler[secim].adres);
  /*D�zenlenmi� veriler tekrar .txt dosyas�na yaz�l�r.*/
  verileriBelgeyeKaydet(musteriler[secim].musteriHesapNO);
  printf("\n**KULLANICI BA�ARIYLA D�ZENLEND�. ANA EKRANA D�NMEK ���N ENTER'A BASINIZ.**\n");
  getch();
  adminGiris();
}
/*E�er girilen miktar hesaptaki bakiyeden y�ksekse bakiye
yetersiz uyar�s� verecektir.*/
void bakiyeCheck(int id, float miktar, int tip) {
  if (miktar > musteriler[id].bakiye) {
    printf("\nYETERS�Z BAK�YE! ANA EKRANA D�NMEK ���N ENTER'A BASINIZ\n");
    getch();
    /*Tip 1 ise admin ekran�na geri d�necektir..*/
    if (tip == 1) {
      adminGiris();
    }
    /*Tip 2 ise kullan�c� ekran�na geri d�necektir.*/
    if (tip == 2) {
      islemleriGoster(id);
    }
  }
}
/*Sistemde ka� kay�tl� kullan�c� oldu�unu bulan metod.*/
int kullaniciSayisiBul() {
  /*sayi.txt'ye giderek ordaki veriyi al�p sistemde
  ka� kullan�c� kay�t oldu�unu bulabiliyoruz.
  E�er dosya null(bo� veya yok) ise 0 d�n�yor. Yani h�
  kullan�c� yok kabul ediyoruz.*/
  FILE * file = fopen("c:\\sayi.txt", "r");
  if (file == NULL) {
    return 0;
  }
  int i = 0;
  fscanf(file, "%d", & i);
  /*Metin sonuna kadar okuyacak bir while yaz�yoruz.*/
  while (!feof(file)) {
    printf("%d ", i);
    fscanf(file, "%d", & i);
  }
  fclose(file);
  return i;
}
/*Yeni kullan�c� kay�t oldu�unda sayi.txt'deki veriyi
1 art�r�yoruz.*/
int yeniKullaniciArtir() {
  int sayac = kullaniciSayisiBul();
  FILE * fOut = fopen("c:\\sayi.txt", "w+");
  /*++sayac yard�m�yla i�indeki veriyi 1 art�rd�k.*/
  fprintf(fOut, "%d", ++sayac);
  fclose(fOut);
}
/*Daha �nce kay�tl� olan kullan�c�lar� struct dizimize atan metod.*/
void veriyiDiziyeAktar() {
	/*sayaca sistemde ka� kullan�c� oldu�unu at�yoruz.*/
  int sayac = kullaniciSayisiBul();
  char * veri;
  /*D�ng�m�z sayac kadar yani kullan�c� say�s� kadar d�n�yor.*/
  for (int i = 0; i < sayac; i++) {
    char dosyaYolu[100];
    char * ilk_musteri_Numara_str;
    /*Verileri s�rayla okuyaca�� i�in:
	�rne�in ilk 20090000 okuyacak.
	Daha sonra 20090001 okuyacakt�r. (i + 1) burdan gelmektedir.*/
    sprintf(ilk_musteri_Numara_str, "%d", ilk_musteri_Numara + (i + 1));
    /*dosya yoluna m��teri numaras�n�da i�eren veriyi aktar�yoruz.*/
    strcpy(dosyaYolu, "c:\\");
    strcat(dosyaYolu, ilk_musteri_Numara_str);
    strcat(dosyaYolu, ".txt");
    /*1. sat�r m��teri numaras�n� tutuyor. satirdanVeriAl metoduna
	dosyaYolunu ve dosyan�n sat�r indexini g�nderip gelen veriyi
	integer'a �evirip atama yap�yoruz.*/
    veri = satirdanVeriAl(dosyaYolu, 1);
    musteriler[i].musteriHesapNO = atoi(veri);
    veri = satirdanVeriAl(dosyaYolu, 2);
    musteriler[i].sifre = atoi(veri);
    /*Ad gibi veriler string oldu�u i�in direkt olarak
	dizinin ilgili indexine atama yap�yoruz.*/
    strcpy(musteriler[i].ad, satirdanVeriAl(dosyaYolu, 3));
    strcpy(musteriler[i].soyad, satirdanVeriAl(dosyaYolu, 4));
    strcpy(musteriler[i].adres, satirdanVeriAl(dosyaYolu, 5));
    veri = satirdanVeriAl(dosyaYolu, 6);
    /*Bakiye float oldu�u i�in 6. sat�rdan gelen veriyi floata �evirip
	ilgili indexe atama yap�yoruz.*/
    musteriler[i].bakiye = atof(veri);
    veri = satirdanVeriAl(dosyaYolu, 7);
    musteriler[i].bloke = atoi(veri);
  }
}
/*satirdanVeriAl metodu yard�m�yla gelen veriyolundaki .txt dosyas�n�n
ilgili sat�r�n� okuyabiliyoruz.*/
char * satirdanVeriAl(char * veriYolu, int index) {
  int end, loop, line;
  char str[512];
  FILE * fd = fopen(veriYolu, "r");
  if (fd == NULL) {}
  for (end = loop = 0; loop < index; ++loop) {
    if (0 == fgets(str, sizeof(str), fd)) {
      break;
    }
  }
  /*Sat�rdan gelen veriyi
  M��teri Numaras�:20090000 oldu�unu d���nelim.*/
  char * p;
  /*strstr(str, ":") yard�m�yla :'ya g�re par�al�yoruz verinin son hali: :20090000*/
  p = strstr(str, ":");
  /*memmove(p, p + 1, strlen(p)) yard�m�yla ilk karakter olan :'y� siliyoruz.*/
  memmove(p, p + 1, strlen(p));
  /*Dosyay� kapat�yoruz.*/
  fclose(fd);
  /*En son verinin sonunda \n kald��� i�in onu temizlemek i�in strtok(p, "\n") kullan�yoruz.*/
  strtok(p, "\n");
  return p;
}
/*Gelen m��teri numaras�ndan bir m��teri varm� onu kontrol ediyoruz.*/
void mustNoKontrol(int id) {
	/*Gelen veri 404 ise b�yle bir kullan�c� yok ve hata mesaj� yaz�yoruz.*/
  clrscr();
  int mustNo = kullaniciBul(id);
  if (mustNo == 404) {
    printf("**BU NUMARAYA A�T B�R M��TER� NUMARASI BULUNMAMAKTADIR. DEVAM ETMEK ���N ENTER'A BASINIZ'**\n");
    getchar();
    adminGiris();
  } else {
    printf("%d - %s %s adl� kullan�c�y� d�zenliyorsunuz\n", musteriler[mustNo].musteriHesapNO, musteriler[mustNo].ad, musteriler[mustNo].soyad);
    kullaniciHesapDuzelt(mustNo);
  }
}
void HataliSecim() {
  printf("**HATALI SE��M YAPTINIZ. ANA EKRANA D�NMEK ���N ENTER'A BASINIZ.'**");
  getchar();
}
void musteriBulunamadiKontrol(int id) {
  id = kullaniciBul(id);
  if (id == 404) {
    printf("\n**BU NUMARAYA A�T B�R M��TER� BULUNAMADI. ANA EKRANA D�NMEK ���N ENTER'A BASINIZ.**\n");
    getch();
    adminGiris();
  }
}
/*Dizideki verileri verileriBelgeyeKaydet metodu yard�m�yla
kaydediyoruz.*/
void verileriBelgeyeKaydet(int hesapNo_int) {
  int id = kullaniciBul(hesapNo_int);
  char sifre_string[4];
  /*Kaydedece�imiz veriler farkl� tiplerde. Biz hepsini string'e
  �evirip tek seferde kaydetmek istiyoruz.*/
  /*�ifreyi stringe �eviriyoruz.*/
  sprintf(sifre_string, "%d", musteriler[id].sifre);
  char hesapNo[8];
  char bloke_str[10];
  char output[1024];
  /*Bakiyeyi stringe �eviriyoruz.*/
  snprintf(output, 1024, "%f", musteriler[id].bakiye);
  /*Hesap noyu stringe �eviriyoruz.*/
  sprintf(hesapNo, "%d", hesapNo_int);
  /*Bloke durumunu stringe �eviriyoruz.*/
  sprintf(bloke_str, "%d", musteriler[id].bloke);
  /*Dosya yolumuzu ekliyoruz.*/
  char dosyaYolu[100];
  strcpy(dosyaYolu, "c:\\");
  strcat(dosyaYolu, hesapNo);
  strcat(dosyaYolu, ".txt");
  char kayitBilgileri[200];
  /*�lgili verileri kayitBilgilerine ekliyoruz.*/
  strcpy(kayitBilgileri, "M��teri Hesap No   :");
  strcat(kayitBilgileri, hesapNo);
  strcat(kayitBilgileri, "\n�ifre              :");
  strcat(kayitBilgileri, sifre_string);
  strcat(kayitBilgileri, "\nAd�                :");
  strcat(kayitBilgileri, musteriler[id].ad);
  strcat(kayitBilgileri, "\nSoyad�             :");
  strcat(kayitBilgileri, musteriler[id].soyad);
  strcat(kayitBilgileri, "\nAdresi             :");
  strcat(kayitBilgileri, musteriler[id].adres);
  strcat(kayitBilgileri, "\nBakiye             :");
  strcat(kayitBilgileri, output);
  strcat(kayitBilgileri, "\nBloke              :");
  strcat(kayitBilgileri, bloke_str);
  /*Dosyay� a��yoruz ve ilgili dosyaYolundaki .txt dosyas�na
  Kullan�c�n�n ilgili verilerini ekliyoruz.*/
  int rc = 0;
  FILE * fOut = fopen(dosyaYolu, "w+");
  if (fOut != NULL) {
    if (fputs(kayitBilgileri, fOut) != EOF) {
      rc = 1;
    }
    fclose(fOut);
  }
}
