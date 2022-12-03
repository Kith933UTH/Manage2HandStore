#pragma once
#include "Product2HList.h"
#include "InvoiceList.h"

bool isEmpty(ifstream& pFile) {
	return pFile.peek() == ifstream::traits_type::eof();
}

//doc file san pham
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

//ghi file san pham
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

//doc file hoa don
void ReadFile1Invoice(ifstream& filein, NodeInvoice*& k) {
	int ntemp = 0;
	string id, spaceTemp;
	string description;
	ProductList l;
	CreateList(l);

	getline(filein, id, ',');
	getline(filein, description, ',');
	filein >> ntemp;
	getline(filein, spaceTemp);

	for (int i = 0; i < ntemp; i++) {
		Product2H p;
		ReadFile1Product(filein, p);
		AddTail(l, CreateNode(p));
	}

	k = CreateNodeInvoice(id, description, ntemp, l);
	getline(filein, spaceTemp);
}

void ReadFileListInvoice(ifstream& filein, InvoiceList &l) {
	if (!filein) {
		cout << "\nCannot find data file.";
		return;
	}
	if (isEmpty(filein)) {
		return;
	}
	while (!filein.eof()) {
		NodeInvoice* k = new NodeInvoice();
		ReadFile1Invoice(filein, k);
		AddTailInvoiceList(l, k);
	}
}

//ghi file hoa don
void WriteFile1Invoice(ofstream& fileout, NodeInvoice *i) {
	fileout << i->id << ", " << i->description << ", " << i->count << endl;
	WriteFileListProduct(fileout, i->data);
	fileout << endl;
}

void WriteFileListInvoice(ofstream& fileout, InvoiceList il) {
	for (NodeInvoice* i = il.head; i != NULL; i = i->next) {
		if (i->next == NULL) {
			WriteFile1Invoice(fileout, i);
		}
		else {
			WriteFile1Invoice(fileout, i);
			fileout << endl;
		}
	}
}