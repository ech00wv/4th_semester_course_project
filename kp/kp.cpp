#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string>
#include <regex>
using namespace std;

int treeSize = 0;
const int HASH_SIZE = 500;

string input_license() {
	string res;
	regex pattern("^\\d{2} [АВЕКМНОРСТУХ]{2} \\d{6}$");
	cout << "\nВведите номер водительского удостоверения клиента в формате RR AA NNNNNN:\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "Номер удостоверения введен в неверном формате, повторите ввод:\n";
	}
}

string input_name() {
	string res;
	regex pattern("^[а-яА-ЯЁё]+ [а-яА-ЯЁё]+ [а-яА-ЯЁё]+$");
	cout << "\nВведите ФИО, разделенные пробелами:\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nФИО введены в неверном формате, повторите ввод:\n";
	}
}

string input_passport() {
	string res;
	regex pattern("^\\d{4} \\d{6}$");
	cout << "\nВведите серию и номер паспорта, разделенные пробелами:\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nСерия и номер паспорта введены в неверном формате, повторите ввод:\n";
	}
}

string input_address() {
	string res;
	regex pattern("^[А-Яа-яЁё]{3,} \\d+$");
	cout << "\nВведите адрес в формате ""улица (не менее 3 русских букв) дом"":\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nАдрес введен в неверном формате, повторите ввод:\n";
	}
}

string input_id() {
	string res;
	regex pattern("^[АВЕКМНОРСТУХ]\\d{3}[АВЕКМНОРСТУХ]{2}-\\d{2}$");
	cout << "\nВведите госномер в формате ANNNAA-NN:\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nГосномер введен в неверном формате, повторите ввод:\n";
	}
}

string input_model() {
	string res;
	regex pattern("^[A-Za-z]{3,}$");
	cout << "\nВведите марку автомобиля (не менее 3 латинских букв):\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nМарка введена в неверном формате, повторите ввод:\n";
	}
}

string input_color() {
	string res;
	regex pattern("^[А-Яа-я]{3,}$");
	std::cin.ignore(32656, '\n');
	cout << "\nВведите цвет автомобиля (не менее 3 русских букв):\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			return res;
		}
		else cout << "\nЦвет введен в неверном формате, повторите ввод:\n";
	}
}

int input_date() {
	int res = 0;
	cout << "\nВведите год выпуска автомобиля (от 1980 до 2023):\n";
	cin >> res;
	while (std::cin.fail() || res < 1980 || res > 2023) {
		std::cin.clear();
		std::cin.ignore(32656, '\n');
		cout << "\nВведен неверный год выпуска автомобиля, повторите ввод:\n";
		std::cin >> res;
	}
	return res;
}

string input_date_full() {
	string res;
	string day;
	string month;
	regex pattern("^((0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[012])\\.(\\d\\d))$");
	cout << "\nВведите дату в формате ""дд.мм.гг"":\n";
	while (1) {
		getline(cin, res);
		if (regex_match(res, pattern)) {
			day = res.substr(0, 2);
			month = res.substr(3, 2);
			if (month == "02" && stoi(day) > 29) {
				cout << "\nВ феврале может быть не более 29 дней, повторите ввод:\n";
				continue;
			}
			return res;
		}
		else 
			cout << "\nДата введена в неверном формате, повторите ввод:\n";
	}
}

class Client {
private:
	string license;
	string name;
	string passport;
	string address;
public:
	Client(string license, string name, string passport, string address) :license(license), name(name), passport(passport), address(address) {};
	Client() : license(""), name(""), passport(""), address("") {};
	Client(string license):license(license), name(""), passport(""), address("") {};
	Client(const Client*& other) {
		license = other->license;
		name = other->name;
		passport = other->passport;
		address = other->address;
	}
	void printClient();
	int getLicenseNum();
	string getLicence() { return license; }
	string getName() { return name; }
	string getPassport() { return passport; }
	string getAddress() { return address; }
	bool clientEqual(Client* other);
};

