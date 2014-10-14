#pragma once

#include <vector>       // std::vector
#include <queue>
#include <stack>
#include <iostream>


using namespace std;
struct Compare_function;

class SolutionSearch
{
public:
    SolutionSearch(void);
    ~SolutionSearch(void);
    
    bool breadthSearch(int *data, vector<int> &solution); //Student Implementation: you need to implement this function
    bool depthSearch(int *data, vector<int> &solution); //Student Implementation: you need to implement this function
    void AStarSearch(int *data, vector<int> &solution);
    

};



class PuzzleNode
{
public:
    int hx=0;
    int gx=0;
    int fx=0;
    int value[9];
    PuzzleNode* parent;
    
    void setFx(int *data){
        for (int i=0; i<=8; i++) {
            for (int j=0; j<=8; j++) {
                if (data[j]==i){
                    hx+=(abs((i/3-j/3)+abs(i%3-j%3)));
                    break;
                }
            }
        }
        gx+=1;
        fx=gx+hx+parent->fx;
    }
    
    vector<PuzzleNode*> children; //the node for all the children
    
    /*constructor*/
    PuzzleNode(void){
        parent=NULL;
    }
    
    /*destructor*/
    ~PuzzleNode(void){
        children.clear();
    }
    
    int BlankPosition()//return the blank element location.
    {
        int p=-1;
        for(int i =0;i<=8;i++)
        {
            if(value[i]==8)
            {
                p=i;
                break;
            }
        }
        return p;
    }
    void loadchildren(deque<PuzzleNode*> &,bool);
    friend class Compare;
};
