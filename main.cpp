#include "MakeTodaysFiles.h"
#include <string>
#include <cstdlib>

int main()
{
	MakeTodaysFiles *pMaker = new MakeTodaysFiles("Resource\\");
	pMaker->MakeFiles(true);
	pMaker->MakeFiles(false);

	return 0;
}