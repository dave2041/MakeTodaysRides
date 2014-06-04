#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MakeTodaysFiles
{

public:
	MakeTodaysFiles(char* cDirectory);
	~MakeTodaysFiles();
	void MakeFiles(bool bMorning);
private:
	int m_iFileDay;
	int m_iFileYear;
	int m_iFileMonth;
	SYSTEMTIME m_nowst;
	char m_cFileDir[MAX_PATH];
};