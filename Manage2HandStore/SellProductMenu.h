#include "Function.h"
#include <windows.h>
string mainSellSelection[] = { 
			"SELL PRODUCT MENU", 
			"Return", 
			"Show all product",
			"Find product",
			"Add product to cart",
			"Delete product from cart",
			"Delete all product in cart",
			"Sort cart",
			"Check cart",
			"Print invoice"},
		findSelection[] = {
			"TYPE OF FIND",
			"Return",
			"Shirt",
			"Trousers",
			"Handbag",
			"Footwear",
			"Others",
			"Men",
			"Women",
			"Key word (id, name, brand)",
			"Price"},
		storeInfor[] = {
			"Store Name",
			"Store Description",
			"Address: Store Address",
			"Phone: Store Contact",
			"Cashier: Staff Name", 
			"5.0"};
void FindProduct(ProductList l);
void SellProduct(ProductList& l, ProductList& cart, string type = "Add");
void PrintInvoice(ProductList& cart, int countProduct, InvoiceList& il, string* inFor, int size = 60);
void ReturnCart(ProductList& cart, ProductList& l);


/*--------------------------------------------------------------------------------*/

void SellProductMenu(ProductList& l, ProductList& cart, InvoiceList &il, ifstream& fileDataIn, ofstream& fileDataOut) {
	CreateList(cart); // Khoi tao danh sach gio hang

	int awn = -1;
	bool ctn = true;

	while (ctn) {
		system("cls");
		awn = PrintMenu(mainSellSelection, 10, 32);
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
			break;
		}
		case 4: {
			SellProduct(cart, l, "Delete");
			break;
		}
		case 5: {
			ReturnCart(cart, l);
			break;
		}
		case 6: {
			bool tmp = SortMenu(cart);
			system("cls");
			OutputFormedList(cart, true, "CART");
			if (tmp) {
				cout << "\n\t\t\t\t\tCart after successfully sorted.\n";
			}
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			OutputFormedList(cart, false, "CART");
			system("pause");
			break;
		}
		case 8: {
			system("cls");
			int i = 0;
			for (NodeProduct* p = cart.head; p != NULL; p = p->next) {
				i++;
			}
			PrintInvoice(cart, i, il, storeInfor, 60);
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
		awn = PrintMenu(findSelection, 11, 33);
		switch (awn) {
		case 0: {
			ctn = false;
			return;
		}
		case 1: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 1)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 2: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 2)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 3: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 3)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 4: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 4)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 5: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 5)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 6: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 0, "Men")) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 7: {
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchType(p, 0, "Women")) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 8: {
			string findString;
			cout << "\t\t\t\t\tEnter infomation of product you want to find (id, name, brand): "; getline(cin, findString);
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchSearchKeyWord(p, findString)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		case 9: {
			string sfrom, sto;
			int from, to;
			cout << "\t\t\t\t\tPrice range to find from: "; getline(cin, sfrom);
			from = CheckSelection(sfrom, 0, 0, true);
			do {
				cout << "\t\t\t\t\tTo: "; getline(cin, sto);
				to = CheckSelection(sto, 0, 0, true);
				if (to < from) {
					cout << "\t\t\t\t\tYour range is invalid(from must less than to).\n\t\t\t\t\t Please enter again.\n";
				}
			} while (to < from);
			for (NodeProduct* p = l.head; p != NULL; p = p->next) {
				if (MatchSearchPrice(p, from, to)) {
					NodeProduct* k = CreateNode(p->data);
					AddTail(result, k);
				}
			}
			break;
		}
		}
		system("cls");
		if (result.head == NULL) {
			cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+----------------------+" << endl;
			cout << "\t\t\t\t\t\t\t\t|   NO PRODUCT MATCH   |" << endl;
			cout << "\t\t\t\t\t\t\t\t+----------------------+\n\n\n\n\n\n" << endl;
		}
		else {
			OutputFormedList(result, false, "MATCH PRODUCT");
		}
		if (Continue("\t\t\t\t\tDo you want to continue find another product")) {
			ctn = true;
		}
		else {
			ctn = false;
			FreeData(result);
		}
	}
}

