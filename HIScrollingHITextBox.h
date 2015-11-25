/*	File:		HIScrollingHITextBox.h	Contains:	Header file associated with HIScrollingHITextBox.cp.	Version:	1.0	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.				("Apple") in consideration of your agreement to the following terms, and your				use, installation, modification or redistribution of this Apple software				constitutes acceptance of these terms.  If you do not agree with these terms,				please do not use, install, modify or redistribute this Apple software.				In consideration of your agreement to abide by the following terms, and subject				to these terms, Apple grants you a personal, non-exclusive license, under Apple�s				copyrights in this original Apple software (the "Apple Software"), to use,				reproduce, modify and redistribute the Apple Software, with or without				modifications, in source and/or binary forms; provided that if you redistribute				the Apple Software in its entirety and without modifications, you must retain				this notice and the following text and disclaimers in all such redistributions of				the Apple Software.  Neither the name, trademarks, service marks or logos of				Apple Computer, Inc. may be used to endorse or promote products derived from the				Apple Software without specific prior written permission from Apple.  Except as				expressly stated in this notice, no other rights or licenses, express or implied,				are granted by Apple herein, including but not limited to any patent rights that				may be infringed by your derivative works or by other works in which the Apple				Software may be incorporated.				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO				WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED				WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR				PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN				COMBINATION WITH YOUR PRODUCTS.				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR				CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE				GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)				ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION				OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT				(INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.	Copyright � 2003 Apple Computer, Inc., All Rights Reserved*/#ifndef __HISCROLLINGHITEXTBOX__#define __HISCROLLINGHITEXTBOX__#include <Carbon/Carbon.h>#ifdef __cplusplusextern "C" {#endifconst ControlID kScrollingHITextBoxViewID = {'CASD', 'HSHT'};#define kScrollingHITextBoxClassID	CFSTR("com.apple.sample.dts.HIScrollingHITextBox")/* *  HICreateScrollingHITextBox() *   *  Summary: *    Creates a scrolling text box HIView based on the scrolling text box control (CDEF 27). *    Differences: *    ------------- *    - It takes a CFURLRef instead of a 'TEXT'/'styl' resource ID pair. *    - That allows the use of a .rtf file such as created by TextEdit. *    - It doesn't need a WindowRef parameter. *   *  Parameters: *     *    inBounds: *      The initial bounds of the view. If this parameter is NULL, the *      view defaults to have empty bounds ( 0, 0, 0, 0 ). *     *    inURLRef: *      The CFURLRef to the text to be displayed in the box. *     *    inAutoScroll: *      If true then the text scrolls automatically using the following parameters, *      If false then the text has to be scrolled manually using the visible scroll bar. *     *    inDelayBeforeAutoScroll: *      If inAutoScroll is true, then this is the delay before the automatic scrolling starts, *      If inAutoScroll is false, this parameter is ignored. *     *    inDelayBetweenAutoScroll: *      If inAutoScroll is true, then this parameter and the next one set the automatic scrolling speed, *      If inAutoScroll is false, this parameter is ignored. *     *    inAutoScrollAmount: *      If inAutoScroll is true, then this parameter and the previous one set the automatic scrolling speed, *      If inAutoScroll is false, this parameter is ignored. *     *    outHIView: *      On exit, contains the new HIView. *   *  Availability: *    Mac OS X:         in version 10.2 and later since it needs the HIView APIs *    CarbonLib:        not available *    Non-Carbon CFM:   not available */extern OSStatus HICreateScrollingHITextBox(	const HIRect * inBounds,                   /* can be NULL */	CFURLRef       inURLRef,	Boolean        inAutoScroll,	UInt32         inDelayBeforeAutoScroll,	UInt32         inDelayBetweenAutoScroll,	UInt16         inAutoScrollAmount,	HIViewRef *    outHIView);#ifdef __cplusplus}#endif#endif