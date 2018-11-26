#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "DynamicBranchPred.h"

int predictor[numOfBr][HISTORYS]; /*declare and initial all 1bit preds NT*/  
int history[numOfBr] = {NT};             /*declare history bits for each branch*/ 
int numOfT[numOfBr]={0},numOfNT[numOfBr]={0}, numOfPred[numOfBr]={0},numOfMissP[numOfBr]={0}; 
int historyPred[numOfBr][n*n];/*record the history predictors for each branch*/ 
 

int main(int argc, char **argv){
    int i,j;
    int a[n];
    /*array for sorting*/
    srand(time(NULL));  /*for generating random number*/    
    initPred();    /*print out initial predictor*/    
    printf("The initialized predictor is: ");    
    printPred(predictor[0][0]);printf("\n"); /*prepare data*/   
     i = 0; 
     loop0:    
        if(i>=n){ 
            /*branch 0*/       
            statTAction(0);    
            goto Endloop0;}    
            statNTAction(0);    
            a[i] = rand()%100;
            i++;    
            goto loop0;
            Endloop0:
            printf("\nBefore heap sort:\n");
            printArray(a,n);printf("\n");     
             /*Heap sorting*/   
        i=(n-2)/2; 
        loop1:     
        if(i<0){
            /*branch 1*/       
            statTAction(1);       
            goto Endloop1;}      
            statNTAction(1);   
            walk_down(a,i,n-1);
            --i;  
            goto loop1; 
            Endloop1:          
            i=n-1; 
            loop2:     
            if(i<=0){              
                /*branch 2*/      
                statTAction(2);    
                goto Endloop2;}  
                statNTAction(2);  
                exchange(&a[0],&a[i]);  
                walk_down(a,0,i-1);  
                --i;     
                goto loop2; 
                Endloop2: 
            printFinalResult(numOfBr);     
            printf("\n\nAfter sorting:\n");     
            printArray(a,n);     
            exit(0); } 
 
/*Aid function for heap sort*/ 
void walk_down(int a[],int parent,int last) {     
    int max_child;  
    bool done=false; 
    loop3:     
        if(2*parent+1>last || done){  
            /*branch 5*/           
            statTAction(5);     
            goto Endloop3;}    
        statNTAction(5);  
        max_child=2*parent+1;  
        if(a[max_child+1]<=a[max_child]||max_child+1>last){
            /*branch 3*/    
            statTAction(3);       
            goto option1;}

        statNTAction(3);  
        ++max_child;   
        option1:     
        if(a[max_child]>a[parent]){   
            /*branch 4*/           
            statTAction(4);     
            goto option2; }     
        done=true;
        goto option3;   
        option2:           
        statNTAction(4);     
        exchange(&a[max_child],&a[parent]);     
        parent = max_child;   
        option3:      
        goto loop3; 
        Endloop3: 
            return; } 
 
/*exchange two values of two variables*/ 
void exchange(int* a,int* b) {   
    int temp;   
    temp = *a;   
    *a = *b;   
    *b = temp; } 
    
/*print data of array b to screen*/ 
void printArray(int b[],int size){     
    int i;  
    printf("{");  
    for(i=0;i<size;++i){     
        printf("%d ",b[i]);  }  
    printf("}\n"); } 
 
/*initializing predictors*/ 
void initPred(){    
    int i,j;    
    for(i=0;i<numOfBr;i++)       
        for(j=0;j<HISTORYS;j++)       
            predictor[i][j] = NT; } 
 
/*print out predictor in binary*/ 
void printPred(int predictor){    
    if(predictor==0)       
        printf("NT(0) ");    
    else   
      printf("T(1) ");  } 
 
 /*print out history predictors*/  
 void printHistory(int history[][n*n],int branch,int size){      
     int i;   
     for(i=0;i<size;i++)      
     printPred(history[branch][i]);  }
     
/*update predictor */  
void updatePred1(int action,int branch){    
    if(action==T){    
        predictor[branch][history[branch]] = T;    }
    else{    
        predictor[branch][history[branch]] = NT; }  } 
 
 /*update history*/  
 void updateHistory(int action, int branch){     
     if(action==T){    
         history[branch] = ((history[branch]&7) << 1) + 1;    }
    else{    
        history[branch] = (history[branch]&7) << 1;    }  } 
 
 /*function return missed or not*/  
 bool isMissed1(int branch,int action){    
     return (predictor[branch][history[branch]] != action);  } 
 
 /*statistics data in Taken action*/  
 void statTAction(int branch){     
     numOfT[branch]++;  
     numOfPred[branch]++;  
     historyPred[branch][numOfPred[branch]] = predictor[branch][history[branch]];  
     if(isMissed1(branch,T))   
        numOfMissP[branch]++;  
        updatePred1(T,branch);  
        updateHistory(T,branch); }  
        
/*statistics data in Not-Taken action*/  
void statNTAction(int branch){     
    numOfNT[branch]++;  
    numOfPred[branch]++;  
 historyPred[branch][numOfPred[branch]] = predictor[branch][history[branch]];
    if(isMissed1(branch,NT))   
        numOfMissP[branch]++;  
    updatePred1(NT,branch);  
    updateHistory(NT,branch);  } 
 
 /*print out the statistics*/  
 void printStat(int numOfT,int numOfNT, int numOfPred,int numOfMissP,int branch){    
    float rightRate = (numOfPred - numOfMissP)*100/(float)numOfPred;    
    printf("\nBranch %d's number of Taken is: %d\n",branch,numOfT);    
    printf("Branch %d's number of Not-Taken is: %d\n",branch,numOfNT);    
    printf("Branch %d's number of predictions is: %d\n",branch,numOfPred);  
    printf("Branch %d's number of miss-predictions is: %d\n",branch,numOfMissP);    
    printf("Branch %d's Right Rate = %3.2f%%\n",branch,rightRate);  } 
 
 /*print final result about predictor*/  
 void printFinalResult(int size){      
    int i;   
    for(i=0;i<size;i++){      
         printf("\nFor Branch %d:\n",i);      
    printHistory(historyPred,i,numOfPred[i]);      
    printStat(numOfT[i],numOfNT[i],numOfPred[i],numOfMissP[i],i);   }  } 