

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed May 02 15:07:34 2012
 */
/* Compiler settings for C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/projects/ambient/gen/FireBreathWin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ambientLib,0xb4e201a2,0x864b,0x5825,0xa2,0x94,0xa8,0x74,0x48,0x4d,0x7d,0x48);


MIDL_DEFINE_GUID(IID, IID_IFBControl,0x59859db2,0xcf0e,0x5bf6,0xbe,0xc6,0x3a,0x04,0x96,0x2d,0x73,0x19);


MIDL_DEFINE_GUID(IID, IID_IFBComJavascriptObject,0x8079d39c,0x44f2,0x52fc,0xb0,0x99,0x05,0xe0,0xa7,0xdf,0xdd,0x4d);


MIDL_DEFINE_GUID(IID, DIID_IFBComEventSource,0xbcba341b,0xb5c7,0x5770,0x82,0x92,0xad,0x65,0xce,0x37,0x22,0x9b);


MIDL_DEFINE_GUID(CLSID, CLSID_FBControl0,0x4e6f1872,0xef30,0x5368,0xa2,0x77,0x5c,0x0c,0x10,0x76,0x22,0xfa);


MIDL_DEFINE_GUID(CLSID, CLSID_FBComJavascriptObject,0xd843af23,0xf9fc,0x5a3a,0xa2,0x34,0xb8,0x1e,0xfa,0x76,0x60,0xb7);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



