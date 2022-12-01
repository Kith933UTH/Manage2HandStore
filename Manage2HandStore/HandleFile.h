#pragma once
#include "Product2HList.h"

bool isEmpty(ifstream& pFile) {
	return pFile.peek() == ifstream::traits_type::eof();
}

void ReadFile1Product(ifstream& filein, Product2H& p) {
	int ntemp = 0;
	string ptemp = "";
	getline(filein, ptemp, ','); p.setId(ptemp);
	getline(filein, ptemp, ','); p.setName(ptemp);
	getline(filein, ptemp, ','); p.setBrand(ptemp);

	filein >> ntemp; p.setImportPrice(ntemp);
	p.setPrice((int)(ntemp * PROFIT));
	filein >> ntemp; p.setQuantity(ntemp);
	getline(filein, ptemp);
}

void ReadFileListProduct(ifstream& filein, ProductList& l) {
	if (!filein) {
		cout << "\nCannot find data file.";
		return;
	}
	if (isEmpty(filein)) {
		return;
	}
	while (!filein.eof()) {
		Product2H p;
		ReadFile1Product(filein, p);
		AddTail(l, CreateNode(p));
	}
}

void WriteFile1Product(ofstream& fileout, Product2H p) {
	fileout << p.getId() << ","
		<< p.getName() << ","
		<< p.getBrand() << ", "
		<< p.getImportPrice() << " "
		<< p.getQuantity();
}

void WriteFileListProduct(ofstream& fileout, ProductList l) {
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->next == NULL) {
			WriteFile1Product(fileout, p->data);
		}
		else {
			WriteFile1Product(fileout, p->data);
			fileout << endl;
		}
	}
}