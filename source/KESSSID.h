//========================================================================================
//  
//  $File: $
//  
//  Owner: 
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __KESSSID_h__
#define __KESSSID_h__

#include "SDKDef.h"

// Company:
#define kKESSSCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kKESSSCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kKESSSPluginName	"KohakuExtendScriptStyleShortcut"			// Name of this plug-in.
#define kKESSSPrefixNumber	0xe204466 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kKESSSVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kKESSSAuthor		""					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kKESSSPrefixNumber above to modify the prefix.)
#define kKESSSPrefix		RezLong(kKESSSPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kKESSSStringPrefix	SDK_DEF_STRINGIZE(kKESSSPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kKESSSMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kKESSSMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kKESSSPluginID, kKESSSPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kKESSSScriptProviderBoss, kKESSSPrefix + 0)
//DECLARE_PMID(kClassIDSpace, kKESSSBoss, kKESSSPrefix + 4)

// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESSSINTERFACE, kKESSSPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kKESSSScriptProviderImpl, kKESSSPrefix + 0 )

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kKESSSAboutActionID, kKESSSPrefix + 0)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kKESSSWidgetID, kKESSSPrefix + 2)

//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kKESSSStyleShortcutPropertyScriptElement, kKESSSPrefix + 0)

// "About Plug-ins" sub-menu:
#define kKESSSAboutMenuKey			kKESSSStringPrefix "kKESSSAboutMenuKey"
#define kKESSSAboutMenuPath		kSDKDefStandardAboutMenuPath kKESSSCompanyKey

// "Plug-ins" sub-menu:
#define kKESSSPluginsMenuKey 		kKESSSStringPrefix "kKESSSPluginsMenuKey"
#define kKESSSPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kKESSSCompanyKey kSDKDefDelimitMenuPath kKESSSPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kKESSSAboutBoxStringKey	kKESSSStringPrefix "kKESSSAboutBoxStringKey"
#define kKESSSTargetMenuPath kKESSSPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kKESSSFirstMajorFormatNumber  RezLong(1)
#define kKESSSFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kKESSSCurrentMajorFormatNumber kKESSSFirstMajorFormatNumber
#define kKESSSCurrentMinorFormatNumber kKESSSFirstMinorFormatNumber

#endif // __KESSSID_h__
