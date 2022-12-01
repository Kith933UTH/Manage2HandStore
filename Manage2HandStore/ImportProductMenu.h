#include "Function.h"

string mainImportSelection[6] = {
			"IMPORT PRODUCT MENU",
			"Return",
			"Show all product",
			"Import product",
			"Change information product",
			"Delele product" },
		type[6] = {
			"ENTER TYPE",
			"Shirt",
			"Trousers",
			"Handbag",
			"Footwear",
			"Others" },
		gender[3] = {
			"ENTER GENDER",
			"Men",
			"Women" },
		sizeProduct[9] = {
			"ENTER SIZE",
			"S",
			"M",
			"L",
			"XL",
			"2XL",
			"3XL",
			"4XL",
			"Others" },
		importSelection[4] = {
			"IMPORT PRODUCT MENU",
			"Return",
			"Import product already exists",
			"Import new product" },
		editSelection[7] = {
			"TYPE TO MODIFY", 
			"Return", 
			"Name", 
			"Brand", 
			"Import price",
			"Quantity", 
			"Price" }
;

string InputID(ProductList l, string& description);
void ImportProduct(ProductList& l);
void DeleteProduct(ProductList& l);
void EditProduct(ProductList& l);
void ImportProductMenu(ProductList& l, ifstream& fileDataIn, ofstream& fileDataOut);

/*--------------------------------------------------------------------------------*/

void ImportProductMenu(ProductList& l, ifstream& fileDataIn, ofstream& fileDataOut) {
	//Import product menu
	int awn = -1;
	bool ctn = true;
	while (ctn) {
		system("cls");
		awn = PrintMenu(mainImportSelection, 6, 35);
		switch (awn) {
		case 0: {
			ctn = false;
			break;
		}
		case 1: {
			system("cls");
			OutputFormedList(l, true);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			ImportProduct(l);
			break;
		}
		case 3: {
			EditProduct(l);
			break;
		}
		case 4: {
			DeleteProduct(l);
			break;
		}
		}
	}
};

string InputID(ProductList l, string &description) {
	string sawn, id = "";
	int awn = -1;
	bool flag = true;
	//Nhap loai hang
	while (flag) {
		system("cls");
		awn = PrintMenu(type, 6, 25, 1);
		switch (awn) {
		case 0: {
			id.append("1");
			description = type[1];
			flag = false;
			break;
		}
		case 1: {
			id.append("2");
			description = type[2];
			flag = false;
			break;
		}
		case 2: {
			id.append("3");
			description = type[3];
			flag = false;
			break;
		}
		case 3: {
			id.append("4");
			description = type[4];
			flag = false;
			break;
		}
		case 4: {
			id.append("5");
			cout << "\nEnter type of this product: "; getline(cin, description);
			flag = false;
			break;
		}
		}
	}
	flag = true;

	//Nhap hang danh cho nam hay nu
	while (flag) {
		system("cls");
		awn = PrintMenu(gender, 3, 20, 1);
		switch (awn) {
		case 0: {
			id.append("1");
			description.append(" for men");
			flag = false;
			break;
		}
		case 1: {
			id.append("0");
			description.append(" for women");
			flag = false;
			break;
		}
		}
	}
	flag = true;

	//Nhap so thu tu id
	{
		if (l.head == NULL) {
			id.append("0001");
		}
		else {
			int tmp = stoi(l.tail->data.getId().substr(2, 4), 0, 10);
			if (++tmp < 10) {
				id.append("000");
			}
			else if (tmp < 100) {
				id.append("00");
			}
			else if (tmp < 1000) {
				id.append("0");
			}
			id.append(to_string(tmp));
		}
		id.append("-");
	}

	//Nhap size
	switch (stoi(id.substr(0,1), 0, 10))
	{
	case 1: case 2:{
		while (flag) {
			system("cls");
			awn = PrintMenu(sizeProduct, 9, 20, 1);

			switch (awn) {
			case 0: {
				id.append(sizeProduct[1]);
				flag = false;
				break;
			}
			case 1: {
				id.append(sizeProduct[2]);
				flag = false;
				break;
			}
			case 2: {
				id.append(sizeProduct[3]);
				flag = false;
				break;
			}case 3: {
				id.append(sizeProduct[4]);
				flag = false;
				break;
			}case 4: {
				id.append(sizeProduct[5]);
				flag = false;
				break;
			}case 5: {
				id.append(sizeProduct[6]);
				flag = false;
				break;
			}case 6: {
				id.append(sizeProduct[7]);
				flag = false;
				break;
			}case 7: {
				cout << "\nEnter size: "; getline(cin, sawn);
				id.append(sawn);
				flag = false;
				break;
			}
			}
		}
		break;
	}
	case 3: {
		id.append("000");
		break;
	}
	case 4: {
		cout << "\nEnter size (from 34 to 45): "; getline(cin, sawn);
		awn = CheckSelection(sawn, 34, 45);
		id.append(sawn);
		break;
	}
	case 5: {
		cout << "\nEnter size: "; getline(cin, sawn);
		id.append(sawn);
		break;
	}
	}
	//Tra ve id
	return id;
}

