/** 
 *  \file   Node.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Node.
 */

#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
	Node();	
	Node( unsigned x, unsigned y);
	~Node();

	unsigned getX() const;
	unsigned getY() const;
	unsigned getSafety() const;

	void roll();
	void print() const;

private:
	unsigned x;
	unsigned y;
	unsigned safety;
};

#endif // NODE_HPP
