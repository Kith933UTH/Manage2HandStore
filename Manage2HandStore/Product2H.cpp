#include "Product2H.h"

Product2H::Product2H(
	string id,
	string name,
	string brand,
	int importPrice,
	int quantity
) {
	this->id = id;
	this->name = name;
	this->brand = brand;
	this->importPrice = importPrice;
	this->quantity = quantity;
	this->price = (int)(importPrice * PROFIT);
};
Product2H::~Product2H(void) {

};

string Product2H::getId() const {
	return this->id;
};
string Product2H::getName() const {
	return this->name;
};
string Product2H::getBrand() const {
	return this->brand;
};
int Product2H::getImportPrice() const {
	return this->importPrice;
};
int Product2H::getQuantity() const {
	return this->quantity;
};
int Product2H::getPrice() const {
	return this->price;
};
int Product2H::getTotal() const {
	return this->price * this->quantity;
}

void Product2H::setId(string id) {
	this->id = id;
};
void Product2H::setName(string name) {
	this->name = name;
};
void Product2H::setBrand(string brand) {
	this->brand = brand;
};
void Product2H::setImportPrice(int importPrice) {
	this->importPrice = importPrice;
};
void Product2H::setQuantity(int quantity) {
	this->quantity = quantity;
};
void Product2H::setPrice(int price) {
	this->price = price;
};

bool Product2H::IsEnoughQuantity(int quantityToTake) {
	return this->getQuantity() >= quantityToTake;
}


ostream& operator<<(ostream& out, const Product2H& p) {
	out << "\t|" << left << setw(12) << p.id
		<< "|  " << left << setw(20) << p.name
		<< "|  " << left << setw(15) << p.brand
		<< "|" << right << setw(9)  << p.quantity
		<< "  |" << right << setw(13)  << p.price << "  " << "|" << endl;
	return out;
};
istream& operator>>(istream& in, Product2H& p) {
	string temp;
	cout << "\n\t\t\tEnter name: "; getline(in, temp); p.setName(temp);
	cout << "\n\t\t\tEnter brand: "; getline(in, temp); p.setBrand(temp);
	cout << "\n\t\t\tEnter import price: "; getline(in, temp); p.setImportPrice(CheckSelection(temp, 0, 0, true));
	cout << "\n\t\t\tEnter quantity: "; getline(in, temp); p.setQuantity(CheckSelection(temp, 0, 0, true));
	p.setPrice((int)(p.importPrice * PROFIT));
	return in;
};


//ham kiem tra lua chon
int CheckSelection(string& sawn, int from, int to, bool isCheckPositiveInteger) {
	int awn = -1;
	bool inRange = false;
	if (isCheckPositiveInteger) {
		do {
			if (atoi(sawn.c_str()) <= 0) {
				cout << "\t\t\t\t\tIt isn't a good number!\n\t\t\t\t\tPlease choose again: ";
				getline(cin, sawn);
				inRange = false;
			}
			else {
				awn = atoi(sawn.c_str());
				return awn;
			}
		} while (!inRange);
	}
	else {
		do {
			for (int i = from; i <= to; i++) {
				if (sawn == to_string(i)) {
					inRange = true;
				}
			}
			if (!inRange) {
				cout << "\t\t\t\t\tYour selection is not exist.\n\t\t\t\t\tPlease choose again: ";
				getline(cin, sawn);
				awn = -1;
			}
			else {
				awn = atoi(sawn.c_str());
			}
		} while (awn < from || awn > to);
	}
	return awn;
}

