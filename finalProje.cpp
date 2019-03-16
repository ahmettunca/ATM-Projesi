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
//Admin þifresini global olarak tanýmladýk.
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
/*Müþterileri tutacaðýmýz bir struct tanýmladýk. Bu struct istenildiði gibi 100 kullanýcý barýndýrabilen bir struct.*/
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
   /*Program dilini Türkçe yapýyoruz.*/
  setlocale(LC_ALL, "Turkish");
  /*Global index deðiþkenine sayi.txt'den aldýðýmýz kullanýcý sayýsýný atýyoruz. Bundan sonra atayacaðýmýz elemanlarý dizinin
  kaçýncý sýrasýna atacaðýmýzý bu sayede bilebiliyoruz.*/
  index = kullaniciSayisiBul();
  /*Daha önceki verileri diziye aktarýyoruz.*/
  veriyiDiziyeAktar();
  kullaniciSec();
}
void adminSifreGiris() {
  clrscr();
  char adminSifre[6];
  /*Admin þifresini doðru girene kadar sormaya devam edecek bir döngü
  tanýmladýk.*/
  while (true) {
    printf("Þifreyi giriniz: ");
    scanf("%s", & adminSifre);
    if (strcmp(adminPassword, adminSifre) == 0)
      break;
    else
      printf("\n**ÞÝFRE YANLIÞ TEKRAR GÝRÝNÝZ!**\n");
  }
  adminGiris();
}
void adminGiris() {
  clrscr();
  int secim, id, hesapNo;
  printf("*** Admin ***\n[1]Kullanýcý Hesap Oluþtur\n[2]Kullanýcý Hesap Düzelt\n[3]Para Çekme\n[4]Para Yatýrma\n[5]ÇIKIÞ\nSeçiminiz:");
  scanf("%d", & secim);
  /*Kullanýcýnýn seçtiði iþleme göre switch-case yardýmýyla yönlendiriyoruz.*/
  switch (secim) {
  case 1:
    kullaniciHesapOlustur();
    break;
  case 2:
    int secim2, mustNo;
    printf("\nDüzenlemek istediðiniz müþteri numarasý: \n");
    scanf("%d", & mustNo);
    /*mustNoKontrol yardýmýyla girilen müþteri numarasý sistemde kayýtlý mý deðil mi öðrenebiliyoruz.*/
    mustNoKontrol(mustNo);
    break;
  case 3:
    printf("\nPara Çekmek Ýstediðiniz Hesap Numarasýný Giriniz: ");
    scanf("%d", & hesapNo);
    id = kullaniciBul(hesapNo);
    /*hesapNo'yu kullanýcýBul fonksiyonuna göndererek böyle bir kullanýcý var mý anlayabiliyoruz.
	Eðer 404 geldiyse böyle bir kullanýcý bulunmuyordur.*/
    if(id==404)
    {
    	printf("\n**BU NUMARAYA AÝT BÝR KULLANICI BULUNMAMAKTADIR. ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ**\n");
    	getch();
		adminGiris(); 	
    }
    /*Para çek metoduna kullanýcý id'sini ver tip = 1 gönderiyoruz. 1 admin olduðumuzu belli ediyor.*/
    paraCek(id, 1);
    break;
  case 4:
    printf("Para Yatýrmak Ýstediðiniz Hesap Numarasýný Giriniz: ");
    scanf("%d", & hesapNo);
    if(id==404)
    {
    	printf("\n**BU NUMARAYA AÝT BÝR KULLANICI BULUNMAMAKTADIR. ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ**\n");
    	getch();
		adminGiris(); 	
    }    id = kullaniciBul(hesapNo);
    paraYatir(id, 1);
    break;
  case 5:
    kullaniciSec();
    break;
    /*Eðer yazýlan seçimler dýþýnda bir seçim yapýldýysa tekrar soruyor.*/
  default:
    printf("\n**YANLIÞ SEÇÝM YAPTINIZ. TEKRAR SEÇÝNÝZ! DEVAM ETMEK ÝÇÝN ENTER'A BASINIZ.**\n");
    getch();
    adminGiris();
    break;
  }
}
/*Bu metod yardýmýyla ekranda þimdiye kadar yazýlan yazýlarý temizleyebiliyoruz.*/
void clrscr() {
  system("@cls||clear");
}
void kullaniciSec() {
  clrscr();
  int secim;
  printf("LÜTFEN KULLANICI TÝPÝNÝ BELÝRLEYÝNÝZ:\n[1]BANKACI\n[2]MÜÞTERÝ\nSeçiminiz: ");
  scanf("%d", & secim);
  if (secim == 1) {
    adminSifreGiris();
  } else if(secim == 2){
    clrscr();
    int hesapNo, sifre, id = 404, hak = 3;
    while (true) {
      printf("Müþteri numarasýný giriniz: ");
      scanf("%d", & hesapNo);
      /*Girilen müþteri numarasý var mý yok mu kontrol ediyoruz.*/
      id = kullaniciBul(hesapNo);
      if (id == 404) {
        printf("**BU MÜÞTERÝ NUMARASINA AÝT BÝR MÜÞTERÝ YOK!**\n");
      } else
        break;
    }
    while (true) {
      printf("Þifrenizi giriniz: ");
      scanf("%d", & sifre);
      /*Þifre ve hesapNo eþleþiyorsa  giriþ yapabiliyor*/
      if (hesapNo == musteriler[id].musteriHesapNO && sifre == musteriler[id].sifre)
        break;
        /*Her yanlýþ girdiðinde 3 hakkýndan 1 hak eksiliyor. 3 yanlýþta ise bloke oluyor.*/
      else
        printf("Þifre yanlýþ girildi!\n\n%d\n\nHakkýnýz Kaldý!\n", --hak);
      if (hak == 0) {
        printf("%d NOLU MÜÞTERÝ HESABINIZ BLOKE OLMUÞTUR.\n\nLÜTFEN BANKANIZ ÝLE ÝLETÝÞÝME GEÇÝNÝZ!\n", musteriler[id].musteriHesapNO);
        musteriler[id].bloke = 1;
        /*verileriBelgeyeKaydet metodu yardýmýyla bloke durumunu .txt'ye kaydediyoruz.*/
        verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
        break;
      }
    }
    if (musteriler[id].bloke == 1) {
      printf("\n**HESABINIZ BLOKE OLMUÞTUR. BANKA ÝLE ÝLETÝÞÝME GEÇÝNÝZ.\nANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ...**\n");
      getch();
      kullaniciSec();
      clrscr();
    } else {
    	/*Eðer adýmlar baþarýyla geçildiyse ana ekrana girebiliyor.*/
      printf("HOÞGELDÝN %s %s!", musteriler[id].ad, musteriler[id].soyad);
      islemleriGoster(kullaniciBul(hesapNo));
    }
  }
  else{
  	kullaniciSec();
  }
}
/*kullaniciBul metodu yardýmýyla girilen hesap numarasýnýn dizideki index'ini bulabiliyoruz.
Eðer kullanýcý yoksa 404 dönüyor.*/
int kullaniciBul(int hesapNO) {
  int id = 404;
  for (int i = 0; i < kullaniciSayisi; i++) {
    if (musteriler[i].musteriHesapNO == hesapNO) {
      id = i;
    }
  }
  return id;
}
/*Tüm kullanýcý iþlemlerinin gösterildiði metod.
Burda paraYatir, paraCek gibi metodlarda 2 deðerini 
göndermemizin sebebi kullanýcý olduðumuzu belli etmek amacýyla.
Bu sayede admin ve kullanýcý ayný para çekme metodunu kullanabiliyor.
Ýþlem bitince geri dönüþlerde eðer 1 ise admin ekranýna, eðer 2 ise
kullanýcý ekranýna dönüyor.*/
void islemleriGoster(int id) {
  clrscr();
  int secim;
  printf("[1]PARA YATIRMA\t[4]FATURA ÖDEME\n[2]PARA ÇEKME\t[5]BAKÝYE GÖRÜNTÜLEME\n[3]HAVALE\nSeçiminiz: ");
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
    printf("\n**YANLIÞ SEÇÝM YAPTINIZ TEKRAR SEÇÝNÝZ.**\n");
    islemleriGoster(id);
    break;
  }
}
void paraYatir(int id, int tip) {
  /*Ekranda yazan yazýlar temizleniyor.*/
  clrscr();
  float miktar;
  printf("%s %s Adýna Yatýrýlacak Miktarý giriniz: ", musteriler[id].ad, musteriler[id].soyad);
  scanf("%f", & miktar);
  /*Para yatýrýlan kullanýya para yatýrýyor ve yatýrýlan para kadar yatýran kullanýcadan
  para eksiltiyor.*/
  musteriler[id].bakiye = musteriler[id].bakiye + miktar;
  /*Veriler belgeye kaydediliyor.*/
  verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
  /*Ýþlem bitince iþlemTamam ekranýna giriyor ve beraberinde tip deðerinide gönderiyor.
  Tip deðeri bu ekrana admin hesabýndan veya kullanýcý hesabýndan gelmesine göre deðiþiklik gösterir.*/
  islemTamam(id, tip);
}
void paraCek(int id, int tip) {
  clrscr();
  float miktar;
  printf("Miktarý giriniz: ");
  scanf("%f", & miktar);
  /*Yeterli miktarda bakiye var mý kontrol ediliyor. Eðer yoksa aþaðýdaki iþlemler
  gerçekleþtirilmiyor.*/
  bakiyeCheck(id, miktar, tip);
  /*Kullanýcýdan çekilen miktar eksiltiliyor.*/
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
  printf("Havale Yapýlacak Kullanýcý Hesap Numarasý Giriniz:  ");
  scanf("%d", & hesapNo);
  printf("Açýklama Giriniz:  ");
  getc(stdin);
  gets(aciklama);
  printf("Havale Miktarýný Giriniz:  ");
  scanf("%f", & miktar);
  /*Bakiye kontrol edilir. Eðer yetersizse aþaðýda adýmlar gerçekleþtirilmez.*/
  bakiyeCheck(id, miktar, 2);
  printf("%d Nolu Kullanýcýya %f TL Gönderilecek Onaylýyor Musunuz? \n[1]EVET\n[2]HAYIR\nSeçiminiz: ", hesapNo, miktar);
  scanf("%d", &secim);
  /*Eðer kullanýcý onaylýyor ise*/
  if (secim == 1) {
    /*1. kullanýcýdan miktar düþülecek ve 2. kullanýcýya miktar eklenecek.
	Daha sonrasýnda iki kullanýcýda ayrý ayrý .txt dosyalarýna tekrar kayýt
	olacaklardýr.*/
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
  /*Kullanýcýdan seçim yapmasý istenir ve seçim pointer char'a atanýr.*/
  printf("\n[1]Elektrik\n[2]Su\n[3]A.D.S.L. Ýnternet\n[4]Geri\nSeçiminiz:");
  scanf("%d", & secim);
  if (secim == 1) {
    firmaAdi = "Elektrik";
  } else if (secim == 2) {
    firmaAdi = "Su";
  } else if (secim == 3) {
    firmaAdi = "A.D.S.L. Ýnternet";
  } else if (secim == 4) {
    islemleriGoster(id);
  } else {
  	/*Yanlýþ bir seçim yapýldýysa iþlem baþtan yapýlýr.*/
    printf("\n**YANLIÞ SEÇÝM YAPTINIZ TEKRAR SEÇÝNÝZ!**\n");
    faturaOde(id);
  }
  printf("Ödeme Miktarýný Giriniz: ");
  scanf("%f", & miktar);
  bakiyeCheck(id, miktar, 2);
  /*Ödemenin bir özeti yazýlýr.*/
  printf("%s Faturasý Olarak Hesabýnýzdan %.2f. Ödeme Yapýlacaktýr.\nOnaylýyor musunuz?\n[1]EVET\n[2]HAYIR\nSeçiminiz:", firmaAdi, miktar);
  scanf("%d", & secim);
  if (secim == 1) {
  	/*Miktar hesaptan düþülür ve .txt dosyasýna kayýt edilir.*/
    musteriler[id].bakiye -= miktar;
    verileriBelgeyeKaydet(musteriler[id].musteriHesapNO);
    islemTamam(id, 2);
  } else {
    faturaOde(id);
  }
}
/*Kullanýcý bakiyesini bu metod yardýmýyla görüntüleyebilir.*/
void bakiyeGoruntule(int id) {
  /*Not defterindeki veriler çalýþma anýnda yönetici tarafýndan
   elle bir deðiþiklik  yapýlma ihtimaline karþý tekrar diziye aktarýlýr.*/
  veriyiDiziyeAktar();
  clrscr();
  printf("Bakiyeniz:%.2fTL", musteriler[id].bakiye);
  islemTamam(id, 2);
}
/*Eðer iþlem tamamsa ve gelen tip 1 ise admin ekranýna geri dönülür.
Eðer 2 ise giriþ yapýlan kullanýcýnýn ekranýna tekrar id gönderilerek
geri döner.*/
void islemTamam(int id, int tip) {
  int secim;
  /*Tip 1 ise iþlemi yapan admindir ve admin ekranýna döner.*/
  if (tip == 1) {
    printf("\n**ISLEMINIZ TAMAMLANDI!**\n[1]ANA MENU\n[2]ÇIKIÞ\nSeçiminiz: ");
    scanf("%d", & secim);
    switch (secim) {
    case 1:
      adminGiris();
      break;
    case 2:
      kullaniciSec();
      /*Seçim yanlýþ ise metod baþýna tekrar döner.*/
    default:
      printf("\n**YANLIÞ SEÇÝM YAPTINIZ TEKRAR SEÇÝNÝZ.**\n");
      islemTamam(id, tip);
      break;
    }
  }
  /*Tip 2 ise kullanýcý ekranýna döner.*/
  if (tip == 2) {
    printf("\n**ISLEMINIZ TAMAMLANDI!**\n[1]ANA MENU\n[2]BAKÝYE GÖRÜNTÜLEME\n[3]ÇIKIÞ\nSeçiminiz: ");
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
      printf("\n**YANLIÞ SEÇÝM YAPTINIZ TEKRAR SEÇÝNÝZ.**\n");
      islemTamam(id, tip);
      break;
    }
  }
}
/*Bu metod yardýmýyla kullanýcý hesabý oluþturulabilir.*/
void kullaniciHesapOlustur() {
  clrscr();
  char temp[1], sifre, basamak, sayac, sifre_yedek;
  int hesapNo_int;
  /*Kullanýcý sayýsý bul metodu sayi.txt'den kaç kullanýcý olduðunu
  alýr ve ilk kullanýcýya o kadar sayý ekler. Böylelikle yeni
  eklenecek kullanýnýn müþteri numarasý otomatik olarak atanacaktýr.*/
  hesapNo_int = 20090000+kullaniciSayisiBul();
  printf("Müþteri Hizmet No: %d\n", hesapNo_int);
  musteriler[index].musteriHesapNO = hesapNo_int;
  printf("4 haneli Þifre: ");
  scanf("%d", & musteriler[index].sifre);
  printf("Adý:");
  /*Kullanýcýnýn girdiði ad verisini gets yardýmýyla alarak
  boþluklarla beraber alýyoruz(Kullanýcý 2 isimli olabilir.)*/
  getc(stdin);
  gets(musteriler[index].ad);
  printf("Soyadý:");
  gets(musteriler[index].soyad);
  printf("Adresi:");
  gets(musteriler[index].adres);
  /*Giriþ bittikten sorna verileri .txt dosyasýna kaydediyoruz.*/
  verileriBelgeyeKaydet(hesapNo_int);
  /*Bu metod yardýmýyla sayi.txt'deki sayacý 1 artýrýyoruz ve böylece
  sistemde kayýtlý kullanýcý sayýsýný güncellemiþ oluyoruz.*/
  yeniKullaniciArtir();
  /*index ise sýradaki kullanýnýn dizideki hangi indexe kayýt olacaðýný belirler.*/
  ++index;
  int secim;
  printf("\n**KULLANICI BAÞARIYLA OLUÞTURULDU!**\n\n[1]ADMIN ANA EKRAN\n[2]YENÝ KULLANICI OLUÞTUR\n[3]ÇIKIÞ\nSeçiminiz: ");
  /*Kullanýcýnýn seçimine göre yanlýþ bir seçim girilmediði takdirde sonsuz döngüden çýkacak ve
  kullanýcýnýn iþlemini gerçekleþtirecektir.*/
  while (true) {
    scanf("%d", & secim);
    if (secim == 1 || secim == 2 || secim == 3) {
      break;
    } else {
      printf("YANLIÞ SEÇÝM. TEKRAR SEÇÝNÝZ.\n");
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
/*Bu metod yardýmýyla kullanýcý hesaplarý düzeltilebilecektir.*/
void kullaniciHesapDuzelt(int secim) {
  int secim2;
  /*Ýlk baþta kullanýcý hesabý bloke mi deðil mi kontro ledilir ve uyarý verilir. Eðer
  bloke olmuþ ise admin .txt dosyasýndan bloke durumunu 1'den 0'a getirebilir.*/
  if (musteriler[secim].bloke == 1) {
    printf("**HESAP BLOKE OLMUÞ. Yönetici C:\\'den açabilir.");
  }
  /*Kullanýcý bilgilerinin bir özeti yazýlýr.*/
  printf("Müþteri Numarasý: %d\nÞifre: %d\nAd: %s\nSoyad: %s\nAdres:%s\n",musteriler[secim].musteriHesapNO,musteriler[secim].sifre,musteriler[secim].ad,musteriler[secim].soyad,musteriler[secim].adres);
  printf("\nÞifre:");
  scanf("%d", & musteriler[secim].sifre);
  printf("Ad:");
  getc(stdin);
  gets(musteriler[secim].ad);
  printf("Soyad:");
  gets(musteriler[secim].soyad);
  printf("Adres:");
  gets(musteriler[secim].adres);
  /*Düzenlenmiþ veriler tekrar .txt dosyasýna yazýlýr.*/
  verileriBelgeyeKaydet(musteriler[secim].musteriHesapNO);
  printf("\n**KULLANICI BAÞARIYLA DÜZENLENDÝ. ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ.**\n");
  getch();
  adminGiris();
}
/*Eðer girilen miktar hesaptaki bakiyeden yüksekse bakiye
yetersiz uyarýsý verecektir.*/
void bakiyeCheck(int id, float miktar, int tip) {
  if (miktar > musteriler[id].bakiye) {
    printf("\nYETERSÝZ BAKÝYE! ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ\n");
    getch();
    /*Tip 1 ise admin ekranýna geri dönecektir..*/
    if (tip == 1) {
      adminGiris();
    }
    /*Tip 2 ise kullanýcý ekranýna geri dönecektir.*/
    if (tip == 2) {
      islemleriGoster(id);
    }
  }
}
/*Sistemde kaç kayýtlý kullanýcý olduðunu bulan metod.*/
int kullaniciSayisiBul() {
  /*sayi.txt'ye giderek ordaki veriyi alýp sistemde
  kaç kullanýcý kayýt olduðunu bulabiliyoruz.
  Eðer dosya null(boþ veya yok) ise 0 dönüyor. Yani hç
  kullanýcý yok kabul ediyoruz.*/
  FILE * file = fopen("c:\\sayi.txt", "r");
  if (file == NULL) {
    return 0;
  }
  int i = 0;
  fscanf(file, "%d", & i);
  /*Metin sonuna kadar okuyacak bir while yazýyoruz.*/
  while (!feof(file)) {
    printf("%d ", i);
    fscanf(file, "%d", & i);
  }
  fclose(file);
  return i;
}
/*Yeni kullanýcý kayýt olduðunda sayi.txt'deki veriyi
1 artýrýyoruz.*/
int yeniKullaniciArtir() {
  int sayac = kullaniciSayisiBul();
  FILE * fOut = fopen("c:\\sayi.txt", "w+");
  /*++sayac yardýmýyla içindeki veriyi 1 artýrdýk.*/
  fprintf(fOut, "%d", ++sayac);
  fclose(fOut);
}
/*Daha önce kayýtlý olan kullanýcýlarý struct dizimize atan metod.*/
void veriyiDiziyeAktar() {
	/*sayaca sistemde kaç kullanýcý olduðunu atýyoruz.*/
  int sayac = kullaniciSayisiBul();
  char * veri;
  /*Döngümüz sayac kadar yani kullanýcý sayýsý kadar dönüyor.*/
  for (int i = 0; i < sayac; i++) {
    char dosyaYolu[100];
    char * ilk_musteri_Numara_str;
    /*Verileri sýrayla okuyacaðý için:
	Örneðin ilk 20090000 okuyacak.
	Daha sonra 20090001 okuyacaktýr. (i + 1) burdan gelmektedir.*/
    sprintf(ilk_musteri_Numara_str, "%d", ilk_musteri_Numara + (i + 1));
    /*dosya yoluna müþteri numarasýnýda içeren veriyi aktarýyoruz.*/
    strcpy(dosyaYolu, "c:\\");
    strcat(dosyaYolu, ilk_musteri_Numara_str);
    strcat(dosyaYolu, ".txt");
    /*1. satýr müþteri numarasýný tutuyor. satirdanVeriAl metoduna
	dosyaYolunu ve dosyanýn satýr indexini gönderip gelen veriyi
	integer'a çevirip atama yapýyoruz.*/
    veri = satirdanVeriAl(dosyaYolu, 1);
    musteriler[i].musteriHesapNO = atoi(veri);
    veri = satirdanVeriAl(dosyaYolu, 2);
    musteriler[i].sifre = atoi(veri);
    /*Ad gibi veriler string olduðu için direkt olarak
	dizinin ilgili indexine atama yapýyoruz.*/
    strcpy(musteriler[i].ad, satirdanVeriAl(dosyaYolu, 3));
    strcpy(musteriler[i].soyad, satirdanVeriAl(dosyaYolu, 4));
    strcpy(musteriler[i].adres, satirdanVeriAl(dosyaYolu, 5));
    veri = satirdanVeriAl(dosyaYolu, 6);
    /*Bakiye float olduðu için 6. satýrdan gelen veriyi floata çevirip
	ilgili indexe atama yapýyoruz.*/
    musteriler[i].bakiye = atof(veri);
    veri = satirdanVeriAl(dosyaYolu, 7);
    musteriler[i].bloke = atoi(veri);
  }
}
/*satirdanVeriAl metodu yardýmýyla gelen veriyolundaki .txt dosyasýnýn
ilgili satýrýný okuyabiliyoruz.*/
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
  /*Satýrdan gelen veriyi
  Müþteri Numarasý:20090000 olduðunu düþünelim.*/
  char * p;
  /*strstr(str, ":") yardýmýyla :'ya göre parçalýyoruz verinin son hali: :20090000*/
  p = strstr(str, ":");
  /*memmove(p, p + 1, strlen(p)) yardýmýyla ilk karakter olan :'yý siliyoruz.*/
  memmove(p, p + 1, strlen(p));
  /*Dosyayý kapatýyoruz.*/
  fclose(fd);
  /*En son verinin sonunda \n kaldýðý için onu temizlemek için strtok(p, "\n") kullanýyoruz.*/
  strtok(p, "\n");
  return p;
}
/*Gelen müþteri numarasýndan bir müþteri varmý onu kontrol ediyoruz.*/
void mustNoKontrol(int id) {
	/*Gelen veri 404 ise böyle bir kullanýcý yok ve hata mesajý yazýyoruz.*/
  clrscr();
  int mustNo = kullaniciBul(id);
  if (mustNo == 404) {
    printf("**BU NUMARAYA AÝT BÝR MÜÞTERÝ NUMARASI BULUNMAMAKTADIR. DEVAM ETMEK ÝÇÝN ENTER'A BASINIZ'**\n");
    getchar();
    adminGiris();
  } else {
    printf("%d - %s %s adlý kullanýcýyý düzenliyorsunuz\n", musteriler[mustNo].musteriHesapNO, musteriler[mustNo].ad, musteriler[mustNo].soyad);
    kullaniciHesapDuzelt(mustNo);
  }
}
void HataliSecim() {
  printf("**HATALI SEÇÝM YAPTINIZ. ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ.'**");
  getchar();
}
void musteriBulunamadiKontrol(int id) {
  id = kullaniciBul(id);
  if (id == 404) {
    printf("\n**BU NUMARAYA AÝT BÝR MÜÞTERÝ BULUNAMADI. ANA EKRANA DÖNMEK ÝÇÝN ENTER'A BASINIZ.**\n");
    getch();
    adminGiris();
  }
}
/*Dizideki verileri verileriBelgeyeKaydet metodu yardýmýyla
kaydediyoruz.*/
void verileriBelgeyeKaydet(int hesapNo_int) {
  int id = kullaniciBul(hesapNo_int);
  char sifre_string[4];
  /*Kaydedeceðimiz veriler farklý tiplerde. Biz hepsini string'e
  çevirip tek seferde kaydetmek istiyoruz.*/
  /*Þifreyi stringe çeviriyoruz.*/
  sprintf(sifre_string, "%d", musteriler[id].sifre);
  char hesapNo[8];
  char bloke_str[10];
  char output[1024];
  /*Bakiyeyi stringe çeviriyoruz.*/
  snprintf(output, 1024, "%f", musteriler[id].bakiye);
  /*Hesap noyu stringe çeviriyoruz.*/
  sprintf(hesapNo, "%d", hesapNo_int);
  /*Bloke durumunu stringe çeviriyoruz.*/
  sprintf(bloke_str, "%d", musteriler[id].bloke);
  /*Dosya yolumuzu ekliyoruz.*/
  char dosyaYolu[100];
  strcpy(dosyaYolu, "c:\\");
  strcat(dosyaYolu, hesapNo);
  strcat(dosyaYolu, ".txt");
  char kayitBilgileri[200];
  /*Ýlgili verileri kayitBilgilerine ekliyoruz.*/
  strcpy(kayitBilgileri, "Müþteri Hesap No   :");
  strcat(kayitBilgileri, hesapNo);
  strcat(kayitBilgileri, "\nÞifre              :");
  strcat(kayitBilgileri, sifre_string);
  strcat(kayitBilgileri, "\nAdý                :");
  strcat(kayitBilgileri, musteriler[id].ad);
  strcat(kayitBilgileri, "\nSoyadý             :");
  strcat(kayitBilgileri, musteriler[id].soyad);
  strcat(kayitBilgileri, "\nAdresi             :");
  strcat(kayitBilgileri, musteriler[id].adres);
  strcat(kayitBilgileri, "\nBakiye             :");
  strcat(kayitBilgileri, output);
  strcat(kayitBilgileri, "\nBloke              :");
  strcat(kayitBilgileri, bloke_str);
  /*Dosyayý açýyoruz ve ilgili dosyaYolundaki .txt dosyasýna
  Kullanýcýnýn ilgili verilerini ekliyoruz.*/
  int rc = 0;
  FILE * fOut = fopen(dosyaYolu, "w+");
  if (fOut != NULL) {
    if (fputs(kayitBilgileri, fOut) != EOF) {
      rc = 1;
    }
    fclose(fOut);
  }
}
