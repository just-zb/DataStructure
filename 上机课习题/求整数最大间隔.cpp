/*
题目描述
请输出数字序列的最大间隔。

请使用以下伪随机数生成函数 rand32 () 生成伪随机数



int  seed  ;
int rand(){ return((( seed   =  seed   * 214013L + 2531011L) >> 16) & 0x7fff); }
int rand32(){
return ((rand() << 16) + (rand() << 1) + rand() % 2);
}

Input Format

2个整数，n seed 其中 2<n<=20000000，seed为随机数种子。

Output Format
整数序列的最大间隔
*/
#include <iostream>
#include "string.h"
#include<algorithm>
using namespace std;
int  seed  ;
int rand(){ return((( seed   =  seed   * 214013L + 2531011L) >> 16) & 0x7fff); }
int rand32(){
    return ((rand() << 16) + (rand() << 1) + rand() % 2);
}
class maxgap{
public:
    long n,maxx=0,minx=0;
    long *data;
     maxgap(long n){
        this->n=n;
        data=new long[n];
        	for (int i = 0; i < n; i++)
	{
        data[i]=rand32();
		if (data[i] > maxx)
			maxx = data[i];
		if (data[i] < minx)
			minx = data[i];
	}
    };
    long GetMaxGap() const;
    void display() const;

};
long maxgap::GetMaxGap() const {
    long dblAvrGap,index;
    	if ((maxx - minx) % (n - 1) == 0)
		dblAvrGap = (maxx - minx) / (n - 1);
	else if ((maxx - minx) % (n - 1) != 0)
		dblAvrGap = (maxx - minx) / (n - 1) + 1;
    //long *low=new long[n];
    //long *high=new long[n];
    long*array=new long [(n - 1) * 2];
    //初始化桶
    for (int i = 0; i < n; ++i) {
        array[2*i]=maxx;
        array[2*i+1]=minx;
    }
    //将n个数分布到n-1个桶中
    array[2*n-3]=maxx;
    for (long i = 0; i < n;i++) {
        index = (data[i] - minx) / dblAvrGap;
        if (data[i] <= array[2*index])
            array[2*index] = data[i];
        if (data[i] >= array[2*index+1])
            array[2*index+1] = data[i];
    }
    if (array[1]!=minx)
    {
        index=array[1];
    }
    
    long dblMaxGap=0;
    for (long i = 1; i < n-2; ++i) {
        if (array[2*i]==maxx)
        {
            continue;
        }
        else
        {
            if (dblMaxGap < array[2*i] -index)
                dblMaxGap =  array[2*i] -index;
            index=array[2*i+1];
        }
        
    }
    	if (array[2*n-2] - index > dblMaxGap){ //最后一个桶一定有元素
		dblMaxGap= array[2*n-2] - index;
	}
    return dblMaxGap;
}
void maxgap::display() const {
    cout<<GetMaxGap();
}
int main() {
    long n;
    cin>>n>>seed;
    maxgap solution(n);
    solution.display();
    return 0;
}
