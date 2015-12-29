/** 
 *  \file Strategy.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Plik nagłówkowy ze startegiami krzyżowania.
 */

#ifndef STRATEGY_HPP
#define STRATEGY_HPP

/**
 * \brief Lista strategii.
 */

enum class Strategy
{
        RANDOM_UNIFORM,   // dobór losowy z rozkładem jednostajnym dyskretnym
                          // osobnik ma równe szanse na sparowanie z dowolnym osobnikiem
        RANDOM_NORMAL,    // dobór losowy z rozkładem dwumianowym skupionym wokół osobnika
                          // wysoka szansa doboru podobnego osobnika, mała szansa na dużo gorszego/lepszego
        CLOSEST,          // sztywny dobór według schematu 1+2, 3+4, 5+6...
};

#endif // STRATEGY_HPP
