#include "View.h"

void View::showMenu() {
	system("CLS");
	cout << "BIBLIOTECA - MENU PRINCIPAL\n";
	cout << "-----------------------------------------------------\n";
	cout << "\n";
	cout << "1) Prestamo\n";
	cout << "2) Historial de Prestamos\n";
	cout << "3) Devolucion\n";
	cout << "4) Historial de Devoluciones\n";
	cout << "5) Socios\n";
	cout << "6) Libros\n";
	cout << "7) Ejemplares\n";
	cout << "8) Salir\n";
	cout << "\n";
	cout << "SELECCIONE UNA OPCION DEL MENU: ";
}

void View::loanHistory(vector<Loan> loans)
{
	system("CLS");
	cout << "BIBLIOTECA - HISTORIAL DE PRESTAMOS\n";
	cout << "-----------------------------------------------------\n";
	if ((int)loans.size() == 0) {
		cout << "No hay historial de prestamos\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione cualquier tecla para volver al menu principal";
	}
	else {
		vector<Loan>::iterator iter;
		for (iter = loans.begin(); iter != loans.end(); ++iter) {
			cout << "Fecha: " << iter->getDate() << "\n";
			cout << "Libro: " << iter->getExemplar().getBookName() << " (" << iter->getExemplar().getBookISBNcode() << ")" << "\n";
			cout << "Ejemplar: " << iter->getExemplar().geteditionNumber() << "\n";
			cout << "Socio: " << iter->getMember().getName() << " " << iter->getMember().getLastname() << "\n";
			cout << "-----------------------------------------------------\n";
		}		
		cout << "Presione cualquier tecla para volver al menu principal";
	}
}

