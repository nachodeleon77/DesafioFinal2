#include "Presenter.h"

Presenter::Presenter()
{
	initializeBooks();
	initializeExemplars();
	initializeMembers();
	initializeLoanHistory();
	initializeReturnHistory();

	menu();
}

void Presenter::initializeBooks() {
	string myText;
	ifstream MyReadFile("books.txt");
	vector<std::string> val;
	while (getline(MyReadFile, myText)) {
		val = explode(myText, 'ƒ');
		// Check that all the values are filled
		val.at(0);
		val.at(1);
		val.at(2);

		Book book;
		book.setName(val[0]);
		book.setISBNcode(val[1]);
		book.setAuthor(val[2]);
		library->addBook(book);
	}
	MyReadFile.close();
}

void Presenter::initializeMembers()
{
	string myText;
	ifstream MyReadFile("members.txt");
	vector<std::string> val;
	while (getline(MyReadFile, myText)) {
		val = explode(myText, 'ƒ');
		// Check that all the values are filled
		val.at(0);
		val.at(1);
		val.at(2);

		if (stoi(val[3]) == 0) {
			Member m;
			m.setName(val[0]);
			m.setLastName(val[1]);
			m.setIDnumber(val[2]);
			library->addMember(m);
		}
		else {
			VIP v;
			v.setName(val[0]);
			v.setLastName(val[1]);
			v.setIDnumber(val[2]);
			library->addMember(v);
		}
	}
	MyReadFile.close();
}

void Presenter::initializeExemplars()
{
	string myText;
	ifstream MyReadFile("exemplars.txt");
	vector<std::string> val;
	while (getline(MyReadFile, myText)) {
		try {
			val = explode(myText, 'ƒ');
			// Check that all the values are filled
			val.at(0);
			val.at(1);
			val.at(2);

			int bookindex = library->getBookIndexfromList(val[0]);
			Book book = library->getBookfromIndex(bookindex);
			Exemplar exemplar;
			exemplar.seteditionNumber(stoi(val[1]));
			exemplar.setLocation(val[2]);
			exemplar.setBookISBNcode(book.getISBNcode());
			book.addExemplar(exemplar);
			library->setBookfromIndex(bookindex, book);
		} catch(...) {
			// Ignore row
		}
	}
	MyReadFile.close();
}

void Presenter::initializeLoanHistory()
{
		string myText;
		ifstream MyReadFile("loan.txt");
		vector<std::string> val;
		while (getline(MyReadFile, myText)) {
			string bookISBNcode, memberIdnumber;
			int editionNumber;
			time_t date;
			val = explode(myText, 'ƒ');
			// Check that all the values are filled
			val.at(0);
			val.at(1);
			val.at(2);
			val.at(3);

			bookISBNcode = val[0];
			editionNumber = stoi(val[1]);
			date = (time_t)std::stoi(val[2]);
			memberIdnumber = val[3];
			Member member = library->getMemberfromIndex(library->getMemberIndexfromList(memberIdnumber));
			Book book = library->getBookfromIndex(library->getBookIndexfromList(bookISBNcode));
			Exemplar exemplar = book.getExemplarfromIndex(book.getExemplarIndexfromList(editionNumber));
			exemplar.setBookName(book.getName());

			member.Borrow(exemplar);
			library->setMemberfromIndex(library->getMemberIndexfromList(memberIdnumber), member);
			
			if (exemplarloaned.find(exemplar.geteditionNumber()) == exemplarloaned.end()) {
				exemplarloaned[exemplar.geteditionNumber()] = 1;
			}
			else {
				exemplarloaned[exemplar.geteditionNumber()] = 1 + exemplarloaned[exemplar.geteditionNumber()];
			}

			Loan loan(exemplar, member, date);
			library->addLoanHistory(loan);
		}
		
		MyReadFile.close();
}

