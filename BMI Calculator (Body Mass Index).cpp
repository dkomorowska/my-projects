#include <iostream>

using namespace std;
int main()
{
	float weight, height0, height1, bmi;
	cout<<"PROGRAM THAT CALCULATES AND INTERPRETS THE BMI INDICATOR"<<endl;
	

	while (true)
	{
		cout<<"Enter the weight in kilograms:  "<<endl;
		cin>>weight;
		if (weight > 0)
		break;
		cout<<"ERROR - Incorrect number was given"<<endl;
	}

	while (true)
	{
		cout<<"Enter the height in centimeters:  "<<endl;
		cin>>height0;
	if (height0 > 0)
		break;
		cout<<"ERROR - Incorrect number was given"<<endl;		
	}		
		
	height1 = height0/100; 
	
	bmi = weight / (height1 * height1);
	
	cout<<"Your BMI is:  "<<bmi<<endl;
	
	if (bmi < 18.5)
	{
		cout<<"Underweight"<<endl;
	}
	else if (bmi >= 18.5 && bmi <= 24.9)
	{
		cout<<"Normal weight"<<endl;
	}
	else if (bmi >= 25 && bmi <= 29.9)
	{
		cout<<"Overweight"<<endl;
	}
	else
	{
		cout<<"Obesity"<<endl<<endl<<endl<<endl;
	}
	cout<<"click any key to close the program";
	
	system("pause>>null");
	return 0;
}

