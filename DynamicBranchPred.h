#define n 25 
#define bool int     
#define true 1 
#define false 0 
#define numberOfBranches 6   /*number of branches*/ 
#define INIT 1      /*initialize predictor 01*/ 
#define T 1 
#define NT 0 
#define HISTORYBIT 3 /*history bits*/ 
#define HISTORYS 8 
 
 
/*functions*/ 
/*print out elements of array*/ 
void printArrayElements(int b[],int size); 
/*exchange the values of two variables*/
void swap(int* val1,int* val2); 
/*aid heap sort function*/ 
void heap_down(int a[],int parent,int last);
/*initializing predictors*/ 
void initialize_Predictor();
/*print out predictor*/ 
void printPredictor(int predictor); 
/*print out history predictors*/ 
void printHistory(int history[][n*n],int branch,int size);
/*record statistics when Taken action*/ 
void statTA(int branch);
/*record statistics when Not-Taken action*/ 
void statNTA(int branch); 
/*record initial predictor for each branch*/ 
void recordInitPred(int size); 
/*print final result about predictor*/ 
void printFinalResult(int size);
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
