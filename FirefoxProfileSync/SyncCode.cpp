#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>



using namespace std;


DWORD proc_id[1024];
DWORD ret_bytes;
FILE *proc_list;
 

void printProcessNameAndId(DWORD processID) 
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	  
	//Get a handle to the process. 
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	//Get the process name
	if (NULL != hProcess) 
	{
		HMODULE hmod; 
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hmod, sizeof(hmod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hmod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

		}
	}
	//Print the process name and identifier
	//_tprintf(TEXT("%s (PID: %u)\n"), szProcessName, processID);
	wcout << szProcessName << endl;
	TCHAR toEqual[] = _T("firefox.exe");
	if (_tcscmp(szProcessName,toEqual) == 0)
	{
		cout << "FIREFOOOOOOOOOOX" << endl;
	}

	//Release the handle to the process
	CloseHandle(hProcess);
}


int main(void )
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}

	// Calculate how many process identifiers were returned
	cProcesses = cbNeeded / sizeof(DWORD);
	//Print the name and process identifier for each process
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			printProcessNameAndId(aProcesses[i]);
		}
	}
	/*
	system("pause");

	if (!EnumProcesses(proc_id, sizeof(proc_id), &ret_bytes)) {
		cout << "Can not execute EnumProcesses()" << endl;
		system("pause");
		return;
	}
	*/

	system("pause");
	return 0;
}