void Client::printClient() {
	cout << "\nНомер удостоверения : " << license << ", ФИО клиента : " << name  << ", паспортные данные : " << passport << ", адрес : " << address << endl;
}

int Client::getLicenseNum() {
	return stoi(license.substr(0, 2) + license.substr(6, 6));
}

Client* addClient() {
	Client* client = new Client(input_license(), input_name(), input_passport(), input_address());
	return client;
}

bool Client::clientEqual(Client* other) {
	return (this->getLicenseNum() == other->getLicenseNum());
}


struct cell {
	Client client;
	int height;
	cell* previous;
	cell* left;
	cell* right;
	cell(Client* _client, cell* prev) {
		client = *_client;
		left = 0;
		right = 0;
		height = 1;
		previous = prev;
	}
	cell() {
		left = 0;
		right = 0;
		height = -1;
		previous = 0;
	}
};

int heightTree(cell* element) {
	if (element)
		return element->height;
	else
		return 0;
}

cell* searchTree(cell* element, Client* data) {
	cell* savedelem = new cell();
	if (element) {
		if (data->getLicenseNum() < element->client.getLicenseNum())
			return (savedelem = searchTree(element->left, data));
		if (data->getLicenseNum() > element->client.getLicenseNum())
			return (savedelem = searchTree(element->right, data));
		if (element->client.clientEqual(data))
			return (savedelem = element);
	}
	return savedelem;
}

int absH(cell* element) {//разница высот между правым и левым поддеревом
	return (heightTree(element->right) - heightTree(element->left));
}

void reheightTree(cell* element) {
	int heightL = heightTree(element->left);
	int heightR = heightTree(element->right);
	if (heightL > heightR)
		element->height = heightL + 1; // элемент добавлен в левое поддерево
	else
		element->height = heightR + 1;// элемент добавлен в правое  поддерево
}

cell* rotateR(cell* element) { //правый малый поворот
	cell* element_2 = element->left;
	element_2->previous = element->previous;
	element->left = element_2->right;
	element_2->right = element;
	element->previous = element_2;
	reheightTree(element);
	reheightTree(element_2);
	return element_2;
}

cell* rotateL(cell* element) { //правый левый поворот
	cell* element_2 = element->right;
	element_2->previous = element->previous;
	element->right = element_2->left;
	element_2->left = element;
	element->previous = element_2;
	reheightTree(element);
	reheightTree(element_2);
	return element_2;
}

cell* rebalanceTree(cell* element) {
	reheightTree(element);
	if (absH(element) == 2) {//левый поворот
		if (absH(element->right) < 0)//большой левый поворот
			element->right = rotateR(element->right);
		return rotateL(element);
	}
	if (absH(element) == -2)//правый поворот
	{
		if (absH(element->left) > 0)//большой правый поворот(если высота больше у левое пд -> правое пд)
			element->left = rotateL(element->left);//для примера [60,50,61,45,55,62,44,54,57]->56
		return rotateR(element);
	}
	return element;
}

cell* add(cell* element,Client* client, cell* prev = 0) {
	if (!element) {
		return new cell(client, prev); //двигаемся рекурсивно, если будет найдено пустое место, то добавляем элемент в него
	}
	if (client->getLicenseNum() < element->client.getLicenseNum())
		element->left = add(element->left, client, element);
	if (client->getLicenseNum() > element->client.getLicenseNum()) {
		element->right = add(element->right, client, element);
	}
	return rebalanceTree(element);
}


cell* minTree(cell* element) { //поиск ближайшего левого поддерева без левых листьев (первой вершины при отсутствии левого поддерева у нее) из правого поддерева при удалении элемента
	if (element->left)
		return minTree(element->left);
	else
		return element;
}

cell* delMinTree(cell* element) { //запись на место перенесенного элемента его правого поддерева при удалении элемента
	if (element->left == 0)
		return element->right;
	element->left = delMinTree(element->left);
	return rebalanceTree(element);
}