void ImportProduct(ProductList& l) {
	int awn = -1;
	bool ctn = true;
	while (ctn) {
		system("cls");
		awn = PrintMenu(importSelection, 4, 40);
		switch (awn) {
		case 0: {
			ctn = false;
			break;
		}
		case 1: {//Nhap hang da co san
			system("cls");
			OutputFormedList(l, true);
			if (l.head == NULL) {
				system("pause");
				return;
			}
			string id;
			NodeProduct* p = new NodeProduct;
			do {
				cout << "\nEnter ID of product : "; getline(cin, id);
				if (ExistInList(l, id, p)) {
					string awn;
					cout << "\nEnter number to import: "; getline(cin, awn);
					p->data.setQuantity(p->data.getQuantity() + CheckSelection(awn, 0, 0, true));
					ctn = false;
				}
				else {
					if (!Continue("This ID not exist in list.\n Do you want to input again")) {
						delete p;
						ctn = false;
						return;
					}
				}
			} while (ctn);
			
			system("cls");
			OutputFormedList(l, true);
			cout << "\nImport successfully.";
			system("pause");
			break;
		}
		case 2: {//Nhap hang moi
			Product2H p;
			string des, idTmp = InputID(l, des);
			p.setId(idTmp);
			system("cls");
			cout << "\n\nYour product will have id: " << p.getId() << " (its mean a " << des << ").";
			cin >> p;
			//Nhap hang thanh cong
			if (AddTail(l, CreateNode(p))) {
				if (Continue("\nSuccessfully imported this product. \n Do you want to continue importing product")) {
					ImportProduct(l);
				}
				else {
					return;
				}
			}
			//Nhap hang that bai
			else {
				if (Continue("\nImport failed. Do you want to try again")) {
					ImportProduct(l);
				}
				else {
					return;
				}
			}
			cin.ignore();
			break;
		}
		}

	}
};

void DeleteProduct(ProductList& l) {
	bool ctn = true;
	system("cls");
	if (l.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t+----------------------------------+" << endl;
		cout << "\t\t\t|   LIST HAS NO PRODUCT TO DELETE  |" << endl;
		cout << "\t\t\t+----------------------------------+\n\n\n\n\n\n" << endl;
		system("pause");
		return;
	}
	string id;
	NodeProduct* p = new NodeProduct; p->data.setQuantity(9303);
	OutputFormedList(l, true);
	do {
		cout << "\nEnter ID of product to delete: "; getline(cin, id);
		if (ExistInList(l, id, p)) {
			string awn;
			cout << "\nEnter number to delete: "; getline(cin, awn);
			p->data.setQuantity(p->data.getQuantity() - CheckSelection(awn, 0, 0, true));
			if (p->data.getQuantity() <= 0) {
				DeleteById(l, id);
			}
			ctn = false;
		}
		else {
			if (!Continue("This ID not exist in list.\n Do you want to input again")) {
				delete p;
				return;
			}
		}
	} while (ctn);
	system("cls");
	OutputFormedList(l, true);
	cout << "\nDelete successfully.";
	cin.ignore();
	system("pause");
}

void EditProduct(ProductList& l) {
	system("cls");
	bool ctn = true;
	if (l.head == NULL) {
		cout << "\n\n\n\n\n\t\t\t+----------------------------------+" << endl;
		cout << "\t\t\t|   LIST HAS NO PRODUCT TO MODIFY  |" << endl;
		cout << "\t\t\t+----------------------------------+\n\n\n\n\n\n" << endl;
		system("pause");
		return;
	}
	string id;
	NodeProduct* p = new NodeProduct;
	OutputFormedList(l, true);
	do {
		cout << "\nEnter ID of product to modify: "; getline(cin, id);
		if (ExistInList(l, id, p)) {
			string sawn;
			int awn = -1;
			while (ctn) {
				awn = PrintMenu(editSelection, 7, 20);
				switch (awn) {
				case 0: {
					ctn = false;
					break;
				}
				case 1: {
					cout << "Enter new " << editSelection[2] << ": "; getline(cin, sawn);
					p->data.setName(sawn);
					break;
				}
				case 2: {
					cout << "Enter new " << editSelection[3] << ": "; getline(cin, sawn);
					p->data.setBrand(sawn);
					break;
				}
				case 3: {
					cout << "Enter new " << editSelection[4] << ": "; getline(cin, sawn);
					p->data.setImportPrice(CheckSelection(sawn, 0, 0, true));
					break;
				}
				case 4: {
					cout << "Enter new " << editSelection[5] << ": "; getline(cin, sawn);
					p->data.setQuantity(CheckSelection(sawn, 0, 0, true));
					break;
				}
				case 5: {
					cout << "Enter new " << editSelection[6] << ": "; getline(cin, sawn);
					p->data.setPrice(CheckSelection(sawn, 0, 0, true));
					break;
				}
				}
				system("cls");
				OutputFormedList(l, true);
				if (Continue("\nSuccessfully modified this product. \n Do you want to continue modified another attribute of this product")) {
					ctn = true;
				}
				else {
					system("cls");
					OutputFormedList(l, true);
					cout << "\n\tModifying is complete.\n\n";
					system("pause");
					return;
				}
			}
		}
		else {
			if (!Continue("This ID not exist in list.\n Do you want to input again")) {
				return;
			}
		}
	} while (ctn);
}