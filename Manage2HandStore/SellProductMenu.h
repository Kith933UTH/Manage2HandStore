#include "Function.h"
#include <windows.h>
string mainSellSelection[] = { 
			"SELL PRODUCT MENU", 
			"Return", 
			"Show all product",
			"Find product",
			"Add product to cart",
			"Delete product from cart",
			"Check cart",
			"Print invoice" },
		findSelection[] = {
			"TYPE OF FIND",
			"Return",
			"Key word (id, name, brand)",
			"Price"},
		storeInfor[] = {
			"Store Name",
			"Store Description",
			"Address: Store Address",
			"Phone: Store Contact",
			"Cashier: Staff Name" };
void FindProduct(ProductList l);
void SellProduct(ProductList& l, ProductList& cart, string type = "Add");
void PrintInvoice(ProductList cart, string* inFor, int size = 60);


/*--------------------------------------------------------------------------------*/

void SellProductMenu(ProductList& l, ProductList& cart, ifstream& fileDataIn, ofstream& fileDataOut) {
	int awn = -1;
	bool ctn = true;

	while (ctn) {
		system("cls");
		awn = PrintMenu(mainSellSelection, 8, 32);
		switch (awn) {
		case 0: {
			ctn = false;
			break;
		}
		case 1: {
			system("cls");
			OutputFormedList(l);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			FindProduct(l);
			break;
		}
		case 3: {
			system("cls");
			SellProduct(l, cart);
			system("pause");
			break;
		}
		case 4: {
			SellProduct(cart, l, "Delete");
			break;
		}
		case 5: {
			system("cls");
			OutputFormedList(cart, false, "CART");
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			PrintInvoice(l, storeInfor, 60);
			system("pause");
			break;
		}
		}
	}
}


void FindProduct(ProductList l) {
	int awn = -1;
	bool ctn = true;
	ProductList result;
	CreateList(result);

	while (ctn) {
		system("cls");
		awn = PrintMenu(findSelection, 4, 33);
		switch (awn) {
		case 0: {
			ctn = false;
			return;
		}
		case 1: {
			string findString;
			cout << "Enter infomation of product you want to find (id, name, brand): "; getline(cin, findString);
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchSearchKeyWord(p, findString)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			ctn = false;
			break;
		}
		case 2: {
			string sfrom, sto;
			int from, to;
			cout << "Price range to find from: "; getline(cin, sfrom);
			from = CheckSelection(sfrom, 0, 0, true);
			do {
				cout << "To: "; getline(cin, sto);
				to = CheckSelection(sto, 0, 0, true);
				if (to < from) {
					cout << "Your range is invalid(from must less than to).\n Please enter again.\n";
				}
			} while (to < from);
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchSearchPrice(p, from, to)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			ctn = false;
			break;
		}
		}
	
	}
	system("cls");
	if (result.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t+----------------------+" << endl;
		cout << "\t\t\t|   NO PRODUCT MATCH   |" << endl;
		cout << "\t\t\t+----------------------+\n\n\n\n\n\n" << endl;
	}
	else {
		OutputFormedList(result, false, "MATCH PRODUCT");
	}
	system("pause");
}

