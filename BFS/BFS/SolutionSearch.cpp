#include "SolutionSearch.h"



SolutionSearch::SolutionSearch(void)
{
}


SolutionSearch::~SolutionSearch(void)
{
}


bool compare(PuzzleNode* &a,PuzzleNode* &b)
{
    return a->fx < b->fx;
}

void SolutionSearch::AStarSearch(int *data, vector<int> &solution){
    const int goal[9]={0,1,2,3,4,5,6,7,8};
    
    vector<PuzzleNode*> RList;
    
    deque<PuzzleNode*> AStardeque; //using deque for both bfs and dfs
    
    PuzzleNode* Root=new PuzzleNode;
    
    for(int i=0;i<=8;i++)
        Root->value[i]=data[i];
    for (int i=0; i<=8; i++) {
        for (int j=0; j<=8; j++) {
            if (data[j]==i){
                Root->hx+=(abs((i/3-j/3)+abs(i%3-j%3)));
                break;
            }
        }
    }
    Root->gx+=1;
    Root->fx=Root->gx+Root->hx;
    AStardeque.push_back(Root);
    
    while(!AStardeque.empty()){
        sort(AStardeque.begin(), AStardeque.end(), compare);
        PuzzleNode* NODE=AStardeque.front();
        AStardeque.pop_front();
            if (memcmp(NODE->value,goal,sizeof(goal))==0) {
                solution.clear();
                while (NODE->parent!=NULL) {
                    solution.push_back(NODE->BlankPosition());
                    NODE=NODE->parent;
                }
                reverse(solution.begin(), solution.end());
                AStardeque.clear();
            }
            else{
                NODE->loadchildren(AStardeque, true);
            }
        }
}


bool SolutionSearch::breadthSearch(int *data, vector<int> &solution)
{
    const int goal[9]={0,1,2,3,4,5,6,7,8};
    
    vector<PuzzleNode*> RList;
    
    deque<PuzzleNode*> BFSDeque; //using deque for both bfs and dfs
    
    PuzzleNode* Root=new PuzzleNode;
    
    for(int i=0;i<=8;i++)
        Root->value[i]=data[i];
    
    BFSDeque.push_back(Root);
    
    while(!BFSDeque.empty()){
        PuzzleNode* NODE=BFSDeque.front();
        BFSDeque.pop_front();
        bool Existed=false;
        for(int i=0;i<RList.size();i++){
            if (memcmp(RList[i]->value,NODE->value,sizeof(NODE->value))==0) {
                printf("excited\n");
                Existed=true;
                delete NODE;
                break;
            }
        }
        if (!Existed) {
            RList.push_back(NODE);
            if (memcmp(NODE->value,goal,sizeof(goal))==0) {
                solution.clear();
                while (NODE->parent!=NULL) {
                    solution.push_back(NODE->BlankPosition());
                    NODE=NODE->parent;
                }
                reverse(solution.begin(), solution.end());
                BFSDeque.clear();
            }
            else{
                NODE->loadchildren(BFSDeque, true);
            }
        }
    }
    return 1;
}

/*  Student Implementation: here you need to implement the Depth First Search Method   */
/*  The input parameters follow the same rule as above "breadthSearch"				   */
bool SolutionSearch::depthSearch(int *data, vector<int> &solution)
{
    const int goal[9]={0,1,2,3,4,5,6,7,8};
    
    vector<PuzzleNode*> RList;
    
    deque<PuzzleNode*> DFSDeque; //using deque for both bfs and dfs
    
    PuzzleNode* Root=new PuzzleNode;
    
    for(int i=0;i<=8;i++)
        Root->value[i]=data[i];
    
    DFSDeque.push_front(Root);
    
    while(!DFSDeque.empty()){
        bool Existed=false;
        PuzzleNode* NODE=DFSDeque.front();
        DFSDeque.pop_front();
        for(int i=0;i<RList.size();i++){
            if (memcmp(RList[i]->value,NODE->value,sizeof(NODE->value))==0) {
                printf("exisited\n");
                Existed=true;
                delete NODE;
                break;
            }
        }
        if (!Existed) {
            RList.push_back(NODE);
            if (memcmp(NODE->value,goal,sizeof(goal))==0) {
                solution.clear();
                while (NODE->parent!=NULL) {
                    solution.push_back(NODE->BlankPosition());
                    NODE=NODE->parent;
                }
                reverse(solution.begin(), solution.end());
                DFSDeque.clear();
            }
            else{
                NODE->loadchildren(DFSDeque, false);
            }
        }
    }
    return 1;
}