void Presenter::initializeReturnHistory()
{
	string myText;
	ifstream MyReadFile("return.txt");
	vector<std::string> val;
	while (getline(MyReadFile, myText)) {
		string bookISBNcode, memberIdnumber;
		int editionNumber;
		time_t date;
		val = explode(myText, 'ƒ');
		// Check that all the values are filled
		val.at(0);
		val.at(1);
		val.at(2);
		val.at(3);

		bookISBNcode = val[0];
		editionNumber = stoi(val[1]);
		date = (time_t)std::stoi(val[2]);
		memberIdnumber = val[3];
		Member member = library->getMemberfromIndex(library->getMemberIndexfromList(memberIdnumber));
		Book book = library->getBookfromIndex(library->getBookIndexfromList(bookISBNcode));
		Exemplar exemplar = book.getExemplarfromIndex(book.getExemplarIndexfromList(editionNumber));
		exemplar.setBookName(book.getName());

		member.returnExemplar(exemplar);
		library->setMemberfromIndex(library->getMemberIndexfromList(memberIdnumber), member);

		if (exemplarloaned.find(exemplar.geteditionNumber()) == exemplarloaned.end()) {
			exemplarloaned[exemplar.geteditionNumber()] = -1;
		}
		else {
			exemplarloaned[exemplar.geteditionNumber()] = exemplarloaned[exemplar.geteditionNumber()] - 1;
		}

		Return ret(exemplar, member, date);
		library->addReturnHistory(ret);
	}
	MyReadFile.close();
	for(Book b : library->getBookList()) {
		for (Exemplar e : b.getExemplarList()) {
			if (exemplarloaned.find(e.geteditionNumber()) != exemplarloaned.end()) {
				if (exemplarloaned[e.geteditionNumber()] > 0) {
					Member m;
					b.lendExemplar(m);
					library->setBookfromIndex(library->getBookIndexfromList(b.getISBNcode()), b);
					cout << "hay";
				}
			}
		}
	}

}

std::vector<std::string> explode(std::string const& s, char delim)
{
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim); )
	{
		result.push_back(std::move(token));
	}

	return result;
}

void Presenter::menu()
{
	view->showMenu();
	char ch = _getch();
	cout << ch;
	switch (ch) {

	case '1':
		addLoan_ChooseMember(0);
		break;
	case '2':
		loanHistory();
		break;
	case '3':
		addReturn_ChooseMember(0);
		break;
	case '4':
		returnHistory();
		break;
	case '5':
		membersMenu();
		break;
	case '6':
		bookMenu();
		break;
	case '7':
		bookExemplars(0);
		break;
	case '8':
		exit(0);
		break;
	default:
		menu();
	}
}

void Presenter::loanHistory()
{
	view->loanHistory(library->getLoanHistory());
	_getch();
	menu();
}

void Presenter::returnHistory()
{
	view->returnHistory(library->getReturnHistory());
	_getch();
	menu();
}

void Presenter::membersMenu()
{
	view->membersMenu();
	char ch = _getch();
	cout << ch;
	switch (ch) {
	case '1':
		membersList();
		break;
	case '2':
		membersNew(0,0);
		break;
	case '3':
		membersDelete();
		break;
	case esc:
		menu();
		break;
	default:
		membersMenu();
	}
}

void Presenter::membersList()
{
	view->membersList(library->getmemberList());
	_getch();
	membersMenu();
}

void Presenter::membersNew(int step, int error)
{
	int type;
	if (step == 0) {
		view->memberNew(0, error);
		getline(std::cin, member_name);
		if (member_name == "") {
			membersNew(0, 1);
		}
		else {
			error = 0;
		}
	}
	if (step == 0 || step == 1) {
		view->memberNew(1, error);
		getline(std::cin, member_lastname);
		if (member_lastname == "") {
			membersNew(1, 1);
		}
		else {
			error = 0;
		}
	}
	if (step == 0 || step == 2) {
		view->memberNew(2, error);
		getline(std::cin, member_number);
		if (member_number == "") {
			membersNew(2, 1);
		}
		else {
			error = 0;
		}
	}
	if (step == 0 || step == 3) {
		view->memberNew(3, error);
		getline(std::cin, member_stringtype);
		try {
			type = stoi(member_stringtype);
			if (type != 0 && type != 1) {
				membersNew(3, 1);
			}
			else {
				if (type == 0) {
					Member m;
					m.setName(member_name);
					m.setLastName(member_lastname);
					m.setIDnumber(member_number);
					library->addMember(m);
				}
				else if (type == 1) {
					VIP v;
					v.setName(member_name);
					v.setLastName(member_lastname);
					v.setIDnumber(member_number);
					library->addMember(v);
				}
				saveMembersToFile();
				membersMenu();
			}
		}
		catch (...) {
			membersNew(3, 1);
		}
	}
}

