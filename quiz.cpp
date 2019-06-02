#include "quiz.h"
#include <fstream>
#include <windows.h>
#include <limits>
#include <random>
#include <windows.h>
#undef max

namespace Quiz
{
	void ustaw_kolor(const kolor kolor)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, kolor);
	}

	void flush()
	{
		std::wcin.clear();
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	std::wstring set_path(const std::string& path)
	{
		if (path.empty())
		{
			return L"slowka.txt";
		}
		else
		{
			std::wstring result;
			result.assign(path.begin(), path.end());
			return result;
		}
	}

	int Pytanie::get_nr_pytania() const { return m_nr_pytania; }

	void Pytanie::set_nr_pytania(const unsigned int numer) { m_nr_pytania = numer; }

	std::wstring Pytanie::get_slowko() const { return m_slowko; }

	void Pytanie::set_slowko(const std::wstring& text) { m_slowko = text; }

	std::wstring Pytanie::get_tlumaczenie() const { return m_tlumaczenie; }

	void Pytanie::set_tlumaczenie(const std::wstring& text) { m_tlumaczenie = text; }

	std::wstring Pytanie::get_odpowiedz() const { return m_odpowiedz; }

	void Pytanie::set_odpowiedz(const std::wstring& text) { m_odpowiedz = text; }

	bool Pytanie::get_czy_dobrze() const { return m_czy_dobra_odpowiedz; }

	void Pytanie::set_czy_dobrze(const bool flaga) { m_czy_dobra_odpowiedz = flaga; }

	Pytanie::Pytanie(const std::wstring& s = L"", const std::wstring& t = L"", const std::wstring& o = L"", int nr = 0, bool czy = false)
		: m_slowko(s), m_tlumaczenie(t), m_odpowiedz(o), m_nr_pytania(nr), m_czy_dobra_odpowiedz(czy)
	{
	}

	Pytanie::~Pytanie() { }

	void Pytanie::zadaj()
	{
		std::string odp{};
		std::wstring wodp{};
		std::wcout << L"\t\t" << get_tlumaczenie() << L"?\n";
		std::wcout << L"\tOdp: ";
		getline(std::cin, odp);
		wodp.assign(odp.begin(), odp.end());
		set_odpowiedz(wodp);
	}

	bool Pytanie::sprawdz_odpowiedz()
	{
		if (get_odpowiedz() == get_slowko())
		{
			set_czy_dobrze(true);
			ustaw_kolor(zielony);
			std::wcout << L"\tDobrze!\n\n";
			ustaw_kolor(bialy);
			Sleep(700);
			system("cls");
			return true;
		}
		else
		{
			ustaw_kolor(czerwony);
			std::wcout << L"  le!\n";
			std::wcout << "  Poprawna odp to: " << get_slowko() << L"\n\n";
			ustaw_kolor(bialy);
			flush();
			system("cls");
			return false;
		}
	}

	size_t losuj_pytanie(const std::vector<Pytanie>& pytania)
	{
		std::random_device random;
		std::mt19937 mt(random());
		std::uniform_int_distribution<unsigned int> dist(1, pytania.size());

		return dist(mt) - 1;
	}

	bool wczytaj(const std::wstring& path, std::vector<Pytanie>& pytania)
	{
		std::wifstream in_file;
		in_file.open(path);
		if (!in_file)
		{
			in_file.clear();
			in_file.close();
			return false;
		}
		else
		{
			int aktualny_nr{};
			std::wstring linia{};

			while (!in_file.eof())
			{

				getline(in_file, linia);
				if (aktualny_nr % 2 == 0)
				{
					pytania.push_back(Quiz::Pytanie::Pytanie());
					pytania[aktualny_nr / 2].set_nr_pytania((aktualny_nr / 2) + 1);
					pytania[aktualny_nr / 2].set_slowko(linia);
				}
				else
				{
					pytania[aktualny_nr / 2].set_tlumaczenie(linia);
				}

				aktualny_nr++;
			}

			in_file.close();
			return true;
		}
	}
}