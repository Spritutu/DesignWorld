/* Ganitam.cpp ganitam

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#include "Ganitam.h"
#include <iostream>

double nfact( int n )
{
	if( n >= 0 )
	{
		double fact = 1;
		for( int i = 1; i <= n; i++ )
			fact = fact *  i;
		return fact;
	}
	else return 0; 
}
double nCr( int n, int r )
{
	double ncr = 0;
	if( n >= r )
	{
		ncr = nfact( n )/(nfact( r ) * nfact( n - r ));
		return  ncr;
	}
	return 0;
}
