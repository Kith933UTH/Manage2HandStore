#pragma once
#include "Product2HList.h" 

// ham chuyen string thanh chu thuong
string ToLower(string str) {
	for (auto& c : str) {
		c = tolower(c);
	}
	return str;
}

//ham thoa theo loai hang
bool MatchType(NodeProduct* p, int type, string gender = "") {
	int indexToSearch = 0;
	string valueToSearch = to_string(type);
	if (gender == "Men" || gender == "Women") {
		indexToSearch = 1;
		valueToSearch = gender == "Men" ? to_string(1) : to_string(0);
	}
	return (p->data.getId().substr(indexToSearch, 1) == valueToSearch);
}

//ham thoa tim kiem tu khoa
bool MatchSearchKeyWord(NodeProduct* p, string findString) {
	findString = ToLower(findString);
	size_t result = ToLower(p->data.getId()).find(findString);
	size_t ndresult = ToLower(p->data.getName()).find(findString);
	size_t rdresult = ToLower(p->data.getBrand()).find(findString);
	return (result != string::npos || ndresult != string::npos || rdresult != string::npos);
}

//ham thoa tim kiem theo khoang gia
bool MatchSearchPrice(NodeProduct* p, int from, int to) {
	return (p->data.getPrice() >= from && p->data.getPrice() <= to);
}

//ham tach so luong san pham
NodeProduct* TranferQuantity(ProductList& l, NodeProduct*& from, int quantity) {
	NodeProduct* to = CreateNode(from->data); to->data.setQuantity(0);
	if (from->data.IsEnoughQuantity(quantity)) {
		to->data.setQuantity(quantity);
		from->data.setQuantity(from->data.getQuantity() - quantity);
	}
	else {
		return NULL;
	}
	if (from->data.getQuantity() <= 0) {
		DeleteById(l, from->data.getId());
	}
	return to;
}

