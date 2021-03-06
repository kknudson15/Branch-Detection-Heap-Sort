#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "DynamicBranchPred.h"

int pred[numberOfBranches][HISTORYS]; 
/*declare and initial all 1bit predictors to NT*/  
int history[numberOfBranches] = {NT}; 
/*declare history bits for each branch*/ 
int numOfT[numberOfBranches]={0},numOfNT[numberOfBranches]={0}, numOfPred[numberOfBranches]={0},numOfMissP[numberOfBranches]={0}; 
int historyPred[numberOfBranches][n*n];/*record the history predictors for each branch*/ 
 

int main(int argc, char **argv){
    int i,j;
    int a[n];
    /*array for sorting*/
    srand(time(NULL));  /*for generating random number*/    
    initialize_Predictor();    /*print out initial predictor*/    
    printf("The initialized predictor is: ");    
    printPredictor(pred[0][0]);
    printf("\n");  
     i = 0; 
     loop0:    
        if(i>=n){ 
            /*branch 0*/       
            statTA(0);    
            goto Endloop0;}    
            statNTA(0);    
            a[i] = rand()%100;
            i++;    
            goto loop0;
            Endloop0:
            printf("\nBefore heap sort:\n");
            printArrayElements(a,n);
            printf("\n");     
             /*Heap sorting*/   
        i=(n-2)/2; 
        loop1:     
        if(i<0){
            /*branch 1*/       
            statTA(1);       
            goto Endloop1;}      
            statNTA(1);   
            heap_down(a,i,n-1);
            --i;  
            goto loop1; 
            Endloop1:          
            i=n-1; 
            loop2:     
            if(i<=0){              
                /*branch 2*/      
                statTA(2);    
                goto Endloop2;}  
                statNTA(2);  
                swap(&a[0],&a[i]);  
                heap_down(a,0,i-1);  
                --i;     
                goto loop2; 
                Endloop2: 
            printFinalResult(numberOfBranches);     
            printf("\n\nAfter sorting:\n");     
            printArrayElements(a,n);     
            exit(0); } 
 
/*function that aids in the heap sort*/ 
void heap_down(int a[],int parent,int last) {     
    int max_child;  
    bool done=false; 
    loop3:     
        if(2*parent+1>last || done){  
            /*branch 5*/           
            statTA(5);     
            goto Endloop3;}    
        statNTA(5);  
        max_child=2*parent+1;  
        if(a[max_child+1]<=a[max_child]||max_child+1>last){
            /*branch 3*/    
            statTA(3);       
            goto option1;}

        statNTA(3);  
        ++max_child;   
        option1:     
        if(a[max_child]>a[parent]){   
            /*branch 4*/           
            statTA(4);     
            goto option2; }     
        done=true;
        goto option3;   
        option2:           
        statNTA(4);     
        swap(&a[max_child],&a[parent]);     
        parent = max_child;   
        option3:      
        goto loop3; 
        Endloop3: 
            return; } 
 
/*exchange two values of two variables*/ 
void swap(int* val1,int* val2) {   
    int temp;   
    temp = *val1;   
    *val1 = *val2;   
    *val2 = temp; } 
    
/*print data of array b to the terminal*/ 
void printArrayElements(int b[],int size){     
    int i;  
    printf("{");  
    for(i=0;i<size;++i){     
        printf("%d ",b[i]);  }  
    printf("}\n"); } 
 
/*initializing predictors*/ 
void initialize_Predictor(){    
    int i,j;    
    for(i=0;i<numberOfBranches;i++)       
        for(j=0;j<HISTORYS;j++)       
            pred[i][j] = NT; } 
 
/*print out predictor in binary*/ 
void printPredictor(int predictor){    
    if(predictor==0)       
        printf("NT(0) ");    
    else   
      printf("T(1) ");  } 
 
 /*print out history predictors*/  
 void printHistory(int history[][n*n],int branch,int size){      
     int i;   
     for(i=0;i<size;i++)      
     printPredictor(history[branch][i]);  }
     
/*update predictor */  
void updatePred1(int action,int branch){    
    if(action==T){    
        pred[branch][history[branch]] = T;    }
    else{    
        pred[branch][history[branch]] = NT; }  } 
 
 /*update history*/  
 void updateHistory(int action, int branch){     
     if(action==T){    
         history[branch] = ((history[branch]&7) << 1) + 1;    }
    else{    
        history[branch] = (history[branch]&7) << 1;    }  } 
 
 /*function return missed or not*/  
 bool isMissed1(int branch,int action){    
     return (pred[branch][history[branch]] != action);  } 
 
 /*statistics data in Taken action*/  
 void statTA(int branch){     
     numOfT[branch]++;  
     numOfPred[branch]++;  
     historyPred[branch][numOfPred[branch]] = pred[branch][history[branch]];  
     if(isMissed1(branch,T))   
        numOfMissP[branch]++;  
        updatePred1(T,branch);  
        updateHistory(T,branch); }  
        
/*statistics data in Not-Taken action*/  
void statNTA(int branch){     
    numOfNT[branch]++;  
    numOfPred[branch]++;  
 historyPred[branch][numOfPred[branch]] = pred[branch][history[branch]];
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