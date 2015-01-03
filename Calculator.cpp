#include "Calculator.h"

Calculator::Calculator(){
	for(int i = 0 ; i <= 628 ; i++){
		double angle = (double)i / 100.0;
		sinArr[i] = sin((double)angle);
		cosArr[i] = cos((double)angle);
	}
}

double Calculator::mysin(double n){
	int angle = n * 100.0;
	angle = angle % 628;
	if(angle < 0){
		angle += 628;
	}
	return sinArr[angle];
}

double Calculator::mycos(double n){
	int angle = n * 100.0;
	angle = angle % 628;
	if(angle < 0){
		angle += 628;
	}
	return cosArr[angle];
}
