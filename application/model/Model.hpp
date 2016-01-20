/**
 *  \file    Model.hpp
 *
 *  \authors Tomasz Jakubczyk, Andrzej Roguski
 *
 *  \brief   Plik nagłówkowy klasy Model.
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <array>
#include <vector>
#include <string>

#include "Graph.hpp"
#include "Path.hpp"
#include "Population.hpp"

#include "parameters.hpp"
#include "strategy.hpp"
#include "types.hpp"

#include "../controller/Event.hpp"
#include "../controller/BlockingQueue.hpp"
#include "../controller/Command.hpp"


/**
 * \brief Klasa główna modelu odpowiadająca za komunikację z kontrolerem
 */
class Model
{
public:
	Model();
	/**
	 * \breif            Generuje graf i zwraca do niego wskaźnik.
	 * \param[in] nodes  liczba węzłów
	 * \return           wskaźnik do wygenerowanego grafu
	 */
	Graph * generateGraph( const unsigned nodes, const GraphGenerator * const generator ) const;

	/**
	 * \brief           Wczytuje kody lotnisk z listy i tworzy graf na jej podstawie.
	 *                  Zakłada, że w danej linii jest co najwyżej jedna fraza <iata>KOD</iata>.
	 *                  Zakłada, że każda fraza <iata>KOD</iata> znajduje się w całości w jednej linii.
	 *
	 * \param[in] file  Ścieżka pliku z listą lotnisk
	 *
	 * \return          Liczba wczytanych lotnisk
	 */
	unsigned loadAirportList( const std::string file );

	/**
	 * \brief           Wczytuje kody IATA z listy i tworzy graf na jej podstawie.
	 *                  Zakłada, że w danej linii jest dokładnie jeden kod IATA.
	 *
	 * \param[in] file  Ścieżka pliku z listą IATA
	 *
	 * \return          Liczba wczytanych kodów
	 */
	unsigned loadIataList( const std::string file );

	/**
	 * \brief              Ustawia wagi parametrów trasy.
	 * \param[in]  weights Tablica wag przypisanych parametrom trasy
	 */
	void setWeights( const Weights & weights );

	/**
	 * \brief               Tworzy populację o zadanym rozmiarze.
	 * \param[in] size      rozmiar populacji (liczba parzysta; jeśli jest nieparzysta, model używa size + 1)
	 * \param[in] strategy  wskaźnik na strategię krzyżowania
	 * \param[in] mutation  wskaźnik na mutację
	 */
	void createPopulation( unsigned size, Strategy * strategy = nullptr, Mutation * mutation = nullptr );

	/**
	 * \brief              Krzyżuje osobniki.
	 * \param[in] times    liczba iteracji
	 * \param[in] strategy sposób krzyżowania
	 */
	void evolve( unsigned times );

	/**
	 * \brief              Ustala punkt końcowy i początkowy (resetuje populację)
	 * \param[in] start    punkt początkowy
	 * \param[in] end      punkt końcowy
	 */
	void setEndNodes( unsigned start, unsigned end );

	/**
	 * \brief              Ustala punkt końcowy i początkowy (resetuje populację)
	 * \param[in] start    punkt początkowy
	 * \param[in] end      punkt końcowy
	 */
	void setEndNodes( std::string start, std::string end );

	/**
	 * \brief               Ustawia strategię krzyżowania populacji.
	 * \param[in] strategy  wskaźnik na strategię krzyżowania
	 */
	void setStrategy( Strategy * strategy );

	/**
	 * \brief               Ustawia sposób działania mutacji.
	 * \param[in] mutation  wskaźnik na mutację
	 */
	void setMutation( Mutation * mutation );

	/**
	 * \brief  Zwraca wskaźnik do populacji.
	 * \return wskaźnik do populacji
	 */
	Population * getPopulation();

	/**
	 * \brief   Zwraca n-tą ścieżkę
	 * \return  n-ta najlepsza ścieżka
	 */
	Path getPath ( unsigned n );

	/**
	 * \brief   Zwraca n-tą ścieżkę jako wektor stringów IATA
	 * \return  n-ta najlepsza ścieżka
	 */
	std::vector<std::string> getPathIata ( unsigned n );
	
	/**
	 * \brief            Wczytuje graf z pamięci.
	 * \param[in] graph  graf do załadowania
	 */
	void useGraph( Graph * const graph );

	/**
	 * \brief            Wczytuje graf z pliku.
	 * \param[in] file   ściezka pliku z grafem
	 */
	void useGraph( const std::string & file );

	/**
	 * \brief            Zapisuje graf do pliku.
	 *                   Uwaga! Plik zostanie nadpisany, używać ostrożnie.
	 * \param[in] file   ściezka pliku do zapisu
	 * \param[in] graph  wskaźnik do grafu do zapisania,
	 *                   pominięcie parametru lub podanie nullptr zapisuje obecnie używany graf
	 */
	void saveGraph( const std::string & file, Graph * graph = nullptr ) const;



	/**
	 * \brief  Zadanie główne modelu.
	 *         Motoda zostaje uruchomiona w osobnym wątku i komunikuje się z kontrolerem
	 *         przez dwie kolejki blokujące: controllerBlockingQueue i modelBlockingQueue.
	 * \return void
	 */
	void doMainJob();

	/** \brief    Ustawia wskaźnik na kolejkę kontrolera.
	 *  \param q  BlockingQueue<Event*>*
	 *  \return   void
	 */
	void setControllerBlockingQueue(BlockingQueue<Event*>* q);

	/** \brief Metoda kończąca pracę głównego wątka modelu.
	 *         Ustawia shutDown.
	 * \return void
	 */
	void triggerShutDown();

private:
	unsigned start;

	unsigned end;

	friend class Controller;/**< \todo być może ładniej rozwiazać problemy */

	std::string getIATAbyId(int id);

	Graph * graph;

	Population * population;

	std::vector<std::string> airportList;

	BlockingQueue<Event*>* controllerBlockingQueue;/**< na tą kolejkę wrzucamy zgłoszenia do kontrolera */

	BlockingQueue<Command*>* modelBlockingQueue;/**< kolejka na którą mają przychodzić polecenia z kontrolera */

	bool shutDown;/**< czy nie zamykamy aplikacji */

	unsigned int evolutionStep;

	bool stopCalc;
};

#endif // MODEL_HPP
