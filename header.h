#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <vector>
#include <Stack>
using namespace std;

#ifndef TEST_H
#define TEST_H

typedef struct BTNode
{
    double temperature;
    int layer; 
    double sum;    
    int SOC;     
    vector<double> path;
    vector<BTNode *> children;
} * BTree;

struct Point 
{
    double x;//time
    double y;//temparature
    Point(double a,double b){x=a;y=b;}
};

//config.cpp
double getI();
double cal_power(double parent,double child,int layer,double I,double SOC);
double get_highest_temp(double T,int layer,double I,double SOC);
double get_lowest_temp(double T,int layer,double I,double SOC);
double get_firstLayer_temp(int i,int N,double parentT,double I,double SOC);
double getTime(double lastTime,int layer);
void getDt(int segment,double I);
double getSoc(double parentT, double childT, double parentSOC,double I,int parentLayer);
double getPptc(double T,double Tnex,double Pcool,double Pexo,int layer);
double getPexo(double T,double I,double SOC,int layer);
double getPcool(double T,double Tnex);
//tree.cpp,里面用到了config.cpp
void creatBTree(BTNode *&root, double initial,int firstLayerNum,int node_num,double I);
void depthFirstSearch(BTree root,double I);

//spline.cpp
vector<double> interpolation(vector<Point> pointList,int option);
double getValue(double xx);

//main.cpp
vector<double> getMArray(int segment,double initialVal,int firstLayerNum);
double getM(int index);
double getX(int index);
double getY(int index);

#endif