void PuzzleNode::loadchildren(deque<PuzzleNode*> &Queue,bool dfs)
{
    int positon=BlankPosition();
    int Operator=0;
    int childvalues[4][9];
    switch (positon)
    {
        case 0:
            Operator=2;// 2 operators.
            memcpy(childvalues[0],value,sizeof(value));//copy present value to the child node.
            childvalues[0][0]=value[3];
            childvalues[0][3]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][0]=value[1];
            childvalues[1][1]=8;
            break;
        case 1:
            Operator=3;// 3 opeators.
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][1]=value[0];
            childvalues[0][0]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][1]=value[2];
            childvalues[1][2]=8;
            memcpy(childvalues[2],value,sizeof(value));
            childvalues[2][1]=value[4];
            childvalues[2][4]=8;
            break;
        case 2:
            Operator=2;// 2 opeators.
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][2]=value[1];
            childvalues[0][1]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][2]=value[5];
            childvalues[1][5]=8;
            break;
        case 3:
            Operator=3;// 3 opeators.
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][3]=value[0];
            childvalues[0][0]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][3]=value[4];
            childvalues[1][4]=8;
            memcpy(childvalues[2],value,sizeof(value));
            childvalues[2][3]=value[6];
            childvalues[2][6]=8;
            break;
        case 4:
            Operator=4; //4 opeators.
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][4]=value[1];
            childvalues[0][1]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][4]=value[3];
            childvalues[1][3]=8;
            memcpy(childvalues[2],value,sizeof(value));
            childvalues[2][4]=value[5];
            childvalues[2][5]=8;
            memcpy(childvalues[3],value,sizeof(value));
            childvalues[3][4]=value[7];
            childvalues[3][7]=8;
            break;
        case 5:
            Operator=3; // 3 operators
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][5]=value[2];
            childvalues[0][2]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][5]=value[4];
            childvalues[1][4]=8;
            memcpy(childvalues[2],value,sizeof(value));
            childvalues[2][5]=value[8];
            childvalues[2][8]=8;
            break;
        case 6:
            Operator=2;// 2 operators
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][6]=value[3];
            childvalues[0][3]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][6]=value[7];
            childvalues[1][7]=8;
            break;
        case 7:
            Operator=3;// 3 operators
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][7]=value[6];
            childvalues[0][6]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][7]=value[4];
            childvalues[1][4]=8;
            memcpy(childvalues[2],value,sizeof(value));
            childvalues[2][7]=value[8];
            childvalues[2][8]=8;
            break;
        case 8:
            Operator=2;// 2 operators
            memcpy(childvalues[0],value,sizeof(value));
            childvalues[0][8]=value[5];
            childvalues[0][5]=8;
            memcpy(childvalues[1],value,sizeof(value));
            childvalues[1][8]=value[7];
            childvalues[1][7]=8;
            break;
        default:
            cout<<"An error occurred"<<endl;
            exit(-1);
    }
    
    for(int i=0;i<Operator;i++)
    {
        PuzzleNode *child=new PuzzleNode;
        child->parent=this;
        memcpy(child->value,childvalues[i],sizeof(value));
        child->setFx(child->value);
        this->children.push_back(child);
        if(dfs)
            Queue.push_back(child);
        if(!dfs)
            Queue.push_front(child);
    }
}