void Presenter::saveMembersToFile() {
	ofstream MyFile("members.txt");
	vector<Member> list = library->getmemberList();
	vector<Member>::iterator iter;

	// use iterator with for loop
	for (iter = list.begin(); iter != list.end(); ++iter) {
		MyFile << iter->getName() << "ƒ";
		MyFile << iter->getLastname() << "ƒ";
		MyFile << iter->getIdnumber() << "ƒ";
		MyFile << iter->getTypeRaw() << "\n";
	}
	MyFile.close();
}

void Presenter::membersDelete()
{
	view->memberDelete(library->getmemberList());
	string number;
	getline(std::cin, number);
	if (number == "q") {
		membersMenu();
	}
	else {
		int indexToDelete = library->getMemberIndexfromList(number);
		cout << indexToDelete;
		if (indexToDelete == -1) {
			membersDelete();
		}
		else {
			library->deleteMemberByIndex(indexToDelete);
			saveMembersToFile();
			membersMenu();
		}
	}
}

void Presenter::addLoan_ChooseMember(int error)
{
	string number;
	Book selectedBook;
	view->addLoan(0, library->getmemberList(), library->getBookList(), selectedBook,error);
	getline(std::cin, number);
	if (number == "q") {
		menu();
	}
	else {
		int memberindex = library->getMemberIndexfromList(number);
		cout << memberindex;
		if (memberindex == -1) { // No existe el miembro seleccionado
			addLoan_ChooseMember(1);
		}
		else { // Existe el miembro, ahora pido el libro
			if (library->getMemberfromIndex(memberindex).canBorrow()) {
				addLoan_ChooseBook(memberindex);
			}
			else {
				addLoan_ChooseMember(2);
			}
			
		}
	}
}

void Presenter::addLoan_ChooseBook(int memberindex)
{
	string number, booknumber;
	Book selectedBook;
	view->addLoan(1, library->getmemberList(), library->getBookList(), selectedBook,0);
	getline(std::cin, booknumber);
	if (booknumber == "q") {
		menu();
	}
	else {
		int bookindex = library->getBookIndexfromList(booknumber);
		if (bookindex == -1) { // No existe el libro seleccionado
			addLoan_ChooseBook(memberindex);
		}
		else {
			addLoan_Save(memberindex, bookindex);
		}
	}
}

void Presenter::addLoan_ChooseExemplar(int memberindex, int bookindex)
{
	string exemplarnumber;
	Book selectedbook = library->getBookfromIndex(bookindex);
	view->addLoan(2, library->getmemberList(), library->getBookList(), selectedbook,0);
	getline(std::cin, exemplarnumber);
	if (exemplarnumber == "q") {
		menu();
	}
	else {
		int exemplarindex = selectedbook.getExemplarIndexfromList(stoi(exemplarnumber));
		if (exemplarindex == -1) { // No existe el ejemplar seleccionado
			addLoan_ChooseExemplar(memberindex,bookindex);
		}
		else {
			addLoan_Save(memberindex, bookindex);
		}
	}
}

void Presenter::addLoan_Save(int memberindex, int bookindex)
{
	Member member = library->getMemberfromIndex(memberindex);
	Book book = library->getBookfromIndex(bookindex);
	if (book.hasExemplars()) {
		Exemplar exemplar = book.lendExemplar(member);
		exemplar.setBookName(book.getName());
		Loan loan(exemplar, member);
		member.Borrow(exemplar);
		library->setBookfromIndex(bookindex, book);
		library->setMemberfromIndex(memberindex, member);
		library->addLoanHistory(loan);
		saveLoanOnFile(loan);
		view->showLoan(exemplar,book);
		_getch();
		menu();
	}
	else {
		view->showNoExemplars();
		_getch();
		menu();
	}
}

void Presenter::addReturn_ChooseMember(int error)
{
	string number;
	Book selectedBook;
	vector<Exemplar> empty;
	view->addReturn(0, library->getmemberList(), empty, error);
	getline(std::cin, number);
	if (number == "q") {
		menu();
	}
	else {
		int memberindex = library->getMemberIndexfromList(number);
		if (memberindex == -1) { // No existe el miembro seleccionado
			addReturn_ChooseMember(1);
		}
		else { // Existe el miembro
			if (library->getMemberfromIndex(memberindex).getBooksLoaned() > 0) {
				addReturn_ChooseExemplar(memberindex,1,0);
			}
			else {
				addReturn_ChooseMember(2);
			}
		}
	}
}

