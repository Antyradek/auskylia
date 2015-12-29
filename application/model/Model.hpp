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
#include "parameters.hpp"


/** 
 * \brief Na razie pusta/zaślepkowa klasa Modelu
 */
class Model
{
public:
        /*
         * \breif            Generuje graf i zwraca do niego wskaźnik
         * \param[in] nodes  liczba węzłów
         * \param[in] dense  czy ma być gęsty
         * \return           wskaźnik do wygenerowanego grafu   
         */
        Graph * generateGraph( unsigned nodes, bool dense ) const;

        /*  
         * \brief            Wczytuje graf z pamięci
         * \param[in] graph  graf do załadowania
         */
        void useGraph( Graph * const graph );

        /*
         * \brief            Wczytuje graf z pliku
         * \param[in] file   ściezka pliku z grafem
         */
        void useGraph( const std::string & file );

        /*
         * \brief            Zapisuje graf do pliku
         *                   Uwaga! Plik zostanie nadpisany, używać ostrożnie.
         * \param[in] file   ściezka pliku do zapisu
         * \param[in] graph  wskaźnik do grafu do zapisania,
         *                   pominięcie parametru lub podanie nullptr zapisuje obecnie używany graf
         */
        void saveGraph( const std::string & file, Graph * graph = nullptr ) const;

        /**
         * \brief              Funkcja wyliczjąca najlepszą trasę
         * \param[in]  weights Tablica wag przypisanych parametrom trasy
         * \param[in[  start   Numer wierzchołka początkowego
         * \param[in]  end     Numer wierzchołka końcowego
         *
         * \return             Wskaźnik do najlepszej ścieżki
         */
        Path * findBestPath( const std::array<unsigned short, (unsigned)Parameters::Count> & weights, unsigned start, unsigned end );

	void doMainJob(){};

private:
        Graph * graph;
};

#endif
