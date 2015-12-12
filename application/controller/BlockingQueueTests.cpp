/** \file BlockingQueueTests.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z testami do klasy BlockingQueue.
 *
 */

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "BlockingQueue.hpp"
#include <thread>
#include <unistd.h>
#include <iostream>

BlockingQueue<int>* Q=nullptr;

inline void pushFn()
{
	std::cout<<"\n3, ";
	sleep(1);
	std::cout<<"2, ";
	sleep(1);
	std::cout<<"1, ";
	sleep(1);
	std::cout<<"0 - push_back\n";
	if(Q!=nullptr)
	Q->push_back(1);
}

BOOST_AUTO_TEST_SUITE( BlockingQueue_Tests )

	BOOST_AUTO_TEST_CASE( BQ1 )
	{
		BlockingQueue<int> q;
		q.push_back(1);
		int n=0;
		n=q.pop_front();
		BOOST_CHECK( n==1 );
	}


	BOOST_AUTO_TEST_CASE(BQ2_thread)
	{
		BlockingQueue<int> q;
		Q=&q;
		int n=0;
		std::thread pushThread(pushFn);
		std::cout<<"\nstart pop_front\n";
		n=q.pop_front();
		std::cout<<"\nend pop_front\n";
		if(pushThread.joinable())
		{
			pushThread.join();
		}
		BOOST_CHECK( n==1 );
	}

BOOST_AUTO_TEST_SUITE_END()
















