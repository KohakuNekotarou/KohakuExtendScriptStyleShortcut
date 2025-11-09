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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IApplication.h"
#include "IControlView.h"
#include "IObjectStyleInfo.h"
#include "IPanelMgr.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IShortcutUtils.h"
#include "IStyleInfo.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "CScriptProvider.h"
#include "GlobalTime.h"
#include "ObjStylesUIID.h" // for kObjectStylePanelActionID etc
#include "StylePanelID.h" // for kCharacterStylesPanelActionID etc
#include "TabStyUIID.h" // for kCellStylesPanelActionID etc

// Project includes:
#include "KESSSScriptingDefs.h"
#include "KESSSID.h"

class KESSSScriptProvider : public CScriptProvider
{
public:
	// Constructor.
	// param boss interface ptr from boss object on which this interface is aggregated.
	KESSSScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) {};

	// Destructor. Does nothing.
	~KESSSScriptProvider() {}

	// This method is called if a provider can handle a property.
	// @param scriptID_property identifies the ID of the property to handle.
	// @param iScriptRequestData identifies an interface pointer used to extract data.
	// @param iScript_parent identifies an interface pointer on the script object representing the parent of the application object.
	virtual ErrorCode AccessProperty
	(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);

private:
	// Keyboard shortcut
	virtual ErrorCode GetSetShortcut
	(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent);
};


// CREATE_PMINTERFACE
// Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
CREATE_PMINTERFACE(KESSSScriptProvider, kKESSSScriptProviderImpl)

// AccessProperty
ErrorCode KESSSScriptProvider::AccessProperty
(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	switch (scriptID_property.Get())
	{
	case KESSSScriptProperties::p_KESSSStyleShortcut:

		status = this->GetSetShortcut(scriptID_property, iScriptRequestData, iScript_parent);
		break;

	default:
		status = CScriptProvider::AccessProperty(scriptID_property, iScriptRequestData, iScript_parent);
	}

	return status;
}

// Get set shortcut
ErrorCode KESSSScriptProvider::GetSetShortcut
(ScriptID scriptID_property, IScriptRequestData* iScriptRequestData, IScript* iScript_parent)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		PMString pMString_shortcut;
		int16 int16_modifiers;
		VirtualKey virtualKey_shortcutKey;
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			// ---------------------------------------------------------------------------------------
			// Get style shortcut
			InterfacePtr<IStyleInfo> iStyleInfo(iScript_parent, ::UseDefaultIID());
			if (iStyleInfo == nil) break;

			virtualKey_shortcutKey = iStyleInfo->GetKeyboardShortcut(&int16_modifiers);

			// Returns a string describing the key & modifiers passed in.
			pMString_shortcut = Utils<IShortcutUtils>()->GetShortcutString(virtualKey_shortcutKey, int16_modifiers);

			// ---------------------------------------------------------------------------------------
			// Append return data
			scriptData.SetPMString(pMString_shortcut);

			iScriptRequestData->AppendReturnData(iScript_parent, scriptID_property, scriptData);
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			// ---------------------------------------------------------------------------------------
			// Extract request data
			status = iScriptRequestData->ExtractRequestData(scriptID_property.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetPMString(pMString_shortcut);
			if (status != kSuccess) break;

			// Parse a shortcut string into key & modifiers.
			Utils<IShortcutUtils>()->ParseShortcutString(pMString_shortcut, &virtualKey_shortcutKey, &int16_modifiers);

			// TimeStamp
			GlobalTime globalTime_TimeStamp;
			globalTime_TimeStamp.CurrentTime();

			// Query formatted name.
			PMString PMString_targetStyle = iScript_parent->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();

			// ---------------------------------------------------------------------------------------
			// Set shortcut.
			if (PMString_targetStyle == "object style")
			{
				InterfacePtr<IObjectStyleInfo> iObjectStyleInfo(iScript_parent, ::UseDefaultIID());
				if (!iObjectStyleInfo) break;

				// Set shortcut.
				iObjectStyleInfo->SetKeyboardShortcut(virtualKey_shortcutKey, int16_modifiers);

				// Set timeStamp.
				if (pMString_shortcut != "") iObjectStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
			}
			else if (
				PMString_targetStyle == "character style" ||
				PMString_targetStyle == "paragraph style" ||
				PMString_targetStyle == "cell style" ||
				PMString_targetStyle == "table style"
			)
			{
				InterfacePtr<IStyleInfo> iStyleInfo(iScript_parent, ::UseDefaultIID());
				if (!iStyleInfo) break;

				// Set shortcut.
				iStyleInfo->SetKeyboardShortcut(virtualKey_shortcutKey, int16_modifiers);

				// Set timeStamp.
				if (pMString_shortcut != "") iStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
			}

			// ---------------------------------------------------------------------------------------
			// Panel redraw.
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
			if (iApplication == nil) break;

			InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());

			WidgetID widgetID;
			ActionID actionID;
			if (PMString_targetStyle == "object style")
			{
				actionID = kObjectStylePanelActionID;
				widgetID = kObjStylesTreeViewPanelWidgetID;
			}
			else if (PMString_targetStyle == "cell style")
			{
				actionID = kCellStylesPanelActionID;
				widgetID = kTabStyUICellStylePanelWidgetID;
			}
			else if (PMString_targetStyle == "table style")
			{
				actionID = kTableStylesPanelActionID;
				widgetID = kTabStyUITableStylePanelWidgetID;
			}
			else if (PMString_targetStyle == "character style")
			{
				actionID = kCharacterStylesPanelActionID;
				widgetID = kCharStylePanelWidgetID;
			}
			else if (PMString_targetStyle == "paragraph style")
			{
				actionID = kParagraphStylesPanelActionID;
				widgetID = kParaStylePanelWidgetID;
			}

			bool16 result = iPanelMgr->DoesPanelExist(widgetID);
			if (result)
			{
				result = iPanelMgr->IsPanelWithMenuIDShown(actionID);
				if (result)
				{
					IControlView* iControlView = iPanelMgr->GetPanelFromWidgetID(widgetID);

					iControlView->ForceRedraw();
				}
			}
		}
		status = kSuccess;

	} while (false); // only do once

	return status;
}