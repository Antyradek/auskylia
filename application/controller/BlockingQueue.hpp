/** \file BlockingQueue.hpp
 * \author Tomasz Jakubczyk
 * \brief plik nagłówkowy klasy kolejki blokującej
 *
 */

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

/** \brief Kolejka blokująca. Dziedziczy po queue.
 * Żeby nie ryzykować użycia niezabezpieczonych wątkowo dziedziczonych metod
 * dziedziczenie po queue jest prywatne.
 * W celu zmniejszenia ryzyka niepoprawności synchronizacji
 * wzorowałem się na implementacjach CONCURRENT QUEUE w internecie.
 */
template <class T>
class BlockingQueue: private std::queue<T>
{
public:
    BlockingQueue();
    ~BlockingQueue();
    /** \brief Dodanie niepodzielnie elementu na koniec kolejki.
     * \param T Dodawany element typu parametrycznego T.
     * \return void
     */
    void push_back(const T&);
    /** \brief Zdejmuje pierwszy element z kolejki niepodzielnie i go zwraca.
     * \return T Zwracany element typu parametrycznego T.
     */
    T pop_front();
private:
    std::queue<T> q;/**< wewnętrzna kolejka */
    std::mutex m;/**< wewnętrzny zamek do kolejki */
    std::condition_variable c;/**< warunek blokowania */
};

#include "BlockingQueue.cpp"/**< Doklejenie implementacji metod rozwiązuje problem z nie obsługiwaniem przez gcc i większość innych kompilatorów dyrektywy export template */









