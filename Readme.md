# Win32 Dialog Application

## Table of Contents

- [Introduction](#introduction)
- [Windows Target Version](#windows-target-version)
- [Distributing Your Application](#distributing-your-application)
- [Terms of Use](#terms-of-use)
- [Problems?](#problems)
- [Changelog](#changelog)

## Introduction

This application is an example Windows dialog application. It uses a dialog resource and Windows dialog box functions
for creating the dialog, meaning it can be edited using the resource editor in Visual Studio (or the equivalent in other
IDEs) rather than having to manually create controls at runtime.

The following changes from a standard Windows application are required for this to happen:

- The dialog being used for the main window must have a class name associated with it. In order to do this in Visual
  Studio, you must first disable MFC Mode for the resource. This is done by going into "Resource View", selecting the
  resource file name (e.g. "Resource.rc"), going to "Properties", then setting "MFC Mode" to false. You will then be
  able to set the "Class Name" property of the dialog. If you don't disable MFC Mode, the "Class Name" property will be
  visible but disabled, so you won't be able to set it.
- The Window class for the main window must have the "cbWndExtra" field set to "DLGWINDOWEXTRA", and the "lpszClassName"
  must match the class name you gave to the dialog resource. All other properties (e.g. the window procedure and icons)
  are set the same as you normally would for a Windows application.
- The dialog window is created with "CreateDialog()" rather than "CreateWindow()". The "lpTemplate" parameter should be
  set to the resource ID of the dialog (not the class name of the dialog!), and the "lpDialogFunc" parameter should be
  set to NULL.
- The application's message pump should call "IsDialogMessage()" on each message it gets. This is optional, but doing so
  means that the dialog behaves like a dialog, e.g. pressing the tab key moves focus to the next dialog control.
- The "WM_CREATE" message handler includes some code to reposition the dialog before it is displayed. This is also
  optional, but if this isn't done then the dialog will always display in the centre of the main display. If two
  instances of the application are launched, the second instance could hide the first one.

Other than that, the application code is the same as that for a standard Windows application.

To build the application, open the solution file in Visual Studio, right click the solution in the Solution Explorer and
select "Retarget solution". Choose which version of the Windows SDK you'd like to use to build the solution. Next,
select the configuration and platform from the drop-down menu, and use "Build Solution" from the "Build" menu.

The solution was created in Visual Studio 2017, but it should open in any version of Visual Studio from 2010 SP1
onwards.

## Windows Target Version

The project targets Windows Vista. If you attempt to call Windows API functions in your source code which were
introduced after Windows Vista, you will get a compilation error. If you'd like to use newer API functions (at the
expense of the application not running on older versions of Windows), you will need to change the "_WIN32_WINNT"
preprocessor definition in "targetver.h" to match the version of Windows you are targeting. For example, to target
Windows 7, change it to "0x0601".

You can also target Windows XP using the above method with the value "0x0501". However, you will also need to go into
your project properties, and set the "Platform Toolset" under "Configuration Properties" to a toolset which supports
Windows XP.

You can find a complete list of target version numbers in the "SDKDDKVer.h" Windows SDK header file.

## Distributing Your Application

The application will depend on the Microsoft Visual C++ Runtime. This will either be in the form of a Visual C++ Runtime
redistributable MSI (or merge module which you can use in your own installer), or DLL(s) which you must redistribute
with the application. Check the product documentation for your version of Visual Studio to see what your options are,
and be careful to ensure that you are allowed to redistribute the DLL(s) if you choose this option.

## Terms of Use

Refer to "License.txt" for terms of use.

## Problems?

If you have any problems or questions, please ensure you have read this readme. If you are still having trouble, you can
[get in contact](http://www.transmissionzero.co.uk/contact/).

## Changelog
1. 2017-11-10: Version 1.0
  - Initial release.

Transmission Zero
2017-11-10
