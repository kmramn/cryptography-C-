// dllmain.h : Declaration of module class.

class CMITMAGMPCOMLibModule : public ATL::CAtlDllModuleT< CMITMAGMPCOMLibModule >
{
public :
	DECLARE_LIBID(LIBID_MITMAGMPCOMLibLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MITMAGMPCOMLIB, "{0e915943-beb8-4e88-ac0b-8453d306dd72}")
};

extern class CMITMAGMPCOMLibModule _AtlModule;
