#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Quiz
{
	enum kolor { zielony = 2, niebieski = 11, czerwony = 12, filoetowy = 13, bialy = 15 }; //kolory tekstu w konsoli

	void ustaw_kolor(const kolor kolor); //zmiana koloru tekstu w konsoli

	void flush(); //czyszczenie wcin i ignorowanie znaku enter

	std::wstring set_path(const std::string& path); //zwraca sciezkie do pliku ze slowkami

	class Pytanie
	{
	private:
		std::wstring m_slowko; //aktualne slowko
		std::wstring m_tlumaczenie; //aktualne tlumaczenie
		std::wstring m_odpowiedz; //aktualna odpowiedz
		int m_nr_pytania; //numer aktualnego slowka
		bool m_czy_dobra_odpowiedz; //flaga czy odpowiedz uzytkownika jest poprawna

	public:
		void zadaj(); //wyswietlanie pytania w konsoli
		bool sprawdz_odpowiedz(); //sprawdzanie czy odpowiedz jest poprawna
		int get_nr_pytania() const; //zwraca numer pytania
		void set_nr_pytania(const unsigned int numer); //ustawia numer pytania
		std::wstring get_slowko() const; //zwraca slowko
		void set_slowko(const std::wstring& text); //ustawia slowko
		std::wstring get_tlumaczenie() const; //zwraca tlumaczenie
		void set_tlumaczenie(const std::wstring& text); //ustawia tlumaczenie
		std::wstring get_odpowiedz() const; //zwraca opdowiedz
		void set_odpowiedz(const std::wstring& text); //ustawia odpowiedz
		bool get_czy_dobrze() const; //sprawdzenie wartosci flagi
		void set_czy_dobrze(const bool flaga); //ustawienie flagi

		Pytanie(const std::wstring& s, const std::wstring& t, const std::wstring& o, int nr, bool czy); //konstrukotr, ustawia wszystko na domyœlne (czyli na puste)
		~Pytanie(); //destruktor na razie nic nie robi
	};

	size_t losuj_pytanie(const std::vector<Pytanie>& pytania); //losowanie pytania z wektora

	bool wczytaj(const std::wstring& path, std::vector<Pytanie>& pytania); //wczytywanie pytan do wektora
}