void Presenter::addReturn_ChooseExemplar(int memberindex, int param, int error)
{
	string exemplarnumber;
	view->addReturn(param, library->getmemberList(), library->getMemberfromIndex(memberindex).getExemplarList(), error);
	getline(std::cin, exemplarnumber);
	if (exemplarnumber == "q") {
		menu();
	}
	else {
		try {
			vector<Exemplar> exemplarmemberlist = library->getMemberfromIndex(memberindex).getExemplarList();
			int exemplarindex = library->getExemplarfromList(exemplarmemberlist, stoi(exemplarnumber));
			if (exemplarindex == -1) { // No existe el ejemplar seleccionado
				addReturn_ChooseExemplar(memberindex, 1, 1);
			}
			else { // Existe el miembro
				addReturn_Save(memberindex, exemplarmemberlist[exemplarindex]);
			}
		}
		catch (...) {
			addReturn_ChooseExemplar(memberindex, 1, 1);
		}
	}

}

void Presenter::addReturn_Save(int memberindex, Exemplar e)
{
	Member member = library->getMemberfromIndex(memberindex);
	member.returnExemplar(e);
	library->setMemberfromIndex(memberindex, member);
	Book book = library->getBookfromIndex(library->getBookIndexfromList(e.getBookISBNcode()));
	e.setBookName(book.getName());
	book.returnExemplar(e);
	library->setBookfromIndex(library->getBookIndexfromList(e.getBookISBNcode()), book);
	Return ret(e,member);
	library->addReturnHistory(ret);
	saveReturnOnFile(ret);
	menu();
}

void Presenter::saveLoanOnFile(Loan loan)
{
	ofstream MyFile;
	MyFile.open("loan.txt", std::ios::app);
	MyFile << loan.getExemplar().getBookISBNcode() << "ƒ";
	MyFile << loan.getExemplar().geteditionNumber() << "ƒ";
	MyFile << loan.getDateRaw() << "ƒ";
	MyFile << loan.getMember().getIdnumber() << "\n";
	MyFile.close();
}

void Presenter::saveReturnOnFile(Return ret)
{
	ofstream MyFile;
	MyFile.open("return.txt", std::ios::app);
	MyFile << ret.getExemplar().getBookISBNcode() << "ƒ";
	MyFile << ret.getExemplar().geteditionNumber() << "ƒ";
	MyFile << ret.getDateRaw() << "ƒ";
	MyFile << ret.getMember().getIdnumber() << "\n";
	MyFile.close();
}

void Presenter::bookMenu()
{
	view->bookMenu();
	char ch = _getch();
	cout << ch;
	switch (ch) {
	case '1':
		bookList();
		break;
	case '2':
		bookNew(0,0);
		break;
	case '3':
		bookDelete();
		break;
	case esc:
		menu();
		break;
	default:
		bookMenu();
	}
}

void Presenter::bookList()
{
	view->bookList(library->getBookList());
	_getch();
	bookMenu();
}

void Presenter::bookNew(int step, int error)
{

	if (step == 0) {
		view->bookNew(0,error);
		getline(std::cin, book_ISBNcode);
		if (book_ISBNcode == "") {
			bookNew(0, 1);
		}
		else {
			error = 0;
			step = 0;
		}
	}

	if (step == 0 || step == 1) {
		view->bookNew(1, error);
		getline(std::cin, book_name);
		if (book_name == "") {
			bookNew(1, 1);
		}
		else {
			error = 0;
			step = 0;
		}
	}

	if (step == 0 || step == 2) {
		view->bookNew(2, error);
		getline(std::cin, book_autor);
		if (book_autor == "") {
			bookNew(2, 1);
		}
		else {
			error = 0;
			step = 0;
		}
	}

	Book b;
	b.setISBNcode(book_ISBNcode);
	b.setName(book_name);
	b.setAuthor(book_autor);
	library->addBook(b);
	saveBooksToFile();
	bookMenu();
}