cell* delElemTree(cell* element, Client* data) {
	if (!element)
		return 0;
	if (data->getLicenseNum() < element->client.getLicenseNum())
		element->left = delElemTree(element->left, data);
	else if (data->getLicenseNum() > element->client.getLicenseNum())
		element->right = delElemTree(element->right, data);
	else {
		cell* elemL = element->left;
		cell* elemR = element->right;
		delete element;
		if (!elemR)
			return elemL;//если справа ничего нет, то ближайшая вершина слева подходит для записи на место удаленного элемента
		cell* minimum = minTree(elemR); //ближайшее левое поддерево без левых листьев у правого поддерева, либо вершина правого поддерева при отсутствии левых поддеревьев у нее
		minimum->right = delMinTree(elemR); //minim - новый элемент на месте удаленного, балансировка и перезапись нужных элементов справа
		minimum->left = elemL; //старый элемент слева остается
		return rebalanceTree(minimum); //балансируем получившееся поддерево
	}
	return rebalanceTree(element);
}

//void print(cell* element, int hig) {
//	if (element) {
//		print(element->right, hig + 1);
//		for (int i = 0; i < hig; i++)
//			cout << "   ";
//		cout << element->data << '\n';
//		print(element->left, hig + 1);
//	}
//}

void printTree(cell* element) {
	if (treeSize < 1) {
		cout << "\nДерево пусто!\n";
			return;
	}
	if (element) {
		printTree(element->left);
		printTree(element->right);
		element->client.printClient();
	}
}

void deleteTree(cell* element) {
	if (element) {
		deleteTree(element->left);
		deleteTree(element->right);
		delete element;
	}
}

class Car {
private:
	string id;
	string model;
	string color;
	int date;
	bool in_stock;
public:
	Car(string id, string model, string color, int date) : id(id), model(model), color(color), date(date), in_stock(true) {};
	Car() : id("-1"), model(""), color(""), date(0), in_stock(false) {};
	Car(string id) : id(id), model(""), color(""), date(0), in_stock(false) {};
	string getId() { return id; }
	string getModel() { return model; }
	bool getInStock(){ return in_stock; }
	void setInStock(bool in_stock) { this->in_stock = in_stock; }
	void setDeleted() { id = "deleted"; model = ""; color = ""; date = 0; in_stock = false; }
	void setClear(){ id = "-1"; model = ""; color = ""; date = 0; in_stock = false; }
	void print_car();
};

void Car::print_car(){
	cout << "\nГосномер автомобиля: " << id << ",  марка: " << model << ",  цвет: " << color << ",  год выпуска: " << date << endl;
}

int hashFunc(string id) {
	int key = 0;
	for (int i = 0; i < id.length(); i++) {
		key += int(id[i]) * int(id[i]);
	}
	return (key % HASH_SIZE);
}

void showHash(Car* arr) {
	int flag = 0;
	for (int i = 0; i < HASH_SIZE; i++) {
		if (arr[i].getId() != "deleted" && arr[i].getId() != "-1") {
			flag++;
			arr[i].print_car();
		}
	}
	if (!flag) cout << "\nСписок машин пуст!\n";
}

void addElemHash(Car* arr, Car* key, int i) {
	int j = i;
	while (arr[i].getId() != "-1" && i <= HASH_SIZE) {
		if (arr[i].getId() == "deleted")
			while (arr[j].getId() != "-1") {
				if (arr[j].getId() == (*key).getId()) {
					cout << "\nТакой автомобиль уже есть в базе!\n";
					delete key;
					return;
				}
				j++;
			}
		if ((*key).getId() == arr[i].getId()) {
			cout << "\nТакой автомобиль уже есть в базе!\n";
			delete key;
			return;
		}
		i++;
		if (i >= HASH_SIZE) {
			cout << "\nСвободная ячейка не была найдена!\n";
			delete key;
			return;
		}
	}
	cout << "\nАвтомобиль успешно добавлен!\n";
	arr[i] = *key;
}

Car* findElemHash(Car* arr, Car* key, int i) {
	while (arr[i].getId() != key->getId()) {
		i++;
		if (i == HASH_SIZE) {
			return key;
		}
		if (arr[i].getId() == "-1") {
			return key;
		}
	}
	return &arr[i];
}

