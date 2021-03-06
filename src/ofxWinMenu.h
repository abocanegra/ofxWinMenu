/*

	ofxWinMenu

	Create a menu for a Microsoft Windows Openframeworks application.
	
	==== updated ====
	creative commons 2018 Nontrivial Studio
	updated by Aaron BocANEGRA
	tested in Windows 10 x64
	Visual Studio 2017
	openFrameworks 0.98

	<https://github.com/abocanegra/ofxWinMenu>

	=========================================================================  

	==== Original ====
	Copyright (C) 2016 Lynn Jarvis.

	https://github.com/leadedge

	http://www.spout.zeal.co

    =========================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =========================================================================

*/

#pragma once

//-------------------------------
#define OF_VERSION			("OF_0.9.8")
//-------------------------------

//-------------------------------
//  find the system type --------
//-------------------------------

#if defined( __WIN32__ ) || defined( _WIN32 )
#define TARGET_WIN32
#define WIN32_HIGH_RES_TIMING
#elif defined( __APPLE_CC__)
#define TARGET_OSX
#else
#define TARGET_LINUX
#endif
//-------------------------------

class ofApp; // Forward declaration

class ofxWinMenu {

	public:

		ofxWinMenu(ofApp *app, HWND Ahwnd);
		~ofxWinMenu();

		HWND g_hwnd; // ofApp window
		HMENU g_hMenu; // ofApp menu we are building

		// Main menu
		HMENU CreateWindowMenu();

		// Popup menu of the main menu
		HMENU AddPopupMenu(HMENU hMenu, string menuName);
		// Popup menu items
		bool AddPopupItem(HMENU hSubMenu, string ItemName);
		bool AddPopupItem(HMENU hSubMenu, string ItemName, bool bChecked);
		bool AddPopupItem(HMENU hSubMenu, string ItemName, bool bChecked, bool bAutoCheck);
		bool AddPopupSeparator(HMENU hSubMenu);

		// Set the menu to the application
		bool SetWindowMenu();

		// Remove the menu but do not destroy it
		bool RemoveWindowMenu();

		// Toggle Setup Remove Menu
		bool ToggleWindowMenu(bool TopMost);

		// Destroy the menu
		bool DestroyWindowMenu();

		// Set the menu checkmark of a popup item
		bool SetPopupItem(string ItemName, bool bChecked);

		// Function from ofApp for return of memu item selection
		void CreateMenuFunction(void(ofApp::*function)(string title, bool bChecked));

		// Function for ofxWinMenu to return menu item selection to ofApp
		void MenuFunction(string title, bool bChecked);

		ofApp *pApp; // Pointer to access the ofApp class
		void(ofApp::*pAppMenuFunction)(string title, bool bChecked); // The ofApp menu function

		void DoTopMost(bool TopMost);
		bool IsTopMost;

		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window
		ofRectangle window, screen;

		// Menu item data
		vector<string> itemNames; // Name of the menu item
		vector<HMENU> subMenus;   // Submenu containing the menu item
		vector<int> itemIDs;      // Position of the item in the submenu
		vector<bool> autoCheck;   // Check the menu item on and off
		vector<bool> isChecked;   // Item checked flag
};
