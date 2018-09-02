// GomokuServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include "GomokuServerTypeInfo_i.c"
#include "GomokuServerRoomFactory.h"

using namespace std;

DWORD g_allLocks;
int main(int argc, char** argv)
{
	HRESULT hr;
	ITypeLib* pTLib = NULL;
	GomokuServerRoomFactory factory;
	DWORD regID = 0;
	MSG ms;

	cout << "Initializing Server!" << endl;
	CoInitialize(NULL);

	cout << "Fetching lib" << endl;
	hr = LoadTypeLibEx(L"GomokuServer.tlb", REGKIND_REGISTER, &pTLib);
	if (!FAILED(hr))
	{
		if (argc == 2 && (strstr(argv[1], "/Embedding") || strstr(argv[1], "-Embedding")))
		{
			cout << "Started by Embedding" << endl;

			cout << "Registering the factory" << endl;
			hr = CoRegisterClassObject(CLSID_GomokuServerRoom, (IClassFactory*)&factory,
				CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &regID);
			if (!FAILED(hr))
			{

				cout << "Server running" << endl;
				while (GetMessage(&ms, 0, 0, 0))
				{
					TranslateMessage(&ms);
					DispatchMessage(&ms);
				}
				hr = 0;
				CoRevokeClassObject(regID);
			}
		}
	}
	cout << "Server dying in peace" << endl;
	CoUninitialize();
	cout << "Press enter to continue" << endl;
	getchar();
	return hr;
}