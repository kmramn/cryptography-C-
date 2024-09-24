// GetMITMAG.h : Declaration of the CGetMITMAG

#pragma once
#include "resource.h"       // main symbols



#include "MITMAGMPCOMLib_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CGetMITMAG

class ATL_NO_VTABLE CGetMITMAG :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGetMITMAG, &CLSID_GetMITMAG>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGetMITMAG, &IID_IGetMITMAG, &LIBID_MITMAGMPCOMLibLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CGetMITMAG()
	{
		m_pUnkMarshaler = nullptr;
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CGetMITMAG)
	COM_INTERFACE_ENTRY(IGetMITMAG)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

public:



};

OBJECT_ENTRY_AUTO(__uuidof(GetMITMAG), CGetMITMAG)
