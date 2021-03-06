/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "uidef.h"
#include "uidebug.h"

#if defined( __GNUC__ ) && defined( __APPLE__ )
// Workaround for buggy GCC on OS X - if initializer isn't present, variable won't be defined!
EVENT               Event = 0;
#else
EVENT               Event;
#endif


EVENT intern saveevent( void )
/****************************/
{
    register    EVENT                   ev;

    if( Event > EV_NO_EVENT && uiinlist( Event ) ) {
        ev = Event;
        Event = -Event;
    } else {
        Event = EV_NO_EVENT;
        ev = EV_NO_EVENT;
    }
    return( ev );
}


EVENT intern getprime( VSCREEN *vptr )
/************************************/
{
    _uicheckuidata();
    if( Event <= EV_NO_EVENT ) {
        if( vptr != NULL ) {
//            uivsetactive( vptr );
        }
        uivsetcursor( vptr );
        uidoneevent();
        Event = uiget();
        uistartevent();
    }
    return( Event );
}


EVENT UIAPI uivgetprime( VSCREEN *vptr )
/***************************************/
{
    getprime( vptr );
    return( saveevent() );
}


EVENT UIAPI uivgetprimevent( VSCREEN *vptr )
/*******************************************/
{
    register    EVENT                   ev;

    ev = uivgetprime( vptr );
//    switch( ev ) {
//    case EV_NO_EVENT:
//    case EV_SINK:
//        uirefresh();
//    }
    return( ev );
}


