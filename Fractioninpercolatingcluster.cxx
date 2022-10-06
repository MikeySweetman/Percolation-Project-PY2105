
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
const int size = 25	;

int main()
{
	//arrays and variables
	int lattice[size][size] = {};	// = {} sets all lattice sites to zero so ensures the programme starts with an empty lattice
	int i, j, x, y,  col, row ; //used for setting lattice points and for while loops e.g. lattice[x][y] or while(i<size*size)
	int filled, cluster_number, old, new_, clusterfilled; //integer values that aren't used to get certain sites in the array
	int bottom, top, left, right ; //variables used to detect spanning cluster
	double f_c, filledbutdouble, sizeofsquare, p, sitestobefilled ; 
	int doesspexist ; //value set to zero if no spanning cluster exists, one if it does. This ensures programme only calculates Fc if there is a spanning cluster
	
	doesspexist = 0 ;
	
	
	
	
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


	//inputting p
	cout << "Please input the probablitiy of a lattice site being filled\n" ;
	cin >> p ;
	while(p<0 || p > 1)//maiking sure p in between 1 and 0
	{	cout << "Please input the probablitiy of a lattice site being filled\n" ;
		cin >> p ;
	}
	
	
	
	
	sizeofsquare = size*size ;	
	
	sitestobefilled = sizeofsquare*p ;
	cout << endl << round(sitestobefilled) << " sites will be filled at this probability\n\n" ;
	
	
	
	//filling lattice randomly
	i = 0 ;
	cluster_number = 1 ;
	srand(time(NULL)) ;
	while(i<round(sizeofsquare*p)) //the inclusion of p here is one of the important differences in this programme 	
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
					
					for(int x = 0 ; x<size; x++) //the for loops relabel all sites needed to be relablled
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



		
			
		}
		
		
		
		
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
				
				doesspexist = 1 ;
				cout << "the cluster has percolated, the value of the percolating cluster is " << new_ << endl << endl ; 
				
			}
			
			else
			{
				cout << "no spanning cluster exists\n\n" ;
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
	
	
	
	
	
	
	
	
	
	if(doesspexist == 1)
	{
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
	
	
}
	
	
	
	return 0;
}
