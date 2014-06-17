#include "MakeTodaysFiles.h"
#include <direct.h>
#include <vector>

MakeTodaysFiles::MakeTodaysFiles(char* cDirectory)
{
	// save directory for later
	strncpy_s(m_cFileDir, cDirectory, sizeof(m_cFileDir));

	// ensure dir exists
	_mkdir(cDirectory);

	//m_stream.open(cFilePath, ios_base::app);
	m_iFileDay = 0;
	m_iFileYear = 0;
	m_iFileMonth = 0;
}

void MakeTodaysFiles::MakeFiles(bool bMorning)
{
	// remake full filepath
	char cOrigFilePath[MAX_PATH];
	char cDestFilePath[MAX_PATH];
	char cFileName[MAX_PATH];
	char cDestFileName[MAX_PATH];

	if(bMorning)
		strncpy_s(cFileName, "Morning.tcx", sizeof(cFileName));
	else
		strncpy_s(cFileName, "Evening.tcx", sizeof(cFileName));

	strncpy_s(cOrigFilePath, m_cFileDir, sizeof(cOrigFilePath));
	strncat_s(cOrigFilePath, cFileName, sizeof(cOrigFilePath));

	// get todays date
	GetSystemTime(&m_nowst);
	m_iFileDay = m_nowst.wDay;
	m_iFileMonth = m_nowst.wMonth;
	m_iFileYear = m_nowst.wYear;
	char cDateTime[256];

	sprintf_s(cDateTime, "%d-%02d-%02d", 
			m_iFileYear,
			m_iFileMonth,
			m_iFileDay);

	if(bMorning)
		sprintf_s(cDestFileName,sizeof(cDestFileName),"Morning%s.tcx",cDateTime);
	else
		sprintf_s(cDestFileName,sizeof(cDestFileName),"Evening%s.tcx",cDateTime);

	char tmpPath[MAX_PATH];
	sprintf(tmpPath,"E:\\Dropbox\\Activities\\", sizeof("E:\\Dropbox\\Activities\\"));
	strncpy_s(cDestFilePath, tmpPath, sizeof(tmpPath));
	strncat_s(cDestFilePath, cDestFileName, sizeof(cDestFilePath));
	std::ifstream ifile(cOrigFilePath,std::ios::binary);
	ifile.seekg(0,std::ios_base::end);
	long s=ifile.tellg();
	char *buffer=new char[s];
	ifile.seekg(0);
	ifile.read(buffer,s);
	ifile.close();
	std::string txt(buffer,s);
	delete[] buffer;

	vector<const string> vecDate;
	vecDate.push_back("2014-04-01\0");
	vecDate.push_back("2014-06-04\0");

	const string strDate[] = {"2014-06-04", "2014-06-04"};

	for(int i = 0; i < vecDate.size(); i++)
	{
		size_t off=0;
		while ((off=txt.find(vecDate[i],off))!=std::string::npos)
			txt.replace(off,sizeof("2014-04-01")-1,cDateTime);
	}
	std::ofstream ofile(cDestFilePath);
	ofile.write(txt.c_str(),txt.size());
}

MakeTodaysFiles::~MakeTodaysFiles()
{
}