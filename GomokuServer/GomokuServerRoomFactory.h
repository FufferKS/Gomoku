#pragma once
#include "stdafx.h"
class GomokuServerRoom;
class GomokuServerRoomFactory : public IClassFactory
{
public:
	GomokuServerRoomFactory();
	virtual ~GomokuServerRoomFactory();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
	STDMETHODIMP_(ULONG)AddRef();
	STDMETHODIMP_(ULONG)Release();

	// IClassFactory
	STDMETHODIMP LockServer(BOOL fLock);
	STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv);

private:
	ULONG m_refCount;

	bool oddRoomWasProduced;
	GomokuServerRoom* oddRoom;
};