void View::returnHistory(vector<Return> r)
{
	system("CLS");
	cout << "BIBLIOTECA - HISTORIAL DE DEVOLUCIONES\n";
	cout << "-----------------------------------------------------\n";
	if ((int)r.size() == 0) {
		cout << "No hay historial de devoluciones\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione cualquier tecla para volver al menu principal";
	}
	else {
		vector<Return>::iterator iter;
		for (iter = r.begin(); iter != r.end(); ++iter) {
			cout << "Fecha: " << iter->getDate() << "\n";
			cout << "Libro: " << iter->getExemplar().getBookName() << " (" << iter->getExemplar().getBookISBNcode()  << ")" << "\n";
			cout << "Ejemplar: " << iter->getExemplar().geteditionNumber() << "\n";
			cout << "Socio: " << iter->getMember().getName() << " " << iter->getMember().getLastname() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Presione cualquier tecla para volver al menu principal";
	}
}

void View::membersMenu()
{
	system("CLS");
	cout << "BIBLIOTECA - SOCIOS\n";
	cout << "-----------------------------------------------------\n";
	cout << "\n";
	cout << "1) Listado de Socios\n";
	cout << "2) Nuevo Socio\n";
	cout << "3) Eliminar Socio\n";
	cout << "esc) Volver\n";
	cout << "\n";
	cout << "SELECCIONE UNA OPCION DEL MENU: ";
}

void View::membersList(vector<Member> members)
{
	system("CLS");
	cout << "BIBLIOTECA - LISTADO DE SOCIOS\n";
	cout << "-----------------------------------------------------\n";
	if ((int)members.size() == 0) {
		cout << "No hay socios\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione cualquier tecla para volver al menu principal";
	}
	else {
		vector<Member>::iterator iter;
		for (iter = members.begin(); iter != members.end(); ++iter) {
			cout << "Socio #: " << iter->getIdnumber() << "\n";
			cout << "Nombre: " << iter->getName() << "\n";
			cout << "Apellido: " << iter->getLastname() << "\n";			
			cout << "Tipo: " << iter->getType() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Presione cualquier tecla para volver al menu principal";
	}
}

void View::memberNew(int param, int error)
{
	if (param == 0) {
		system("CLS");
		cout << "BIBLIOTECA - NUEVO SOCIO\n";
		cout << "-----------------------------------------------------\n";
	}

	if (param == 0) {
		if (error == 1) {
			//system("CLS");
			cout << "\033[31m" << "Ingrese Nombre\n" << "\033[0m";
		}
		cout << "Nombre: ";
	} else 	if (param == 1) {
		if (error == 1) {
			//system("CLS");
			cout << "\033[31m" << "Ingrese Apellido\n" << "\033[0m";
		}
		cout << "Apellido: ";
	}
	else if (param == 2) {
		if (error == 1) {
			//system("CLS");
			cout << "\033[31m" << "Ingrese numero de socio correcto\n" << "\033[0m";
		}
		cout << "Numero Socio: ";
	} else if (param == 3) {
		if (error == 1) {
			//system("CLS");
			cout << "\033[31m" << "Ingrese tipo de socio correcto (0,1)\n" << "\033[0m";
		}
		cout << "Tipo de Socio (0- Regular, 1 - VIP): ";
	}
}

void View::memberDelete(vector<Member> members)
{
	system("CLS");
	cout << "BIBLIOTECA - Eliminar Socio\n";
	cout << "-----------------------------------------------------\n";
	if ((int)members.size() == 0) {
		cout << "No hay socios\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Member>::iterator iter;
		for (iter = members.begin(); iter != members.end(); ++iter) {
			cout << "# "  << iter->getIdnumber() << " - " << iter->getName() << " " << iter->getName() << " - " << iter->getType() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Ingrese el numero de socio # ((q) para volver): ";
	}
}

void View::addLoan(int param, vector<Member> members, vector<Book> books, Book selectedbook, int error)
{
	system("CLS");
	cout << "BIBLIOTECA - REALIZAR PRESTAMO DE LIBRO\n";
	cout << "-----------------------------------------------------\n";
	if (error == 1) {
		cout << "\033[31m" << "El numero de socio ingresado no existe\n" << "\033[0m";
		cout << "-----------------------------------------------------\n";
	}
	if (param == 0) {
		if (error == 2) {
			cout << "\033[31m" << "El socio seleccionado no puede pedir mas prestamos\n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Seleccione Socio\n";
		cout << "-----------------------------------------------------\n";
		if ((int)members.size() == 0) {
			cout << "\033[31m" << "No hay socios \n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
			cout << "Presione (q) para volver: ";
		}
		else {
			vector<Member>::iterator iter;
			for (iter = members.begin(); iter != members.end(); ++iter) {
				cout << "# "  << iter->getIdnumber() << " - " << iter->getName() << " " << iter->getLastname() << " - " << iter->getType() << " - Tiene " << iter->getBooksLoaned() << " prestamo(s)" "\n";
				cout << "-----------------------------------------------------\n";
			}
			cout << "Ingrese el numero de socio # ((q) para volver): ";
		}
	}
	else if (param == 1) {
		cout << "Seleccione Libro\n";
		cout << "-----------------------------------------------------\n";
		if ((int)books.size() == 0) {
			cout << "\033[31m" << "No hay libros ingresados \n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
			cout << "Presione (q) para volver: ";
		}
		else {
			vector<Book>::iterator iter;
			for (iter = books.begin(); iter != books.end(); ++iter) {
				cout << "# "  << iter->getISBNcode() << " - " << iter->getName() << " - " << "disponibles " << iter->availableExemplars() << " ejemplares" << "\n";
				cout << "-----------------------------------------------------\n";
			}
			cout << "Ingrese el codigo del ejemplar # ((q) para volver): ";
		}
	}
}

void View::showLoan(Exemplar exemplar, Book book)
{
	system("CLS");
	cout << "BIBLIOTECA - REALIZAR PRESTAMO DE LIBRO\n";
	cout << "-----------------------------------------------------\n";
	cout << "\033[32m" << "Se presto el siguiente ejemplar\n" << "\033[0m";
	cout << "-----------------------------------------------------\n";
	cout << "Nombre del libro: " << book.getName() << "\n";
	cout << "Numero de Ejemplar: " << exemplar.geteditionNumber() << "\n";
	cout << "Ubicacion: " << exemplar.getLocation() << "\n";
	cout << "-----------------------------------------------------\n";
	cout << "Presione una tecla para volver al menu\n";
}

void View::showNoExemplars()
{
	system("CLS");
	cout << "BIBLIOTECA - REALIZAR PRESTAMO DE LIBRO\n";
	cout << "-----------------------------------------------------\n";
	cout << "\033[31m" << "No hay ejemplares disponibles para prestar\n" << "\033[0m";
	cout << "-----------------------------------------------------\n";
	cout << "Presione una tecla para volver al menu\n";
}

void View::addReturn(int param, vector<Member> members, vector<Exemplar> exemplars, int error)
{
	system("CLS");
	cout << "BIBLIOTECA - REALIZAR DEVOLUCION DE LIBRO\n";
	cout << "-----------------------------------------------------\n";
	if (param == 0) {
		if (error == 1) {
			cout << "\033[31m" << "El numero de socio ingresado no existe\n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
		}
		if (error == 2) {
			cout << "\033[31m" << "El socio seleccionado no tiene prestamos a devolver\n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Seleccione Socio\n";
		cout << "-----------------------------------------------------\n";
		if ((int)members.size() == 0) {
			cout << "\033[31m" << "No hay socios \n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
			cout << "Presione (q) para volver: ";
		}
		else {
			vector<Member>::iterator iter;
			for (iter = members.begin(); iter != members.end(); ++iter) {
				cout << "# "  << iter->getIdnumber() << " - " << iter->getName() << " " << iter->getLastname() << " - " << iter->getType() << " - Tiene " << iter->getBooksLoaned() << " prestamo(s)" "\n";
				cout << "-----------------------------------------------------\n";
			}
			cout << "Ingrese el numero de socio # ((q) para volver): ";
		}
	}
	else if (param == 1) {
		if (error == 1) {
			cout << "\033[31m" << "El codigo del ejemplar no existe\n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Seleccione Ejemplar a Devolver\n";
		cout << "-----------------------------------------------------\n";
		if ((int)exemplars.size() == 0) {
			cout << "\033[31m" << "El socio no tiene ejemplares a devolver \n" << "\033[0m";
			cout << "-----------------------------------------------------\n";
			cout << "Presione (q) para volver: ";
		}
		else {
			vector<Exemplar>::iterator iter;
			for (iter = exemplars.begin(); iter != exemplars.end(); ++iter) {
				cout << "# " << iter->geteditionNumber() << " - " << iter->getBookName() << " (" << iter->getBookISBNcode() << ") - " << iter->getLocation() << "\n";
				cout << "-----------------------------------------------------\n";
			}
			cout << "Ingrese el codigo del ejemplar # ((q) para volver): ";
		}
	}
}

void View::bookMenu()
{
	system("CLS");
	cout << "BIBLIOTECA - LIBROS\n";
	cout << "-----------------------------------------------------\n";
	cout << "\n";
	cout << "1) Listado de Libros\n";
	cout << "2) Nuevo Libro\n";
	cout << "3) Eliminar Libro\n";
	cout << "esc) Volver\n";
	cout << "\n";
	cout << "SELECCIONE UNA OPCION DEL MENU: ";
}

void View::bookList(vector<Book> books)
{
	system("CLS");
	cout << "BIBLIOTECA - LISTADO DE LIBROS\n";
	cout << "-----------------------------------------------------\n";
	if ((int)books.size() == 0) {
		cout << "No hay libros\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Book>::iterator iter;
		for (iter = books.begin(); iter != books.end(); ++iter) {
			cout << "Codigo ISBN #: " << iter->getISBNcode() << "\n";
			cout << "Nombre: " << iter->getName() << "\n";
			cout << "Autor: " << iter->getAuthor() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Presione cualquier tecla para volver al menu principal";
	}
}

void View::bookNew(int param,int error)
{
	if (param == 0) {
		system("CLS");
		cout << "BIBLIOTECA - NUEVO LIBRO\n";
		cout << "-----------------------------------------------------\n";
	}

	if (param == 0) {
		if (error == 1) {
			cout << "\033[31m" << "Ingrese Codigo ISBN\n" << "\033[0m";
		}
		cout << "Codigo ISBN: ";
	}
	else if (param == 1) {
		if (error == 1) {
			cout << "\033[31m" << "Ingrese Nombre\n" << "\033[0m";
		}
		cout << "Nombre: ";
	}
	else if (param == 2) {
		if (error == 1) {
			cout << "\033[31m" << "Ingrese Autor\n" << "\033[0m";
		}
		cout << "Autor: ";
	}
}

void View::bookDelete(vector<Book> books)
{
	system("CLS");
	cout << "BIBLIOTECA - Eliminar Libro\n";
	cout << "-----------------------------------------------------\n";
	if ((int)books.size() == 0) {
		cout << "No hay libros\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Book>::iterator iter;
		for (iter = books.begin(); iter != books.end(); ++iter) {
			cout << "# " << iter->getISBNcode() << " - " << iter->getName() << " " << iter->getAuthor() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Ingrese el numero de libro # ((q) para volver): ";
	}
}

void View::exemplarMenu(Book book)
{
	system("CLS");
	cout << "BIBLIOTECA - EJEMPLARES\n";
	cout << "-----------------------------------------------------\n";
	cout << book.getName() << "(" << book.getISBNcode() << ")" << "\n";
	cout << "-----------------------------------------------------\n";
	cout << "\n";
	cout << "1) Listado de Ejemplares\n";
	cout << "2) Nuevo Ejemplar\n";
	cout << "3) Eliminar Ejemplar\n";
	cout << "esc) Volver\n";
	cout << "\n";
	cout << "SELECCIONE UNA OPCION DEL MENU: ";
}

void View::exemplarList(vector<Exemplar> exemplar, Book book)
{
	system("CLS");
	cout << "BIBLIOTECA - LISTADO DE EJEMPLARES\n";
	cout << "-----------------------------------------------------\n";
	cout << book.getName() << "(" << book.getISBNcode() << ")" << "\n";
	cout << "-----------------------------------------------------\n";
	if ((int)exemplar.size() == 0) {
		cout << "No hay ejemplares\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Exemplar>::iterator iter;
		for (iter = exemplar.begin(); iter != exemplar.end(); ++iter) {
			cout << "Numero Edicion #: " << iter->geteditionNumber() << "\n";
			cout << "Ubicacion: " << iter->getLocation() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Presione cualquier tecla para volver al menu principal";
	}
}

void View::exemplarNew(int param, Book book, int error)
{
	if (param == 0) {
		system("CLS");
		cout << "BIBLIOTECA - NUEVO EJEMPLAR\n";
		cout << "-----------------------------------------------------\n";
		cout << book.getName() << "(" << book.getISBNcode() << ")" << "\n";
		cout << "-----------------------------------------------------\n";
	}

	if (param == 0) {
		if (error == 1) {
			cout << "\033[31m" << "Ingrese Numero de edicion valido\n" << "\033[0m";
		}
		cout << "Numero de edicion: ";
	}
	else 	if (param == 1) {
		if (error == 1) {
			cout << "\033[31m" << "Ingrese Ubicacion valida\n" << "\033[0m";
		}
		cout << "Ubicacion: ";
	}
}

void View::exemplarDelete(vector<Exemplar> exemplar, Book book)
{
	system("CLS");
	cout << "BIBLIOTECA - Eliminar Ejemplar\n";
	cout << "-----------------------------------------------------\n";
	cout << book.getName() << "(" << book.getISBNcode() << ")" << "\n";
	cout << "-----------------------------------------------------\n";
	if ((int)exemplar.size() == 0) {
		cout << "No hay ejemplares\n";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Exemplar>::iterator iter;
		for (iter = exemplar.begin(); iter != exemplar.end(); ++iter) {
			cout << "# " << iter->geteditionNumber() << " - " << iter->getLocation() << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Ingrese el numero de ejemplar # ((q) para volver): ";
	}
}

void View::exemplarBook(vector<Book> books, int error)
{
	system("CLS");
	cout << "BIBLIOTECA - EJEMPLARES\n";
	cout << "-----------------------------------------------------\n";
	cout << "Seleccione Libro\n";
	cout << "-----------------------------------------------------\n";
	if (error == 1) {
		cout << "\033[31m" << "El codigo del libro no es correcto \n" << "\033[0m";
		cout << "-----------------------------------------------------\n";
	}
	if ((int)books.size() == 0) {
		cout << "\033[31m" << "No hay libros ingresados \n" << "\033[0m";
		cout << "-----------------------------------------------------\n";
		cout << "Presione (q) para volver: ";
	}
	else {
		vector<Book>::iterator iter;
		for (iter = books.begin(); iter != books.end(); ++iter) {
			cout << "# " << iter->getISBNcode() << " - " << iter->getName() << " - " << "disponibles " << iter->availableExemplars() << " ejemplares" << "\n";
			cout << "-----------------------------------------------------\n";
		}
		cout << "Ingrese el codigo del libro # ((q) para volver): ";
	}
}
