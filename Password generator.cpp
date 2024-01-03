#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main()
{
	cout<<"RANDOM PASSWORD GENERATOR PROGRAM "<<endl;
    srand(time(NULL));
	
	int	passwordlength;
	do
	{
		cout<<"Enter the length of the password: "<<endl;
		cin>>passwordlength;
		if (passwordlength <=0)
		{
			cout<<"ERROR - an invalid value was given"<<endl<<endl;
		}
	}
	while (passwordlength <=0);
	
	string password = "";
	
	for (int i=0; i<passwordlength; i++)
	{
		int randomcategory = rand() %2;
		
		char randomsign;
		if (randomcategory == 0)
		{
			randomsign = 'a' + rand() % 26;
		}
		else
		{
			randomsign = 'A' + rand() % 26;
		}
		
		password += randomsign;
	}
	
	cout<<"Generated password: "<<password<<endl;
	
	system("pause>>null");
	return 0;
}