void Presenter::saveBooksToFile() {
	ofstream MyFile("books.txt");
	vector<Book> list = library->getBookList();
	vector<Book>::iterator iter;

	// use iterator with for loop
	for (iter = list.begin(); iter != list.end(); ++iter) {
		MyFile << iter->getName() << "ƒ";
		MyFile << iter->getISBNcode() << "ƒ";
		MyFile << iter->getAuthor() << "\n";
	}
	MyFile.close();
}

void Presenter::bookDelete()
{
	view->bookDelete(library->getBookList());
	string number;
	getline(std::cin, number);
	if (number == "q") {
		bookMenu();
	}
	else {
		int indexToDelete = library->getBookIndexfromList(number);
		cout << indexToDelete;
		if (indexToDelete == -1) {
			bookDelete();
		}
		else {
			library->deleteBookByIndex(indexToDelete);
			saveBooksToFile();
			bookMenu();
		}
	}
}

void Presenter::exemplarMenu(Book book, int index)
{
	view->exemplarMenu(book);
	char ch = _getch();
	cout << ch;
	switch (ch) {
	case '1':
		exemplarList(book,index);
		break;
	case '2':
		exemplarNew(book,index,0,0);
		break;
	case '3':
		exemplarDelete(book,index);
		break;
	case esc:
		menu();
		break;
	default:
		exemplarMenu(book,index);
	}
}



void Presenter::exemplarList(Book book,int index)
{
	view->exemplarList(book.getExemplarList(),book);
	_getch();
	exemplarMenu(book,index);
}

void Presenter::exemplarNew(Book book, int index, int step, int error)
{
	if (step == 0) {
		view->exemplarNew(0, book, error);
		getline(std::cin, exemplar_en);
		try {
			exemplar_editionNumber = stoi(exemplar_en);
			error = 0;
		}
		catch (...) {
			exemplarNew(book, index, 0, 1);
			step = 1;
		}
	}
	if (step == 0 || step == 1) {
		view->exemplarNew(1, book, error);
		getline(std::cin, exemplar_location);
		if (exemplar_location == "") {
			exemplarNew(book,index, 1, 1);
		}
	}


	Exemplar exemplar;
	exemplar.seteditionNumber(exemplar_editionNumber);
	exemplar.setLocation(exemplar_location);
	exemplar.setBookISBNcode(book.getISBNcode());
	book.addExemplar(exemplar);
	library->setBookfromIndex(index,book);
	saveExemplarsToFile(book);
	exemplarMenu(book, index);
}

void Presenter::saveExemplarsToFile(Book book) {
	ofstream MyFile("exemplars.txt");

	vector<Book> list = library->getBookList();
	vector<Book>::iterator iter;

	// use iterator with for loop
	for (iter = list.begin(); iter != list.end(); ++iter) {
		vector<Exemplar> elist = iter->getExemplarList();
		vector<Exemplar>::iterator iter2;
		for (iter2 = elist.begin(); iter2 != elist.end(); ++iter2) {
			MyFile << iter->getISBNcode() << "ƒ";
			MyFile << iter2->geteditionNumber() << "ƒ";
			MyFile << iter2->getLocation() << "\n";
		}

	}
	MyFile.close();
}

void Presenter::exemplarDelete(Book b, int index)
{
	view->exemplarDelete(b.getExemplarList(),b);
	int number;
	string n;
	getline(std::cin, n);
	if (n == "q") {
		exemplarMenu(b,index);
	} else {
		try {
			number = stoi(n);
		}
		catch (...) {
			exemplarDelete(b, index);
		}
		int indexToDelete = b.getExemplarIndexfromList(number);
		cout << indexToDelete;
		if (indexToDelete == -1) {
			exemplarDelete(b,index);
		}
		else {
			b.deleteExemplarByIndex(indexToDelete);
			library->setBookfromIndex(index,b);
			saveExemplarsToFile(b);
			exemplarMenu(b, index);
		}
	}
}

void Presenter::bookExemplars(int error)
{
	string number, booknumber;
	Book selectedBook;
	view->exemplarBook(library->getBookList(),error);
	getline(std::cin, booknumber);
	if (booknumber == "q") {
		menu();
	}
	else {
		int bookindex = library->getBookIndexfromList(booknumber);
		if (bookindex == -1) { // No existe el libro seleccionado
			bookExemplars(1);
		}
		else {
			exemplarMenu(library->getBookfromIndex(bookindex),bookindex);
		}
	}
}
