

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Oct 19 07:23:54 2017
 */
/* Compiler settings for MyMemSearch.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MyMemSearch_h_h__
#define __MyMemSearch_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyMemSearch_FWD_DEFINED__
#define __IMyMemSearch_FWD_DEFINED__
typedef interface IMyMemSearch IMyMemSearch;

#endif 	/* __IMyMemSearch_FWD_DEFINED__ */


#ifndef __MyMemSearch_FWD_DEFINED__
#define __MyMemSearch_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyMemSearch MyMemSearch;
#else
typedef struct MyMemSearch MyMemSearch;
#endif /* __cplusplus */

#endif 	/* __MyMemSearch_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MyMemSearch_LIBRARY_DEFINED__
#define __MyMemSearch_LIBRARY_DEFINED__

/* library MyMemSearch */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyMemSearch;

#ifndef __IMyMemSearch_DISPINTERFACE_DEFINED__
#define __IMyMemSearch_DISPINTERFACE_DEFINED__

/* dispinterface IMyMemSearch */
/* [uuid] */ 


EXTERN_C const IID DIID_IMyMemSearch;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C3DC7F87-C104-4D90-9B0F-4E5C18476527")
    IMyMemSearch : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMyMemSearchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyMemSearch * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyMemSearch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyMemSearch * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyMemSearch * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyMemSearch * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyMemSearch * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyMemSearch * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMyMemSearchVtbl;

    interface IMyMemSearch
    {
        CONST_VTBL struct IMyMemSearchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyMemSearch_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyMemSearch_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyMemSearch_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyMemSearch_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyMemSearch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyMemSearch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyMemSearch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMyMemSearch_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MyMemSearch;

#ifdef __cplusplus

class DECLSPEC_UUID("0449ED02-8B9D-4AF9-A3C5-689786FC7AA3")
MyMemSearch;
#endif
#endif /* __MyMemSearch_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


