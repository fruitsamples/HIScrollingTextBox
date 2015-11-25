/*	File:		TestHIView.cp	Contains:	Minimal application to test HIViews.	Version:	1.0.1	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.				("Apple") in consideration of your agreement to the following terms, and your				use, installation, modification or redistribution of this Apple software				constitutes acceptance of these terms.  If you do not agree with these terms,				please do not use, install, modify or redistribute this Apple software.				In consideration of your agreement to abide by the following terms, and subject				to these terms, Apple grants you a personal, non-exclusive license, under Apple�s				copyrights in this original Apple software (the "Apple Software"), to use,				reproduce, modify and redistribute the Apple Software, with or without				modifications, in source and/or binary forms; provided that if you redistribute				the Apple Software in its entirety and without modifications, you must retain				this notice and the following text and disclaimers in all such redistributions of				the Apple Software.  Neither the name, trademarks, service marks or logos of				Apple Computer, Inc. may be used to endorse or promote products derived from the				Apple Software without specific prior written permission from Apple.  Except as				expressly stated in this notice, no other rights or licenses, express or implied,				are granted by Apple herein, including but not limited to any patent rights that				may be infringed by your derivative works or by other works in which the Apple				Software may be incorporated.				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN				COMBINATION WITH YOUR PRODUCTS.				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT				(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.	Copyright � 2003 Apple Computer, Inc., All Rights Reserved*/#include <Carbon/Carbon.h>#include "HIScrollingTextBox.h"#include "HIScrollingHITextBox.h"// Common stuff to all samplesvoid InitToolbox(void);void InitMenuBar(void);pascal OSErr HandlePref(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon);pascal OSErr HandleOapp(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon);pascal OSErr HandleOdoc(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon);pascal OSErr HandlePdoc(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon);void InstallAppleEventHandlers(void);pascal OSStatus CommandProcess(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData);void InstallApplicationCarbonEventHandlers(void);void DoCloseWindow(WindowRef theWind);void RecursiveCloseWindow(WindowRef theWind);void CloseAllWindows();void InitApplication(void);void TermApplication(void);// End of common stuffvoid DoAboutBox(void);void DoPreferences(void);void DoScrollingTextWindow(void);void DoScrollingHITextWindow(void);int main(void)	{	InitToolbox();	InitApplication();	RunApplicationEventLoop();	TermApplication();   return 0;	}//------------------------------- Initializations ------------------------------void InitToolbox(void)	{	InitCursor();		TXNInitTextension(NULL, 0, 0);	}void InitApplication(void)	{	long response;	OSErr err;   // Can we run this particular demo application?	err = Gestalt(gestaltSystemVersion, &response);	Boolean ok = ((err == noErr) && (response >= 0x00001030));   if (!ok)      {		StandardAlert(kAlertStopAlert, "\pMac OS X 10.3 (minimum) is required for this application", "\p", NULL, NULL);      ExitToShell();      }	InstallAppleEventHandlers();	InstallApplicationCarbonEventHandlers();	InitMenuBar();	DoScrollingTextWindow();	DoScrollingHITextWindow();	}void InitMenuBar(void)	{	// Getting our menu bar	Handle aHand = GetNewMBar(128);	SetMenuBar(aHand);	// Enabling Preferences menu item	EnableMenuCommand(NULL, kHICommandPreferences);	// Adding some menu item commands	MenuHandle menu = GetMenuHandle(128);	SetMenuItemCommandID(menu, 1, kHICommandNew);	SetMenuItemCommandID(menu, 2, kHICommandClose);	SetMenuItemCommandID(GetMenuHandle(1),  1, kHICommandAbout);	// Adding a standard Window menu	CreateStandardWindowMenu(0, &menu);	InsertMenu(menu, 0);	DrawMenuBar();	DisposeHandle(aHand);	}//------------------------------- Apple Events ---------------------------------void InstallAppleEventHandlers(void)	{	OSErr	err;	err = AEInstallEventHandler(kCoreEventClass, kAEShowPreferences, NewAEEventHandlerUPP(HandlePref), 0, false);	if (err) DebugStr("\pAEInstallEventHandler failed for kAEOpenApplication");	err = AEInstallEventHandler(kCoreEventClass, kAEOpenApplication, NewAEEventHandlerUPP(HandleOapp), 0, false);	if (err) DebugStr("\pAEInstallEventHandler failed for kAEOpenApplication");	err = AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments,   NewAEEventHandlerUPP(HandleOdoc), 0, false);	if (err) DebugStr("\pAEInstallEventHandler failed for kAEOpenDocuments");	err = AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments,  NewAEEventHandlerUPP(HandlePdoc), 0, false);	if (err) DebugStr("\pAEInstallEventHandler failed for kAEPrintDocuments");		// Note: Since RunApplicationEventLoop installs a Quit AE Handler, we no longer have to do it here.	}pascal OSErr HandlePref(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon)	{#pragma unused (theAppleEvent, reply, handlerRefcon)	return errAEEventNotHandled;	}pascal OSErr HandleOapp(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon)	{#pragma unused (theAppleEvent, reply, handlerRefcon)	return noErr;	}pascal OSErr HandleOdoc(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon)	{#pragma unused (theAppleEvent, reply, handlerRefcon)	return errAEEventNotHandled;	}pascal OSErr HandlePdoc(const AppleEvent *theAppleEvent, AppleEvent *reply, long handlerRefcon)	{#pragma unused (theAppleEvent, reply, handlerRefcon)	return errAEEventNotHandled;	}//------------------------------- Carbon Events --------------------------------void InstallApplicationCarbonEventHandlers(void)	{	EventTypeSpec eventType = {kEventClassCommand, kEventCommandProcess};	InstallEventHandler(GetApplicationEventTarget(), NewEventHandlerUPP(CommandProcess), 1, &eventType, NULL, NULL);	}pascal OSStatus CommandProcess(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData)	{#pragma unused (nextHandler, userData)	HICommand aCommand;	OSStatus status = noErr;	GetEventParameter(theEvent, kEventParamDirectObject, typeHICommand, NULL, sizeof(HICommand), NULL, &aCommand);      	switch (aCommand.commandID)		{		case kHICommandAbout:			DoAboutBox();			break;		case kHICommandPreferences:			DoPreferences();			break;		case kHICommandNew:			DoScrollingTextWindow();			DoScrollingHITextWindow();			break;		case kHICommandClose:			DoCloseWindow(FrontNonFloatingWindow());			break;		default:			status = eventNotHandledErr;			break;		}	return status;	}//------------------------------- Terminating ----------------------------------void TermApplication(void)	{	CloseAllWindows();	}void CloseAllWindows()	{	WindowRef theWind = FrontWindow();	if (theWind)		{		RecursiveCloseWindow(theWind);		}	}void RecursiveCloseWindow(WindowRef theWind)	{	WindowRef nextWind = GetNextWindow(theWind);	if (nextWind) RecursiveCloseWindow(nextWind);	DoCloseWindow(theWind);	}void DoCloseWindow(WindowRef theWind)	{	EventRef theEvent;	CreateEvent(NULL, kEventClassWindow, kEventWindowClose, 0, 0, &theEvent);	SetEventParameter(theEvent, kEventParamDirectObject, typeWindowRef, sizeof(WindowRef), &theWind);	SendEventToEventTarget(theEvent, GetWindowEventTarget(theWind));	}//------------------------------- End of common stuff --------------------------void DoAboutBox(void)	{	StandardAlert(kAlertNoteAlert, "\pHIScrollingTextBox 1.0 by DTS, Apple � 2003", "\p", NULL, NULL);	}void DoPreferences(void)	{	StandardAlert(kAlertNoteAlert, "\pNo Preferences yet!", "\p", NULL, NULL);	}pascal OSStatus ContentViewHandler(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData)	{	HIViewRef contentView;	GetEventParameter(theEvent, kEventParamDirectObject, typeControlRef, NULL, sizeof(contentView), NULL, &contentView);	HIRect boundsRect;	HIViewGetBounds(contentView, &boundsRect);	boundsRect = CGRectInset(boundsRect, 16.0, 16.0);		HIViewRef theView;	ControlID controlID1 = { 'xyzt', 1 };	HIViewFindByID(contentView, controlID1, &theView);	boundsRect.size.width -= 16.0;	boundsRect.size.width /= 2.0;	boundsRect.size.width = floor(boundsRect.size.width);	HIViewSetFrame(theView, &boundsRect);	ControlID controlID2 = { 'xyzt', 2 };	HIViewFindByID(contentView, controlID2, &theView);	boundsRect.origin.x += (boundsRect.size.width + 16.0);	HIViewSetFrame(theView, &boundsRect);	return eventNotHandledErr;	}void DoScrollingTextWindow(void)	{	WindowRef theWind;	Rect bounds = {50, 50, 550, 550};	OSStatus theStatus = CreateNewWindow(									kDocumentWindowClass,									kWindowStandardDocumentAttributes |									kWindowStandardHandlerAttribute |									kWindowLiveResizeAttribute |									kWindowCompositingAttribute,									&bounds, &theWind);	if ((theStatus != noErr) || (theWind == NULL)) {DebugStr("\pCreateNewWindow failed!"); return;}		SetWindowTitleWithCFString(theWind, CFSTR("HIScrollingTextBox"));		CFStringRef theText = CFSTR("This is a custom HIView developed as a replacement for the Scrolling Text Box Control which does not work in compositing windows.\r\rYou can create it using the same parameters except for the resource ID of the 'TEXT' / 'styl' pair which is replaced by a CFStringRef.\r\rThis means that the text is displayed in mono-style Unicode. #01\r\r\rThis is a custom HIView developed as a replacement for the Scrolling Text Box Control which does not work in compositing windows.\r\rYou can create it using the same parameters except for the resource ID of the 'TEXT' / 'styl' pair which is replaced by a CFStringRef.\r\rThis means that the text is displayed in mono-style Unicode. #02\r\r\rThis is a custom HIView developed as a replacement for the Scrolling Text Box Control which does not work in compositing windows.\r\rYou can create it using the same parameters except for the resource ID of the 'TEXT' / 'styl' pair which is replaced by a CFStringRef.\r\rThis means that the text is displayed in mono-style Unicode. #03\r\r\rThis is a custom HIView developed as a replacement for the Scrolling Text Box Control which does not work in compositing windows.\r\rYou can create it using the same parameters except for the resource ID of the 'TEXT' / 'styl' pair which is replaced by a CFStringRef.\r\rThis means that the text is displayed in mono-style Unicode. #04\r\r\rThis is a custom HIView developed as a replacement for the Scrolling Text Box Control which does not work in compositing windows.\r\rYou can create it using the same parameters except for the resource ID of the 'TEXT' / 'styl' pair which is replaced by a CFStringRef.\r\rThis means that the text is displayed in mono-style Unicode. #05\r");	HIViewRef contentView;	HIViewFindByID(HIViewGetRoot(theWind), kHIViewWindowContentID, &contentView);	EventTypeSpec event = {kEventClassControl, kEventControlBoundsChanged};	InstallEventHandler(GetControlEventTarget(contentView), ContentViewHandler, 1, &event, NULL, NULL);	HIRect boundsRect;	HIViewGetBounds(contentView, &boundsRect);	boundsRect = CGRectInset(boundsRect, 16.0, 16.0);	HIViewRef scrollingTextBoxView;		// let's create the automatic scrolling text box view	boundsRect.size.width -= 16.0;	boundsRect.size.width /= 2.0;	boundsRect.size.width = floor(boundsRect.size.width);	theStatus = HICreateScrollingTextBox(&boundsRect, theText, true, 20, 10, 1, &scrollingTextBoxView);	if (theStatus != noErr) {DebugStr("\p HICreateScrollingTextBox failed"); return;}	HIViewSetVisible(scrollingTextBoxView, true);		theStatus = HIViewAddSubview(contentView, scrollingTextBoxView);		// and assigned an ID to find it later	ControlID controlID1 = { 'xyzt', 1 };	SetControlID(scrollingTextBoxView, &controlID1);		// let's create the manual scrolling text box view	boundsRect.origin.x += (boundsRect.size.width + 16.0);	theStatus = HICreateScrollingTextBox(&boundsRect, theText, false, 0, 0, 0, &scrollingTextBoxView);	if (theStatus != noErr) {DebugStr("\p HICreateScrollingTextBox failed"); return;}	HIViewSetVisible(scrollingTextBoxView, true);		theStatus = HIViewAddSubview(contentView, scrollingTextBoxView);		// and assigned an ID to find it later	ControlID controlID2 = { 'xyzt', 2 };	SetControlID(scrollingTextBoxView, &controlID2);	ShowWindow(theWind);	}void DoScrollingHITextWindow(void)	{	WindowRef theWind;	Rect bounds = {80, 80, 580, 580};	OSStatus theStatus = CreateNewWindow(									kDocumentWindowClass,									kWindowStandardDocumentAttributes |									kWindowStandardHandlerAttribute |									kWindowLiveResizeAttribute |									kWindowCompositingAttribute,									&bounds, &theWind);	if ((theStatus != noErr) || (theWind == NULL)) {DebugStr("\pCreateNewWindow failed!"); return;}		SetWindowTitleWithCFString(theWind, CFSTR("HIScrollingHITextBox"));		HIViewRef contentView;	HIViewFindByID(HIViewGetRoot(theWind), kHIViewWindowContentID, &contentView);	EventTypeSpec event = {kEventClassControl, kEventControlBoundsChanged};	InstallEventHandler(GetControlEventTarget(contentView), ContentViewHandler, 1, &event, NULL, NULL);	HIRect boundsRect;	HIViewGetBounds(contentView, &boundsRect);	boundsRect = CGRectInset(boundsRect, 16.0, 16.0);		// let's get the URL to our .rtf file	CFURLRef theURL = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("Test"), CFSTR("rtf"), NULL);	HIViewRef scrollingHITextBoxView;	// let's create the automatic scrolling text box view	boundsRect.size.width -= 16.0;	boundsRect.size.width /= 2.0;	boundsRect.size.width = floor(boundsRect.size.width);	theStatus = HICreateScrollingHITextBox(&boundsRect, theURL, true, 20, 10, 1, &scrollingHITextBoxView);	if (theStatus != noErr) {DebugStr("\p HICreateScrollingHITextBox failed"); return;}	HIViewSetVisible(scrollingHITextBoxView, true);		theStatus = HIViewAddSubview(contentView, scrollingHITextBoxView);		// and assigned an ID to find it later	ControlID controlID1 = { 'xyzt', 1 };	SetControlID(scrollingHITextBoxView, &controlID1);	// let's create the manual scrolling text box view	boundsRect.origin.x += (boundsRect.size.width + 16.0);	theStatus = HICreateScrollingHITextBox(&boundsRect, theURL, false, 0, 0, 0, &scrollingHITextBoxView);	if (theStatus != noErr) {DebugStr("\p HICreateScrollingHITextBox failed"); return;}	HIViewSetVisible(scrollingHITextBoxView, true);		theStatus = HIViewAddSubview(contentView, scrollingHITextBoxView);		// and assigned an ID to find it later	ControlID controlID2 = { 'xyzt', 2 };	SetControlID(scrollingHITextBoxView, &controlID2);	CFRelease(theURL);	ShowWindow(theWind);	}