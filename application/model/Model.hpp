/**
 *  \file Model.hpp
 *  \authors Tomasz Jakubczyk, Andrzej Roguski
 *  \brief Plik nagłówkowy klasy Model.
 *
 * \todo Andrzej napisze Model :D
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <array>
#include <string>

#include "Graph.hpp"
#include "Path.hpp"
#include "Population.hpp"

#include "parameters.hpp"
#include "strategy.hpp"

#include "../controller/Event.hpp"
#include "../controller/BlockingQueue.hpp"
#include "../controller/Command.hpp"

/**
 * \brief Na razie pusta/zaślepkowa klasa Modelu
 */
class Model
{
public:
	Model();
	/*
	 * \breif            Generuje graf i zwraca do niego wskaźnik.
	 * \param[in] nodes  liczba węzłów
	 * \return           wskaźnik do wygenerowanego grafu
	 */
	Graph * generateGraph( const unsigned nodes, const GraphGenerator * const generator ) const;

	/*
	 * \brief            Wczytuje graf z pamięci.
	 * \param[in] graph  graf do załadowania
	 */
	void useGraph( Graph * const graph );

	/*
	 * \brief            Wczytuje graf z pliku.
	 * \param[in] file   ściezka pliku z grafem
	 */
	void useGraph( const std::string & file );

	/*
	 * \brief            Zapisuje graf do pliku.
	 *                   Uwaga! Plik zostanie nadpisany, używać ostrożnie.
	 * \param[in] file   ściezka pliku do zapisu
	 * \param[in] graph  wskaźnik do grafu do zapisania,
	 *                   pominięcie parametru lub podanie nullptr zapisuje obecnie używany graf
	 */
	void saveGraph( const std::string & file, Graph * graph = nullptr ) const;

	/**
	 * \brief              Ustawia wagi parametrów trasy.
	 * \param[in]  weights Tablica wag przypisanych parametrom trasy
	 */
	void setWeights( const std::array<unsigned, (unsigned)Parameters::Count> & weights );

	/**
	 * \brief               Tworzy populację o zadanym rozmiarze.
	 * \param[in] size      rozmiar populacji (liczba parzysta; jeśli jest nieparzysta, model używa size + 1)
	 * \param[in] strategy  wskaźnik na strategię krzyżowania
	 * \param[in] mutation  wskaźnik na mutację
	 */
	void createPopulation( unsigned size, Strategy * strategy, Mutation * mutation );

	/**
	 * \brief              Krzyżuje osobniki.
	 * \param[in] times    liczba iteracji
	 * \param[in] strategy sposób krzyżowania
	 */
	void evolve( unsigned times );

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

	/** \brief Zadanie główne modelu.
	* Motoda zostaje uruchomiona w osobnym wątku i komunikuje się z kontrolerem
	* przez dwie kolejki blokujące: controllerBlockingQueue i modelBlockingQueue.
	* \return void
	*/
	void doMainJob();

	/** \brief Ustawia wskaźnik na kolejkę kontrolera.
	* \param q BlockingQueue<Event*>*
	* \return void
	*/
	void setControllerBlockingQueue(BlockingQueue<Event*>* q);

private:
	friend class Controller;/**< \todo być może ładniej rozwiazać problemy */

	Graph * graph;

	Population * population;

	BlockingQueue<Event*>* controllerBlockingQueue;/**< na tą kolejkę wrzucamy zgłoszenia do kontrolera */

	BlockingQueue<Command*>* modelBlockingQueue;/**< kolejka na którą mają przychodzić polecenia z kontrolera */

	bool shutDown;/**< czy nie zamykamy aplikacji */
};

#endif // MODEL_HPP