void SellProduct(ProductList& from, ProductList& to, string type) {
	system("cls");
	//thoat neu lít rong
	if (from.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t+----------------------+" << endl;
		cout << "\t\t\t|  NO PRODUCT IN HERE  |" << endl;
		cout << "\t\t\t+----------------------+\n\n\n\n\n\n" << endl;
		system("pause");
		return;
	}

	string log[3] = { "\nEnter ID of product to buy: ", "\nHow many you want to buy: ", "Add successfully. Do you want to continue shopping" };
	bool ctn = true, isAdd = true;
	if (type != "Add") {
		isAdd = false;
		log[0] = "\nEnter ID of product to remove: ";
		log[1] = "\nHow many you want to remove: ";
		log[2] = "Remove successfully. Do you want to remove another product";
	};

	string id, awn;
	NodeProduct* p = new NodeProduct;
	//in danh sach
	if (isAdd) { 
		OutputFormedList(from);
	}
	else {
		OutputFormedList(from, false, "CART");
	}

	do {
		cout << log[1]; getline(cin, id);
		if (ExistInList(from, id, p)) {
			do {
				cout << log[1]; getline(cin, awn);
				int quantity = CheckSelection(awn, 0, 0, true);
				if (p->data.IsEnoughQuantity(quantity)) {
					NodeProduct* k = TranferQuantity(from, p, quantity);
					AddToList(to, k);
					ctn = false;
				}
				else {
					cout << "Quantity of this product is not enough.\n Please enter again.\n";
				}
			} while (ctn);
		}
		else {
			if (!Continue("This ID not exist in list.\n Do you want to input again")) {
				delete p;
				return;
			}
		}
	} while (ctn);

	system("cls");
	if (isAdd) {
		OutputFormedList(to, false, "CART");
	}
	else {
		OutputFormedList(from, false, "CART");
	}
	if (Continue(log[2])) {
		if (type == "Add") {
			SellProduct(from, to);
		}
		else {
			SellProduct(from, to, type);
		}
	}
	else {
		return;
	}
}

void PrintInvoice(ProductList cart, string *inFor, int size) {
	if (cart.head == NULL) {
		OutputFormedList(cart, false, "CART");
		return;
	}
	//set mau chu
	system("color 7");
	//lay date
	time_t cur = time(0);
	tm* ltm = localtime(&cur);
	string o = "0";
	string date = "Date: ";
	date.append((ltm->tm_mday >= 10) ? to_string(ltm->tm_mday) : o.append(to_string(ltm->tm_mday)))
		.append("/")
		.append((ltm->tm_mon + 1 >= 10) ? to_string(ltm->tm_mon + 1) : o.append(to_string(ltm->tm_mon + 1)))
		.append("/")
		.append(to_string(1900 + ltm->tm_year));
	string time = "Time: ";
	time.append((ltm->tm_hour >= 10) ? to_string(ltm->tm_hour) : o.append(to_string(ltm->tm_hour)))
		.append(":")
		.append((ltm->tm_min >= 10) ? to_string(ltm->tm_min) : o.append(to_string(ltm->tm_min)))
		.append(":")
		.append((ltm->tm_sec >= 10) ? to_string(ltm->tm_sec) : o.append(to_string(ltm->tm_sec)));
	int innerSize = size - 2;
	//in canh tren
	cout << "\n\t\t";
	for (int i = 0; i < size; i++) {
		if (i == 0 || i == size - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << endl;
	//in ten cua hang
	PrintLineInvoice(size, inFor[0], "", "center");
	//in mieu ta cua hang
	PrintLineInvoice(size, inFor[1], "", "center");
	//in dia chi
	PrintLineInvoice(size, inFor[2], "", "left");
	//in sdt
	PrintLineInvoice(size, inFor[3], "", "left");

	PrintLineInvoice(size, "_____________________________________", "", "center");

	PrintLineInvoice(size, "INVOICE", "", "center");

	string MPBH = "NO: PBH100001";
	//in ma hoa don va ngay
	PrintLineInvoice(size, MPBH, date);
	//in ten nhan vien va gio
	PrintLineInvoice(size, inFor[4], time);
	PrintLineInvoice(size, "________________________________________________________", "", "center");
	cout << "\t\t|   " << left << setw(15) << "QUANTITY" << right << setw(17) << "PRICE" << right << setw(size - 15 - 16 - 4) << "TOTAL   |\n";
	PrintLineInvoice(size, "________________________________________________________", "", "center");
	PrintLineInvoice(size, "", "", "center");


	int total = 0;
	// in san pham
	for (NodeProduct* p = cart.head; p != NULL; p = p->next) {
		PrintLineProduct(size, p, total);
	}
	PrintLineInvoice(size, "", "", "center");
	string stotal = "TOTAL: ";
	PrintLineInvoice(size, stotal.append(to_string(total)), "", "right");
	

	PrintLineInvoice(size, "________________________________________________________", "", "center");
	PrintLineInvoice(size, "Thank you and see you again <3", "", "center");

	cout << "\t\t";
	for (int i = 0; i < size; i++) {
		if (i == 0 || i == size - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << "\n\n";
}