#include "GomokuServerRoomFactory.h"
#include "GomokuServerRoom.h"
#include <iostream>
#include "locks.h"
GomokuServerRoomFactory::GomokuServerRoomFactory()
{
	m_refCount = 0;
	oddRoomWasProduced = false;
	oddRoom = nullptr;
}

GomokuServerRoomFactory::~GomokuServerRoomFactory()
{
	std::cout << "Factory is being destroyed" << std::endl;
}

STDMETHODIMP GomokuServerRoomFactory::QueryInterface(REFIID riid, void ** pIFace)
{
	if (riid == IID_IUnknown)
		*pIFace = (IUnknown*)this;
	else if (riid == IID_IClassFactory)
		*pIFace = (IClassFactory*)this;
	else
	{
		*pIFace = NULL;
		return E_NOINTERFACE;
	}
	((IUnknown*)(*pIFace))->AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) GomokuServerRoomFactory::AddRef()
{
	return 0;
}

STDMETHODIMP_(ULONG) GomokuServerRoomFactory::Release()
{
	return 0;
}

STDMETHODIMP GomokuServerRoomFactory::LockServer(BOOL fLock)
{
	if (fLock) Lock();
	else UnLock();
	return S_OK;
}

STDMETHODIMP GomokuServerRoomFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void ** ppv)
{
	if (pUnkOuter != NULL) 
		return CLASS_E_NOAGGREGATION;

	GomokuServerRoom* room = NULL;
	HRESULT hr;
	if (oddRoomWasProduced == false)
	{
		room = new GomokuServerRoom();
		oddRoom = room;
		oddRoomWasProduced = true;
	}
	else
	{
		room = oddRoom;
		oddRoomWasProduced = false;
	}
	hr = room->QueryInterface(riid, ppv);

	if (FAILED(hr)) 
		delete room;
	return hr;
}
