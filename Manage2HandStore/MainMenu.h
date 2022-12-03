#pragma once
#include "HandleFile.h"
#include "ImportProductMenu.h"
#include "SellProductMenu.h"

string selection[4] = { "MENU", "Exit this program", "Import product", "Sell product" };

void MainMenu(ProductList& l, ProductList& cart, InvoiceList& il, ifstream& fileDataIn, ofstream& fileDataOut) {
	CreateList(l); // Khoi tao danh sach san pham
	fileDataIn.open("DATA.txt", ios::in);
	ReadFileListProduct(fileDataIn, l);
	fileDataIn.close();

	CreateListInvoice(il);// Khoi tao danh sach hoa don
	fileDataIn.open("INVOICEHISTORY.txt", ios::in);
	ReadFileListInvoice(fileDataIn, il);
	fileDataIn.close();


	//Main menu
	int awn = -1;
	bool ctn = true;
	while (ctn) {
		system("cls");
		awn = PrintMenu(selection, 4, 30);
		switch (awn) {
		case 0: {
			WriteFileListProduct(fileDataOut, l);
			system("cls");
			cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+--------------------------------------------+";
			cout << "\n\t\t\t\t\t\t\t\t|   YOU HAVE EXITED THIS PROGRAM. THANKS <3  |";
			cout << "\n\t\t\t\t\t\t\t\t+--------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\n";
			ctn = false;
			break;
		}
		case 1: {
			ImportProductMenu(l, il, fileDataIn, fileDataOut);
			break;
		}
		case 2: {
			SellProductMenu(l, cart, il, fileDataIn, fileDataOut);
			break;
		}
		}
	}
	//Mo file de ghi du lieu sau khi ket thuc chuong trinh
	fileDataOut.open("DATA.txt", ios::out);
	WriteFileListProduct(fileDataOut, l);
	fileDataOut.close();

	//Mo file hoa don de ghi lich su hoa don sau khi ket thuc chuong trinh
	fileDataOut.open("INVOICEHISTORY.txt", ios::out);
	WriteFileListInvoice(fileDataOut, il);
	fileDataOut.close();

	FreeData(l);
	FreeData(cart);
	FreeData(il);
}