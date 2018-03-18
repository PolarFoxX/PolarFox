#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <io.h>
#include <vector>
#include <algorithm>


using namespace std;

string rus(char s[])
{
	string t;
	int i = 0;
	t = s;
	while (t[i] != 0)
	{
		if (t[i] >= 'А' && t[i] <= 'п')
			t[i] -= 64;
		if (t[i] >= 'Р' && t[i] <= 'я')
			t[i] -= 16;
		i++;
	}
	return t;
}

struct CurObj {
	char ObjName[80];
	char PlaceOfObj[80];
	int OnjCount;
	// конструктор объекта
	CurObj(char* ObjName, char* PlaceOfObj, int OnjCount) : OnjCount(OnjCount)
	{
		strncpy_s(this->ObjName, ObjName, sizeof(this->ObjName));
		strncpy_s(this->PlaceOfObj, PlaceOfObj, sizeof(this->PlaceOfObj));
	}
};

void CallMenu()
{
	cout << "1.Show table" << endl;
	cout << "2.Add object" << endl;
	cout << "3.Delete object" << endl;
	cout << "4.Search object" << endl;
	cout << "5.Save" << endl;
	cout << "6.Clear table" << endl;
	cout << "7.Exit" << endl;
	return;
}

int main()
{
	//setlocale(LC_ALL, "");
	int CurAction=0;
	if (_access("db.txt",0) == -1)
	{
		ofstream db("db.txt");
		db.close();
	}

	vector<CurObj> ObjsInRoom;
	int SizeOfVect = 0;
	ifstream in_file("db.txt");
	in_file.read(reinterpret_cast<char*>(&SizeOfVect), sizeof(SizeOfVect));
	for (int i = 0; i < SizeOfVect; i++)
	{
		CurObj NewObj("", "", 0);
		in_file.read((char*)&NewObj.ObjName, sizeof(ObjsInRoom[i].ObjName));
		in_file.read((char*)&NewObj.PlaceOfObj, sizeof(ObjsInRoom[i].PlaceOfObj));
		in_file.read((char*)&NewObj.OnjCount, sizeof(ObjsInRoom[i].OnjCount));
		ObjsInRoom.push_back(NewObj);
	}
	in_file.close();

	CallMenu();

	do
	{	
		cin >> CurAction;
		switch (CurAction)
		{
			case 1:
			{
				system("cls");
				for (int i = 0; i < ObjsInRoom.size(); i++) 
				{
					cout << ObjsInRoom[i].ObjName << " ";
					cout << ObjsInRoom[i].PlaceOfObj << " ";
					cout << ObjsInRoom[i].OnjCount << endl;
				}
				cout << endl << endl;
				CallMenu();
				break;
			}
			case 2:
			{
				char ObjName[80];
				char PlaceOfObj[80];
				int OnjCount;
				
				cout << "Enter name of object:";
				cin >> ObjName;
				cout << endl;
				cout << "Enter plase of object:";
				cin >> PlaceOfObj;
				cout << endl;
				cout << "Enter count of objects:";
				
				//cin >> OnjCount;
				/*if(!cin)
				{
					do
					{
						cout << "Invalid number, please enter again:";
						cin >> OnjCount;
					} while (!cin);
				}*/
				while (!(cin >> OnjCount))
				{
					cout << "Invalid number, please enter again:";
					cin.clear();
					fflush(stdin);
				}
				CurObj Buff(ObjName, PlaceOfObj, OnjCount);
				ObjsInRoom.push_back(Buff);
				system("cls");
				CallMenu();
				break;
			}
			case 3:
			{
				system("cls");
				for (int i = 0; i < ObjsInRoom.size(); i++)
				{
					cout << i + 1 << " ";
					cout << ObjsInRoom[i].ObjName << " ";
					cout << ObjsInRoom[i].PlaceOfObj << " ";
					cout << ObjsInRoom[i].OnjCount << endl;
				}
				cout << endl << "Enter index of object to delete or enter 0 to cancel:";
				int ObjToDel = 0;
				//cin >> ObjToDel;
				while (!(cin >> ObjToDel))
				{
					cout << "Invalid number, please enter again:";
					cin.clear();
					fflush(stdin);
				}
				if (ObjToDel == 0)
				{
					system("cls");
					CallMenu();
					break;
				}
				else if (ObjToDel > 0 && ObjToDel < ObjsInRoom.size() + 1)
				{
					ObjsInRoom.erase(ObjsInRoom.begin() + ObjToDel - 1);
					system("cls");
					CallMenu();
					break;
				}
				else
				{
					cout << "There is no object with this index, press ENTER to return to main menu";
					_getch();
					system("cls");
					CallMenu();
					break;
				}
			}
			case 4:
			{
				system("cls");
				cout << endl;
				char StrToFind[80];
				cout << "Enter string to search:";
				cin >> StrToFind;

				vector<CurObj>::iterator it = find_if(ObjsInRoom.begin(), ObjsInRoom.end(), [&](const CurObj & s)->bool { return strstr(s.ObjName, StrToFind); });
				if (it != ObjsInRoom.end())
				{
					cout << "Objects found: "  << endl;
					cout << (*it).ObjName << " " << (*it).PlaceOfObj << " " << (*it).OnjCount << endl;
					it++;
				}
				else
				{
					cout << "No objects were found" << endl;
					break;
				}

				while (it != ObjsInRoom.end())
				{
					it = find_if(it, ObjsInRoom.end(), [&](const CurObj & s)->bool { return strstr(s.ObjName, StrToFind); });
					if (it != ObjsInRoom.end())
					{
						cout << (*it).ObjName << " " << (*it).PlaceOfObj << " " << (*it).OnjCount << endl;
						it++;
					}
				}

				CallMenu();
				break;
			}
			case 5:
			{
				ofstream out_file("db.txt");
				int OC = ObjsInRoom.size();
				out_file.write((const char*)&OC, sizeof(int));
				for (int i = 0; i < ObjsInRoom.size(); i++)
				{
					out_file.write((const char*)&ObjsInRoom[i].ObjName, sizeof(ObjsInRoom[i].ObjName));
					out_file.write((const char*)&ObjsInRoom[i].PlaceOfObj, sizeof(ObjsInRoom[i].PlaceOfObj));
					out_file.write((const char*)&ObjsInRoom[i].OnjCount, sizeof(ObjsInRoom[i].OnjCount));
				}	
				out_file.close();
			}
			case 6:
			{
				ObjsInRoom.clear();
				cout << "Table is clear, press ENTER to return to main menu" << endl;
				system("cls");
				CallMenu();
			}
			case 7:
			{break;}
		}
	} while (CurAction != 7);
	//_getch();

	return 0;
}