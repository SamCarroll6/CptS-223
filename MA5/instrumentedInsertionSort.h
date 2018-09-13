/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTEDIS_H
#define __INSTRUMENTEDIS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();
	int count = 0;          // Grab starting time before sort
	for (int i = 1; i < a.size(); i++){
		bool ins = true;
		int hold = a[i];
		count = i - 1;
		while(++stats.compares && ins){
			if(hold >= a[count]){
				a[count + 1] = hold;
				ins = false;
			}
			else{
			stats.moves++;
			a[count + 1] = a[count];
			count--;
			}
		}
	}




	clock_t time_end = clock();             // Grab ending time after sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
