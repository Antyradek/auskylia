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
	Graph * generateGraph( unsigned nodes ) const;

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
	 * \brief              Ustawia parametry trasy do wiliczenia.
	 * \param[in]  weights Tablica wag przypisanych parametrom trasy
	 * \param[in[  start   Numer wierzchołka początkowego
	 * \param[in]  end     Numer wierzchołka końcowego
	 */
	void setTargetPath( const std::array<unsigned short, (unsigned)Parameters::Count> & weights, unsigned start, unsigned end );

	/**
	 * \brief           Tworzy populację o zadanym rozmiarze.
	 * \param[in] size  rozmiar populacji (liczba parzysta; jeśli jest nieparzysta, model używa size + 1)
	 */
	void createPopulation( unsigned size );

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
	void setStrategy( const Strategy * strategy );

	/**
	 * \brief               Ustawia sposób działania mutacji.
	 * \param[in] mutation  wskaźnik na mutację
	 */
	void setMutation( const Mutation * mutation );

	/**
	 * \brief  Zwraca wskaźnik do populacji.
	 * \return wskaźnik do populacji
	 */
	Population * getPopulation();

    /** \brief Zadanie główne modelu.
     * Jeszcze nie wiem, czy ta metoda będzie potrzebna.
     * \return void
     */
	void doMainJob();

    /** \brief Ustawia wskaźnik na kolejkę kontrolera.
     * \param q BlockingQueue<Event*>*
     * \return void
     */
	void setControllerBlockingQueue(BlockingQueue<Event*>* q);

private:
	Graph * graph;

	Population * population;

	Strategy * strategy;

	Mutation * mutation;

	BlockingQueue<Event*>* controllerBlockingQueue;/**< na tą kolejkę wrzucamy zgłoszenia do kontrolera */
};

#endif // MODEL_HPP
