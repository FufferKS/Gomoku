

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Sep 02 00:20:31 2018
 */
/* Compiler settings for GomokuServerTypeInfo.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __GomokuServerTypeInfo_h_h__
#define __GomokuServerTypeInfo_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGomokuServerRoom_FWD_DEFINED__
#define __IGomokuServerRoom_FWD_DEFINED__
typedef interface IGomokuServerRoom IGomokuServerRoom;

#endif 	/* __IGomokuServerRoom_FWD_DEFINED__ */


#ifndef __GomokuServerRoom_FWD_DEFINED__
#define __GomokuServerRoom_FWD_DEFINED__

#ifdef __cplusplus
typedef class GomokuServerRoom GomokuServerRoom;
#else
typedef struct GomokuServerRoom GomokuServerRoom;
#endif /* __cplusplus */

#endif 	/* __GomokuServerRoom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GomokuServerTypeInfo_0000_0000 */
/* [local] */ 

#define	B_SIZE_Y	( 42 )

#define	B_SIZE_X	( 30 )

typedef 
enum _player_sign
    {
        NON_INITIALIZED	= 0,
        PLAYER_O	= ( NON_INITIALIZED + 1 ) ,
        PLAYER_X	= ( PLAYER_O + 1 ) ,
        EMPTY	= ( PLAYER_X + 1 ) 
    } 	player_sign;

typedef 
enum _move_result
    {
        OK	= 0,
        FAIL	= 1
    } 	move_result;

typedef 
enum _game_state
    {
        INITIAL	= 0,
        WAITING_FOR_2ND_PLAYER	= ( INITIAL + 1 ) ,
        IN_PROGRESS	= ( WAITING_FOR_2ND_PLAYER + 1 ) ,
        FINISHED	= ( IN_PROGRESS + 1 ) 
    } 	game_state;

typedef struct _field
    {
    player_sign fieldState;
    } 	field;



extern RPC_IF_HANDLE __MIDL_itf_GomokuServerTypeInfo_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GomokuServerTypeInfo_0000_0000_v0_0_s_ifspec;

#ifndef __IGomokuServerRoom_INTERFACE_DEFINED__
#define __IGomokuServerRoom_INTERFACE_DEFINED__

/* interface IGomokuServerRoom */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IGomokuServerRoom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFAFD844-C50F-499D-BAA2-0AA4B70C5CB6")
    IGomokuServerRoom : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE JoinGame( 
            /* [retval][out] */ player_sign *ps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentPlayer( 
            /* [retval][out] */ player_sign *ps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBoard( 
            /* [out] */ field board[ 42 ][ 30 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MakeAMove( 
            /* [out] */ move_result *mr,
            /* [in] */ player_sign *pi,
            /* [in] */ int *y,
            /* [in] */ int *x) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGameState( 
            /* [retval][out] */ game_state *gs) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGomokuServerRoomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGomokuServerRoom * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGomokuServerRoom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGomokuServerRoom * This);
        
        HRESULT ( STDMETHODCALLTYPE *JoinGame )( 
            IGomokuServerRoom * This,
            /* [retval][out] */ player_sign *ps);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentPlayer )( 
            IGomokuServerRoom * This,
            /* [retval][out] */ player_sign *ps);
        
        HRESULT ( STDMETHODCALLTYPE *GetBoard )( 
            IGomokuServerRoom * This,
            /* [out] */ field board[ 42 ][ 30 ]);
        
        HRESULT ( STDMETHODCALLTYPE *MakeAMove )( 
            IGomokuServerRoom * This,
            /* [out] */ move_result *mr,
            /* [in] */ player_sign *pi,
            /* [in] */ int *y,
            /* [in] */ int *x);
        
        HRESULT ( STDMETHODCALLTYPE *GetGameState )( 
            IGomokuServerRoom * This,
            /* [retval][out] */ game_state *gs);
        
        END_INTERFACE
    } IGomokuServerRoomVtbl;

    interface IGomokuServerRoom
    {
        CONST_VTBL struct IGomokuServerRoomVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGomokuServerRoom_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGomokuServerRoom_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGomokuServerRoom_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGomokuServerRoom_JoinGame(This,ps)	\
    ( (This)->lpVtbl -> JoinGame(This,ps) ) 

#define IGomokuServerRoom_GetCurrentPlayer(This,ps)	\
    ( (This)->lpVtbl -> GetCurrentPlayer(This,ps) ) 

#define IGomokuServerRoom_GetBoard(This,board)	\
    ( (This)->lpVtbl -> GetBoard(This,board) ) 

#define IGomokuServerRoom_MakeAMove(This,mr,pi,y,x)	\
    ( (This)->lpVtbl -> MakeAMove(This,mr,pi,y,x) ) 

#define IGomokuServerRoom_GetGameState(This,gs)	\
    ( (This)->lpVtbl -> GetGameState(This,gs) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGomokuServerRoom_INTERFACE_DEFINED__ */



#ifndef __GomokuLib_LIBRARY_DEFINED__
#define __GomokuLib_LIBRARY_DEFINED__

/* library GomokuLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_GomokuLib;

EXTERN_C const CLSID CLSID_GomokuServerRoom;

#ifdef __cplusplus

class DECLSPEC_UUID("4914A6AE-B125-41AC-AAA2-20598FABDF4E")
GomokuServerRoom;
#endif
#endif /* __GomokuLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


