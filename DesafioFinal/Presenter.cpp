#include "Presenter.h"

Presenter::Presenter()
{
	initializeBooks();
	initializeMembers();
	initializeLoanHistory();
	initializeReturnHistory();

	menu();
}

void Presenter::initializeBooks() {
	/**************** Libro 1 *************************/
	Book book;
	book.setName("Padre Rico, padre Pobre");
	book.setISBNcode("P435");
	book.setAuthor("Robert Kirosaki");
	Exemplar e(1010, "A54", book.getISBNcode());
	book.addExemplar(e);
	Exemplar e1(1001, "C76", book.getISBNcode());
	book.addExemplar(e1);
	Exemplar e2(1002, "A32", book.getISBNcode());
	book.addExemplar(e2);
	Exemplar e3(1003, "G87", book.getISBNcode());
	book.addExemplar(e3);
	Exemplar e4(1004, "H92", book.getISBNcode());
	book.addExemplar(e4);
	library->addBook(book);
	/**************** Libro 2 *************************/
	Book book1;
	book1.setName("Ocho millones de dioses");
	book1.setISBNcode("F574");
	book1.setAuthor("Juan Alberto");
	Exemplar e0(1005, "F43", book1.getISBNcode());
	book1.addExemplar(e0);
	Exemplar e01(1006, "T71", book1.getISBNcode());
	book1.addExemplar(e01);
	library->addBook(book1);
	/**************** Libro 3 *************************/
	Book book2;
	book2.setName("Harry Potter");
	book2.setISBNcode("J765");
	book2.setAuthor("JK Rowling");
	Exemplar e10(1007, "U35", book2.getISBNcode());
	book2.addExemplar(e10);
	library->addBook(book2);
	/**************** Libro 4 *************************/
	Book book3;
	book3.setName("Crepusculo");
	book3.setISBNcode("L654");
	book3.setAuthor("Stephenie Meyer");
	Exemplar e20(1008, "T39", book3.getISBNcode());
	book3.addExemplar(e20);
	Exemplar e21(1009, "Q81", book3.getISBNcode());
	book3.addExemplar(e21);
	library->addBook(book3);
}

void Presenter::initializeMembers()
{
	string myText;
	ifstream MyReadFile("members.txt");
	vector<std::string> val;
	while (getline(MyReadFile, myText)) {
		val = explode(myText, 'ƒ');
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
		cout << "Ejemplares";
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
		membersNew();
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

void Presenter::membersNew()
{
	string name, lastname, number, stringtype;
	int type;
	view->memberNew(0);
	getline(std::cin, name);
	view->memberNew(1);
	getline(std::cin, lastname);
	view->memberNew(2);
	getline(std::cin, number);
	view->memberNew(3);
	getline(std::cin, stringtype);
	type = stoi(stringtype);
	if (type == 0) {
		Member m;
		m.setName(name);
		m.setLastName(lastname);
		m.setIDnumber(number);
		library->addMember(m);
	} else if (type == 1) {
		VIP v;
		v.setName(name);
		v.setLastName(lastname);
		v.setIDnumber(number);
		library->addMember(v);
	}
	saveMembersToFile();
	membersMenu();
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
		bookNew();
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

void Presenter::bookNew()
{
	string name, autor, ISBNcode;
	view->bookNew(0);
	getline(std::cin, ISBNcode);
	view->bookNew(1);
	getline(std::cin, name);
	view->bookNew(2);
	getline(std::cin, autor);
	Book b;
	b.setISBNcode(ISBNcode);
	b.setName(name);
	b.setAuthor(autor);	
	library->addBook(b);
	saveBooksToFile();
	bookMenu();
}

void Presenter::saveBooksToFile() {
	ofstream MyFile("bookw.txt");
	vector<Book> list = library->getBookList();
	vector<Book>::iterator iter;

	// use iterator with for loop
	for (iter = list.begin(); iter != list.end(); ++iter) {
		MyFile << iter->getName() << "ƒ";
		MyFile << iter->getISBNcode() << "ƒ";
		MyFile << iter->getName() << "ƒ";
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
