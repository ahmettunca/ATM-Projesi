#include <string>
class musteriIslem
{
public:
	musteriIslem();
	~musteriIslem();
	virtual bool paraCekme(double neKadar) = 0;
	virtual void paraYatirma(double neKadar) = 0;
	virtual void menu() = 0;
	virtual bool faturaOde() = 0;
	virtual bool havale(std::string yatirilanNo, std::string kacinciKayit, double havaleMiktari) = 0;
	virtual void faturaIslemKayit(std::string hangiFatura, double sayi)= 0;
	virtual void paraIslemleriKayit(std::string islem, double neKadar) = 0;
	virtual void havaleKayit(std::string yatirilanNo, double neKadar, string aciklama) = 0;
};

