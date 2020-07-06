/* 
 * This file is part of the LDPCycleList distribution.
 * Copyright (c) 2018 Titouan GENDRON.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>


//#define VERB  //uncomment this line if you whant to display all the informations



int main(int argc, char *argv[])
{
    printf("**********************************************************************\n");
    printf("******************LDPCycleList by Titouan GENDRON*********************\n");
    printf("**********************************************************************\n");

    /* *************************************************************
     * Initialisation
     * *************************************************************/
    
    int i,j;
    int MaxLenght;
    
    if(argc < 2)
    {
        printf("[CycleList]Error : Usage : Girth [Path] [max cycle lenght]\n 3rd argument optional : default 16\n");
        return 1;
    }

    if(argc == 3)
    {
        MaxLenght = atoi(argv[2]);
        if(MaxLenght<4)
        {
            MaxLenght = 16;
            printf("[CycleList]Warning : Maximum cycle lenght under 4. \n[CycleList]Maximum cycle lenght set to default \n" );
        }
        if(MaxLenght>20)
        {
            printf("[CycleList]Warning : Maximum cycle lenght above 20. \n[CycleList]Maximum cycle lenght set to max \n");
            MaxLenght = 20;
        }
        printf("[CycleList]Maximum cycle lenght set to %d\n",MaxLenght);
    }
    else
    {
        MaxLenght = 16;
        printf("Maximum cycle lenght set to default : 16\n");
    }


    /****************************************************************
     * Reading input file
     * *************************************************************/
    FILE* f;
    f=fopen(argv[1],"r");

    if(f == NULL)
    {
        printf("[CycleList]Error : %s not found or invalid\n",argv[1]);
        return 1;
    }

    int N , M , dc , dv;      /* size of the matrix */
    int **m;     /* list of integer coordinates in the m direction where the non-zero entries are */
    int **n;     /* list of integer coordinates in the n direction where the non-zero entries are */
    int *num_m;  /* weight of each row, m */
    int *num_n;  /* weight of each column n */
    
    fscanf ( f , "%d %d\n" , &N , &M ) ;    //read M,N
    fscanf ( f , "%d %d\n" , &dv , &dc ) ;

#if defined(VERB)
    printf("Matrix alist : \n\n%d %d %d %d\n", N, M, dv, dc) ; //debug
#endif

    num_n=(int*)malloc(N*sizeof(int));
    num_m=(int*)malloc(M*sizeof(int));
    
    for(i=0;i<N;i++)                            //read num_m,num_n
    {
        fscanf(f,"%d ",&num_n[i]);
#if defined(VERB)
        printf("%d ",num_n[i]);
#endif
    }

#if defined(VERB)
    printf("\n");
#endif

    for(i=0;i<M;i++)
    {
        fscanf(f,"%d ",&num_m[i]);
#if defined(VERB)
        printf("%d ",num_m[i]);
#endif
    }

#if defined(VERB)
    printf("\n\n");
#endif
    
    n=(int**)malloc(N*sizeof(int*));

    for(i=0;i<N;i++)                            //read n
    {
        n[i]=(int*)malloc(dv*sizeof(int));
        for(j=0;j<num_n[i];j++)
        {
            fscanf(f,"%d ",&n[i][j]);
#if defined(VERB)
            printf("%d ",n[i][j]);
#endif
        }
#if defined(VERB)
        printf("\n");
#endif
    }
#if defined(VERB)
    printf("\n");
#endif
    

    m=(int**)malloc(M*sizeof(int*));               //read m

    for(i=0;i<M;i++)
    {
        m[i]=(int*)malloc(dc*sizeof(int));
        for(j=0;j<num_m[i];j++)
        {
            fscanf(f,"%d ",&m[i][j]);
#if defined(VERB)
            printf("%d ",m[i][j]);
#endif
        }
#if defined(VERB)
        printf("\n");
#endif
    }
    
#if defined(VERB)
    printf("\n");
