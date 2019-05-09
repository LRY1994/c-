/*
https://blog.csdn.net/mingwanganyu/article/details/72033122
https://blog.csdn.net/qq_33001647/article/details/69808560
http://www.cnblogs.com/davidxu/p/9031055.html

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
int min_sum = 99999999;  //��С����
vector<double> min_path; //��С����·��

typedef struct BTNode
{
    double temperature; //�¶�
    double sum;         //�Ӹ��ڵ㵽�˽ڵ�Ĺ���
    vector<double> path;
    BTNode *lchild;
    BTNode *rchild;
} * BTree;

double cal_power(double a, double b);
double get_hightest_temp(double origin);
double get_lowest_temp(double origin);
void CreatBTree(BTree &root, double initial);
void depthFirstSearch(BTree root);

//���㹦��
double cal_power(double a, double b)
{
    return 0;
}
//��������¶�
double get_hightest_temp(double origin)
{
    return origin + 1;
}
//��������¶�
double get_lowest_temp(double origin)
{
    return origin - 1;
}

//����ν���������
void CreatBTree(BTNode *&root, double initial)
{
    int count_num = 0; //������  
    vector<BTNode *> list;

    root = new BTNode();
    root->temperature = initial;
    root->sum = 0;
    root->path.push_back(root->temperature);
    count_num++;  
    list.push_back(root);

    //�����ѵ�һ��Ž�ջ
    // int firstLayer = firstLayerNum;
    // while(firstLayer--){
    //     root = new BTNode();
    //     root->temperature = initial;
    //     root->sum = 0;
    //     root->path.push_back(root->temperature);
    //     count_num++;  
    //     list.push_back(root);
    // }
    


    while (count_num < node_num)
    {
        vector<BTNode *> tmplist;

        for (int i = 0; i < list.size(); i++)
        {
            BTNode *node = list[i];
            //��ڵ�
            node->lchild = new BTNode();
            node->lchild->temperature = get_lowest_temp(node->temperature);
            node->lchild->sum = 0;
            count_num++;
            tmplist.push_back(node->lchild);
            //�ҽڵ�
            node->rchild = new BTNode();
            node->rchild->temperature = get_hightest_temp(node->temperature);
            node->lchild->sum = 0;
            count_num++;
            tmplist.push_back(node->rchild);
        }

        list = tmplist;
    }
}
//�������
void depthFirstSearch(BTree root)
{
    stack<BTNode *> nodeStack; //ʹ��C++��STL��׼ģ���
    nodeStack.push(root);
    BTNode *node;

    vector<double> tmp;
    while (!nodeStack.empty())
    {

        node = nodeStack.top();
        printf("%lf\n", node->temperature); //���������
        nodeStack.pop();
        tmp = node->path;

        if (node->rchild)
        {
            node->rchild->sum = node->sum + cal_power(node->temperature, node->rchild->temperature);
            if (node->rchild->sum < min_sum)
            { //��֦
                node->rchild->path = tmp;
                node->rchild->path.push_back(node->rchild->temperature);
                nodeStack.push(node->rchild); //�Ƚ�������ѹջ
            }
        }
        if (node->lchild)
        {
            node->lchild->sum = node->sum + cal_power(node->temperature, node->lchild->temperature);
            if (node->rchild->sum < min_sum)
            { //��֦
                node->lchild->path = tmp;
                node->lchild->path.push_back(node->lchild->temperature);
                nodeStack.push(node->lchild); //�ٽ�������ѹջ
            }
        }

        if (!node->rchild && !node->lchild)
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
    printf("����ʱ��θ�����");
    scanf("%d", &segment);

    double initialVal;
    printf("�����ʼ�¶ȣ�");
    scanf("%lf", &initialVal);

    double firstLayerNum;
    printf("�����һ��ڵ������");
    scanf("%d", &firstLayerNum);

    node_num = 2 * (pow(2, segment) - 1) + 1;

    BTree tree;
    CreatBTree(tree, initialVal);

    printf("������ȱ������������: \n");

    depthFirstSearch(tree);

    printf("��С����Ϊ��\n");
    printf("%lf\n", min_sum);

    printf("��С����·��Ϊ��\n");
    for (int i = 0; i < min_path.size(); i++)
    {
        printf("%lf,", min_path[i]);
    }

    return 0;
}