void SellProduct(ProductList& from, ProductList& to, string type) {
	system("cls");
	//thoat neu list rong
	if (from.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+----------------------+" << endl;
		cout << "\t\t\t\t\t\t\t\t|  NO PRODUCT IN HERE  |" << endl;
		cout << "\t\t\t\t\t\t\t\t+----------------------+\n\n\n\n\n\n" << endl;
		system("pause");
		return;
	}
	string log[3] = { "\n\t\t\t\t\tEnter ID of product to buy: ", "\n\t\t\t\t\tHow many you want to buy: ", "\t\t\t\t\tAdd successfully. Do you want to continue shopping" };
	bool ctn = true, isAdd = true;
	if (type != "Add") {
		isAdd = false;
		log[0] = "\n\t\t\t\t\tEnter ID of product to remove: ";
		log[1] = "\n\t\t\t\t\tHow many you want to remove: ";
		log[2] = "\t\t\t\t\tRemove successfully. Do you want to remove another product";
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
		cout << "\t\t\t\t\t" << log[0]; getline(cin, id);
		if (ExistInList(from, id, p)) {
			do {
				cout << "\t\t\t\t\t" << log[1]; getline(cin, awn);
				int quantity = CheckSelection(awn, 0, 0, true);
				if (p->data.IsEnoughQuantity(quantity)) {
					NodeProduct* k = TranferQuantity(from, p, quantity);
					AddToList(to, k);
					ctn = false;
				}
				else {
					cout << "\t\t\t\t\tQuantity of this product is not enough.\n\t\t\t\t\t Please enter again.\n";
				}
			} while (ctn);
		}
		else {
			if (!Continue("\t\t\t\t\tThis ID not exist in list.\n\t\t\t\t\tDo you want to input again")) {
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

void PrintInvoice(ProductList& cart, int countProduct, InvoiceList &il, string *inFor, int size) {
	if (cart.head == NULL) {
		OutputFormedList(cart, false, "CART");
		system("pause");
		return;
	}
	else {
		string noInvoice = "No: PBH", discription = "";
		noInvoice.append(MakeNoId(il, 3, 6));
		int total = 0;
		time_t cur = time(0);	//lay date
		tm* ltm = localtime(&cur);
		string o = "0",
			date = "Date: ",
			time = "Time: ";
		;
		date.append((ltm->tm_mday >= 10) ? to_string(ltm->tm_mday) : o.substr(0, 1).append(to_string(ltm->tm_mday)))
			.append("/")
			.append((ltm->tm_mon + 1 >= 10) ? to_string(ltm->tm_mon + 1) : o.substr(0, 1).append(to_string(ltm->tm_mon + 1)))
			.append("/")
			.append(to_string(1900 + ltm->tm_year));
		time.append((ltm->tm_hour >= 10) ? to_string(ltm->tm_hour ) : o.substr(0, 1).append(to_string(ltm->tm_hour)))
			.append(":")
			.append((ltm->tm_min >= 10) ? to_string(ltm->tm_min) : o.substr(0, 1).append(to_string(ltm->tm_min)))
			.append(":")
			.append((ltm->tm_sec >= 10) ? to_string(ltm->tm_sec) : o.substr(0, 1).append((to_string(ltm->tm_sec))))
			.append("  ");
		discription.append(storeInfor[4].substr(9)).append("-").append(date.substr(6)).append("-").append(time.substr(6));
		//khoi tao hoa don
		NodeInvoice* invoice = CreateNodeInvoice(noInvoice.substr(4),discription, countProduct, cart);
		//in canh tren
		cout << "\n\t\t\t\t\t\t\t";
		for (int i = 0; i < size; i++) {
			if (i == 0 || i == size - 1) {
				cout << "+";
			}
			else {
				cout << "-";
			}
		}
		cout << endl;
		//in thong tin cua hang
		PrintLineInvoice(size, inFor[0], "", "center");//in ten cua hang
		PrintLineInvoice(size, inFor[1], "", "center");	//in mieu ta cua hang
		PrintLineInvoice(size, inFor[2], "", "left");	//in dia chi
		PrintLineInvoice(size, inFor[3], "", "left");	//in sdt
		PrintLineInvoice(size, "_____________________________________", "", "center");
		PrintLineInvoice(size, "INVOICE", "", "center");
		PrintLineInvoice(size, noInvoice, date);	//in ma hoa don va ngay
		PrintLineInvoice(size, inFor[4], time);	//in ten nhan vien va gio

		//in tieu de
		PrintLineInvoice(size, "________________________________________________________", "", "center");
		cout << "\t\t\t\t\t\t\t|   " << left << setw(15) << "QUANTITY" << right << setw(17) << "PRICE" << right << setw(size - 15 - 16 - 4) << "TOTAL   |\n";
		PrintLineInvoice(size, "________________________________________________________", "", "center");
		PrintLineInvoice(size, "", "", "center");


		// in san pham
		for (NodeProduct* p = cart.head; p != NULL; p = p->next) {
			PrintLineProduct(size, p, total);
		}
		// in thanh toan
		string discount = "                         DISCOUNT";
		float discountRate = stof(inFor[5]);
		PrintLineInvoice(size, "", "", "center");
		PrintLineInvoice(size, "                         TOTAL: ", to_string(total));
		PrintLineInvoice(size, discount.append("(").append(inFor[5]).append("%): "), to_string((int)(total * discountRate / 100)));
		PrintLineInvoice(size, "                         TOTAL PAYMENT: ", to_string((int)(total - total * discountRate / 100)));
		//in footer
		PrintLineInvoice(size, "________________________________________________________", "", "center");
		PrintLineInvoice(size, "Thank you and see you again <3", "", "center");
		//in canh duoi
		cout << "\t\t\t\t\t\t\t";
		for (int i = 0; i < size; i++) {
			if (i == 0 || i == size - 1) {
				cout << "+";
			}
			else {
				cout << "-";
			}
		}

		// kiem tra khach hang co chac chan mua hay khong

		if (Continue("\n\t\t\t\t\t\tAre you sure to buy this order or change your cart")) {
			FreeData(cart);
			AddTailInvoiceList(il, invoice);
			system("cls");
			cout << "\n\n\n\n\n\t\t\t\t\t\t+-----------------------------------+";
			cout << "\n\t\t\t\t\t\t|   SUCCESSFUL PURCHASE. THANKS <3  |";
			cout << "\n\t\t\t\t\t\t+-----------------------------------+\n\n\n\n\n\n\n\n\n\n\n\n";
			system("pause");
			return;
		}
		else {
			return;
		}
	}
}

void ReturnCart(ProductList& cart, ProductList& l) {
	if (cart.head == NULL) {
		system("cls");
		cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+----------------------+" << endl;
		cout << "		   \t\t\t\t\t\t|  NO PRODUCT IN HERE  |" << endl;
		cout << "		   \t\t\t\t\t\t+----------------------+\n\n\n\n\n\n" << endl;
		system("pause");
		return;
	}
	NodeProduct* k = NULL;
	for (NodeProduct* p = cart.head; p != NULL; p = k) {
		k = p->next;
		NodeProduct* tmp = TranferQuantity(cart, p, p->data.getQuantity());
		AddToList(l, tmp);
	}
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+----------------------------+" << endl;
	cout <<           "\t\t\t\t\t\t\t\t|  RETURN CART SUCCESSFULLY  |" << endl;
	cout <<			  "\t\t\t\t\t\t\t\t+----------------------------+\n\n\n\n\n\n" << endl;
	system("pause");
	return;
	delete k;
}