void delElemHash(Car* arr, Car* key, int i) {
	while (arr[i].getId() != key->getId()) {
		i++;
		if (i == HASH_SIZE) {
			cout << "\nНужный автомобиль не был найден!\n";
			return;
		}
		if (arr[i].getId() == "-1") {
			cout << "\nНужный автомобиль не был найден!\n";
			return;
		}
	}
	if (!(arr[i].getInStock())) {
		cout << "\nАвтомобиль найден, но он либо в ремонте, либо не возвращен клиентом, удаление невозможно!\n";
		return;
	}
	cout << "Автомобиль успешно удален!\n";
	arr[i].setDeleted();
}

struct Node {
	string license; //клиент
	string id; // автомобиль
	string issue_date; //дата выдачи
	string return_date; //дата возврата
	Node* next;
	Node(string license, string id, string issue_date) : license(license), id(id),issue_date(issue_date), return_date(""), next(nullptr) {};
	Node() : license(""), id(""), issue_date(""), return_date(""), next(nullptr) {};
	void setReturn(string return_date) { this->return_date = return_date; }
	bool isReturned(){ return return_date != ""; }
	bool isEqual(Node* other) { return (this->license == other->license) && (this->id == other->id) && (this->issue_date == other->issue_date) && (this->return_date == other->return_date); }
};

class List {
private:
	Node* first;
public:
	List() : first(nullptr) {};
	~List();
	bool is_empty();
	void add_node(string license, string id, string issue_date);
	void print();
	Node* findByLicense(string license);
	Node* findById(string id);
	Node* getFirst() { return first; }
	void setFirst(Node* node) { first = node; }
	void partition(Node*& head, Node*& front, Node*& back);
	Node* merge(Node* left, Node* right);
	Node* mergeSort(Node*& first);
	void setCycled();
	void setUncycled();
};

bool List::is_empty() {
	return first == nullptr;
}

void List::add_node(string license, string id, string issue_date) {
	Node* p = new Node(license, id, issue_date);
	if (is_empty()) {
		first = p;
		p->next = first;
		return;
	}
	Node* current = first;
	while (current->next != first) {
		current = current->next;
	}
	current->next = p;
	p->next = first;
}

void List::print() {
	if (is_empty()) {
		cout << "\nНет информации о выдаче автомобилей клиентам!\n";
		return;
	}
	Node* current = first;
	while (1) {
		if (current->isReturned())
			cout << "\nКлиенту " << current->license << " выдан автомобиль " << current->id << ", дата выдачи: " << current->issue_date << ", дата возврата: " << current->return_date << endl;
		else
			cout << "\nКлиенту " << current->license << " выдан автомобиль " << current->id << ", дата выдачи: " << current->issue_date << ", дата возврата: не возвращен" << endl;
		if (current->next == first) {
			break;
		}
		current = current->next;
	}
}

List::~List() {
	Node* current = first;
	while (current) {
		current = current->next;
		delete first;
		first = current;
	}
}

Node* List::findByLicense(string license) {
	if (is_empty()) {
		return nullptr;
	}
	Node* current = first;
	Node* found = nullptr;
	while (1) {
		if (current->license == license && !(current->isReturned())) {
			found = current;
			return found;
		}
		if (current->next == first) {
			break;
		}
		current = current->next;
		
	}
	return found;
}

Node* List::findById(string id) {
	if (is_empty()) {
		return nullptr;
	}
	Node* current = first;
	Node* found = nullptr;
	while (1) {
		if (current->id == id)
			found = current;
		if (current->next == first) {
			break;
		}
		current = current->next;
	}
	return found;
}

void List::partition(Node*& head, Node*& front, Node*& back) {
	Node* fast;
	Node* slow;
	if (head == nullptr || head->next == nullptr) {
		front = head;
		back = nullptr;
	}
	else {
		slow = head;
		fast = head->next;
		while (fast != nullptr){ 
			fast = fast->next;
			if (fast != nullptr) {
				slow = slow->next;
				fast = fast->next;

			}
		}
		front = head;
		back = slow->next;
		slow->next = nullptr;
	}
}

