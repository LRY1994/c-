//����ԪLU�㷨
#pragma warning(disable:4996)
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
double a[1000][1000];
double b[1000];
double l[1000][1000];
double u[1000][1000];
double s[1000];
double y[1000];
double x[1000];
int main(){
	int n;
	printf("������n\n");
	scanf("%d", &n);

	printf("������A����\n");
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%lf", &a[i][j]);
		}
	}
	printf("������b����\n");
	for (int i = 1; i <= n; i++)
		scanf("%lf", &b[i]);
	/*
	1 2 1
	2 2 3
	-1 -3 0
	*/


	double e;
	printf("�������������:");
	scanf("%lf", &e);

	for (int j = 1; j <= n; j++) { u[1][j] = a[1][j]; }
	l[1][1] = 1;
	for (int i = 2; i <= n; i++){ l[i][1] = a[i][1] / u[1][1]; l[i][i] = 1; }
	

	double sum;
	double temp;
	int fail;
	int ik;
	double zhuyuan;

	for (int k = 1; k <= n; k++){
		sum = 0;
		zhuyuan = 0;
		fail = 0;
		for (int i = k; i <= n; i++){
			for (int m = 1; m < k; m++)
			{
				sum += l[i][m] * u[m][k];
			}
			s[i] = a[i][k] - sum;
			if (fabs(zhuyuan) < fabs(s[i])){
				zhuyuan = s[i];
				ik = i;
			}
		}


		if (fabs(zhuyuan) < e){
			printf("���ʧ��");
			fail = 1;
			break;
		}
		else {
			//����A�ĵ�k�к͵�ik��
			for (int j = 1; j <= n; j++){
				temp = a[k][j];
				a[k][j] = a[ik][j];
				a[ik][j] = temp;
			}
			//����U�ĵ�k��Ԫ��
			for (int j = k; j <= n; j++){
				sum = 0;
				for (int m = 1; m < k; m++)
					sum += l[k][m] * u[m][j];
				u[k][j] = a[k][j] - sum;
			}
			//����L�ĵ�k��Ԫ��
			for (int i = k + 1; i <= n; i++){
				sum = 0;
				for (int m = 1; m < k; m++)
					sum += l[i][m] * u[m][k];
				l[i][k] = (a[i][k] - sum) / u[k][k];
			}



			//��b�����ĵ�k��Ԫ�غ͵�ik��Ԫ�ؽ���
			for (int j = 1; j <= n; j++){
				temp = b[k];
				b[k] = b[ik];
				b[ik] = temp;
			}
		}
	}


	if (!fail){

		//���LY=b
		y[1] = b[1];
		for (int i = 2; i <= n; i++){
			sum = 0;
			for (int j = 1; j <= i - 1; j++){
				sum += l[i][j] * y[j];
			}
			y[i] = b[i] - sum;
		}
		//���UX=Y
		x[n] = y[n] /u[n][n];
		for (int i = n - 1; i >= 1; i--){
			sum = 0;
			for (int j = i + 1; j <= n; j++){
				sum += u[i][j] * x[j];
			}
			x[i] = (y[i] - sum) / u[i][i];
		}
		//��ӡX
		printf("X�Ľ�Ϊ��");
		for (int i = 1; i <= n; i++)printf("%lf ", x[i]);
	}
}