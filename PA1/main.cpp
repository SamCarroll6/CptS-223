/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 * Now also doing testing & height calculations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *  * Also doing height calculations
 *
 */

#include <iostream>
#include <queue>
#include <cstring>
#include <fstream>
#include <math.h>
#include "BST.h"
#include "TestData.h"
using namespace std;

/*
 *  Interface to run all tests if --test is passed on command line
 */
void runTests() {
	cout << " [x] Running tests. " << endl;
	TestData *testing = new TestData();			// Create object with testing data and interfaces

  BST<int> *bst_test = new BST<int>;

	/* Should make a tree like this:
              10
         5          14
     1      7           17
                            19
                          18

   */
	int testval = testing->get_next_minitest();
	while( testval >= 0 ){
		bst_test->add( testval );
		testval = testing->get_next_minitest();
	}
	cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
  cout << " [x] Resulting print out test:      ";
	bst_test->print();
  cout << endl;

	cout << " [x] Should print a tree height of  : 5" << endl;
  cout << " [x] Currently calculating height of: ";
  cout << bst_test->height();
  cout << endl;
	cout << log2 (bst_test->height());
	cout << endl;
}


/*
 * Generate the CSV file for the project output here
 */



void genCSV() {
	cout << " [x] Generating CSV output file. " << endl;
	cout << " [!!!] UNIMPLEMENTED - Need to generate the CSV file based on the tree height growth." << endl;
	ofstream outfile;
	TestData *testing = new TestData();
	BST<int> *bst_sorted = new BST<int>;
	BST<int> *bst_balanced = new BST<int>;
	BST<int> *bst_random = new BST<int>;
	BST<int> *bst_random1 = new BST<int>;
	BST<int> *bst_random2 = new BST<int>;
	BST<int> *bst_random3 = new BST<int>;
	BST<int> *bst_random4 = new BST<int>;

	outfile.open("OutputData-BST.csv");
	if (!outfile)
	cout << "File not opened." << endl;

	else{

	int count = 0;
	int sorted = testing->get_next_sorted();
	int balanced = testing->get_next_balanced();
	int random = testing->get_next_scrambled(count);

	/************************************************************************************/

	outfile << "N,Log_2 (N),Sorted,Balanced,Scrambled #0,Scrambled #1,Scrambled #2,Scrambled #3,Scrambled #4" << endl;
	outfile << bst_sorted->height() << "," << "-infinity" << ","
	<< bst_sorted->height() << "," << bst_balanced->height() << "," << bst_random->height()
	<< "," << bst_random1->height() << "," << bst_random2->height() <<
	"," << bst_random3->height() << "," << bst_random4->height() << endl;

	while (sorted >= 0){

			bst_sorted->add( sorted );
			sorted = testing->get_next_sorted();

		/************************************************************************************/

		bst_balanced->add(balanced);
		balanced = testing->get_next_balanced();

		/************************************************************************************/

		count = 0;
		bst_random->add(random);
		random = testing->get_next_scrambled(count);

		/************************************************************************************/
		count = 1;
		random = testing->get_next_scrambled(count);
		bst_random1->add(random);
		random = testing->get_next_scrambled(count);

		/************************************************************************************/

		count = 2;
		random = testing->get_next_scrambled(count);
		bst_random2->add(random);
		random = testing->get_next_scrambled(count);

		/************************************************************************************/

		count = 3;
		random = testing->get_next_scrambled(count);
		bst_random3->add(random);
		random = testing->get_next_scrambled(count);

		/************************************************************************************/

		count = 4;
		random = testing->get_next_scrambled(count);
		bst_random4->add(random);
		random = testing->get_next_scrambled(count);

		/************************************************************************************/

		outfile << bst_sorted->height() << "," << log2 (bst_sorted->height()) << ","
		<< bst_sorted->height() << "," << bst_balanced->height() << "," << bst_random->height()
		<< "," << bst_random1->height() << "," << bst_random2->height() <<
		"," << bst_random3->height() << "," << bst_random4->height() << endl;
		} 		//while

		cout << "Sorted height: " << bst_sorted->height() << endl;
		cout << "Balanced height: " << bst_balanced->height() << endl;
		cout << "Random height: " << bst_random->height() << endl;
		cout << "Random height1: " << bst_random1->height() << endl;
		cout << "Random height2: " << bst_random2->height() << endl;
		cout << "Random height3: " << bst_random3->height() << endl;
		cout << "Random height4: " << bst_random4->height() << endl;
	}				//else
	/*  Sample of how to use the TestData structure for getting the test data sets
	int sorted = testing->get_next_sorted();
	while(sorted >= 0){
		bst_sorted->add( sorted );
		sorted = testing->get_next_sorted();
	}
	cout << "Sorted height: " << bst_sorted->height() << endl;
	*/

    // make a file: OutputData-BST.csv
		// make 7 trees (sorted, balanced, scrambled[0..4])
		// fill trees with data from TestData
		//  -- as you fill, get the heights and output to CSV file: log_2 N, height sorted, height balanced, height scrambled[0..4]
    //  -- fill until the get_next_* functions return -1
}


/*
 *   Main function for execution
 */
int main( int argc, char* argv[] ) {
	if( argc > 1 && !strcmp(argv[1], "--test") )
	{
		cout << " [x] Program in test mode, doing simple tests. " << endl;
		runTests();  // testing should just do a simple tree insert set and search
	}
	else
	{
		cout << " [x] Program built and running in full CSV generation mode. " << endl;
		genCSV();
	}
	return 0;
}
