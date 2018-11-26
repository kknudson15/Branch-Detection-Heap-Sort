#define n 25 
#define bool int     
#define true 1 
#define false 0 
#define numOfBr 6   /*number of branches*/ 
#define INIT 1      /*initialize predictor 01*/ 
#define T 1 
#define NT 0 
#define HISTORYBIT 3 /*history bits*/ 
#define HISTORYS 8 
 
 
/*functions*/ 
/*print out elements of array*/ 
void printArray(int b[],int size); 
/*exchange the values of two variables*/
void exchange(int* a,int* b); 
/*aid heap sort function*/ 
void walk_down(int a[],int parent,int last);
/*initializing predictors*/ 
void initPred();
/*print out predictor*/ 
void printPred(int predictor); 
/*update predictor*/ 
void updatePred(int* predictor, int action);
void updatePred1(int action,int branch); 
/*update history*/ 
void updateHistory(int action, int branch);
/*print out statistics about predictor for branch*/ 
void printStat(int numOfT,int numOfNT,int numOfPred,int numOfMissP,int branch); 
/*return true if missing prediction,else false*/ 
bool isMissed(int predictor,int action); 
bool isMissed1(int branch,int action);
/*print out history predictors*/ 
void printHistory(int history[][n*n],int branch,int size);
/*record statistics when Taken action*/ 
void statTAction(int branch);
/*record statistics when Not-Taken action*/ 
void statNTAction(int branch); 
/*record initial predictor for each branch*/ 
void recordInitPred(int size); 
/*print final result about predictor*/ 
void printFinalResult(int size);