int compareId(const string& id1, const string& id2) {
	// сравниваем ключи license
	int num1 = stoi(id1.substr(1, 3) + id1.substr(7, 2));
	int num2 = stoi(id2.substr(1, 3) + id2.substr(7, 2));
	return num1 - num2;
}

Node* List::merge(Node* left, Node* right) {
	Node* mergedList = nullptr;
	if (left == nullptr) {
		return right;
	}
	else if (right == nullptr) {
		return left;
	}

	if (compareId(left->id, right->id) <= 0) {
		mergedList = left;
		mergedList->next = merge(left->next, right);
	}
	else {
		mergedList = right;
		mergedList->next = merge(left, right->next);
	}

	return mergedList;
}

//Node* List::merge(Node*& left, Node*& right) {
//	Node* mergedList = nullptr;
//	Node* cur = nullptr; // Дополнительная переменная для указания текущего элемента в объединенном списке
//
//	if (left == nullptr) {
//		return right;
//	}
//	else if (right == nullptr) {
//		return left;
//	}
//
//	if (compareId(left->id, right->id) <= 0) {
//		mergedList = left;
//		left = left->next; // Перемещаем указатель left на следующий элемент
//	}
//	else {
//		mergedList = right;
//		right = right->next; // Перемещаем указатель right на следующий элемент
//	}
//
//	cur = mergedList; // Устанавливаем начальное значение текущего элемента
//
//	// Продолжаем объединять списки, перемещая указатели на следующие элементы
//	while (left != nullptr && right != nullptr) {
//		if (compareId(left->id, right->id) <= 0) {
//			cur->next = left;
//			left = left->next;
//		}
//		else {
//			cur->next = right;
//			right = right->next;
//		}
//		cur = cur->next; // Перемещаем указатель на текущий элемент
//	}
//
//	// Добавляем оставшиеся элементы из левого или правого списка
//	if (left != nullptr) {
//		cur->next = left;
//	}
//	else {
//		cur->next = right;
//	}
//
//	return mergedList;
//}


Node* List::mergeSort(Node*& cur) {
	Node* head = cur;
	Node* a = nullptr;
	Node* b = nullptr;
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	partition(head, a, b);
	head = merge(mergeSort(a), mergeSort(b));
	setFirst(head);
	return head;
}

void List::setCycled() {
	Node* current = first;
	while (current->next) {
		current = current->next;
	}
	current->next = first;
}

void List::setUncycled() {
	Node* current = first;
	while (current->next != first)
		current = current->next;
	current->next = nullptr;
}

void findByName(cell* element, string name) {
	if (element) {
		findByName(element->left, name);
		findByName(element->right, name);
		string text = element->client.getName();
		for (int i = 0; i <= text.length() - name.length(); i++) {
			int j;
			for (j = 0; j < name.length(); j++) {
				if (text[i + j] != name[j]) {
					break;
				}
			}

			if (j == name.length()) {
				element->client.printClient();
				return;
			}
		}
	}
}

