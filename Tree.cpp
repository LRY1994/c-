#include "header.h"
#include "global.h"
using namespace std;

void creatBTree(BTNode *&root, double initial,int firstLayerNum,int node_num)
{
    int count_num = 0; 
    vector<BTNode *> list;

    //root
    root = new BTNode();
    root->temperature = initial;
    root->sum = 0;
    root->layer = 0;
    root->path.push_back(root->temperature);
    count_num++;  

    //first layer
    BTNode * tmp;int i=0;
    while(i<firstLayerNum){
        i++;
        tmp = new BTNode();
        tmp->temperature = get_firstLayer_temp(i,initial,firstLayerNum,1);
        tmp->sum = 0;
        tmp->layer = 1;
        tmp->path.push_back(root->temperature);

        root->children.push_back(tmp);

        count_num++;  
        list.push_back(tmp);
    }

    
    while (count_num < node_num)
    {
        vector<BTNode *> tmplist;

        for (int i = 0; i < list.size(); i++)
        {
            
            BTNode *node = list[i];
            double high = get_highest_temp(node->temperature,node->layer) ;
            double low = get_lowest_temp(node->temperature,node->layer) ;
            double dist = high - low;
            //left node
            tmp = new BTNode();
            tmp->temperature = low + dist * 0.25;
            tmp->sum=0;
            tmp->layer = node->layer + 1;
            count_num++;
            node->children.push_back(tmp);
            tmplist.push_back(tmp);
            //right node
            tmp = new BTNode();
            tmp->temperature = high - dist * 0.25;
            tmp->sum=0;
            tmp->layer = node->layer + 1;
            count_num++;
            node->children.push_back(tmp);
            tmplist.push_back(tmp);
        }

        list = tmplist;
    }
}

void depthFirstSearch(BTree root)
{
    stack<BTNode *> nodeStack; 
    nodeStack.push(root);
    BTNode *node;

    vector<double> tmp;
    while (!nodeStack.empty())
    {

        node = nodeStack.top();
        // printf("%lf\n", node->temperature); 
        nodeStack.pop();
        tmp = node->path;

        BTNode *child;
        for(int i=0;i<node->children.size();i++){
            child = node->children[i];
            child->sum = node->sum + cal_power(node->temperature, child->temperature,node->layer);
           
            if (child->sum < min_sum)
            { //pruning
                child->path = tmp;
                child->path.push_back(child->temperature);
                nodeStack.push(child); 
            }
        }

        if (node->children.size() == 0)
        { //child node
            if (node->sum < min_sum)
            {
                min_sum = node->sum;
                min_path = node->path;
            }
        }
    }
}