//ham in menu tra ve lua chon
int PrintMenu(string attr[], int nAttr, int lenghtMenu, int printFrom = 0, string tab = "") {
	//in header
	int titleLen = (int)((lenghtMenu - attr[0].length()) / 2);
	if ((lenghtMenu - attr[0].length()) % 2 != 0) {
		lenghtMenu++;
		titleLen++;
	}
	cout << "\n\t\t\t\t\t\t\t\t" << tab;
	for (int i = 0; i < titleLen; i++) {
		if (i == 0 || i == titleLen - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << attr[0];
	for (int i = 0; i < titleLen; i++) {
		if (i == 0 || i == titleLen - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}

	// in body
	if (printFrom == 0) {
		for (int i = 1; i < nAttr; i++) {
			if (i - 1 < 10) {
				cout << "\n\t\t\t\t\t\t\t\t" << tab << "| " << i - 1 << ". " << left << setw(lenghtMenu - 6) << attr[i].append(".") << "|";
			}
			else {
				cout << "\n\t\t\t\t\t\t\t\t" << tab << "| " << i - 1 << ". " << left << setw(lenghtMenu - 7) << attr[i].append(".") << "|";
			}
			attr[i] = attr[i].substr(0, attr[i].length() - 1);
		}
	}
	else {
		for (int i = 1; i < nAttr; i++) {
			if (i < 10) {
				cout << "\n\t\t\t\t\t\t\t\t" << tab << "| "  << i << ". " << left << setw(lenghtMenu - 6) << attr[i].append(".") << "|";
			}
			else {
				cout << "\n\t\t\t\t\t\t\t\t" << tab << "| " << i << ". " << left << setw(lenghtMenu - 7) << attr[i].append(".") << "|";
			}
			attr[i] = attr[i].substr(0, attr[i].length() - 1);
		}
	}

	// in footer
	cout << "\n\t\t\t\t\t\t\t\t" << tab;
	for (int i = 0; i < lenghtMenu; i++) {
		if (i == 0 || i == lenghtMenu - 1) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	string sawn;
	cout << "\n\t\t\t\t\t\t" << tab << "Enter your selection : "; getline(cin, sawn);
	int awn = (printFrom == 0) ? CheckSelection(sawn, 0, nAttr - 2) : CheckSelection(sawn, 1, nAttr - 1);
	return (printFrom == 0) ? awn : (awn - 1);
}

//ham in danh sach
void OutputFormedList(ProductList l, bool allInfor = false, string title = "PRODUCT") {
	string attr[6] = { "ID", "NAME", "BRAND", "IMPORT PRICE", "REMAINING", "PRICE" };
	if (title == "CART") attr[4] = "QUANTITY";
	if (l.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t+-------------------------+" << endl;
		if (title == "CART") {
			cout << "\t\t\t\t\t\t\t\t|   " << title << " HAS NO PRODUCT   |" << endl;
		}
		else {
			cout << "\t\t\t\t\t\t\t\t|   LIST HAS NO PRODUCT   |" << endl;
		}
		cout << "\t\t\t\t\t\t\t\t+-------------------------+\n\n\n\n\n\n" << endl;
	}
	else if (!allInfor) {
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t" << title << " LIST\n";
		cout << "\t\t\t\t\t\t+---------------------------------------------------------------------------------+" << endl;
		cout << "\t\t\t\t\t\t|" << left << setw(12) << attr[0]
			<< "|  " << left << setw(20) << attr[1]
			<< "|  " << left << setw(15) << attr[2]
			<< "| " << left << setw(10) << attr[4]
			<< "|  " << left << setw(13) << attr[5] << "|" << endl;
		cout << "\t\t\t\t\t\t+---------------------------------------------------------------------------------+" << endl;
		for (NodeProduct* p = l.head; p != NULL; p = p->next) {
			cout << "\t\t\t\t\t" << p->data;
		}
		cout << "\t\t\t\t\t\t+---------------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "\n\n\t\t\t\t\t\t\t\t\t" << title << " LIST\n";
		cout << "\t\t\t\t+-----------------------------------------------------------------------------------------------+" << endl;
		cout << "\t\t\t\t|" << left << setw(12) << attr[0]
			<< "|  " << left << setw(20) << attr[1]
			<< "|  " << left << setw(15) << attr[2]
			<< "| " << left << setw(13) << attr[3]
			<< "| " << left << setw(10) << attr[4]
			<< "|  " << left << setw(12) << attr[5] << "|" << endl;
		cout << "\t\t\t\t+-----------------------------------------------------------------------------------------------+" << endl;
		for (NodeProduct* p = l.head; p != NULL; p = p->next) {
			cout << "\t\t\t\t|" << left << setw(12) << p->data.getId()
				<< "|  " << left << setw(20) << p->data.getName()
				<< "|  " << left << setw(15) << p->data.getBrand()
				<< "|" << right << setw(12) << p->data.getImportPrice()
				<< "  |" << right << setw(9) << p->data.getQuantity()
				<< "  |" << right << setw(12) << p->data.getPrice() << "  |" << endl;
		}
		cout << "\t\t\t\t+-----------------------------------------------------------------------------------------------+" << endl;
	}
}

//ham kiem tra ton tai trong list
bool ExistInList(ProductList l, string id, NodeProduct*& k) {
	for (NodeProduct* p = l.head; p != NULL; p = p->next) {
		if (p->data.getId() == id) {
			k = p;
			return true;
		}
	}
	k = NULL;
	return false;
}

//ham kiem tra khach hang co muon tiep tuc hay khong
bool Continue(string log) {
	string awn;
	cout << "\n" << log << "(yes or no)? ";
	getline(cin, awn);
	if (ToLower(awn).substr(0,1) == "y" || ToLower(awn) == "yes") {
		return true;
	}
	else {
		return false;
	}
}

//ham in hang thong tin hoa don
void PrintLineInvoice(int size, string s = "", string s2 = "", string type = "left") {
	int spaceLen = (int)floor(((size - s.length())) - 4);
	if (s2 != "") {
		spaceLen = (int)floor(((size - s.length() - s2.length())) - 4);
		cout << "\t\t\t\t\t\t\t| ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s2;
		cout << " |\n";
		return;
	}
	if (spaceLen + s.length() + 4 != size) s.append(" ");
	if (type == "center") {
		spaceLen = (int)floor(((size - s.length()) / 2) - 1);
		if (spaceLen * 2 + s.length() + 2 != size) {
			s.append(" ");
		};
		cout << "\t\t\t\t\t\t\t|";
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << "|\n";
	}
	else if (type == "right") {
		cout << "\t\t\t\t\t\t\t| ";
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << s;
		cout << " |\n";
	}
	else {
		cout << "\t\t\t\t\t\t\t| ";
		cout << s;
		for (int i = 0; i < spaceLen; i++) cout << " ";
		cout << " |\n";
	}

}

//ham in hang san pham
void PrintLineProduct(int size, NodeProduct* p, int& total) {
	PrintLineInvoice(size, p->data.getName().append("(").append(p->data.getId()).append(")"), "", "left");
	cout << "\t\t\t\t\t\t\t|     " << left << setw(15) << p->data.getQuantity() << right << setw(15) << p->data.getPrice() << right << setw(size- 15 - 15 - 8) << p->data.getTotal();
	cout << " |\n\t\t\t\t\t\t\t|";
	for (int i = 0; i < (size - 2) / 2; i++) {
		cout << "- ";
	}
	cout << "|\n";
	total += p->data.getTotal();
}

//ham xuat hoa don
void OutputInvoice(NodeInvoice* p) {
	cout << "\t\t\t\t\t\t" << p->id << ", " << p->description << ", " << p->count << endl;
	OutputFormedList(p->data, true);
}

//ham xuat danh sach hoa don
void OutputListInvoice(InvoiceList il) {
	for (NodeInvoice* p = il.head; p != NULL; p = p->next) {
		OutputInvoice(p);
		cout << endl;
	}
}

//ham tim so thu tu lon nhat
string MakeNoId(ProductList list, int from, int lenght) {
	string max = list.head->data.getId().substr(from, lenght);
	string result = "";
	for (NodeProduct* p = list.head; p != NULL; p = p->next) {
		string tmp = p->data.getId().substr(from, lenght);
		if (tmp > max) {
			max = tmp;
		}
	}
	int noId = stoi(max, 0, 10) + 1;
	int count = 0, tmp = noId;
	while (tmp != 0) {
		count++;
		tmp /= 10;
	}
	for (int i = 0; i < lenght - count; i++) {
		result.append("0");
	}
	return result.append(to_string(noId));
}
string MakeNoId(InvoiceList list, int from, int lenght) {
	string max = list.head->id.substr(from, lenght);
	string result = "";
	for (NodeInvoice* p = list.head; p != NULL; p = p->next) {
		string tmp = p->id.substr(from, lenght);
		if (tmp > max) {
			max = tmp;
		}
	}
	int noId = stoi(max, 0, 10) + 1;
	int count = 0, tmp = noId;
	while (tmp != 0) {
		count++;
		tmp /= 10;
	}
	for (int i = 0; i < lenght - count; i++) {
		result.append("0");
	}
	return result.append(to_string(noId));
}

//ham sap xep(type, gender, noId)
void Sort(ProductList& l, string type = "id") {
	if (type == "name") {
		for (NodeProduct* p = l.head; p != l.tail; p = p->next) {
			for (NodeProduct* k = p->next; k != NULL; k = k->next) {
				if (ToLower(p->data.getName().substr(0, 1)) > ToLower(k->data.getName().substr(0, 1))) {
					SwapData(p, k);
				}
			}
		}
		return;
	}
	if (type == "price") {
		for (NodeProduct* p = l.head; p != l.tail; p = p->next) {
			for (NodeProduct* k = p->next; k != NULL; k = k->next) {
				if (p->data.getPrice() > k->data.getPrice()) {
					SwapData(p, k);
				}
			}
		}
		return;
	}
	if (type == "brand") {
		for (NodeProduct* p = l.head; p != l.tail; p = p->next) {
			for (NodeProduct* k = p->next; k != NULL; k = k->next) {
				if (ToLower(p->data.getBrand().substr(0, 1)) > ToLower(k->data.getBrand().substr(0, 1))) {
					SwapData(p, k);
				}
			}
		}
		return;
	}
	int index, lenght;
	if (type == "type") {
		index = 0;
		lenght = 1;
	}
	else if (type == "gender") {
		index = 1;
		lenght = 1;
	}
	else {
		index = 2;
		lenght = 4;
	}
	for (NodeProduct* p = l.head; p != l.tail; p = p->next) {
		for (NodeProduct* k = p->next; k != NULL; k = k->next) {
			if (p->data.getId().substr(index, lenght) > k->data.getId().substr(index, lenght)) {
				SwapData(p, k);
			}
		}
	}
}

//menu sap xep
string sortSelection[] = {
	"SORT BY",
	"Type",
	"Gender",
	"Number id",
	"Name",
	"Brand",
	"Price" };
bool SortMenu(ProductList& l) {
	if (l.head == NULL) return false;
	system("cls");
	int awn = PrintMenu(sortSelection, 7, 20, 1);
	switch (awn) {
	case 0: {
		Sort(l, "type");
		break;
	}
	case 1: {
		Sort(l, "gender");
		break;
	}
	case 2: {
		Sort(l, "id");
		break;
	}
	case 3: {
		Sort(l, "name");
		break;
	}
	case 4: {
		Sort(l, "brand");
		break;
	}
	case 5: {
		Sort(l, "price");
		break;
	}
	}
	return true;
}