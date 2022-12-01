#pragma once
#include <iostream> //Thu vien nhap xuat co ban
#include <fstream> //lam viec voi file
#include <string> //lam viec voi chuoi
#include <iomanip> //setw()
#include <ctime> //time
#include <cmath>
#include <conio.h>

#define PROFIT 1.2
#pragma warning(disable : 4996)
using namespace std;


class Product2H
{
private:
	string id;
	string name;
	string brand;
	int importPrice;
	int quantity;
	int price;
public:
	Product2H(
		string id = "",
		string name = "",
		string brand = "",
		int importPrice = 0,
		int quantity = 0
	);
	~Product2H(void);

	string getId() const;
	string getName() const;
	string getBrand() const;
	int getImportPrice() const;
	int getQuantity() const;
	int getPrice() const;
	int getTotal() const;

	void setId(string id);
	void setName(string name);
	void setBrand(string brand);
	void setImportPrice(int importPrice);
	void setQuantity(int quantity);
	void setPrice(int importPrice);

	bool IsEnoughQuantity(int quantityToTake);

	friend ostream& operator<<(ostream& out,const Product2H &p);
	friend istream& operator>>(istream& in, Product2H& p);
};

int CheckSelection(string& sawn, int from = 0, int to = 0, bool isCheckPositiveInteger = false);