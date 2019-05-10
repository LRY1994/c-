/**һ����
 */
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <Stack>
#include <Queue>
#include <vector>
#include <cmath>
using namespace std;

int node_num = 0;
int min_sum = 99999999;  
vector<double> min_path; 

typedef struct BTNode
{
    double temperature; 
    double sum;         
    vector<double> path;
    vector<BTNode *> children;
} * BTree;

typedef struct Point 
{
    double x;//ʱ��
    double y;//�¶�
    Point(double a,double b){ x=a;y=b;}
};

double cal_power(double a, double b);
double get_hightest_temp(double origin);
double get_lowest_temp(double origin);
double get_firstLayer_temp(int index,double rootVal);
void CreatBTree(BTree &root, double initial);
void depthFirstSearch(BTree root);

double cal_power(double a, double b)
{
    return 0;
}
double get_hightest_temp(double origin)
{
    return origin + 1;
}
double get_lowest_temp(double origin)
{
    return origin - 1;
}

double get_firstLayer_temp(int index,double rootVal){
    return index * rootVal;
}

void CreatBTree(BTNode *&root, double initial,int firstLayerNum)
{
    int count_num = 0; 
    vector<BTNode *> list;

    //��
    root = new BTNode();
    root->temperature = initial;
    root->sum = 0;
    root->path.push_back(root->temperature);
    count_num++;  

    //��һ��
    BTNode * tmp;int i=0;
    while(i<firstLayerNum){
        i++;
        tmp = new BTNode();
        tmp->temperature = get_firstLayer_temp(i,initial);
        tmp->sum = 0;
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
            //��ڵ�
            tmp = new BTNode();
            tmp->temperature = get_lowest_temp(node->temperature);
            tmp->sum=0;
            count_num++;
            node->children.push_back(tmp);
            tmplist.push_back(tmp);
            //�ҽڵ�
            tmp = new BTNode();
            tmp->temperature = get_hightest_temp(node->temperature);
            tmp->sum=0;
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
        printf("%lf\n", node->temperature); 
        nodeStack.pop();
        tmp = node->path;

        BTNode *child;
        for(int i=0;i<node->children.size();i++){
            child = node->children[i];
            child->sum = node->sum + cal_power(node->temperature, child->temperature);
            if (child->sum < min_sum)
            { //��֦
                child->path = tmp;
                child->path.push_back(child->temperature);
                nodeStack.push(child); 
            }
        }

        if (node->children.size() == 0)
        { //Ҷ�ӽڵ�
            if (node->sum < min_sum)
            {
                min_sum = node->sum;
                min_path = node->path;
            }
        }
    }
}

int main()
{
    int segment;
    printf("����ʱ��������");
    scanf("%d", &segment);

    double initialVal;
    printf("�����ʼ�¶ȣ�");
    scanf("%lf", &initialVal);

    int firstLayerNum;
    printf("�����һ��ڵ������");
    scanf("%d", &firstLayerNum);

    node_num = firstLayerNum * (pow(2, segment) - 1) + 1;
     printf("һ������%d���ڵ�\n4",node_num);

    BTree tree;
    CreatBTree(tree, initialVal ,firstLayerNum);

    printf("������ȱ������������(������֦): \n");

    depthFirstSearch(tree);

    printf("��С����Ϊ%lf\n",min_sum);

    printf("��С����·��Ϊ��\n");
    for (int i = 0; i < min_path.size(); i++)
    {
        printf("%lf,", min_path[i]);
    }

    return 0;
}
