#include <iostream>
using namespace std;

//��ָ������������λ 

long long fastPower(long long base, long long power){
	long long result = 1;
	while(power > 0){
//		ָ��Ϊż�� 
		if(power % 2 == 0){
			power = power/2;
			base = base*base%1000;
		}else{
			power = power - 1;
			result = base*result%1000;
			power = power/2;
			base = base*base%1000;
		} 
	}
	return result;
}

int main()
{
	
	return 0;
}


