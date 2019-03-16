#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <wincon.h>
int musteriSayisi,aktifNum;
char adminSifre[9]="12q34w56e";
char dosyaYolu[80]="C:\\ATMProject\\",dosyaDevam[50],yolTemp[80]="C:\\ATMProject\\",anaYol[80]="C:\\ATMProject\\";
struct kayit{
	long numara;
	int sifre;
	char ad[20],soyAd[20],adres[50];
	int aktif;
	float bakiye;
	int bloke;
}musteri[100];
void adminMenu(){
	system("CLS");
	int secim;
	printf("Yonetici Olarak Giris Yapildi\n");
	printf("[1]Kullanici Hesabi Olusturma\n[2]Kullanici Hesabi Degistirme\n[3]Para Cekme\n[4]Para Yatirma\n[5]Cikis		");
	do{
	scanf("%d",&secim);
	if(secim==1){
		hesapOlustur();
	}
	else if(secim==2){
		hesapDegistir();
	}
	else if(secim==3){
		adminCekme();
	}
	else if(secim==4){
		adminYatirma();
	}
	else if(secim==5){
		ilkEkran();
	}
	else{
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}
	}while(secim!=1&&secim!=2&&secim!=3&&secim!=4&&secim!=5);
}
void hesapOlustur(){
	system("CLS");
	int onayIptal;
	char ad[20],soyad[20],adres[50];
	int sifre;
	printf("Musteri Numarasi: %ld\n",musteri[musteriSayisi].numara);
	printf("Musteri Adi: ");
	scanf("%s",&ad);
	printf("Musteri Soyadi: ");
	scanf("%s",&soyad);
	printf("Musteri Adresi: ");
	scanf("%s",&adres);
	printf("Musteri Sifresi: ");
	scanf("%d",&sifre);
	printf("[1]Onayla\n[2]Iptal		");
	do{
	scanf("%d",&onayIptal);
	if(onayIptal==1){
		strcpy(dosyaYolu,anaYol);
		strcpy(musteri[musteriSayisi].ad,ad);
		strcpy(musteri[musteriSayisi].soyAd,soyad);
		strcpy(musteri[musteriSayisi].adres,adres);
		musteri[musteriSayisi].sifre=sifre;
		musteri[musteriSayisi].aktif=1;
		musteri[musteriSayisi].bakiye=0;
		musteri[musteriSayisi].bloke=0;
		sprintf(dosyaDevam,"%ld",musteri[musteriSayisi].numara);
		strcat(dosyaYolu,dosyaDevam);
		strcpy(yolTemp,dosyaYolu);
		CreateDirectory(dosyaYolu,NULL);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\ad.txt");
		FILE *yaz1=fopen(dosyaYolu,"w+");
		fprintf(yaz1,"%s",ad);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\soyad.txt");
		FILE *yaz2=fopen(dosyaYolu,"w+");
		fprintf(yaz2,"%s",soyad);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\adres.txt");
		FILE *yaz3=fopen(dosyaYolu,"w+");
		fprintf(yaz3,"%s",adres);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\bloke.txt");
		FILE *yaz4=fopen(dosyaYolu,"w+");
		fprintf(yaz4,"%d",musteri[musteriSayisi].bloke);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\sifre.txt");
		FILE *yaz5=fopen(dosyaYolu,"w+");
		fprintf(yaz5,"%d",sifre);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\bakiye.txt");
		FILE *yaz6=fopen(dosyaYolu,"w+");
		fprintf(yaz6,"%f",musteri[musteriSayisi].bakiye);
		fclose(yaz1);
		fclose(yaz2);
		fclose(yaz3);
		fclose(yaz4);
		fclose(yaz5);
		fclose(yaz6);
		musteriSayisi++;
		FILE *sayi=fopen("C:\\ATMProject\\musterisayisi.txt","w+");
		fprintf(sayi,"%d",musteriSayisi);
		fclose(sayi);
		printf("Kullanici Olusturuldu. Menuye Donmek Icin Bir Tusa Basin...");
	}
	else if(onayIptal==2){
		printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");
	}
	else
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}while(onayIptal!=1&&onayIptal!=2);
	getch();
	system("CLS");
	adminMenu();
}
void hesapDegistir(){
	system("CLS");
	long girisNo;
	int musteriNo,onayIptal,sifre;
	char ad[20],soyad[20],adres[50];
	printf("Degistirmek Istediginiz Musterinin Numarasini Girin: ");
	do{
	scanf("%ld",&girisNo);
	if(girisNo<20090000||girisNo>20090099){
		printf("Hatali Giris Yaptiniz! Lutfen Tekrar Giris Yapin: ");
	}
	else{
		musteriNo=girisNo-20090000;
		if(musteri[musteriNo].aktif==1){
			printf("Musteri Ad-Soyadi: %s %s\n",musteri[musteriNo].ad,musteri[musteriNo].soyAd);
			printf("Musteri Adresi: %s\n",musteri[musteriNo].adres);
			printf("Yeni Bilgileri Girin\nMusteri Adi: ");
			scanf("%s",&ad);
			printf("Musteri Soyadi: ");
			scanf("%s",&soyad);
			printf("Musteri Adresi: ");
			scanf("%s",&adres);
			printf("Musteri Sifresi: ");
			scanf("%d",&sifre);
			printf("[1]Onayla\n[2]Iptal		");
			do{
			scanf("%d",&onayIptal);
			if(onayIptal==1){
				strcpy(dosyaYolu,anaYol);
				strcpy(musteri[musteriNo].ad,ad);
				strcpy(musteri[musteriNo].soyAd,soyad);
				strcpy(musteri[musteriNo].adres,adres);
				musteri[musteriNo].sifre=sifre;
				sprintf(dosyaDevam,"%ld",musteri[musteriNo].numara);
				strcat(dosyaYolu,dosyaDevam);
				printf("%s",dosyaYolu);
				strcpy(yolTemp,dosyaYolu);
				strcpy(dosyaYolu,yolTemp);
				strcat(dosyaYolu,"\\ad.txt");
				FILE *yaz1=fopen(dosyaYolu,"r+");
				fprintf(yaz1,"%s",musteri[musteriSayisi].ad);
				strcpy(dosyaYolu,yolTemp);
				strcat(dosyaYolu,"\\soyad.txt");
				FILE *yaz2=fopen(dosyaYolu,"r+");
				fprintf(yaz2,"%s",musteri[musteriSayisi].soyAd);
				strcpy(dosyaYolu,yolTemp);
				strcat(dosyaYolu,"\\adres.txt");
				FILE *yaz3=fopen(dosyaYolu,"r+");
				fprintf(yaz3,"%s",musteri[musteriSayisi].adres);
				strcpy(dosyaYolu,yolTemp);
				strcat(dosyaYolu,"\\sifre.txt");
				FILE *yaz4=fopen(dosyaYolu,"r+");
				fprintf(yaz4,"%d",musteri[musteriSayisi].sifre);
				strcpy(dosyaYolu,yolTemp);
				fclose(yaz1);
				fclose(yaz2);
				fclose(yaz3);
				fclose(yaz4);
				printf("Kullanici Bilgileri Degistirildi. Menuye Donmek Icin Bir Tusa Basin...");
			}
			else if(onayIptal==2){			
				printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
			}
			else
				printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
			}while(onayIptal!=1&&onayIptal!=2);
		}
		else
			printf("Musteri Bulunamadi! Menuye Donmek Icin Bir Tusa Basin...");
	}
	}while(girisNo<20090000||girisNo>20090099);
	getch();
	system("CLS");
	adminMenu();
}
void adminCekme(){
	system("CLS");
	long girisNo;
	int musteriNo,onayIptal;
	float cekmePara;
	printf("Para Cekmek Istediginiz Musterinin Numarasini Girin: ");
	do{
	do{
	scanf("%ld",&girisNo);
	musteriNo=girisNo-20090000;
	if(girisNo<20090000||girisNo>20090099){
		printf("Hatali Giris Yaptiniz! Lutfen Tekrar Giris Yapin: ");
	}
	else{
		if(musteri[musteriNo].aktif==1){
			printf("Musteri Numarasi: %ld\nMusteri Ad-Soyadi: %s %s\nMevcut Bakiye: %.2f\n",musteri[musteriNo].numara,musteri[musteriNo].ad,musteri[musteriNo].soyAd,musteri[musteriNo].bakiye);
			printf("Cekmek Istediginiz Para Miktarini Girin: ");
			scanf("%f",&cekmePara);
			if(cekmePara<0)
				cekmePara=cekmePara*(-1);
			printf("%ld Numarali Hesaptan %.2f TL Para Cekilecektir. Onayliyor Musunuz?\n",musteri[musteriNo].numara,cekmePara);
			printf("[1]Onayla\n[2]Iptal		");
			do{
			scanf("%d",&onayIptal);
			if(onayIptal==1){
				if(musteri[musteriNo].bakiye<cekmePara)
					printf("Yetersiz Bakiye! Menuye Donmek Icin Bir Tusa Basin...");
				else{
					musteri[musteriNo].bakiye=musteri[musteriNo].bakiye-cekmePara;
					strcpy(dosyaYolu,anaYol);
					sprintf(dosyaDevam,"%ld",musteri[musteriNo].numara);
					strcat(dosyaYolu,dosyaDevam);
					strcat(dosyaYolu,"\\bakiye.txt");
					FILE *yaz=fopen(dosyaYolu,"r+");
					fprintf(yaz,"%f",musteri[musteriNo].bakiye);
					fclose(yaz);
					printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[musteriNo].bakiye);
				}
			}
			else if(onayIptal==2){			
				printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
			}
			else
				printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
			}while(onayIptal!=1&&onayIptal!=2);	
		}
		else
			printf("Musteri Bulunamadi! Lutfen Tekrar Giris Yapin: ");
	}
	}while(girisNo<20090000||girisNo>20090099);
	}while(musteri[musteriNo].aktif!=1);
	getch();
	adminMenu();
}
void adminYatirma(){
	system("CLS");
	long girisNo;
	int musteriNo,onayIptal;
	float yatirmaPara;
	printf("Para Yatirmak Istediginiz Musterinin Numarasini Girin: ");
	do{
	do{
	scanf("%ld",&girisNo);
	musteriNo=girisNo-20090000;
	if(girisNo<20090000||girisNo>20090099){
		printf("Hatali Giris Yaptiniz! Lutfen Tekrar Giris Yapin: ");
	}
	else{
		if(musteri[musteriNo].aktif==1){
			printf("Musteri Numarasi: %ld\nMusteri Ad-Soyadi: %s %s\nMevcut Bakiye: %.2f\n",musteri[musteriNo].numara,musteri[musteriNo].ad,musteri[musteriNo].soyAd,musteri[musteriNo].bakiye);
			printf("Yatirmak Istediginiz Para Miktarini Girin: ");
			scanf("%f",&yatirmaPara);
			if(yatirmaPara<0)
				yatirmaPara=yatirmaPara*(-1);
			printf("%ld Numarali Hesaba %.2f TL Para Yatirilacaktir. Onayliyor Musunuz?\n",musteri[musteriNo].numara,yatirmaPara);
			printf("[1]Onayla\n[2]Iptal		");
			do{
			scanf("%d",&onayIptal);
			if(onayIptal==1){
				musteri[musteriNo].bakiye=musteri[musteriNo].bakiye+yatirmaPara;
				strcpy(dosyaYolu,anaYol);
				sprintf(dosyaDevam,"%ld",musteri[musteriNo].numara);
				strcat(dosyaYolu,dosyaDevam);
				strcat(dosyaYolu,"\\bakiye.txt");
				FILE *yaz=fopen(dosyaYolu,"r+");
				fprintf(yaz,"%f",musteri[musteriNo].bakiye);
				fclose(yaz);
				printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[musteriNo].bakiye);
			}
			else if(onayIptal==2){			
				printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
			}
			else
				printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
			}while(onayIptal!=1&&onayIptal!=2);	
		}
		else
			printf("Musteri Bulunamadi! Lutfen Tekrar Giris Yapin:");
	}
	}while(girisNo<20090000||girisNo>20090099);
	}while(musteri[musteriNo].aktif!=1);
	getch();
	system("CLS");
	adminMenu();
}
void musteriMenu(){
	system("CLS");
	int secim;
	printf("%ld Numarali Musteri Olarak Giris Yapildi\n",musteri[aktifNum].numara);
	printf("Hosgeldiniz %s %s\n",musteri[aktifNum].ad,musteri[aktifNum].soyAd);
	printf("[1]Para Yatirma\n[2]Para Cekme\n[3]Havale\n[4]Fatura Odeme\n[5]Bakiye Goruntuleme\n[6]Cikis		");
	do{
	scanf("%d",&secim);
	if(secim==1){
		paraYatirma();
	}
	else if(secim==2){
		paraCekme();
	}
	else if(secim==3){
		havale();
	}
	else if(secim==4){
		fatura();
	}
	else if(secim==5){
		bakiye();
	}
	else if(secim==6){
		ilkEkran();
	}
	else{
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}
	}while(secim!=1&&secim!=2&&secim!=3&&secim!=4&&secim!=5&&secim!=6);
}
void paraYatirma(){
	system("CLS");
	int onayIptal;
	float yatirmaPara;
	printf("Mevcut Bakiye: %.2f\n",musteri[aktifNum].bakiye);
	printf("Yatirmak Istediginiz Para Miktarini Girin: ");
	scanf("%f",&yatirmaPara);
	if(yatirmaPara<0)
		yatirmaPara=yatirmaPara*(-1);
	printf("%ld Numarali Hesaba %.2f TL Para Yatirilacaktir. Onayliyor Musunuz?\n",musteri[aktifNum].numara,yatirmaPara);
	printf("[1]Onayla\n[2]Iptal		");
	do{
	scanf("%d",&onayIptal);
	if(onayIptal==1){
		musteri[aktifNum].bakiye=musteri[aktifNum].bakiye+yatirmaPara;
		strcpy(dosyaYolu,anaYol);
		sprintf(dosyaDevam,"%ld",musteri[aktifNum].numara);
		strcat(dosyaYolu,dosyaDevam);
		strcat(dosyaYolu,"\\bakiye.txt");
		FILE *yaz=fopen(dosyaYolu,"r+");
		fprintf(yaz,"%f",musteri[aktifNum].bakiye);
		fclose(yaz);
		printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[aktifNum].bakiye);
	}
	else if(onayIptal==2){			
		printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
	}
	else
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}while(onayIptal!=1&&onayIptal!=2);
	getch();
	system("CLS");
	musteriMenu();
}
void paraCekme(){
	system("CLS");
	int onayIptal;
	float cekmePara;
	printf("Mevcut Bakiye: %.2f\n",musteri[aktifNum].bakiye);
	printf("Cekmek Istediginiz Para Miktarini Girin: ");
	scanf("%f",&cekmePara);
	if(cekmePara<0)
		cekmePara=cekmePara*(-1);
	printf("%ld Numarali Hesaptan %.2f TL Para Cekilecektir. Onayliyor Musunuz?\n",musteri[aktifNum].numara,cekmePara);
	printf("[1]Onayla\n[2]Iptal		");
	do{
	scanf("%d",&onayIptal);
	if(onayIptal==1){
		if(musteri[aktifNum].bakiye<cekmePara)
			printf("Yetersiz Bakiye! Menuye Donmek Icin Bir Tusa Basin...");
		else{
			musteri[aktifNum].bakiye=musteri[aktifNum].bakiye-cekmePara;
			strcpy(dosyaYolu,anaYol);
			sprintf(dosyaDevam,"%ld",musteri[aktifNum].numara);
			strcat(dosyaYolu,dosyaDevam);
			strcat(dosyaYolu,"\\bakiye.txt");
			FILE *yaz=fopen(dosyaYolu,"r+");
			fprintf(yaz,"%f",musteri[aktifNum].bakiye);
			fclose(yaz);
			printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[aktifNum].bakiye);
		}
	}
	else if(onayIptal==2){			
		printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
	}
	else
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}while(onayIptal!=1&&onayIptal!=2);	
	getch();
	system("CLS");
	musteriMenu();
}
void havale(){
	system("CLS");
	long havaleGiris;
	int havaleNo,onayIptal;
	float havalePara;
	printf("Havale Yapilacak Hesap Numarasini Girin: ");
	do{
	do{
	scanf("%ld",&havaleGiris);
	havaleNo=havaleGiris-20090000;
	if(havaleGiris<20090000||havaleGiris>20090099){
		printf("Hatali Giris Yaptiniz! Lutfen Tekrar Giris Yapin: ");
	}
	else{
		if(musteri[havaleNo].aktif==1){
			printf("Havale Etmek Istediginiz Para Miktarini Girin: ");
			scanf("%f",&havalePara);
			if(havalePara<0)
				havalePara=havalePara*(-1);
			printf("%ld Numarali Hesaptan %ld Numarali Hesaba %.2f TL Para Havale Edilecektir. Onayliyor Musunuz?\n",musteri[aktifNum].numara,musteri[havaleNo].numara,havalePara);
			printf("[1]Onayla\n[2]Iptal		");
			do{
			scanf("%d",&onayIptal);
			if(onayIptal==1){
				if(musteri[aktifNum].bakiye<havalePara)
					printf("Yetersiz Bakiye! Menuye Donmek Icin Bir Tusa Basin...");
				else{
					musteri[aktifNum].bakiye=musteri[aktifNum].bakiye-havalePara;
					strcpy(dosyaYolu,anaYol);
					sprintf(dosyaDevam,"%ld",musteri[aktifNum].numara);
					strcat(dosyaYolu,dosyaDevam);
					strcat(dosyaYolu,"\\bakiye.txt");
					FILE *yaz=fopen(dosyaYolu,"r+");
					fprintf(yaz,"%f",musteri[aktifNum].bakiye);
					musteri[havaleNo].bakiye=musteri[havaleNo].bakiye+havalePara;
					strcpy(dosyaYolu,anaYol);
					sprintf(dosyaDevam,"%ld",musteri[havaleNo].numara);
					strcat(dosyaYolu,dosyaDevam);
					strcat(dosyaYolu,"\\bakiye.txt");
					yaz=fopen(dosyaYolu,"r+");
					fprintf(yaz,"%f",musteri[havaleNo].bakiye);
					fclose(yaz);
					printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[aktifNum].bakiye);
				}
			}
			else if(onayIptal==2){			
				printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
			}
			else
				printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
			}while(onayIptal!=1&&onayIptal!=2);	
		}
		else
			printf("Musteri Bulunamadi! Lutfen Tekrar Giris Yapin: ");
	}
	}while(havaleGiris<20090000||havaleGiris>20090099);
	}while(musteri[havaleNo].aktif!=1);
	getch();
	musteriMenu();
}
void fatura(){
	system("CLS");
	int secim,onayIptal;
	char fatura[10];
	float tutar;
	printf("[1]Elektrik\n[2]Su\n[3]ADSL\n[4]Iptal		");
	do{
	scanf("%d",&secim);
	if(secim==1){
		strcpy(fatura,"Elektrik");
	}
	else if(secim==2){
		strcpy(fatura,"Su");
	}
	else if(secim==3){
		strcpy(fatura,"ADSL");
	}
	else if(secim==4){
		musteriMenu();
	}
	else{
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}
	}while(secim!=1&&secim!=2&&secim!=3&&secim!=4);
	printf("Fatura Tutari Girin :");
	scanf("%f",&tutar);
	printf("%s Faturasi Icin Hesabinizdan %.2f TL Odeme Yapilacaktir. Onayliyor Musunuz?\n",fatura,tutar);
	printf("[1]Onayla\n[2]Iptal		");
	do{
	scanf("%d",&onayIptal);
	if(onayIptal==1){
		if(musteri[aktifNum].bakiye<tutar)
			printf("Yetersiz Bakiye! Menuye Donmek Icin Bir Tusa Basin...");
		else{
			musteri[aktifNum].bakiye=musteri[aktifNum].bakiye-tutar;
			strcpy(dosyaYolu,anaYol);
			sprintf(dosyaDevam,"%ld",musteri[aktifNum].numara);
			strcat(dosyaYolu,dosyaDevam);
			strcat(dosyaYolu,"\\bakiye.txt");
			FILE *yaz=fopen(dosyaYolu,"r+");
			fprintf(yaz,"%f",musteri[aktifNum].bakiye);
			fclose(yaz);
			printf("Islem Tamamlandi.\nYeni Bakiye: %.2f\nMenuye Donmek Icin Bir Tusa Basin...",musteri[aktifNum].bakiye);
		}
	}
	else if(onayIptal==2){			
		printf("Islem Iptal Edildi. Menuye Donmek Icin Bir Tusa Basin...");	
	}
	else
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}while(onayIptal!=1&&onayIptal!=2);	
	getch();
	musteriMenu();
}
void bakiye(){
	system("CLS");
	printf("Mevcut Bakiye: %.2f\n",musteri[aktifNum].bakiye);
	printf("Menuye Donmek Icin Bir Tusa Basin...");
	getch();
	musteriMenu();
}
void ilkEkran(){
	system("CLS");
	long girisNo;
	int musteriNo,sifreGiris,hak=3;
	char adminGiris[9];
	int ilkSecim, adminSayac=0,i;
	printf("KULLANICI TIPINI SECIN\n");
	printf("[1]BANKACI\n[2]MUSTERI		");
	do{
	scanf("%d",&ilkSecim);
	if(ilkSecim==1){
		printf("Yonetici Sifresini Girin: ");
		do{
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	    scanf("%s",&adminGiris);
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	    adminSayac=0;
	    for(i=0;i<9;i++){
			if(adminGiris[i]==adminSifre[i]){
				adminSayac++;
			}
		}
		if(adminSayac==9){
			adminMenu();
		}
		else{
			printf("Yanlis Sifre! Lutfen Tekrar Giris Yapin: ");
		}
		}while(adminSayac!=9);
	}
	else if(ilkSecim==2){
		printf("Musteri Numarasi Girin: ");
		do{
		do{
		scanf("%ld",&girisNo);
		musteriNo=girisNo-20090000;
		if(girisNo<20090000||girisNo>20090099){
			printf("Hatali Giris Yaptiniz! Lutfen Tekrar Giris Yapin: ");
		}
		else{
			if(musteri[musteriNo].aktif==1&&musteri[musteriNo].bloke==0){
				printf("Sifre Girin: ");	
				do{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				scanf("%d",&sifreGiris);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				if(sifreGiris!=musteri[musteriNo].sifre){
					hak--;
					if(hak!=0)
						printf("Yanlis Sifre! %d Hakkiniz Kaldi: ",hak);
				}
				else if(sifreGiris==musteri[musteriNo].sifre){
					aktifNum=musteriNo;
					musteriMenu();
				}
				if(hak==0){
					printf("%ld NUMARALI HESAP BLOKE OLMUSTUR!",musteri[musteriNo].numara);
					musteri[musteriNo].bloke=1;
					strcpy(dosyaYolu,anaYol);
					sprintf(dosyaDevam,"%ld",musteri[musteriNo].numara);
					strcat(dosyaYolu,dosyaDevam);
					strcat(dosyaYolu,"\\bloke.txt");
					FILE *yaz=fopen(dosyaYolu,"r+");
					fprintf(yaz,"%d",musteri[musteriNo].bloke);
					fclose(yaz);
					printf("\nTekrar Kullanici Tipi Secimi Icin Bir Tusa Basin...");			
				}
				}while(sifreGiris!=musteri[musteriNo].sifre&&hak!=0);
			}
			else if(musteri[musteriNo].bloke==1){
				printf("%ld NUMARALI HESAP BLOKE OLMUSTUR!",musteri[musteriNo].numara);
				printf("\nTekrar Kullanici Tipi Secimi Icin Bir Tusa Basin...");
			}
			else
				printf("Musteri Bulunamadi! Lutfen Tekrar Giris Yapin: ");
		}
		}while(girisNo<20090000||girisNo>20090099);
		}while(musteri[musteriNo].aktif!=1);
	}
	else{
		printf("Hatali Giris! Lutfen Tekrar Secim Yapin: ");
	}
	}while(ilkSecim!=1&&ilkSecim!=2);
	getch();
	ilkEkran();
}
int main(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CreateDirectory("C:\\ATMProject\\",NULL);
	FILE *sayi=fopen("C:\\ATMProject\\musterisayisi.txt","r");
	fscanf(sayi,"%d",&musteriSayisi);
	fclose(sayi);
	strcpy(dosyaYolu,anaYol);
	int i;
	for(i=0;i<100;i++){
		musteri[i].numara=20090000+i;
	}
	for(i=0;i<musteriSayisi;i++){	
		musteri[i].aktif=1;
		strcpy(dosyaYolu,anaYol);
		sprintf(dosyaDevam,"%ld",musteri[i].numara);
		strcat(dosyaYolu,dosyaDevam);
		strcpy(yolTemp,dosyaYolu);
		strcat(dosyaYolu,"\\ad.txt");
		FILE *oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%s",&musteri[i].ad);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\soyad.txt");
		oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%s",&musteri[i].soyAd);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\adres.txt");
		oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%s",&musteri[i].adres);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\sifre.txt");
		oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%d",&musteri[i].sifre);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\bakiye.txt");
		oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%f",&musteri[i].bakiye);
		strcpy(dosyaYolu,yolTemp);
		strcat(dosyaYolu,"\\bloke.txt");
		oku=fopen(dosyaYolu,"r");
		fscanf(oku,"%d",&musteri[i].bloke);
		strcpy(dosyaYolu,yolTemp);
		fclose(oku);
	}
	ilkEkran();
	getch();
	return 0;
}
