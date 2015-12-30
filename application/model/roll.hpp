/*  \file   roll.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy z funkcjami losującymi.
 */

#ifndef ROLL_HPP
#define ROLL_HPP

#include <random>
#include <algorithm>

unsigned rollUniform( unsigned min, unsigned max );

unsigned rollBinomial( unsigned value, unsigned min, unsigned max );

#endif // ROLL_HPP