void findByAddress(cell* element, string address) {
	if (element) {
		findByAddress(element->left, address);
		findByAddress(element->right, address);
		string text = element->client.getAddress();
		for (int i = 0; i <= text.length() - address.length(); i++) {
			int j;
			for (j = 0; j < address.length(); j++) {
				if (text[i + j] != address[j]) {
					break;
				}
			}
			if (j == address.length()) {
				element->client.printClient();
				return;
			}
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cell* tree = nullptr;
	//Client* test3 = new Client("52 АА 222222", "БББ БББ БББ", "2222 222222", "БББББ 2");
	tree = add(tree, new Client("51 АА 111111", "ААА ААА ААА", "1111 111111", "ААААА 1"));
	tree = add(tree, new Client("52 АА 222222", "БББ БББ БББ", "2222 222222", "БББББ 2"));
	tree = add(tree, new Client("53 АА 333333", "ВВВ ВВВ ВВВ", "3333 333333", "ВВВВВ 3"));
	tree = add(tree, new Client("54 АА 444444", "ЕЕЕ ЕЕЕ ЕЕЕ", "4444 444444", "ЕЕЕЕЕ 4"));
	tree = add(tree, new Client("60 АА 666666", "Орлов Евгений Антонович", "6666 666666", "УУУУУУ 5"));
	tree = add(tree, new Client("65 АА 777777", "Орлов Антон Александрович", "7777 777777", "ККККК 6"));
	treeSize = 6;
	Car arr[HASH_SIZE];
	Car* test1 = new Car("А111АА-11", "Mazda", "Красный", 2010);
	Car* test2 = new Car("Е333ЕЕ-33", "Subaru", "Синий", 1992);
	Car* test3 = new Car("В222ВВ-22", "Mazda", "Желтый", 2010);
	Car* test4 = new Car("К444КК-44", "Mazda", "Желтый", 2010);
	addElemHash(arr, test1, hashFunc(test1->getId()));
	addElemHash(arr, test2, hashFunc(test2->getId()));
	addElemHash(arr, test3, hashFunc(test3->getId()));
	addElemHash(arr, test4, hashFunc(test4->getId()));
	List* events = new List();
	while (1) {
		cout << "Выберите действие:\n1 - регистрация нового клиента или автомобиля\n2 - удаление сведений о клиенте или автомобиле\n3 - просмотр всех зарегистрированных клиентов или автомобилей\n4 - очистить все данные о клиентах или автомобилях\n5 - поиск клиента или автомобиля\n6 - регистрация события\nдругой символ - выход\n";
		switch (_getch()) {
		case '1':
			cout << "\nВыберите действие : \n1 - регистрация нового клиента\n2 - регистрация нового автомобиля\nдругой символ - выход\n";
			switch (_getch()) {
			case '1': {
				Client* new_client = addClient();
				if (searchTree(tree, new_client)->height != -1) {
					cout << "\nКлиент с таким номером водительского удостоверения уже существует!\n";
					delete new_client;
					break;
				}
				tree = add(tree, new_client);
				treeSize++;
				cout << "\nКлиент успешно добавлен!\n";
				break;
			}
			case '2': {
				Car* new_car = new Car(input_id(), input_model(), input_color(), input_date());
				addElemHash(arr, new_car, hashFunc(new_car->getId()));
				break;
			}
			default:
				break;
			}
			break;
		case '2':
			cout << "\nВыберите действие : \n1 - удалить сведения о клиенте\n2 - удалить сведения об автомобиле\nдругой символ - выход\n";
			switch(_getch()) {
			case '1': {
				if (treeSize < 1) {
					cout << "\nКлиентов нет!\n";
					break;
				}
				Client* search = new Client(input_license());
				cell* element = searchTree(tree, search);
				if (element->height == -1) {
					cout << "\nТакого клиента не существует!\n";
					delete search;
					break;
				}
				Node* atClient = events->findByLicense(element->client.getLicence());
				if (atClient && !(atClient->isReturned())) {
					cout << "\nНевозможно удалить данные о клиенте, он не вернул автомобиль!\n";
					break;
				}
				tree = delElemTree(tree, search);
				treeSize--;
				cout << "\nКлиент успешно удален!\n";
				break;
			}
			case '2': {
				Car* search_car = new Car(input_id());
				delElemHash(arr, search_car, hashFunc(search_car->getId()));
				delete search_car;
				break;
			}
			default:
				break;
			}
			break;
		case '3':
			cout << "\nВыберите действие : \n1 - просмотр сведений о всех клиентах\n2 - просмотр сведений о всех автомобилях\nдругой символ - выход\n";
			switch (_getch()) {
			case '1':
				if (treeSize < 1) {
					cout << "\nКлиентов нет!\n";
					break;
				}
				printTree(tree);
				break;
			case '2':
				showHash(arr);
				break;
			default:
				break;
			}
			break;
		case '4':
			cout << "\nВыберите действие : \n1 - очистить данные о всех клиентах\n2 - очистить данные о всех автомобилях\nдругой символ - выход\n";
			switch (_getch()) {
			case '1':
				if (treeSize < 1) {
					cout << "\nКлиентов нет!\n";
					break;
				}
				deleteTree(tree);
				treeSize = 0;
				cout << "\nДанные о всех клиентах успешно удалены!\n";
				break;
			case '2':
				for (int i = 0; i < HASH_SIZE; i++) {
					arr[i].setClear();
				}
				cout << "\nДанные о всех автомобилях успешно удалены!\n";
				break;
			default:
				break;
			}
			break;
		case '5':
			cout << "\nВыберите действие : \n1 - поиск клиента\n2 - поиск автомобиля\nдругой символ - выход\n";
			switch (_getch()) {
			case '1':
				cout << "\nВыберите действие : \n1 - по номеру водительского удостоверения\n2 - по фрагментам ФИО или адреса\nдругой символ - выход\n";
				switch (_getch()) {
				case '1': {
					if (treeSize < 1) {
						cout << "\nКлиентов нет!\n";
						break;
					}
					Client* search = new Client(input_license());
					cell* element = searchTree(tree, search);
					if (element->height == -1) {
						cout << "\nТакого клиента не существует!\n";
						delete search;
						delete element;
						break;
					}
					cout << "\nНайденный клиент:\n";
					element->client.printClient();
					Node* atClient = events->findByLicense(element->client.getLicence());
					if (atClient && !(atClient->isReturned())) {
						cout << "\nДанному клиенту выдан автомобиль c номером " << atClient->id << endl;
						break;
					}
					break;
				}
				case '2':
					cout << "\nВыберите действие: \n1 - поиск по фрагменту ФИО\n2 - поиск по адресу\nдругой символ - выход\n";
					switch (_getch()) {
					case '1': {
						cout << "\nВведите фрагмент ФИО:\n";
						string name;
						getline(cin, name);
						cout << "\nНайденные элементы:\n";
;						findByName(tree, name);
						break;
					}
					case '2': {
						cout << "\nВведите фрагмент адреса:\n";
						string address;
						getline(cin, address);
						cout << "\nНайденные элементы:\n";
						findByAddress(tree, address);
						break;
					}
					default:
						break;
					}
					break;
				default:
					break;

				}
				break;
			case '2':
				cout << "\nВыберите действие : \n1 - по «Государственному регистрационному номеру»\n2 - по названию марки автомобиля\nдругой символ - выход\n";
				switch (_getch()) {
				case '1': {
					Car* search_car = new Car(input_id());
					Car* found = findElemHash(arr, search_car, hashFunc(search_car->getId()));
					if (found->getModel() == "") {
						cout << "\nАвтомобиль не был найден!\n";
						delete search_car;
						break;
					}
					cout << "\nНайденный элемент:\n";
					found->print_car();
					Node* atClient = events->findById(found->getId());
					if (atClient && !(atClient->isReturned())) {
						cell* foundClient = searchTree(tree, new Client(atClient->license));
						cout << "\nДанный автомобиль выдан клиенту: ";
						foundClient->client.printClient();
						break;
					}
					break;
				}
				case '2': {
					string model = input_model();
					for (int i = 0; i < HASH_SIZE; i++) {
						if (arr[i].getModel() == model) {
							arr[i].print_car();
						}
					}
					break;
				}
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		case '6':
			cout << "\nВыберите действие : \n1 - зарегистрировать отправку автомобиля в ремонт\n2 - зарегистрировать прибытие автомобиля из ремонта\n3 - зарегистрировать выдачу клиенту автомобиля на прокат\n4 - зарегистрировать возврат автомобиля от клиента\n5 - вывести информацию о выдаче автомобилей клиентам\nдругой символ - выход\n";
			switch (_getch()) {
			case '1': {
				Car* search_car = new Car(input_id());
				Car* found = findElemHash(arr, search_car, hashFunc(search_car->getId()));
				if (found->getModel() == "") {
					cout << "\nАвтомобиль не был найден в базе!\n";
					delete search_car;
					break;
				}
				if (!(found->getInStock())) {
					cout << "\nДанный автомобиль не в наличии у бюро!\n";
					delete search_car;
					break;
				}
				cout << "\nАвтомобиль успешно отправлен в ремонт!\n";
				found->setInStock(false);
				delete search_car;
				break;
			}
			case '2': {
				Car* search_car = new Car(input_id());
				Car* found = findElemHash(arr, search_car, hashFunc(search_car->getId()));
				if (found->getModel() == "") {
					cout << "\nАвтомобиль не был найден в базе!\n";
					delete search_car;
					break;
				}
				if (found->getInStock()) {
					cout << "\nДанный автомобиль находится в наличии у бюро!\n";
					delete search_car;
					break;
				}
				Node* atClient = events->findById(found->getId());
				if (atClient && !(atClient->isReturned())) {
					cout << "\nДанный автомобиль сейчас у клиента!\n";
					delete search_car;
					break;
				}
				cout << "\nАвтомобиль успешно принят из ремонта!\n";
				found->setInStock(true);
				delete search_car;
				break;
			}
			case '3': {
				if (treeSize < 1) {
					cout << "\nКлиентов нет!\n";
					break;
				}
				Client* search = new Client(input_license());
				cell* foundClient = searchTree(tree, search);
				if (foundClient->height == -1) {
					cout << "\nТакого клиента не существует!\n";
					delete search;
					delete foundClient;
					break;
				}
				Node* atClient = events->findByLicense(foundClient->client.getLicence());
				if (atClient && !(atClient->isReturned())) {
					cout << "\nДанному клиенту уже выдан автомобиль!\n";
					break;
				}
				Car* search_car = new Car(input_id());
				Car* foundCar = findElemHash(arr, search_car, hashFunc(search_car->getId()));
				if (foundCar->getModel() == "") {
					cout << "\nАвтомобиль не был найден!\n";
					break;
				}
				if (!(foundCar->getInStock())) {
					cout << "\nДанного автомобиля нет в наличии!\n";
					break;
				}
				string date = input_date_full();
				events->add_node(foundClient->client.getLicence(), foundCar->getId(), date);
				foundCar->setInStock(false);
				events->setUncycled();
				Node* temp = events->getFirst();
				events->mergeSort(temp);
				events->setCycled();
				cout << "\nАвтомобиль успешно выдан клиенту!\n";
				break;
			}
			case '4': {
				if (treeSize < 1) {
					cout << "\nКлиентов нет!\n";
					break;
				}
				Client* search = new Client(input_license());
				cell* foundClient = searchTree(tree, search);
				if (foundClient->height == -1) {
					cout << "\nТакого клиента не существует!\n";
					delete search;
					delete foundClient;
					break;
				}
				Node* atClient = events->findByLicense(foundClient->client.getLicence());
				if ((atClient && atClient->isReturned()) || (!atClient)) {
					cout << "\nДанному клиенту автомобиль не выдавался!\n";
					break;
				}
				string return_date;
				while (1) {
					return_date = input_date_full();
					if (stoi(return_date.substr(6, 2) + return_date.substr(3, 2) + return_date.substr(0, 2)) < stoi(atClient->issue_date.substr(6, 2) + atClient->issue_date.substr(3, 2) + atClient->issue_date.substr(0, 2))) {
						cout << "\nДата возврата не может быть раньше даты выдачи!\n";
						continue;
					}
					break;
				}
				atClient->setReturn(return_date);
				Car* search_car = new Car(atClient->id);
				Car* foundCar = findElemHash(arr, search_car, hashFunc(search_car->getId()));
				foundCar->setInStock(true);
				cout << "\nАвтомобиль успешно принят от клиента!\n";
				break;
			}
			case '5': 
				events->print();
				break;
			default:
				break;
			}
			break;
		default:
			return 0;
			break;
		}
	}
}