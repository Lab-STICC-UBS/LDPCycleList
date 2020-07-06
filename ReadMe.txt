
This file is part of the LDPCycleList distribution.
Copyright (c) 2018 Titouan GENDRON.

This program is free software: you can redistribute it and/or modify  
it under the terms of the GNU General Public License as published by  
the Free Software Foundation, version 3.
This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
General Public License for more details.
You should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu.org/licenses/>.

Note : Version 1.1
- now can be used with non regular matrices


How to use : 

- Compile with the command make (uses gcc), or compile the LDPCycleList.c file (it is alone)
- Run with the command ./LDPCycleList [Path of the matrix file] [Maximum lengh of cycle to search]

ex: ./LDPCycleList ./Dc3_N6.txt 14

Alist format : http://perso-etis.ensea.fr/~declercq/graphs.php

6 4 			//N M
2 3 			//dv dc
2 2 2 2 2 2 	//dv of each column
3 3 3 3 		//dc of each line

1 3 			//position of non zero elements in each column (position of first element noted '1', not like in C++)
2 4 
1 4 
3 4 
1 2 
2 3 

1 3 5 			//position of non zero elements in each line
2 5 6 
1 4 6 
2 3 4

Associated matrix :
1 0 1 0 1 0
0 1 0 0 1 1
1 0 0 1 0 1
0 1 1 1 0 0


You can use the matlab scipt 'matrix2alist.m' by Cédric Marchand to convert a matrix to the right format.


The list of cycles are given in the 'cycles' folders : this is an example of a cycles of lenght 6 in the matrix below :
1 1 3 4 4 3 1 		// mean Check Node 1, Variable node 1, Check 3, V4, C4, V3, C1 -> the check node we began with. 

1 * 6 * X *			//the cycle in the matrix (play the game where you draw something linking the points in the right order)
* X * * X X
2 * * 3 * X
* X 5 4 * *

Contact : gendron.titouan@gmail.com
