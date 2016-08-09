/*************************************************************************
  > File Name   : 1075Therad_in_a_Space.cpp
  > Author      : liudy
  > Mail        : 787896130@qq.com
  > Created Time: 2016年08月09日 星期二 09时03分54秒
 ************************************************************************/

#include<iostream>
#include<cmath>
#include<cstdio>
#include<iomanip>
using namespace std;
/*
 *
 *可知 设 A(x1, y1, z1), B(x2, y2, z2), C(x3, y3, z3);
 *空间直线AB:  x = (x2-x1)t + x1; y = (y2-y1)t + y1; z = (z2-z1)t + z1
 *球: (x-x3)^2 + (y-y3)^2 + (z-z3)^2 = R^2
 *将直线AB代人球方程看是否有解,有解,则求出焦点 E(x4, y4, z4), F(x5, y5, z5), 无解则最短距离为AB两点的距离
 *首先判断 点 E, F 是否在AB之间,如果不在 最短距离仍为 AB两点之间的距离
 *焦点在AB 之间,
 * 见下图
 */
struct Point{
    double x;
    double y;
    double z;
    Point(double x1 = 0, double y1 = 0, double z1 = 0){
        x = x1; 
        y = y1;
        z = z1;
    }
};

Point *P[3];
Point *cross_point[2];
const double Pi = 3.1415;


double dis(Point *A, Point *B){
    return sqrt(pow(A->x - B->x, 2) + pow(A->y - B->y, 2) + pow(A->z - B->z, 2));
}
double Get_3P_Angle(Point *A, Point *B, Point *C);

/*
 * 检查C点是否在AB之间
 */
bool check_Point_Between_AB(Point *C, Point *A, Point *B){
    double k, angle;
    k = dis(A, C) / dis(A, B);
    angle = Get_3P_Angle(C, B, A);
    if(k >= 1 || angle != 0)
        return false;
    return true;
}
bool check_cross(int R){
    /*
     *  a = (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2
     *  b = 2(x2 - x1)(x1 - x3) + 2(y2 - y1)(y1 - y3) + 2(z2-z1)(z1-z3)
     *  c = (x1 - x3)^2 + (y1 - y3)^2 + (z1 - z3)^2
     */
    double a = (P[1]->x - P[0]->x) * (P[1]->x - P[0]->x) + (P[1]->y - P[0]->y) * (P[1]->y - P[0]->y) + (P[1]->z - P[0]->z) * (P[1]->z - P[0]->z);    
    double b = 2 * (P[1]->x - P[0]->x) * (P[0]->x - P[2]->x) + 2 * (P[1]->y - P[0]->y) * (P[0]->y - P[2]->y) + 2 * (P[1]->z - P[0]->z) * (P[0]->z - P[2]->z);
    double c = (P[0]->x - P[2]->x) * (P[0]->x - P[2]->x) + (P[0]->y - P[2]->y) * (P[0]->y - P[2]->y) + (P[0]->z - P[2]->z) * (P[0]->z - P[2]->z) - pow(R, 2);
    double delt = b * b - 4 * a * c;
    if(delt >= 0){ 
        double t1, t2;
        Point *cross_Point = new Point();
        t1 = (-b + sqrt(delt)) / (2 * a);
        t2 = (-b - sqrt(delt)) / (2 * a);
        cross_Point->x = (P[1]->x - P[0]->x) * t1 + P[0]->x;
        cross_Point->y= (P[1]->y - P[0]->y) * t1 + P[0]->y;
        cross_Point->z = (P[1]->z - P[0]->z) * t1 + P[0]->z;
        if(check_Point_Between_AB(cross_Point, P[0], P[1]))
            return true;
        else
            return false;
    }else
        return false;
}


double Arc_length(double Angle, double R){
    return R * Pi * Angle / 180.0;
}
/*
 * 直角三角形中知斜边 邻边求角度
 * L1 为垂直边, L2 为斜边
 */
double Get_Angle(double L1, double L2){
    double cosAngle, Angle;
    cosAngle = L1 / L2;
    Angle = acos(cosAngle);
    return Angle * 180.0 / Pi;
}

/*
 *知三个点,求所成的角 角ACB
 *其中C为顶点
 */
double Get_3P_Angle(Point *A, Point *B, Point *C){
    double DotProduct, ModProduct, cosAngle, Angle;
    DotProduct =  (A->x - C->x) * (B->x - C->x) + (A->y - C->y) * (B->y - C->y) + (A->z - C->z) * (B->z - C->z);
    ModProduct = sqrt(pow(A->x - C->x, 2) + pow(A->y - C->y, 2) + pow(A->z - C->z, 2)) * sqrt(pow(B->x - C->x, 2) + pow(B->y - C->y, 2) + pow(B->z - C->z, 2)); 
    cosAngle = DotProduct / ModProduct; 
    Angle = acos(cosAngle); 
 //   cout << "Angle = " << Angle << " DotProduct = " << DotProduct << " ModProduct = " << ModProduct << endl;
    return Angle * 180.0 / Pi; 
}
/*
 *直角三角形知斜边a, 和一条直角边 b, 求第三条边长c
 *
 */
double Get_Triangle_len(double a, double b){
    return sqrt(a * a - b * b);
}

double Calculate_Len(double R){
    double AngleACE, AngleBCF, AngleACB;
    double Arc_len;
    AngleACB = Get_3P_Angle(P[0], P[1], P[2]);
    AngleACE = Get_Angle(R, dis(P[0], P[2]));
    AngleBCF = Get_Angle(R, dis(P[1], P[2]));
    Arc_len = Arc_length(AngleACB - AngleACE - AngleBCF, R);
//    cout << "AngleACE = " << AngleACE  << " AngleACB = " << AngleACB << " AngleBCF = " << AngleBCF << endl; 
//    cout << "Arc_len = " << Arc_len << endl
    return Get_Triangle_len(dis(P[1], P[2]), R) + Get_Triangle_len(dis(P[0], P[2]), R) + Arc_len;

    
}
void solve(int R){
    if(check_cross(R)){
        double Ans;
        Ans = Calculate_Len(R);    
//        cout << "Ans = " << Ans << endl;
        cout << fixed << setprecision(2) << Ans << endl;
    }else{
  //      cout << "Dis = " << dis(P[0], P[1]) << endl;
        cout << fixed << setprecision(2) << dis(P[0], P[1]) << endl;;
    }
}

int main(){
    double x, y, z, r;
    for(int i = 0; i < 3; i++){
        cin >> x >> y >> z;
        P[i] = new Point(x, y, z);   
    }
    cin >> r;
    solve(r); 
    return 0;
}
