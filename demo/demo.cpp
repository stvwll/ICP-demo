#include "pch.h"
#include <iostream>
#include "icpPointToPlane.h"
#include "icpPointToPoint.h"
#include <fstream>
using namespace std;
//统计文件的行数
int getLineNum(string filename) {
	ifstream ifs(filename);
	int res = 0; string tmp;
	while (getline(ifs, tmp))//逐行读取文件，将行读入字符串tmp   等价于ifs>>tmp；默认回车符停止读入词
		res++;//统计行数
	return res;
}
//读文件数据，每行三个数据，结果保存到data指针数组
double* readfile(string filename) {
	int lineNum = getLineNum(filename);
	double *data = (double*)calloc(3 * lineNum, sizeof(double));//申请空间
	ifstream ifs(filename); string tmp;
	int count = 0;
	while (getline(ifs, tmp)) {
		double x, y, z;
		ifs >> x >> y >> z;
		data[3 * count + 0] = x;
		data[3 * count + 1] = y;
		data[3 * count + 2] = z;
		count++;
	}
	return data;
}
//保存文件：注意传入的是指针数组的索引，num2是要读取的文件的行数
void savefile(double *&T, int num2, string filename = "savedT.xyz") {
	ofstream ofs(filename);//打开文件
	for (int i = 0; i < num2; ++i)
		ofs << T[3 * i + 0] << " " << T[3 * i + 1] << " " << T[3 * i + 2] << "\n";
}
//R矩阵是3*3，t矩阵是3*1   点值，根据旋转矩阵计算之后的值
void rotatePoint(double *&T, int num2, Matrix R, Matrix t) {
	for (int i = 0; i < num2; ++i) {
		FLOAT *val = new FLOAT[3];
		val[0] = (FLOAT)(T[3 * i + 0]);
		val[1] = (FLOAT)(T[3 * i + 1]);
		val[2] = (FLOAT)(T[3 * i + 2]);
		Matrix point(3, 1, val);
		Matrix pointout = R * point + t;
		T[3 * i + 0] = pointout.val[0][0];
		T[3 * i + 1] = pointout.val[1][0];
		T[3 * i + 2] = pointout.val[2][0];
	}
}
int main(int argc, char** argv) {
	// string filename1="originalM.xyz";//"../facedata/result3_1.xyz";
	// string filename2="originalT.xyz";//"../facedata/result3_2.xyz";
	string filename1 = "D:/visual studio learning/demo/originalM.xyz";
	string filename2 = "D:/visual studio learning/demo/originalT.xyz"; //点云图
	int num1 = getLineNum(filename1);
	int num2 = getLineNum(filename2);
	cout << num1 << " " << num2 << endl;
	double *M = readfile(filename1);
	double *T = readfile(filename2);

	int32_t dim = 3;
	// for(int i=0;i<num2;++i){
	// 	T[3*i+0]+=10;
	// 	T[3*i+1]+=10;
	// 	T[3*i+2]+=10;
	// }


	// savefile(M,num1,"originalM.xyz");
	// savefile(T,num2,"originalT.xyz");


	Matrix R = Matrix::eye(3);
	Matrix t(3, 1);

	// run point-to-plane ICP (-1 = no outlier threshold)
	cout << endl << "Running ICP (point-to-plane, no outliers)" << endl;
	IcpPointToPlane icp(M, num1, dim);
	double residual = icp.fit(T, num2, R, t, -1);

	cout << "R:" << endl << R << endl << endl;
	cout << "t:" << endl << t << endl << endl;
	cout << "Residual:" << residual;

	rotatePoint(T, num2, R, t);
	savefile(T, num2, "D:/visual studio learning/demo/rotatedT.xyz");


	free(M);
	free(T);

	return 0;
}