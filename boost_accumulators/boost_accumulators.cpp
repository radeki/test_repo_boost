// boost_accumulators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>


#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace boost::accumulators;


int _tmain(int argc, _TCHAR* argv[])
{

	accumulator_set<double, features<tag::mean, tag::min, tag::max > > acc;

	// push in some data ...
	acc(1.2);
	acc(2.3);
	acc(3.4);
	acc(4.5);

	// Display the results ...
	std::cout << "Min :   " << boost::accumulators::min(acc) << std::endl;
	std::cout << "Mean:   " << boost::accumulators::mean(acc) << std::endl;
	std::cout << "Max :   " << boost::accumulators::max(acc) << std::endl;


	// The data for which we wish to calculate statistical properties:
	std::vector< int > data;
	for( int i=1; i < 10; ++i )
	data.push_back(i);

	// The accumulator set which will calculate the properties for us:    
	accumulator_set< int, features< tag::min, tag::mean, tag::max, tag::sum > > acc1;

	// Use std::for_each to accumulate the statistical properties:
	//acc1 = std::for_each( data.begin(), data.end(), acc1 );
	std::for_each( data.begin(), data.end(), boost::bind<void>( boost::ref(acc1), _1 ) );
	std::cout << "Min :   " << boost::accumulators::min(acc1) << std::endl;
	std::cout << "Mean:   " << boost::accumulators::mean(acc1) << std::endl;
	std::cout << "Max :   " << boost::accumulators::max(acc1) << std::endl;
	std::cout << "Sum :   " << boost::accumulators::sum(acc1) << std::endl;


	//BOOST_CHECK_CLOSE( 2.0,2.0,50.0 );
	return 0;
}

