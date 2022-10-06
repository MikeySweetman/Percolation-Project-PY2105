
//Michael Sweetman, 119322771

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;


//constant declaration, this sets the size of the lattice
const int size = 7		 ;

int main()
{
	//arrays and variables
	int lattice[size][size] = {};	// = {} sets all lattice sites to zero so ensures the programme starts with an empty lattice
	int i, j, x, y,  col, row ; //used for setting lattice points and for while loops e.g. lattice[x][y] or while(i<size*size)
	int filled, cluster_number, old, new_, clusterfilled; //integer values that aren't used to get certain sites in the array
	int bottom, top, left, right ; //variables used to detect spanning cluster
	double p_c, f_c, filledbutdouble, sizeofsquare ; 
	
	
	
	
	//printing the empty lattice
	j = 0 ; //note that  lattice[0][0] refers to the top left as opposed to bottom left of lattice
	while(j<size)
	{
		i = 0 ;
		while(i<size)
		{
			cout << lattice[i][j] << "  "  ;
			i = i + 1 ;
			if(i == size)
				cout << endl ;
		}
		j = j + 1 ;
	}
	
	cout << endl ; //spacing so screen isn't too messy when programme runs
	cout << endl ;


	/* below is the main while loop of this programme. It fills the lattice at a random point,
	 * checks the adjacent sites for for clusters and if some are found, relabels all 
	 * the sites in the lattice to the correct value so that each cluster has a unique
	 * number associated with them, and then checks for the existence of a spanning cluster.
	 * All of this is done in one run and then loops back until a spanning cluster is found
	 */

	
	//filling lattice randomly
	i = 0 ;
	cluster_number = 1 ;
	srand(time(NULL)) ;
	while(i<size*size)
	{
		row = rand() % size ;
		col = rand() % size ;
		
		if(lattice[col][row] == 0) //making sure that only empty sites are filled ie the same site won't be chosen to be filled more than once
		{
			lattice[col][row] = cluster_number ;
			cluster_number = cluster_number + 1 ;
			i = i + 1 ;
	
			
		}
				
				
				//This part checks for the existence of filled sites adjacent to the new site being filled and then also relabels all the sites needed
				x = 0 ;
				y = 0 ;
				
				
				//checking to the left
				if(lattice[col-1][row]>0 && col > 0)
				{
					new_ = lattice[col][row] ;
					old = lattice[col-1][row] ;
					
					for(int x = 0 ; x<size; x++) //the for loops relabel all sites needed to be relablled to the value of the newly filled site
					{
						for(int y = 0 ; y<size; y++)
						{
							if(lattice[x][y] == old)
							{
								lattice[x][y] = new_ ;
							}
						}
					}
				}
				
			
			
				//checking above
				if(lattice[col][row+1]>0 && row < size-1)
				{
					new_ = lattice[col][row] ;
					old = lattice[col][row+1] ;
					
					for(int x = 0 ; x<size; x++)
					{
						for(int y = 0 ; y<size; y++)
						{
							if(lattice[x][y] == old)
							{
								lattice[x][y] = new_ ;
							}
						}
					}
				}


		
				//checking to the right
				if(lattice[col+1][row]>0 && col < size-1)
				{
					new_ = lattice[col][row] ;
					old = lattice[col+1][row] ;
				
					for(int x = 0 ; x<size; x++)
					{
						for(int y = 0 ; y<size; y++)
						{
							if(lattice[x][y] == old)
							{
								lattice[x][y] = new_ ;
							}
						}
					}
				}



				//checking below
				if(lattice[col][row-1]>0 && row>0 ){
					new_ = lattice[col][row] ;
					old = lattice[col][row-1] ;
					
					for(int x = 0 ; x<size; x++)
					{
						for(int y = 0 ; y<size; y++)
						{
							if(lattice[x][y] == old)
							{
								lattice[x][y] = new_ ;
							}
						}
					}
				}



		/* this part of the code checks for the existence of a spanning cluster. The 
		 * variables directly below keep track of the number of filled sites
		 * on the edges which have the same value as the most recently formed cluster
		 * if all are > 0 then spanning cluster must exist and this loop  is exited from
		 */

		bottom = 0 ;
		top = 0 ;
		left = 0 ;
		right = 0 ;
	
		
		//checking the bottom edge
		for(int b = 0 ;b < size; b++)
		{
			if(lattice[b][0] ==	new_ && new_ > 0)
			{
				bottom = bottom + 1 ;
			}	
		}
	
		//checking the top edge
		for(int b = 0 ;b < size; b++){
			if(lattice[b][size-1] == new_ && new_ > 0)
			{
			top = top + 1 ;
			}
		}
		
		//checking the left edge	
		for(int b = 0 ;b < size; b++)
		{
			if(lattice[0][b] ==	new_ && new_ > 0)
			{
				left = left + 1 ;
			}
		}
	
		//checking the right edge
		for(int b = 0 ;b < size; b++)
		{
			if(lattice[size-1][b] == new_ && new_ > 0)
			{
				right = right + 1 ;
			}
		}
	
			//checking for a spanning cluster
			if( bottom > 0 && top > 0 && left > 0 && right > 0)
			{
				i = size*size ;
		
				cout << "the cluster has percolated, the value of the percolating cluster is " << new_ << endl << endl ;  
				break ;
			}
			
		
	//end of this loop
	}
	
	

	
	
	//printing filled lattice
	j = 0 ;
	while(j<size)
	{
		i = 0 ;
		while(i<size)
		{
			cout << lattice[i][j] << "  "  ;
			i = i + 1 ;
			if(i == size)
				cout << endl ;
		}
		j = j + 1 ;
	}
	
	
	
	
	
	

	
	//adding up the number of filled sites
	filled = 0 ;
	
	i = 0 ;
	while(i<size)
	{
		j = 0 ;
		while(j<size)
		{
			if(lattice[i][j]>0)
			{
				filled = filled + 1 ;
				j = j + 1 ;
			}
			else
			j = j + 1 ;
		}
		i = i + 1 ;
	}
	
	cout << "\nThe size if the lattice is " << size*size ;
	cout << endl << filled << " sites are filled\n" ;
	
	//estimating p_c
	filledbutdouble = filled ;		//transfering the values to a double so that division works
	sizeofsquare = size*size ;		
	
	p_c = filledbutdouble/(sizeofsquare) ;
	
	cout << "the critical concentration is " << p_c << endl ;
	
	
	
	
	
	
	
	
	
	//adding up the number of filled sites in the spanning cluster
	clusterfilled = 0 ;
	
	i = 0 ;
	while(i<size)
	{
		j = 0 ;
		while(j<size)
		{
			if(lattice[i][j]== new_)
			{
				clusterfilled = clusterfilled + 1 ;
				j = j + 1 ;
			}
			else
			j = j + 1 ;
		}
		i = i + 1 ;
	}
	
	
	cout << endl << clusterfilled << " of the filled sites are part of the spanning cluster\n" ;

	
	

	//fraction of sites in spanning cluster
	f_c = clusterfilled/filledbutdouble ;
	cout <<"The fraction of filled sites in the percolating cluster is " << f_c << endl ;
	
	
	
	
	
	
	return 0;
}
