#pragma once
#include "HandleFile.h"
#include "ImportProductMenu.h"
#include "SellProductMenu.h"

string selection[4] = { "MENU", "Exit this program", "Import product", "Sell product" };

void MainMenu(ProductList& l, ProductList& cart, ifstream& fileDataIn, ofstream& fileDataOut) {
	//Khoi tao va import data tu file vao list
	CreateList(l);
	CreateList(cart);
	fileDataIn.open("DATA.txt", ios::in);
	ReadFileListProduct(fileDataIn, l);
	fileDataIn.close();
	//Mo file de ghi du lieu sau khi ket thuc chuong trinh
	fileDataOut.open("DATA2.txt", ios::out);
	//Main menu
	int awn = -1;
	while (true) {
		system("cls");
		awn = PrintMenu(selection, 4, 30);
		switch (awn) {
		case 0: {
			WriteFileListProduct(fileDataOut, l);
			system("cls");
			cout << "\n\n\n\n\n\t\t\t+--------------------------------------------+";
			cout << "\n\t\t\t|   YOU HAVE EXITED THIS PROGRAM. THANKS <3  |";
			cout << "\n\t\t\t+--------------------------------------------+\n\n\n\n\n\n\n\n\n\n\n\n";
			return;
		}
		case 1: {
			ImportProductMenu(l, fileDataIn, fileDataOut);
			break;
		}
		case 2: {
			SellProductMenu(l, cart, fileDataIn, fileDataOut);
			break;
		}
		}
	}
	//WriteFileListProduct(fileDataOut, l);
	fileDataOut.close();


	FreeData(l);
	FreeData(cart);
}