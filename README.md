# InDesign Plug-In

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

We cannot be held responsible for any issues arising from your use of this service.<br>
Please use it at your own risk.<br>

On Mac, you cannot use downloaded plug-ins directly.<br>
https://helpx.adobe.com/jp/indesign/kb/indesign-and-macos-catalina.html<br>
Refer to the above and use Terminal to<br>
sudo xattr -r -d com.apple.quarantine /Applications/Adobe\ Indesign\ 2025/Plug-ins/KohakuExtendScriptStyleShortcut.InDesignPlugin<br>
Please execute.

## extendScript for JavaScript
```
// Style Shortcut Settings
app.activeDocument.objectStyles.lastItem().shortcut = ""; // delete
app.activeDocument.objectStyles.lastItem().shortcut = "Shift+Ctrl+Alt+Num 0";
app.activeDocument.cellStyles.lastItem().shortcut = "Shift+Ctrl+Alt+Num 1";
app.activeDocument.tableStyles.lastItem().shortcut = "Shift+Ctrl+Alt+Num 2";
app.activeDocument.paragraphStyles.lastItem().shortcut = "Shift+Ctrl+Alt+Num 3";
app.activeDocument.characterStyles.lastItem().shortcut = "Shift+Ctrl+Alt+Num 4";
alert(app.activeDocument.characterStyles.lastItem().shortcut);
```

## Build Method
**Mac Edition**

**1. Download the SDK**<br>
https://developer.adobe.com/indesign/

**2. Downloading the programming software, Xcode**<br>
SDK/docs/html/index.html<br>
Download the Xcode version compatible with your InDesign version as a reference.<br>
https://developer.apple.com/download/all/?q=xcode

**3. Create a PlugIn template**<br>
Search for and install Java to use dolly.jar<br>
SDK/devtools/dolly/dolly.jar<br>
use<br>

The project directory is located at<br>
SDK/build/mac/prj<br>
Set up and create as follows.

**4. Download the source from Git**<br>
![Git](https://github.com/user-attachments/assets/5157f513-096f-4e2e-b471-af644948e97c)<br>
Place the source files in the<br>
SDK/source/sdksamples/kohakuExtendScriptStyleShortcut<br>
folder.

**5. Build in Xcode**<br>
Load SDK/build/mac/prj/KohakuExtendScriptStyleShortcut.xcodeproj in Xcode.<br>
Set the build configuration to Release.<br>
<img width="279" height="58" alt="rere" src="https://github.com/user-attachments/assets/420c409a-f7f0-495f-95bf-f61c1497d380" /><br>
Product > Build

**6. Load PlugIn**<br>
SDK/build/mac/release_cocoa64/KohakuExtendScriptStyleShortcut.InDesignPlugin<br>
Place the PlugIn in the PlugIn folder in InDesign.<br>
If the message “As the correct plugin” appears.<br>
Product > Clean Build Folder...<br>
After performing the above, please try building.