#endif
    
    fclose(f);
    

    /****************************************************************
     * Girth ressearch
     * *************************************************************/
    int c1=0,c2=0,c3=0,c4=0,c5=0, c6=0, c7=0, c8=0, c9=0, c10=0, c11=0;     //used as for incremented variables
    int v1=0,v2=0,v3=0,v4=0,v5=0, v6=0, v7=0, v8=0, v9=0, v10=0;
    int cycle4=0, cycle6=0, cycle8=0, cycle10=0, cycle12=0, cycle14=0, cycle16=0, cycle18=0, cycle20=0; //to count the cycles
    int C[12],V[12];    //list of the check nodes and variables nodes browsed
    int** tab4=NULL;    //dynamicaly allowed tabs that will contain the details of each cycles
    int** tab6=NULL;
    int** tab8=NULL;
    int** tab10=NULL;
    int** tab12=NULL;
    int** tab14=NULL;
    int** tab16=NULL;
    int** tab18=NULL;
    int** tab20=NULL;


    printf("processing... \n");


    for(c1 = 0 ; c1 < M ; c1++) //for each check node
    {
        for(v1 = 0 ; v1 < num_m[c1] ; v1++)    //for each variable node connected to the check node
        {
            V[0] = m[c1][v1]-1;         //V is the list of variable nodes browsed
            for(c2 = 0 ; c2 < num_n[V[0]]; c2++) //for each check nodes connected to the previous variable node
            {
                if((C[0] = n[V[0]][c2]-1) > c1) //when all cycles begining with a check node are found, don't take account of it anymore
                {
                    for(v2 = 0 ; v2 < num_m[C[0]]; v2++) //for each variable node connected to the previous check node
                    {
                        if((V[1] = m[C[0]][v2]-1) != V[0]) //don't come back to the previous variable node
                        {
                            for(c3 = 0 ; c3 < num_n[V[1]]; c3++) //for each check nodes connected to the previous variable node
                            {
                                if((C[1] = n[V[1]][c3]-1) != C[0])  //don't come back to the previous check node
                                {
                                    if(C[1] >= c1)
                                    {
                                        if(C[1] == c1)  //if this check node is the same than the first one, we found a cicle!
                                        {
                                            tab4 = (int**)realloc(tab4, (cycle4+1)*sizeof(int*));
                                            tab4[cycle4] = (int*)malloc(5*sizeof(int));             //allocation of the memory
                                            tab4[cycle4][0] = c1+1;     //first check node
                                            tab4[cycle4][1] = V[0]+1;   //first variable node
                                            tab4[cycle4][2] = C[0]+1;   //second check node
                                            tab4[cycle4][3] = V[1]+1;   //second variable node
                                            tab4[cycle4][4] = C[1]+1;   //third check node (the same that the first check node)
                                            #if defined VERB
                                            for(i=0;i<5;i++)
                                                printf("%d ",tab4[cycle4][i]);
                                            printf("\n");
                                            #endif
                                            cycle4++;
                                        }
                                        if(MaxLenght>=6)    //if we have to search for lengh 6 cycles, continue to browse the nodes
                                        {
                                            for(v3 = 0 ; v3 < num_m[C[1]]; v3++)
                                            {
                                                if((V[2] = m[C[1]][v3]-1) != V[1])
                                                {
                                                    for(c4 = 0 ; c4 < num_n[V[2]]; c4++)
                                                    {
                                                        if((C[2] = n[V[2]][c4]-1) != C[1])
                                                        {
                                                            if(C[2] >= c1)
                                                            {
                                                                if((C[2] == c1) && (V[2] != V[0]))
                                                                {
                                                                    tab6 = (int**)realloc(tab6, (cycle6+1)*sizeof(int*));
                                                                    tab6[cycle6] = (int*)malloc(7*sizeof(int));
                                                                    tab6[cycle6][0] = c1+1;
                                                                    tab6[cycle6][1] = V[0]+1;
                                                                    tab6[cycle6][2] = C[0]+1;
                                                                    tab6[cycle6][3] = V[1]+1;
                                                                    tab6[cycle6][4] = C[1]+1;
                                                                    tab6[cycle6][5] = V[2]+1;
                                                                    tab6[cycle6][6] = C[2]+1;
                                                                    #if defined VERB
                                                                    for(i=0;i<7;i++)
                                                                        printf("%d ",tab6[cycle6][i]);
                                                                    printf("\n");
                                                                    #endif
                                                                    cycle6++;
                                                                }
                                                                if(MaxLenght>=8)
                                                                {
                                                                    for(v4 = 0 ; v4 < num_m[C[2]]; v4++)
                                                                    {
                                                                        if((V[3] = m[C[2]][v4]-1) != V[2])
                                                                        {
                                                                            for(c5 = 0 ; c5 < num_n[V[3]]; c5++)
                                                                            {
                                                                                if((C[3] = n[V[3]][c5]-1) != C[2])
                                                                                {
                                                                                    if(C[3] >= c1)
                                                                                    {
                                                                                        if((C[3] == c1) && (V[3] != V[0]))
                                                                                        {
                                                                                            tab8 = (int**)realloc(tab8, (cycle8+1)*sizeof(int*));
                                                                                            tab8[cycle8] = (int*)malloc(9*sizeof(int));
                                                                                            tab8[cycle8][0] = c1+1;
                                                                                            tab8[cycle8][1] = V[0]+1;
                                                                                            tab8[cycle8][2] = C[0]+1;
                                                                                            tab8[cycle8][3] = V[1]+1;
                                                                                            tab8[cycle8][4] = C[1]+1;
                                                                                            tab8[cycle8][5] = V[2]+1;
                                                                                            tab8[cycle8][6] = C[2]+1;
                                                                                            tab8[cycle8][7] = V[3]+1;
                                                                                            tab8[cycle8][8] = C[3]+1;
                                                                                            #if defined VERB
                                                                                            for(i=0;i<9;i++)
                                                                                                printf("%d ",tab8[cycle8][i]);
                                                                                            printf("\n");
                                                                                            #endif
                                                                                            cycle8++;
                                                                                        }
                                                                                        if(MaxLenght>=10)
                                                                                        {
                                                                                            for(v5 = 0 ; v5 < num_m[C[3]]; v5++)
                                                                                            {
                                                                                                if((V[4] = m[C[3]][v5]-1) != V[3])
                                                                                                {
                                                                                                    for(c6 = 0 ; c6 < num_n[V[4]]; c6++)
                                                                                                    {
                                                                                                        if((C[4] = n[V[4]][c6]-1) != C[3])
                                                                                                        {
                                                                                                            if(C[4] >= c1)
                                                                                                            {
                                                                                                                if((C[4] == c1) && (V[4] != V[0]))
                                                                                                                {
                                                                                                                    tab10 = (int**)realloc(tab10, (cycle10+1)*sizeof(int*));
                                                                                                                    tab10[cycle10] = (int*)malloc(11*sizeof(int));
                                                                                                                    tab10[cycle10][0] = c1+1;
                                                                                                                    tab10[cycle10][1] = V[0]+1;
                                                                                                                    tab10[cycle10][2] = C[0]+1;
                                                                                                                    tab10[cycle10][3] = V[1]+1;
                                                                                                                    tab10[cycle10][4] = C[1]+1;
                                                                                                                    tab10[cycle10][5] = V[2]+1;
                                                                                                                    tab10[cycle10][6] = C[2]+1;
                                                                                                                    tab10[cycle10][7] = V[3]+1;
                                                                                                                    tab10[cycle10][8] = C[3]+1;
                                                                                                                    tab10[cycle10][9] = V[4]+1;
                                                                                                                    tab10[cycle10][10] = C[4]+1;
                                                                                                                    #if defined VERB
                                                                                                                    for(i=0;i<11;i++)
                                                                                                                        printf("%d ",tab10[cycle10][i]);
                                                                                                                    printf("\n");
                                                                                                                    #endif
                                                                                                                    cycle10++;
                                                                                                                }
                                                                                                                if(MaxLenght>=12)
                                                                                                                {
                                                                                                                    for(v6 = 0 ; v6 < num_m[C[4]]; v6++)
                                                                                                                    {
                                                                                                                        if((V[5] = m[C[4]][v6]-1) != V[4])
                                                                                                                        {
                                                                                                                            for(c7 = 0 ; c7 < num_n[V[5]]; c7++)
                                                                                                                            {
                                                                                                                                if((C[5] = n[V[5]][c7]-1) != C[4])
                                                                                                                                {
                                                                                                                                    if(C[5] >= c1)
                                                                                                                                    {
                                                                                                                                        if((C[5] == c1) && (V[5] != V[0]))
                                                                                                                                        {
                                                                                                                                            tab12 = (int**)realloc(tab12, (cycle12+1)*sizeof(int*));
                                                                                                                                            tab12[cycle12] = (int*)malloc(13*sizeof(int));
                                                                                                                                            tab12[cycle12][0] = c1+1;
                                                                                                                                            tab12[cycle12][1] = V[0]+1;
                                                                                                                                            tab12[cycle12][2] = C[0]+1;
                                                                                                                                            tab12[cycle12][3] = V[1]+1;
                                                                                                                                            tab12[cycle12][4] = C[1]+1;
                                                                                                                                            tab12[cycle12][5] = V[2]+1;
                                                                                                                                            tab12[cycle12][6] = C[2]+1;
                                                                                                                                            tab12[cycle12][7] = V[3]+1;
                                                                                                                                            tab12[cycle12][8] = C[3]+1;
                                                                                                                                            tab12[cycle12][9] = V[4]+1;
                                                                                                                                            tab12[cycle12][10] = C[4]+1;
                                                                                                                                            tab12[cycle12][11] = V[5]+1;
                                                                                                                                            tab12[cycle12][12] = C[5]+1;
                                                                                                                                            #if defined VERB
                                                                                                                                            for(i=0;i<13;i++)
                                                                                                                                                printf("%d ",tab12[cycle12][i]);
                                                                                                                                            printf("\n");
                                                                                                                                            #endif
                                                                                                                                            cycle12++;
                                                                                                                                        }
                                                                                                                                        if(MaxLenght>=14)
                                                                                                                                        {
                                                                                                                                            for(v7 = 0 ; v7 < num_m[C[5]]; v7++)
                                                                                                                                            {
                                                                                                                                                if((V[6] = m[C[5]][v7]-1) != V[5])
                                                                                                                                                {
                                                                                                                                                    for(c8 = 0 ; c8 < num_n[V[6]]; c8++)
                                                                                                                                                    {
                                                                                                                                                        if((C[6] = n[V[6]][c8]-1) != C[5])
                                                                                                                                                        {
                                                                                                                                                            if(C[6] >= c1)
                                                                                                                                                            {
                                                                                                                                                                if((C[6] == c1) && (V[6] != V[0]))
                                                                                                                                                                {
                                                                                                                                                                    tab14 = (int**)realloc(tab14, (cycle14+1)*sizeof(int*));
                                                                                                                                                                    tab14[cycle14] = (int*)malloc(15*sizeof(int));
                                                                                                                                                                    tab14[cycle14][0] = c1+1;
                                                                                                                                                                    tab14[cycle14][1] = V[0]+1;
                                                                                                                                                                    tab14[cycle14][2] = C[0]+1;
                                                                                                                                                                    tab14[cycle14][3] = V[1]+1;
                                                                                                                                                                    tab14[cycle14][4] = C[1]+1;
                                                                                                                                                                    tab14[cycle14][5] = V[2]+1;
                                                                                                                                                                    tab14[cycle14][6] = C[2]+1;
                                                                                                                                                                    tab14[cycle14][7] = V[3]+1;
                                                                                                                                                                    tab14[cycle14][8] = C[3]+1;
                                                                                                                                                                    tab14[cycle14][9] = V[4]+1;
                                                                                                                                                                    tab14[cycle14][10] = C[4]+1;
                                                                                                                                                                    tab14[cycle14][11] = V[5]+1;
                                                                                                                                                                    tab14[cycle14][12] = C[5]+1;
                                                                                                                                                                    tab14[cycle14][13] = V[6]+1;
                                                                                                                                                                    tab14[cycle14][14] = C[6]+1;
                                                                                                                                                                    #if defined VERB
                                                                                                                                                                    for(i=0;i<15;i++)
                                                                                                                                                                        printf("%d ",tab14[cycle14][i]);
                                                                                                                                                                    printf("\n");
                                                                                                                                                                    #endif
                                                                                                                                                                    cycle14++;
                                                                                                                                                                }
                                                                                                                                                                if(MaxLenght>=16)
                                                                                                                                                                {
                                                                                                                                                                    for(v8 = 0 ; v8 < num_m[C[6]]; v8++)
                                                                                                                                                                    {
                                                                                                                                                                        if((V[7] = m[C[6]][v8]-1) != V[6])
                                                                                                                                                                        {
                                                                                                                                                                            for(c9 = 0 ; c9 < num_n[V[7]]; c9++)
                                                                                                                                                                            {
                                                                                                                                                                                if((C[7] = n[V[7]][c9]-1) != C[6])
                                                                                                                                                                                {
                                                                                                                                                                                    if(C[7] >= c1)
                                                                                                                                                                                    {
                                                                                                                                                                                        if((C[7] == c1) && (V[7] != V[0]))
                                                                                                                                                                                        {
                                                                                                                                                                                            tab16 = (int**)realloc(tab16, (cycle16+1)*sizeof(int*));
                                                                                                                                                                                            tab16[cycle16] = (int*)malloc(17*sizeof(int));
                                                                                                                                                                                            tab16[cycle16][0] = c1+1;
                                                                                                                                                                                            tab16[cycle16][1] = V[0]+1;
                                                                                                                                                                                            tab16[cycle16][2] = C[0]+1;
                                                                                                                                                                                            tab16[cycle16][3] = V[1]+1;
                                                                                                                                                                                            tab16[cycle16][4] = C[1]+1;
                                                                                                                                                                                            tab16[cycle16][5] = V[2]+1;
                                                                                                                                                                                            tab16[cycle16][6] = C[2]+1;
                                                                                                                                                                                            tab16[cycle16][7] = V[3]+1;
                                                                                                                                                                                            tab16[cycle16][8] = C[3]+1;
                                                                                                                                                                                            tab16[cycle16][9] = V[4]+1;
                                                                                                                                                                                            tab16[cycle16][10] = C[4]+1;
                                                                                                                                                                                            tab16[cycle16][11] = V[5]+1;
                                                                                                                                                                                            tab16[cycle16][12] = C[5]+1;
                                                                                                                                                                                            tab16[cycle16][13] = V[6]+1;
                                                                                                                                                                                            tab16[cycle16][14] = C[6]+1;
                                                                                                                                                                                            tab16[cycle16][15] = V[7]+1;
                                                                                                                                                                                            tab16[cycle16][16] = C[7]+1;
                                                                                                                                                                                            #if defined VERB
                                                                                                                                                                                            for(i=0;i<17;i++)
                                                                                                                                                                                                printf("%d ",tab16[cycle16][i]);
                                                                                                                                                                                            printf("\n");
                                                                                                                                                                                            #endif
                                                                                                                                                                                            cycle16++;
                                                                                                                                                                                        }
                                                                                                                                                                                        if(MaxLenght>=18)
                                                                                                                                                                                        {
                                                                                                                                                                                            for(v9 = 0 ; v9 < num_m[C[7]]; v9++)
                                                                                                                                                                                            {
                                                                                                                                                                                                if((V[8] = m[C[7]][v9]-1) != V[7])
                                                                                                                                                                                                {
                                                                                                                                                                                                    for(c10 = 0 ; c10 < num_n[V[8]]; c10++)
                                                                                                                                                                                                    {
                                                                                                                                                                                                        if((C[8] = n[V[8]][c10]-1) != C[7])
                                                                                                                                                                                                        {
                                                                                                                                                                                                            if(C[8] >= c1)
                                                                                                                                                                                                            {
                                                                                                                                                                                                                if((C[8] == c1) && (V[8] != V[0]))
                                                                                                                                                                                                                {
                                                                                                                                                                                                                    tab18 = (int**)realloc(tab18, (cycle18+1)*sizeof(int*));
                                                                                                                                                                                                                    tab18[cycle18] = (int*)malloc(19*sizeof(int));
                                                                                                                                                                                                                    tab18[cycle18][0] = c1+1;
                                                                                                                                                                                                                    tab18[cycle18][1] = V[0]+1;
                                                                                                                                                                                                                    tab18[cycle18][2] = C[0]+1;
                                                                                                                                                                                                                    tab18[cycle18][3] = V[1]+1;
                                                                                                                                                                                                                    tab18[cycle18][4] = C[1]+1;
                                                                                                                                                                                                                    tab18[cycle18][5] = V[2]+1;
                                                                                                                                                                                                                    tab18[cycle18][6] = C[2]+1;
                                                                                                                                                                                                                    tab18[cycle18][7] = V[3]+1;
                                                                                                                                                                                                                    tab18[cycle18][8] = C[3]+1;
                                                                                                                                                                                                                    tab18[cycle18][9] = V[4]+1;
                                                                                                                                                                                                                    tab18[cycle18][10] = C[4]+1;
                                                                                                                                                                                                                    tab18[cycle18][11] = V[5]+1;
                                                                                                                                                                                                                    tab18[cycle18][12] = C[5]+1;
                                                                                                                                                                                                                    tab18[cycle18][13] = V[6]+1;
                                                                                                                                                                                                                    tab18[cycle18][14] = C[6]+1;
                                                                                                                                                                                                                    tab18[cycle18][15] = V[7]+1;
                                                                                                                                                                                                                    tab18[cycle18][16] = C[7]+1;
                                                                                                                                                                                                                    tab18[cycle18][17] = V[8]+1;
                                                                                                                                                                                                                    tab18[cycle18][18] = C[8]+1;
                                                                                                                                                                                                                    #if defined VERB
                                                                                                                                                                                                                    for(i=0;i<19;i++)
                                                                                                                                                                                                                        printf("%d ",tab18[cycle18][i]);
                                                                                                                                                                                                                    printf("\n");
                                                                                                                                                                                                                    #endif
                                                                                                                                                                                                                    cycle18++;
                                                                                                                                                                                                                }
                                                                                                                                                                                                                if(MaxLenght>=20)
                                                                                                                                                                                                                {
                                                                                                                                                                                                                    for(v10 = 0 ; v10 < num_m[C[8]]; v10++)
                                                                                                                                                                                                                    {
                                                                                                                                                                                                                        if((V[9] = m[C[8]][v10]-1) != V[8])
                                                                                                                                                                                                                        {
                                                                                                                                                                                                                            for(c11 = 0 ; c11 < num_n[V[9]]; c11++)
                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                if((C[9] = n[V[9]][c11]-1) != C[8])
                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                    if(C[9] >= c1)
                                                                                                                                                                                                                                    {
                                                                                                                                                                                                                                        if((C[9] == c1) && (V[9] != V[0]))
                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                            tab20 = (int**)realloc(tab20, (cycle20+1)*sizeof(int*));
                                                                                                                                                                                                                                            tab20[cycle20] = (int*)malloc(21*sizeof(int));
                                                                                                                                                                                                                                            tab20[cycle20][0] = c1+1;
                                                                                                                                                                                                                                            tab20[cycle20][1] = V[0]+1;
                                                                                                                                                                                                                                            tab20[cycle20][2] = C[0]+1;
                                                                                                                                                                                                                                            tab20[cycle20][3] = V[1]+1;
                                                                                                                                                                                                                                            tab20[cycle20][4] = C[1]+1;
                                                                                                                                                                                                                                            tab20[cycle20][5] = V[2]+1;
                                                                                                                                                                                                                                            tab20[cycle20][6] = C[2]+1;
                                                                                                                                                                                                                                            tab20[cycle20][7] = V[3]+1;
                                                                                                                                                                                                                                            tab20[cycle20][8] = C[3]+1;
                                                                                                                                                                                                                                            tab20[cycle20][9] = V[4]+1;
                                                                                                                                                                                                                                            tab20[cycle20][10] = C[4]+1;
                                                                                                                                                                                                                                            tab20[cycle20][11] = V[5]+1;
                                                                                                                                                                                                                                            tab20[cycle20][12] = C[5]+1;
                                                                                                                                                                                                                                            tab20[cycle20][13] = V[6]+1;
                                                                                                                                                                                                                                            tab20[cycle20][14] = C[6]+1;
                                                                                                                                                                                                                                            tab20[cycle20][15] = V[7]+1;
                                                                                                                                                                                                                                            tab20[cycle20][16] = C[7]+1;
                                                                                                                                                                                                                                            tab20[cycle20][17] = V[8]+1;
                                                                                                                                                                                                                                            tab20[cycle20][18] = C[8]+1;
                                                                                                                                                                                                                                            tab20[cycle20][19] = V[9]+1;
                                                                                                                                                                                                                                            tab20[cycle20][20] = C[9]+1;
                                                                                                                                                                                                                                            #if defined VERB
                                                                                                                                                                                                                                            for(i=0;i<21;i++)
                                                                                                                                                                                                                                                printf("%d ",tab20[cycle20][i]);
                                                                                                                                                                                                                                            printf("\n");
                                                                                                                                                                                                                                            #endif
                                                                                                                                                                                                                                            cycle20++;
                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                }
                                                                                                                                                                                                                            }
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                }
                                                                                                                                                                                                            }
                                                                                                                                                                                                        }
                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                                                                            }
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                }
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%f\n",(float)(c1+1)/M*100);
        printf("\033[A\33[2K");             //display the percentage of progress
    }

    /* ********************************************************************************************
     * Most of the cycles must be twice in each tabs 'tabi'. We need to remove the redundancies ***
     * ********************************************************************************************/

    printf("Done!\n\nSearching for redundancies and saving list files...\n");

    remove("./cycles/cycle04.txt");
    remove("./cycles/cycle06.txt");
    remove("./cycles/cycle08.txt");
    remove("./cycles/cycle10.txt");
    remove("./cycles/cycle12.txt");
    remove("./cycles/cycle14.txt");
    remove("./cycles/cycle16.txt");
    remove("./cycles/cycle18.txt");
    remove("./cycles/cycle20.txt");

    int k;
    int nbcy;


    nbcy=0;
    f = fopen("./cycles/cycle04.txt","w");
    printf("saving ./cycles/cycle04.txt...\n");
    for(i=0;i<cycle4;i++)       //for each cycles in the tab 'tab4'
    {
        j=i-1;                  //for each previously processed cycle
        k=0;
        while((j>=0) & (k<4))   //stop if a redondancy is found
        {
            if(tab4[i][k] == tab4[j][4-k])
                k++;
            else
            {
                j--;
                k=0;
            }
        }
        if(k==0)                //if the while loop ended without having found redundancy, save the cycle in the file
        {
            for(j=0;j<=4;j++)
                fprintf(f, "%d ", tab4[i][j]);
            fprintf(f, "\n");
            nbcy++;
        }
        printf("%f\n",(float)(i+1)/cycle4*100);
        printf("\033[A\33[2K");
    }
    printf("\033[A\33[2K");
    fclose(f);
    printf("Cycles 4  :%d\n",nbcy); //display the final number of cycles found

    if(MaxLenght>=6)
    {
        nbcy=0;
        f = fopen("./cycles/cycle06.txt","w");
        printf("saving ./cycles/cycle06.txt...\n");
        for(i=0;i<cycle6;i++)
        {
            j=i-1;
            k=0;
            while((j>=0) & (k<6))
            {
                if(tab6[i][k] == tab6[j][6-k])
                    k++;
                else
                {
                    j--;
                    k=0;
                }
            }
            if(k==0)
            {
                for(j=0;j<=6;j++)
                    fprintf(f, "%d ", tab6[i][j]);
                fprintf(f, "\n");
                nbcy++;
            }
            printf("%f\n",(float)(i+1)/cycle6*100);
            printf("\033[A\33[2K");
        }
        printf("\033[A\33[2K");
        fclose(f);  
        printf("Cycles 6  :%d\n",nbcy);

        if(MaxLenght>=8)
        {
            nbcy=0;
            f = fopen("./cycles/cycle08.txt","w");
            printf("saving ./cycles/cycle08.txt...\n");
            for(i=0;i<cycle8;i++)
            {
                j=i-1;
                k=0;
                while((j>=0) & (k<8))
                {
                    if(tab8[i][k] == tab8[j][8-k])
                        k++;
                    else
                    {
                        j--;
                        k=0;
                    }
                }
                if(k==0)
                {
                    for(j=0;j<=8;j++)
                        fprintf(f, "%d ", tab8[i][j]);
                    fprintf(f, "\n");
                    nbcy++;
                }
                printf("%f\n",(float)(i+1)/cycle8*100);
                printf("\033[A\33[2K");
            }
            printf("\033[A\33[2K");
            fclose(f);      
            printf("Cycles 8  :%d\n",nbcy);

            if(MaxLenght>=10)
            {
                nbcy=0;
                f = fopen("./cycles/cycle10.txt","w");
                printf("saving ./cycles/cycle10.txt...\n");
                for(i=0;i<cycle10;i++)
                {
                    j=i-1;
                    k=0;
                    while((j>=0) & (k<10))
                    {
                        if(tab10[i][k] == tab10[j][10-k])
                            k++;
                        else
                        {
                            j--;
                            k=0;
                        }
                    }
                    if(k==0)
                    {
                        for(j=0;j<=10;j++)
                            fprintf(f, "%d ", tab10[i][j]);
                        fprintf(f, "\n");
                        nbcy++;
                    }
                    printf("%f\n",(float)(i+1)/cycle10*100);
                    printf("\033[A\33[2K");
                }
                printf("\033[A\33[2K");
                fclose(f);   
                printf("Cycles 10 :%d\n",nbcy);

                if(MaxLenght>=12)
                {
                    nbcy=0;
                    f = fopen("./cycles/cycle12.txt","w");
                    printf("saving ./cycles/cycle12.txt...\n");
                    for(i=0;i<cycle12;i++)
                    {
                        j=i-1;
                        k=0;
                        while((j>=0) & (k<12))
                        {
                            if(tab12[i][k] == tab12[j][12-k])
                                k++;
                            else
                            {
                                j--;
                                k=0;
                            }
                        }
                        if(k==0)
                        {
                            for(j=0;j<=12;j++)
                                fprintf(f, "%d ", tab12[i][j]);
                            fprintf(f, "\n");
                            nbcy++;
                        }
                        printf("%f\n",(float)(i+1)/cycle12*100);
                        printf("\033[A\33[2K");
                    }
                    printf("\033[A\33[2K");
                    fclose(f);     
                    printf("Cycles 12 :%d\n",nbcy);         

                    if(MaxLenght>=14)
                    {
                        nbcy=0;
                        f = fopen("./cycles/cycle14.txt","w");
                        printf("saving ./cycles/cycle14.txt...\n");
                        for(i=0;i<cycle14;i++)
                        {
                            j=i-1;
                            k=0;
                            while((j>=0) & (k<14))
                            {
                                if(tab14[i][k] == tab14[j][14-k])
                                    k++;
                                else
                                {
                                    j--;
                                    k=0;
                                }
                            }
                            if(k==0)
                            {
                                for(j=0;j<=14;j++)
                                    fprintf(f, "%d ", tab14[i][j]);
                                fprintf(f, "\n");
                                nbcy++;
                            }
                            printf("%f\n",(float)(i+1)/cycle14*100);
                            printf("\033[A\33[2K");
                        }
                        printf("\033[A\33[2K");
                        fclose(f);      
                        printf("Cycles 14 :%d\n",nbcy);            

                        if(MaxLenght>=16)
                        {
                            nbcy=0;
                            f = fopen("./cycles/cycle16.txt","w");
                            printf("saving ./cycles/cycle16.txt...\n");
                            for(i=0;i<cycle16;i++)
                            {
                                j=i-1;
                                k=0;
                                while((j>=0) & (k<16))
                                {
                                    if(tab16[i][k] == tab16[j][16-k])
                                        k++;
                                    else
                                    {
                                        j--;
                                        k=0;
                                    }
                                }
                                if(k==0)
                                {
                                    for(j=0;j<=16;j++)
                                        fprintf(f, "%d ", tab16[i][j]);
                                    fprintf(f, "\n");
                                    nbcy++;
                                }
                                printf("%f\n",(float)(i+1)/cycle16*100);
                                printf("\033[A\33[2K");
                            }
                            printf("\033[A\33[2K");
                            fclose(f);   
                            printf("Cycles 16 :%d\n",nbcy);                   

                            if(MaxLenght>=18)
                            {
                                nbcy=0;
                                f = fopen("./cycles/cycle18.txt","w");
                                printf("saving ./cycles/cycle18.txt...\n");
                                for(i=0;i<cycle18;i++)
                                {
                                    j=i-1;
                                    k=0;
                                    while((j>=0) & (k<18))
                                    {
                                        if(tab18[i][k] == tab18[j][18-k])
                                            k++;
                                        else
                                        {
                                            j--;
                                            k=0;
                                        }
                                    }
                                    if(k==0)
                                    {
                                        for(j=0;j<=18;j++)
                                            fprintf(f, "%d ", tab18[i][j]);
                                        fprintf(f, "\n");
                                        nbcy++;
                                    }
                                    printf("%f\n",(float)(i+1)/cycle18*100);
                                    printf("\033[A\33[2K");
                                }
                                printf("\033[A\33[2K");
                                fclose(f);        
                                printf("Cycles 18 :%d\n",nbcy);                  

                                if(MaxLenght>=20)
                                {
                                    nbcy=0;
                                    f = fopen("./cycles/cycle20.txt","w");
                                    printf("saving ./cycles/cycle20.txt...\n");
                                    for(i=0;i<cycle20;i++)
                                    {
                                        j=i-1;
                                        k=0;
                                        while((j>=0) & (k<20))
                                        {
                                            if(tab20[i][k] == tab20[j][20-k])
                                                k++;
                                            else
                                            {
                                                j--;
                                                k=0;
                                            }
                                        }
                                        if(k==0)
                                        {
                                            for(j=0;j<=20;j++)
                                                fprintf(f, "%d ", tab20[i][j]);
                                            fprintf(f, "\n");
                                            nbcy++;
                                        }
                                        printf("%f\n",(float)(i+1)/cycle20*100);
                                        printf("\033[A\33[2K");
                                    }
                                    printf("\033[A\33[2K");
                                    fclose(f);
                                    printf("Cycles 20 :%d\n",nbcy);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("DONE!\n");
}
