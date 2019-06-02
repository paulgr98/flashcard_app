#include <iostream>
#include "quiz.h"
#include <string>
#include <io.h> //polskie znaki
#include <fcntl.h> //polskie znaki
#include <vector>

int main()
{
	int mode = _setmode(_fileno(stdout), _O_U16TEXT); //polskie znaki

	std::vector<Quiz::Pytanie> pytania;

	Quiz::ustaw_kolor(Quiz::zielony);
	std::wcout << L"\n  Œcie¿ka do pliku ze s³ówkami (puste = slowka.txt): ";
	Quiz::ustaw_kolor(Quiz::bialy);
	std::string sciezka{};
	getline(std::cin, sciezka);
	system("cls");

	if (Quiz::wczytaj(Quiz::set_path(sciezka), pytania))
	{
		unsigned int zostalo = pytania.size();
		unsigned int dobrych{};
		size_t numer{};

		while (zostalo > 0)
		{
			numer = Quiz::losuj_pytanie(pytania);
			if (pytania[numer].get_czy_dobrze() == false)
			{
				std::wcout << L"\n\n";
				std::wcout << L"   Pozosta³o ";
				Quiz::ustaw_kolor(Quiz::filoetowy);
				std::wcout << zostalo << L"/" << pytania.size() << L"\n";
				Quiz::ustaw_kolor(Quiz::bialy);

				std::wcout << L"   S³ówko nr ";
				Quiz::ustaw_kolor(Quiz::niebieski);
				std::wcout << pytania[numer].get_nr_pytania() << L"\n\n";
				Quiz::ustaw_kolor(Quiz::bialy);

				pytania[numer].zadaj();
				if (pytania[numer].sprawdz_odpowiedz() == true)
				{
					dobrych++;
					zostalo--;
				}
			}
		}
		Quiz::ustaw_kolor(Quiz::zielony);
		std::wcout << L"\n\n\t\tKONIEC!\n";
		Quiz::ustaw_kolor(Quiz::bialy);
		std::wcin.get();
	}
	else
	{
		Quiz::ustaw_kolor(Quiz::czerwony);
		std::wcout << L"\n\n\tNie ma takiego pliku dzbanie!\n";
		Quiz::ustaw_kolor(Quiz::bialy);
		std::wcin.get();
	}
}