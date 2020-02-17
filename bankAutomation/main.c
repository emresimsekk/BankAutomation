#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<time.h>

void mainMenu(void);
void customerAdd(void);
void customerSelect(void);
void accountMenu(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void accountAdd(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void deposit(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void accountDelete(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void withdrawMoney(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void accountSummary(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void transfer(int customerSelectNumber,int customerSelectType,char customerSelectName[15], char customerSelectSurname[15]);
void reports();


typedef struct customer {
	int  customerNumber;
	char customerTC[12];
	int  customerType; // Bireysel 1 Ticari 2
	char customerName[15];
	char customerSurname[15];
	int  recordDateDay;
	int  recordDateMount;
	int  recordDateYear;
}customer;

typedef struct account {
	int  customerNumber;
	int  accountNumber;
	int  accountType; // Bireysel 1 Ticari 2
	char accountName[15];
	char accountSurname[15];
	int  balance;
	int  recordDateDay;
	int  recordDateMount;
	int  recordDateYear;
}account;

typedef struct bank {
	int  customerNumber;
	int  accountNumber;
	int  accountType; // Bireysel 1 Ticari 2
	char accountName[15];
	char accountSurname[15];
	int operators;
	int  balance;
	int  recordDateDay;
	int  recordDateMount;
	int  recordDateYear;
}bank;

typedef struct bankStatement{
	int  customerNumber;
	int  accountNumber;
	char accountName[15];
	char accountSurname[15];
	int  accountType;// Bireysel 1 Ticari 2
	int  recordDateDay;
	int  recordDateMount;
	int  recordDateYear;
	char  balance[20];

}bankStatement;

int main() {
	printf("\n---------------------------------------------- BANKA OTOMASYONU -----------------------------------------------\n\n");
	setlocale(LC_ALL, "Turkish");
	// Ana Menü Çaðrýlýyor
	mainMenu();
	return 0;
}
// Ana Menü
void mainMenu()
{

	int requestMainMenu;
	printf("1.Müþteri Ekle\n");
	printf("2.Müþteri Seç\n");
	printf("3.Banka Gelir-Gider Raporu\n");
	printf("4.Çýkýþ\n");
	scanf("%d",&requestMainMenu);
	if(requestMainMenu==1)
	{
		customerAdd();
	}
	else if(requestMainMenu==2)
	{
		customerSelect();
	}
	else if(requestMainMenu==3)
	{
		reports();
	}
	else if(requestMainMenu==4)
	{
		exit(1);
	}
	else
	{
		printf("HATA: Lütfen Geçerli Bir Deðer Giriniz.\n");
		mainMenu();
	}
}
//Hesap Menü
void accountMenu( int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	//Müþteri seç Bölümünün Yapabileceði iþlemler
	if(customerSelectNumber!=0)
	{

	   int requestAccount;
		printf("1.Hesap Ekle\n");
		printf("2.Para Çekme\n");
		printf("3.Para Yatýrma\n");
		printf("4.Hesaba Havale\n");
		printf("5.Hesap Özeti\n");
		printf("6.Hesap Kapatma\n");
		printf("7.Ana Menü\n");
		scanf("%d",&requestAccount);
		if(requestAccount==1)
		{
			accountAdd(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==2)
		{
			withdrawMoney(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==3)
		{
			deposit(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==4)
		{
			transfer(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==5)
		{
			accountSummary(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==6)
		{
			accountDelete(customerSelectNumber,customerSelectType,customerSelectName,customerSelectSurname);
		}
		else if(requestAccount==7)
		{
			mainMenu();
		}

		else
		{
			printf("HATA: Lütfen Geçerli Bir Deðer Giriniz.\n");
			mainMenu();
		}






	}
	else
	{
		printf("HATA: Parametre Deðerlerinde Sorun Yaþandý.\n");
		mainMenu();
	}
}
//Müþteri Ekleme
void customerAdd()
{
	struct customer customer;
	struct customer customerSearch;

	printf("Müþteri Tipinizi Giriniz. (Bireysel 1 || Ticari 2)\n");

	scanf("%d",&customer.customerType);


		if(customer.customerType==1)
		{
			//-----------------------Bireysel Müþteri Ekleme Kýsmý-------------------------------------------
			FILE *customerSingularRead=fopen("file/customer/customerSingular.txt","r");
			if (customerSingularRead!=NULL)
			{
				 //sistem tarihini alýyoruz
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				// rastgele sayý üretiyoruz
				srand(time(NULL));
				int randomNumber=rand()%9999+1000;
				//Dosyadaki degerleri okuyoruz
				while(!feof(customerSingularRead))
			 	{
			 		 //Dosyadak, degerleri customerSearch struct adýndaki struct kaydediyoruz.
			 		 fscanf(customerSingularRead,"%d %s %d %s %s %d %d %d",
					 &customerSearch.customerNumber,customerSearch.customerTC,&customerSearch.customerType,customerSearch.customerName,
					 customerSearch.customerSurname,&customerSearch.recordDateDay,&customerSearch.recordDateMount,&customerSearch.recordDateYear);
					 fclose(customerSingularRead);
					 //Random Oluþturduðumuz sayý ile dosyadan gelen müþteri numarasýný kýyaslýyoruz.
					 if(customerSearch.customerNumber!=randomNumber)
					 {
					 	FILE *customerSingularWrite=fopen("file/customer/customerSingular.txt","a+");
					 	customer.customerNumber=randomNumber;
					 	printf("Müþteri Türkiye Cumhuriyeti Kimlik Numarasýný Giriniz.\n");
					 	scanf("%s",customer.customerTC);
					 	printf("Müþteri Adýný Giriniz.\n");
					 	scanf("%s",customer.customerName);
					 	printf("Müþteri Soyad Giriniz.\n");
					 	scanf("%s",customer.customerSurname);
					 	customer.recordDateDay=tm.tm_mday;
						customer.recordDateMount=tm.tm_mon + 1;
						customer.recordDateYear= tm.tm_year + 1900;

					 	fprintf(customerSingularWrite,"\n%d ",customer.customerNumber);
				        fprintf(customerSingularWrite,"%s ",customer.customerTC);
				        fprintf(customerSingularWrite,"%d ",customer.customerType);
				        fprintf(customerSingularWrite,"%s ",customer.customerName);
				        fprintf(customerSingularWrite,"%s ",customer.customerSurname);
				        fprintf(customerSingularWrite,"%d ",customer.recordDateDay);
				        fprintf(customerSingularWrite,"%d ",customer.recordDateMount);
				        fprintf(customerSingularWrite,"%d",customer.recordDateYear);
				        printf("--------------------------------- Müþteri Baþarýyla Eklendi.--------------------------------- \n");
					 	fclose(customerSingularWrite);
						mainMenu();

					 }
					 else
					 {
					 	printf("HATA: Müþteri Numaralarý Çakýþýyor.\n");
					 	customerAdd();
					 }

			 	}

			}
			else
			{
				printf("HATA: Dosya Açýlamýyor\n");
			}
		}
	//-----------------------Ticari Müþteri Ekleme Kýsmý-------------------------------------------
		else if(customer.customerType==2)
		{

			FILE *customerTradingRead=fopen("file/customer/customerTrading.txt","r");
			if (customerTradingRead!=NULL)
			{
				 //sistem tarihini alýyoruz
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				// rastgele sayý üretiyoruz
				srand(time(NULL));
				int randomNumber=rand()%9999+1000;
				//Dosyadaki degerleri okuyoruz
				while(!feof(customerTradingRead))
			 	{
			 		 //Dosyadak, degerleri customerSearch struct adýndaki struct kaydediyoruz.
			 		 fscanf(customerTradingRead,"%d %s %d %s %s %d %d %d",
					 &customerSearch.customerNumber,customerSearch.customerTC,&customerSearch.customerType,customerSearch.customerName,
					 customerSearch.customerSurname,&customerSearch.recordDateDay,&customerSearch.recordDateMount,&customerSearch.recordDateYear);
					 fclose(customerTradingRead);
					 //Random Oluþturduðumuz sayý ile dosyadan gelen müþteri numarasýný kýyaslýyoruz.
					 if(customerSearch.customerNumber!=randomNumber)
					 {
					 	FILE *customerTradingWrite=fopen("file/customer/customerTrading.txt","a+");
					 	customer.customerNumber=randomNumber;
					 	printf("Müþteri Türkiye Cumhuriyeti Kimlik Numarasýný Giriniz.\n");
					 	scanf("%s",customer.customerTC);
					 	printf("Müþteri Adýný Giriniz.\n");
					 	scanf("%s",customer.customerName);
					 	printf("Müþteri Soyad Giriniz.\n");
					 	scanf("%s",customer.customerSurname);
					 	customer.recordDateDay=tm.tm_mday;
						customer.recordDateMount=tm.tm_mon + 1;
						customer.recordDateYear= tm.tm_year + 1900;

					 	fprintf(customerTradingWrite,"\n%d ",customer.customerNumber);
				        fprintf(customerTradingWrite,"%s ",customer.customerTC);
				        fprintf(customerTradingWrite,"%d ",customer.customerType);
				        fprintf(customerTradingWrite,"%s ",customer.customerName);
				        fprintf(customerTradingWrite,"%s ",customer.customerSurname);
				        fprintf(customerTradingWrite,"%d ",customer.recordDateDay);
				        fprintf(customerTradingWrite,"%d ",customer.recordDateMount);
				        fprintf(customerTradingWrite,"%d",customer.recordDateYear);
				        printf("--------------------------------- Müþteri Baþarýyla Eklendi.--------------------------------- \n");
					 	fclose(customerTradingWrite);
						mainMenu();

					 }
					 else
					 {
					 	printf("HATA: Müþteri Numaralarý Çakýþýyor.\n");
					 	customerAdd();
					 }

			 	}

			}
			else
			{
				printf("HATA: Dosya Açýlamýyor\n");
			}


		}
		else
		{
			printf("HATA: Lütfen Geçerli Bir Deðer Giriniz.\n");
			customerAdd();
		}






}
//Müþteri Seçme
void customerSelect()
{
	struct customer customerSelect;
	struct customer customerSearch;
	printf("Müþteri Tipinizi Giriniz. (Bireysel 1 || Ticari 2)\n");
	scanf("%d",&customerSelect.customerType);
	// Bireysel Müþteri ise bireysel müþteri dosyasýndan arama yapýyoruz
	if(customerSelect.customerType==1)
	{
		FILE *customerSingularRead=fopen("file/customer/customerSingular.txt","r");
		printf("Müþteri Numaranýzý Giriniz.\n");
		scanf("%d",&customerSelect.customerNumber);

		if(customerSingularRead!=NULL)
		{
			while(!feof(customerSingularRead))
			{
				fscanf(customerSingularRead,"%d %s %d %s %s %d %d %d",
			    &customerSearch.customerNumber,customerSearch.customerTC,&customerSearch.customerType,customerSearch.customerName,
	   		    customerSearch.customerSurname,&customerSearch.recordDateDay,&customerSearch.recordDateMount,&customerSearch.recordDateYear);

				if(customerSelect.customerNumber==customerSearch.customerNumber)
				{
					printf("-------------------------------- Seçilen Müþteri Bilgileri --------------------------------\n");
					printf("Müþteri Numarasý: %d\n",customerSearch.customerNumber);
					printf("Müþteri TC: %s\n",customerSearch.customerTC);
					printf("Müþteri Tipi: %d\n",customerSearch.customerType);
					printf("Müþteri Ad: %s\n",customerSearch.customerName);
					printf("Müþteri Soyad: %s\n",customerSearch.customerSurname);
					printf("Müþteri Kayýt Tarihi: %d.%d.%d\n",customerSearch.recordDateDay,customerSearch.recordDateMount,customerSearch.recordDateYear);
					printf("\n-------------------------------------------------------------------------------------------\n");
					accountMenu(customerSearch.customerNumber,customerSearch.customerType,customerSearch.customerName,customerSearch.customerSurname);
				}


			}
			fclose(customerSingularRead);


		}
		else
		{
			printf("HATA: Dosya Açýlamýyor");
		}


	}
	// Ticari Müþteri ise bireysel müþteri dosyasýndan arama yapýyoruz
	else if(customerSelect.customerType==2)
	{
		FILE *customerTradingRead=fopen("file/customer/customerTrading.txt","r");
		printf("Müþteri Numaranýzý Giriniz.\n");
		scanf("%d",&customerSelect.customerNumber);

		if(customerTradingRead!=NULL)
		{
			while(!feof(customerTradingRead))
			{
				fscanf(customerTradingRead,"%d %s %d %s %s %d %d %d",
			    &customerSearch.customerNumber,customerSearch.customerTC,&customerSearch.customerType,customerSearch.customerName,
	   		    customerSearch.customerSurname,&customerSearch.recordDateDay,&customerSearch.recordDateMount,&customerSearch.recordDateYear);

				if(customerSelect.customerNumber==customerSearch.customerNumber)
				{
					printf("-------------------------------- Seçilen Müþteri Bilgileri --------------------------------\n");
					printf("Müþteri Numarasý: %d\n",customerSearch.customerNumber);
					printf("Müþteri TC: %s\n",customerSearch.customerTC);
					printf("Müþteri Tipi: %d\n",customerSearch.customerType);
					printf("Müþteri Ad: %s\n",customerSearch.customerName);
					printf("Müþteri Soyad: %s\n",customerSearch.customerSurname);
					printf("Müþteri Kayýt Tarihi: %d.%d.%d\n",customerSearch.recordDateDay,customerSearch.recordDateMount,customerSearch.recordDateYear);
					printf("\n-------------------------------------------------------------------------------------------\n");
					accountMenu(customerSearch.customerNumber,customerSearch.customerType,customerSearch.customerName,customerSearch.customerSurname);
				}

			}
			fclose(customerTradingRead);


		}
		else
		{
			printf("HATA: Dosya Açýlamýyor");
		}


	}
	else
	{
		printf("HATA: Lütfen Geçerli Bir Deðer Giriniz.\n");
		mainMenu();

	}


}
//Hesap Açma
void accountAdd(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	//Müþteri seçtikten sonra ki menüden hesap ekleme kýsmý gelen parametrelere göre dosyaya hesap ekliyoruz.
	struct account account;
	printf("Hesap Açýlýþtaki Miktarý Giriniz.\n");
	scanf("%d",&account.balance);

	FILE *accountWrite=fopen("file/account/accountAdd.txt","a+");
	if(accountWrite!=NULL)
	{
		//sistem tarihini alýyoruz
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		// rastgele sayý üretiyoruz
		srand(time(NULL));
		int randomNumber=rand()%1000000+9999999;

		account.customerNumber=customerSelectNumber;
		account.accountNumber=randomNumber;
		account.accountType=customerSelectType;
		account.recordDateDay=tm.tm_mday;
		account.recordDateMount=tm.tm_mon + 1;
		account.recordDateYear= tm.tm_year + 1900;


		fprintf(accountWrite,"\n%d ",account.customerNumber);
		fprintf(accountWrite,"%d ",account.accountNumber);
		fprintf(accountWrite,"%d ",account.accountType);
		fprintf(accountWrite,"%s ",customerSelectName);
		fprintf(accountWrite,"%s ",customerSelectSurname);
		fprintf(accountWrite,"%d ",account.balance);
		fprintf(accountWrite,"%d %d %d",account.recordDateDay,account.recordDateMount,account.recordDateYear);
		fclose(accountWrite);
		accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);



	}
	else
	{
		printf("HATA: Dosya Açýlamadý.");
	}



}
//Para Yatýrrma
void deposit(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	struct account accountDeposit;

	FILE  *accountFileDeposit=fopen("file/account/accountAdd.txt","r");
	if(accountFileDeposit!=NULL)
	{
		//Müþteri Numarasýna Göre Kiþinin Hesaplarýný Ekrana yazdýrýyoruz.
		while(!feof(accountFileDeposit))
		{
			fscanf(accountFileDeposit,"%d %d %d %s %s %d %d %d %d",
			&accountDeposit.customerNumber,&accountDeposit.accountNumber,&accountDeposit.accountType,accountDeposit.accountName,accountDeposit.accountSurname,
			&accountDeposit.balance,&accountDeposit.recordDateDay,&accountDeposit.recordDateMount,&accountDeposit.recordDateYear);
			if(customerSelectNumber==accountDeposit.customerNumber)
			{
				printf("\n---------------------- Hesap Bilgileri ----------------------\n");
				printf("Müþteri numarasý:%d\n",accountDeposit.customerNumber);
				printf("Hesap Numarasý:%d\n",accountDeposit.accountNumber);
				printf("Hesap Tipi:%d\n",accountDeposit.accountType);
				printf("Hesap Adý :%s\n",accountDeposit.accountName);
				printf("Hesap Soyadý:%s\n",accountDeposit.accountSurname);
				printf("Hesap Bakiyesi:%d\n",accountDeposit.balance);
				printf("Hesap Açýlýþ Tarihi:%d.%d.%d\n",accountDeposit.recordDateDay,accountDeposit.recordDateMount,accountDeposit.recordDateYear);
				printf("\n-------------------------------------------------------------\n");

			}

		}
		fclose(accountFileDeposit);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}

    	FILE  *accountFileMoneyRead=fopen("file/account/accountAdd.txt","r");
	    FILE  *accountFileMoneyDelete=fopen("file/account/accountAddYeni.txt","a+");
	    FILE  *bankStatement=fopen("file/bankStatement/bankStatement.txt","a+");
	    if(accountFileMoneyRead!=NULL && accountFileMoneyDelete!=NULL && bankStatement!=NULL)
		{
			int amountDeposit;
			int balance;
			printf("Para Yatýrýlacak Hesap Numarasýný Giriniz.\n");
			scanf("%d",&amountDeposit);
			printf("Yatýrýlacak Miktarý Giriniz.\n");
			scanf("%d",&balance);
	
			struct account accountMoneyUpdate;
	
	
			while(!feof(accountFileMoneyRead))
			{
	
				fscanf(accountFileMoneyRead,"%d %d %d %s %s %d %d %d %d",
				&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);
	
				// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
				if(amountDeposit!=accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
				// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
				else if(amountDeposit==accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance+balance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
						fprintf(bankStatement,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountType);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountName);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountSurname);
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
	
						accountMoneyUpdate.recordDateDay=tm.tm_mday;
						accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
						accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
						fprintf(bankStatement,"+%d ",balance);
						fprintf(bankStatement,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
	
			}
	
	
			fclose(accountFileMoneyRead);
	    	fclose(accountFileMoneyDelete);
	    	fclose(bankStatement);
	    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
			remove("file/account/accountAdd.txt");
			rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");
	
			accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);
	
		}
		else
		{
			printf("HATA: Dosya Açýlamýyor.");
		}


}
//Kullanýcý Silme
void accountDelete(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
  struct account accountDepositRead;

  //Silinecek kulllanýcý  bilgislerini ve hesap özeti için dosyalar açtýrýyoruz
  FILE  *accountFileDeposit=fopen("file/account/accountAdd.txt","r");
  FILE  *accountFileDepositDelete=fopen("file/account/accountAddYeni.txt","a+");
  FILE  *bankStatementFile=fopen("file/bankStatement/bankStatement.txt","r");
  FILE  *bankStatementFileDelete=fopen("file/bankStatement/bankStatementYeni.txt","a+");

  FILE  *accountFileDepositRead=fopen("file/account/accountAdd.txt","r");

  if(accountFileDeposit!=NULL && accountFileDepositDelete!=NULL && bankStatementFile !=NULL && bankStatementFileDelete!=NULL &&accountFileDepositRead!=NULL )
	{
		//Hesap Bilgilerini Ekrana yazdýrýyoruz.
		while(!feof(accountFileDepositRead))
		{
			fscanf(accountFileDepositRead,"%d %d %d %s %s %d %d %d %d",
			&accountDepositRead.customerNumber,&accountDepositRead.accountNumber,&accountDepositRead.accountType,accountDepositRead.accountName,accountDepositRead.accountSurname,
			&accountDepositRead.balance,&accountDepositRead.recordDateDay,&accountDepositRead.recordDateMount,&accountDepositRead.recordDateYear);
		
				if(customerSelectNumber==accountDepositRead.customerNumber)
				{
					printf("\n---------------------- Hesap Bilgileri ----------------------\n");
					printf("Müþteri numarasý:%d\n",accountDepositRead.customerNumber);
					printf("Hesap Numarasý:%d\n",accountDepositRead.accountNumber);
					printf("Hesap Tipi:%d\n",accountDepositRead.accountType);
					printf("Hesap Adý :%s\n",accountDepositRead.accountName);
					printf("Hesap Soyadý:%s\n",accountDepositRead.accountSurname);
					printf("Hesap Bakiyesi:%d\n",accountDepositRead.balance);
					printf("Hesap Açýlýþ Tarihi:%d.%d.%d\n",accountDepositRead.recordDateDay,accountDepositRead.recordDateMount,accountDepositRead.recordDateYear);
					printf("\n-------------------------------------------------------------\n");
	
				}
				

		}
		fclose(accountFileDepositRead);

		int amountDeposit;
		printf("Kapatmak Ýstediðiniz Hesap Numarasýný Giriniz.\n");
		scanf("%d",&amountDeposit);

		struct account accountDepositUpdate;

		// Müþteri hesabý siliniyor bu bölümde
		while(!feof(accountFileDeposit))
		{

			fscanf(accountFileDeposit,"%d %d %d %s %s %d %d %d %d",
			&accountDepositUpdate.customerNumber,&accountDepositUpdate.accountNumber,&accountDepositUpdate.accountType,
			accountDepositUpdate.accountName,accountDepositUpdate.accountSurname,&accountDepositUpdate.balance,
			&accountDepositUpdate.recordDateDay,&accountDepositUpdate.recordDateMount,&accountDepositUpdate.recordDateYear);
		
				if(amountDeposit!=accountDepositUpdate.accountNumber)
				{
	
					
						fprintf(accountFileDepositDelete,"%d ",accountDepositUpdate.customerNumber);
						fprintf(accountFileDepositDelete,"%d ",accountDepositUpdate.accountNumber);
						fprintf(accountFileDepositDelete,"%d ",accountDepositUpdate.accountType);
						fprintf(accountFileDepositDelete,"%s ",accountDepositUpdate.accountName);
						fprintf(accountFileDepositDelete,"%s ",accountDepositUpdate.accountSurname);
						fprintf(accountFileDepositDelete,"%d ",accountDepositUpdate.balance);
						fprintf(accountFileDepositDelete,"%d %d %d\n",accountDepositUpdate.recordDateDay,accountDepositUpdate.recordDateMount,accountDepositUpdate.recordDateYear);									
					
	
				}
			
		
		}


		fclose(accountFileDepositDelete);
		fclose(accountFileDeposit);
		remove("file/account/accountAdd.txt");
		rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");



		struct bankStatement bankStatement;
		//Müþteri hesap özeti siliniyor bu bölümde
		while(!feof(bankStatementFile))
		{
			fscanf(bankStatementFile,"%d %d %d %s %s %s %d %d %d",
			&bankStatement.customerNumber,&bankStatement.accountNumber,&bankStatement.accountType,bankStatement.accountName,bankStatement.accountSurname,
			bankStatement.balance,&bankStatement.recordDateDay,&bankStatement.recordDateMount,&bankStatement.recordDateYear);

			
				if(amountDeposit!=bankStatement.accountNumber)
				{
				
						fprintf(bankStatementFileDelete,"%d ",bankStatement.customerNumber);
						fprintf(bankStatementFileDelete,"%d ",bankStatement.accountNumber);
						fprintf(bankStatementFileDelete,"%d ",bankStatement.accountType);
						fprintf(bankStatementFileDelete,"%s ",bankStatement.accountName);
						fprintf(bankStatementFileDelete,"%s ",bankStatement.accountSurname);
						fprintf(bankStatementFileDelete,"%s ",bankStatement.balance);
						fprintf(bankStatementFileDelete,"%d %d %d\n",bankStatement.recordDateDay,bankStatement.recordDateMount,bankStatement.recordDateYear);
					
	
				}
			



		}

		printf("\n------------------- Hesabýnýz Baþarýyla Silindi -------------------\n");
		fclose(bankStatementFileDelete);
		fclose(bankStatementFile);
		remove("file/bankStatement/bankStatement.txt");
		rename("file/bankStatement/bankStatementYeni.txt","file/bankStatement/bankStatement.txt");


		accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);

	}
	else{
		printf("HATA: Dosya Açýlamadý.");

	}



}
//Para Çekme
void withdrawMoney(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	struct account accountMoney;
	FILE  *accountMoneyFile=fopen("file/account/accountAdd.txt","r");
	if(accountMoneyFile!=NULL)
	{
		//Müþteri Numarasýna Göre Kiþinin Hesaplarýný Ekrana yazdýrýyoruz.
		while(!feof(accountMoneyFile))
		{
			
			
			fscanf(accountMoneyFile,"%d %d %d %s %s %d %d %d %d",
			&accountMoney.customerNumber,&accountMoney.accountNumber,&accountMoney.accountType,accountMoney.accountName,accountMoney.accountSurname,
			&accountMoney.balance,&accountMoney.recordDateDay,&accountMoney.recordDateMount,&accountMoney.recordDateYear);
			if(customerSelectNumber==accountMoney.customerNumber)
			{
				printf("\n----------------------Para Çekilecek Hesap Bilgileri ----------------------\n");
				printf("Müþteri numarasý:%d\n",accountMoney.customerNumber);
				printf("Hesap Numarasý:%d\n",accountMoney.accountNumber);
				printf("Hesap Tipi:%d\n",accountMoney.accountType);
				printf("Hesap Adý :%s\n",accountMoney.accountName);
				printf("Hesap Soyadý:%s\n",accountMoney.accountSurname);
				printf("Hesap Bakiyesi:%d\n",accountMoney.balance);
				printf("Hesap Açýlýþ Tarihi:%d.%d.%d\n",accountMoney.recordDateDay,accountMoney.recordDateMount,accountMoney.recordDateYear);
				printf("\n-------------------------------------------------------------\n");

			}

		}
		fclose(accountMoneyFile);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}

	FILE  *accountFileMoneyRead=fopen("file/account/accountAdd.txt","r");
    FILE  *accountFileMoneyDelete=fopen("file/account/accountAddYeni.txt","a+");
    FILE  *bankStatement=fopen("file/bankStatement/bankStatement.txt","a+");
    if(accountFileMoneyRead!=NULL && accountFileMoneyDelete!=NULL && bankStatement!=NULL)
	{
		int amountDeposit;
		int balance;
		printf("Para Çekilecek Hesap Numarasýný Giriniz.\n");
		scanf("%d",&amountDeposit);
		printf("Çekilecek Miktarý Giriniz.\n");
		scanf("%d",&balance);



		
		struct account accountMoneyUpdate;


		while(!feof(accountFileMoneyRead))
		{
		
			fscanf(accountFileMoneyRead,"%d %d %d %s %s %d %d %d %d",
			&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);

			if(accountMoneyUpdate.accountType==1 && balance>750)
			{
				printf("Bireysel Müþteri Para Çekme Limiti 750 TL Ticari Müüþterilerin ise 1500 TL Lütfen Uygun Ýçerik Giriniz.\n");
				accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);
			}
			else if(accountMoneyUpdate.accountType==2 && balance>1500)
			{
				printf("Bireysel Müþteri Para Çekme Limiti 750 TL Ticari Müüþterilerin ise 1500 TL Lütfen Uygun Ýçerik Giriniz.\n");
				accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);
			}


			
			// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
			if(amountDeposit!=accountMoneyUpdate.accountNumber)
			{

					fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
					fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
					fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance);
					fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);




			}
			// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
			else if(amountDeposit==accountMoneyUpdate.accountNumber)
			{

					fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
					fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
					fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
					fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance-balance);
					fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);

					fprintf(bankStatement,"\n%d ",accountMoneyUpdate.customerNumber);
					fprintf(bankStatement,"%d ",accountMoneyUpdate.accountNumber);
					fprintf(bankStatement,"%d ",accountMoneyUpdate.accountType);
					fprintf(bankStatement,"%s ",accountMoneyUpdate.accountName);
					fprintf(bankStatement,"%s ",accountMoneyUpdate.accountSurname);
					time_t t = time(NULL);
					struct tm tm = *localtime(&t);

					accountMoneyUpdate.recordDateDay=tm.tm_mday;
					accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
					accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
					fprintf(bankStatement,"-%d ",balance);
					fprintf(bankStatement,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);




			}

		}


		fclose(accountFileMoneyRead);
    	fclose(accountFileMoneyDelete);
    	fclose(bankStatement);
    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
		remove("file/account/accountAdd.txt");
		rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");

		accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}



}
//Hesap Özeti
void accountSummary(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	struct account accountDeposit;

	FILE  *accountFileDeposit=fopen("file/account/accountAdd.txt","r");
	if(accountFileDeposit!=NULL)
	{
		//Müþteri Numarasýna Göre Kiþinin Hesaplarýný Ekrana yazdýrýyoruz.
		while(!feof(accountFileDeposit))
		{
			fscanf(accountFileDeposit,"%d %d %d %s %s %d %d %d %d",
			&accountDeposit.customerNumber,&accountDeposit.accountNumber,&accountDeposit.accountType,accountDeposit.accountName,accountDeposit.accountSurname,
			&accountDeposit.balance,&accountDeposit.recordDateDay,&accountDeposit.recordDateMount,&accountDeposit.recordDateYear);
			if(customerSelectNumber==accountDeposit.customerNumber)
			{
				printf("\n---------------------- Hesap Bilgileri ----------------------\n");
				printf("Müþteri numarasý:%d\n",accountDeposit.customerNumber);
				printf("Hesap Numarasý:%d\n",accountDeposit.accountNumber);
				printf("Hesap Tipi:%d\n",accountDeposit.accountType);
				printf("Hesap Adý :%s\n",accountDeposit.accountName);
				printf("Hesap Soyadý:%s\n",accountDeposit.accountSurname);
				printf("Hesap Bakiyesi:%d\n",accountDeposit.balance);
				printf("Hesap Açýlýþ Tarihi:%d.%d.%d\n",accountDeposit.recordDateDay,accountDeposit.recordDateMount,accountDeposit.recordDateYear);
				printf("\n-------------------------------------------------------------\n");

			}

		}
		fclose(accountFileDeposit);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}

	int accountNumber;
	printf("Hesap Özetini Görmek için Hesap Numarasýný Giriniz.");
	scanf("%d",&accountNumber);


	struct bankStatement bankStatement;

	// seçilen hesap numarasýnýna göre  bankstatement dosya içersindeki hesap özetini ekrana basýyoruz
	FILE  *accountFileBankStatement=fopen("file/bankStatement/bankStatement.txt","r");
	if(accountFileBankStatement!=NULL)
	{

		printf("\n---------------------- Hesap Özeti ----------------------\n");
		while(!feof(accountFileBankStatement))
		{
			fscanf(accountFileBankStatement,"%d %d %d %s %s %s %d %d %d",
			&bankStatement.customerNumber,&bankStatement.accountNumber,&bankStatement.accountType,bankStatement.accountName,bankStatement.accountSurname,
			&bankStatement.balance,&bankStatement.recordDateDay,&bankStatement.recordDateMount,&bankStatement.recordDateYear);
			if(accountNumber==bankStatement.accountNumber)
			{

				printf("Müþteri numarasý:%d\n",bankStatement.customerNumber);
				printf("Hesap Numarasý:%d\n",bankStatement.accountNumber);
				printf("Hesap Tipi:%d\n",bankStatement.accountType);
				printf("Hesap Adý :%s\n",bankStatement.accountName);
				printf("Hesap Soyadý:%s\n",bankStatement.accountSurname);
				printf("Hesap Bakiyesi:%s\n",bankStatement.balance);
				printf("Hesap Ýþlem Tarihi:%d.%d.%d\n",bankStatement.recordDateDay,bankStatement.recordDateMount,bankStatement.recordDateYear);
				printf("\n-------------------------------------------------------------\n");

			}

		}
		fclose(accountFileBankStatement);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}


	accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);







}
//Havale
void transfer(int customerSelectNumber,int customerSelectType, char customerSelectName[15], char customerSelectSurname[15])
{
	//para çekme 0 yatýrma 1
	struct account transfer;
	FILE  *accountTransfer=fopen("file/account/accountAdd.txt","r");
	if(accountTransfer!=NULL)
	{
		//Müþteri Numarasýna Göre Kiþinin Hesaplarýný Ekrana yazdýrýyoruz.
		while(!feof(accountTransfer))
		{
			fscanf(accountTransfer,"%d %d %d %s %s %d %d %d %d",
			&transfer.customerNumber,&transfer.accountNumber,&transfer.accountType,transfer.accountName,transfer.accountSurname,
			&transfer.balance,&transfer.recordDateDay,&transfer.recordDateMount,&transfer.recordDateYear);
			if(customerSelectNumber==transfer.customerNumber)
			{
				printf("\n----------------------Havale Hesap Bilgileri ----------------------\n");
				printf("Müþteri numarasý:%d\n",transfer.customerNumber);
				printf("Hesap Numarasý:%d\n",transfer.accountNumber);
				printf("Hesap Tipi:%d\n",transfer.accountType);
				printf("Hesap Adý :%s\n",transfer.accountName);
				printf("Hesap Soyadý:%s\n",transfer.accountSurname);
				printf("Hesap Bakiyesi:%d\n",transfer.balance);
				printf("Hesap Açýlýþ Tarihi:%d.%d.%d\n",transfer.recordDateDay,transfer.recordDateMount,transfer.recordDateYear);
				printf("\n-------------------------------------------------------------\n");

			}

		}
		fclose(accountTransfer);

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}

	
	//-------------------------------Para çekme----------------------
	
	
	int amountDeposit;
	int amountDeposiBe;
	int balance;
	printf("Para Çekilecek Hesap Numarasýný Giriniz.\n");
	scanf("%d",&amountDeposit);
	printf("Para Gönderilecek Hesap Numarasýný Giriniz.\n");
	scanf("%d",&amountDeposiBe);
	printf("Gönderilecek Miktarý Giriniz.\n");
	scanf("%d",&balance);
	int newBalance =balance+(balance*0.02);
	
	if(customerSelectType==1)
	{
		//----------------------Para Çekme-----------------------------
		FILE  *accountFileMoneyRead=fopen("file/account/accountAdd.txt","r");
	    FILE  *accountFileMoneyDelete=fopen("file/account/accountAddYeni.txt","a+");
	    FILE  *bankStatement=fopen("file/bankStatement/bankStatement.txt","a+");
	    FILE  *report=fopen("file/report/report.txt","a+");
	    
	    if(accountFileMoneyRead!=NULL && accountFileMoneyDelete!=NULL && bankStatement!=NULL)
		{
			
			struct account accountMoneyUpdate;
	
	
			while(!feof(accountFileMoneyRead))
			{
	
				fscanf(accountFileMoneyRead,"%d %d %d %s %s %d %d %d %d",
				&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);
	
				// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
				if(amountDeposit!=accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
				// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
				else if(amountDeposit==accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance-newBalance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
						fprintf(bankStatement,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountType);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountName);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountSurname);
						
						fprintf(report,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(report,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(report,"%d ",accountMoneyUpdate.accountType);
						fprintf(report,"%s ",accountMoneyUpdate.accountName);
						fprintf(report,"%s ",accountMoneyUpdate.accountSurname);
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
	
						accountMoneyUpdate.recordDateDay=tm.tm_mday;
						accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
						accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
						fprintf(bankStatement,"-%d ",balance);
						fprintf(bankStatement,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
						
						fprintf(report,"0 %d ",balance);
						fprintf(report,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
	
			}
	
	
			fclose(accountFileMoneyRead);
	    	fclose(accountFileMoneyDelete);
	    	fclose(report);
	    	fclose(bankStatement);
	    	
	    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
			remove("file/account/accountAdd.txt");
			rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");
	
			
	
		}
		else
		{
			printf("HATA: Dosya Açýlamýyor.");
		}

		//---------------------Para Yatýrma--------------------------------------------
		FILE  *accountFileMoneyReadPut=fopen("file/account/accountAdd.txt","r");
	    FILE  *accountFileMoneyDeletePut=fopen("file/account/accountAddYeni.txt","a+");
	    FILE  *bankStatementPut=fopen("file/bankStatement/bankStatement.txt","a+");
	    FILE  *reportPut=fopen("file/report/report.txt","a+");
	    
	    if(accountFileMoneyReadPut!=NULL && accountFileMoneyDeletePut!=NULL && bankStatementPut!=NULL)
		{
			
			struct account accountMoneyUpdate;
	
	
			while(!feof(accountFileMoneyReadPut))
			{
	
				fscanf(accountFileMoneyReadPut,"%d %d %d %s %s %d %d %d %d",
				&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);
	
				// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
				if(amountDeposiBe!=accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDeletePut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.balance);
						fprintf(accountFileMoneyDeletePut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
				// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
				else if(amountDeposiBe==accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDeletePut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.balance+balance);
						fprintf(accountFileMoneyDeletePut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
						fprintf(bankStatementPut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(bankStatementPut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(bankStatementPut,"%d ",accountMoneyUpdate.accountType);
						fprintf(bankStatementPut,"%s ",accountMoneyUpdate.accountName);
						fprintf(bankStatementPut,"%s ",accountMoneyUpdate.accountSurname);
						
						fprintf(reportPut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(reportPut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(reportPut,"%d ",accountMoneyUpdate.accountType);
						fprintf(reportPut,"%s ",accountMoneyUpdate.accountName);
						fprintf(reportPut,"%s ",accountMoneyUpdate.accountSurname);
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
	
						accountMoneyUpdate.recordDateDay=tm.tm_mday;
						accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
						accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
						fprintf(bankStatementPut,"+%d ",balance);
						fprintf(bankStatementPut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
						
						fprintf(reportPut,"1 %d ",balance);
						fprintf(reportPut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
	
			}
	
	
			fclose(accountFileMoneyReadPut);
	    	fclose(accountFileMoneyDeletePut);
	    	fclose(bankStatementPut);
	    	fclose(reportPut);
	    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
			remove("file/account/accountAdd.txt");
			rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");
			
			accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);
			
	
		}
		else
		{
			printf("HATA: Dosya Açýlamýyor.");
		}

		
		
	}
	else if(customerSelectType==2)
	{
		//-------------Para Çekme Ticari--------------------
		FILE  *accountFileMoneyRead=fopen("file/account/accountAdd.txt","r");
	    FILE  *accountFileMoneyDelete=fopen("file/account/accountAddYeni.txt","a+");
	    FILE  *bankStatement=fopen("file/bankStatement/bankStatement.txt","a+");
	    FILE  *report=fopen("file/report/report.txt","a+");
	    if(accountFileMoneyRead!=NULL && accountFileMoneyDelete!=NULL && bankStatement!=NULL)
		{
			
			struct account accountMoneyUpdate;
	
	
			while(!feof(accountFileMoneyRead))
			{
	
				fscanf(accountFileMoneyRead,"%d %d %d %s %s %d %d %d %d",
				&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);
	
				// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
				if(amountDeposit!=accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
				// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
				else if(amountDeposit==accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDelete,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDelete,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDelete,"%d ",accountMoneyUpdate.balance-balance);
						fprintf(accountFileMoneyDelete,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
						fprintf(bankStatement,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(bankStatement,"%d ",accountMoneyUpdate.accountType);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountName);
						fprintf(bankStatement,"%s ",accountMoneyUpdate.accountSurname);
						
						fprintf(report,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(report,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(report,"%d ",accountMoneyUpdate.accountType);
						fprintf(report,"%s ",accountMoneyUpdate.accountName);
						fprintf(report,"%s ",accountMoneyUpdate.accountSurname);
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
	
						accountMoneyUpdate.recordDateDay=tm.tm_mday;
						accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
						accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
						fprintf(bankStatement,"-%d ",balance);
						fprintf(bankStatement,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
						fprintf(report,"0 %d ",balance);
						fprintf(report,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
	
			}
	
	
			fclose(accountFileMoneyRead);
	    	fclose(accountFileMoneyDelete);
	    	fclose(bankStatement);
	    	fclose(report);
	    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
			remove("file/account/accountAdd.txt");
			rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");
	
			
	
		}
		else
		{
			printf("HATA: Dosya Açýlamýyor.");
		}

		//---------------------Para Yatýrma Ticari--------------------------------------------
		FILE  *accountFileMoneyReadPut=fopen("file/account/accountAdd.txt","r");
	    FILE  *accountFileMoneyDeletePut=fopen("file/account/accountAddYeni.txt","a+");
	    FILE  *bankStatementPut=fopen("file/bankStatement/bankStatement.txt","a+");
	    FILE  *reportPut=fopen("file/report/report.txt","a+");
	    if(accountFileMoneyReadPut!=NULL && accountFileMoneyDeletePut!=NULL && bankStatementPut!=NULL)
		{
			
			struct account accountMoneyUpdate;
	
	
			while(!feof(accountFileMoneyReadPut))
			{
	
				fscanf(accountFileMoneyReadPut,"%d %d %d %s %s %d %d %d %d",
				&accountMoneyUpdate.customerNumber,&accountMoneyUpdate.accountNumber,&accountMoneyUpdate.accountType,accountMoneyUpdate.accountName,accountMoneyUpdate.accountSurname,&accountMoneyUpdate.balance,&accountMoneyUpdate.recordDateDay,&accountMoneyUpdate.recordDateMount,&accountMoneyUpdate.recordDateYear);
	
				// para çekilecek hesap bilgilerini dýþýndaki hesaplarý baþka dosyaya yazdýrýyoruz
				if(amountDeposiBe!=accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDeletePut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.balance);
						fprintf(accountFileMoneyDeletePut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
				// para çekilecek hesap bilgilerini baþka dosyaya yazdýrýyoruz
				else if(amountDeposiBe==accountMoneyUpdate.accountNumber)
				{
	
						fprintf(accountFileMoneyDeletePut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.accountType);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountName);
						fprintf(accountFileMoneyDeletePut,"%s ",accountMoneyUpdate.accountSurname);
						fprintf(accountFileMoneyDeletePut,"%d ",accountMoneyUpdate.balance+balance);
						fprintf(accountFileMoneyDeletePut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
						fprintf(bankStatementPut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(bankStatementPut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(bankStatementPut,"%d ",accountMoneyUpdate.accountType);
						fprintf(bankStatementPut,"%s ",accountMoneyUpdate.accountName);
						fprintf(bankStatementPut,"%s ",accountMoneyUpdate.accountSurname);
						
						fprintf(reportPut,"\n%d ",accountMoneyUpdate.customerNumber);
						fprintf(reportPut,"%d ",accountMoneyUpdate.accountNumber);
						fprintf(reportPut,"%d ",accountMoneyUpdate.accountType);
						fprintf(reportPut,"%s ",accountMoneyUpdate.accountName);
						fprintf(reportPut,"%s ",accountMoneyUpdate.accountSurname);
						
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
	
						accountMoneyUpdate.recordDateDay=tm.tm_mday;
						accountMoneyUpdate.recordDateMount=tm.tm_mon + 1;
						accountMoneyUpdate.recordDateYear= tm.tm_year + 1900;
						fprintf(bankStatementPut,"+%d ",balance);
						fprintf(bankStatementPut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
						fprintf(reportPut,"1 %d ",balance);
						fprintf(reportPut,"%d %d %d",accountMoneyUpdate.recordDateDay,accountMoneyUpdate.recordDateMount,accountMoneyUpdate.recordDateYear);
	
	
	
	
				}
	
			}
	
	
			fclose(accountFileMoneyReadPut);
	    	fclose(accountFileMoneyDeletePut);
	    	fclose(reportPut);
	    	fclose(bankStatementPut);
	    	//dosyalarý kapatýp isimleri deðiþtiriyoruz
			remove("file/account/accountAdd.txt");
			rename("file/account/accountAddYeni.txt","file/account/accountAdd.txt");
			
			accountMenu(customerSelectNumber,customerSelectType,customerSelectName, customerSelectSurname);
			
	
		}
		else
		{
			printf("HATA: Dosya Açýlamýyor.");
		}

		
		
	}




	
    












}

void reports()
{
	struct bank bankReport;
	int accountSum=0;
	int customerSingular=0;
	int customerTrading=0;
	FILE  *bankReportFile=fopen("file/report/report.txt","r");
	FILE  *customerSingularFile=fopen("file/customer/customerSingular.txt","r");
	FILE  *customerTradingFile=fopen("file/customer/customerTrading.txt","r");
	if(bankReportFile!=NULL)
	{
		int incoming=0;// o giden 1 gelen
		int outgoing=0;
		//Müþteri Numarasýna Göre Kiþinin Hesaplarýný Ekrana yazdýrýyoruz.
		while(!feof(bankReportFile))
		{
			fscanf(bankReportFile,"%d %d %d %s %s %d %d %d %d %d",
			&bankReport.customerNumber,&bankReport.accountNumber,&bankReport.accountType,bankReport.accountName,bankReport.accountSurname,&bankReport.operators,
			&bankReport.balance,&bankReport.recordDateDay,&bankReport.recordDateMount,&bankReport.recordDateYear);
			accountSum++;
			
			if(bankReport.operators==0)
			{
				outgoing=outgoing+ bankReport.balance;
				
			

			}
			else if(bankReport.operators==1)
			{
				incoming=incoming+ bankReport.balance;
			}

		}
		fclose(bankReportFile);
		
				   
		
		char customerSingularNumber;
		
		while(feof(customerSingularFile)==NULL)
		{
			customerSingularNumber=getc(customerSingularFile);
			if(customerSingularNumber=='\n')
			{ 
				customerSingular++; 
			}
			
		}
		
		char customerTradingNumber;
		while(feof(customerTradingFile)==NULL)
		{
			customerTradingNumber=getc(customerTradingFile);
			if(customerTradingNumber=='\n')
			{ 
				customerTrading++; 
			}
			
		}
	
				
		
		printf("Toplam Bankaya Gelen Para: %d\n",incoming);
		printf("Toplam Bankayadan Giden Para: %d\n",outgoing);
		printf("Toplam Açýlan Hesap Sayýsý: %d\n",accountSum);
		printf("Toplam Bireysel Müþteri Sayýsý: %d\n",(customerSingular+1));
		printf("Toplam Ticari Müþteri Sayýsý: %d\n",(customerTrading+1));

	}
	else
	{
		printf("HATA: Dosya Açýlamýyor.");
	}
	
}































