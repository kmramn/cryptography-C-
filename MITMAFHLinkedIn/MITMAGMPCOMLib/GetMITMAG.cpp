// GetMITMAG.cpp : Implementation of CGetMITMAG

#include "pch.h"
#include "GetMITMAG.h"


// CGetMITMAG

STDMETHODIMP CGetMITMAG::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IGetMITMAG
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
