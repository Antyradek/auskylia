/**
 *  \file Strategy.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Plik nagłówkowy ze startegiami krzyżowania.
 */

#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <vector>

#include "Path.hpp"

/**
 * \brief Klasy strategii.
 */
class Strategy
{
public:
	virtual void match( const std::vector<Path *> & in, std::vector<Path *> & out1, std::vector<Path *> & out2, const unsigned size ) const = 0;
};

class StrategyRandUniform : public Strategy
{
public:
	virtual void match( const std::vector<Path *> & in, std::vector<Path *> & out1, std::vector<Path *> & out2, const unsigned size) const {};
};

class StrategyRandBinomial : public Strategy
{
public:
	virtual void match( const std::vector<Path *> & in, std::vector<Path *> & out1, std::vector<Path *> & out2, const unsigned size) const {};
};

class StrategyClosest : public Strategy
{
public:
	virtual void match( const std::vector<Path *> & in, std::vector<Path *> & out1, std::vector<Path *> & out2, const unsigned size) const ;
};

#endif // STRATEGY_HPP
