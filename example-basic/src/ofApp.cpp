/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	==== updated ====
	creative commons 2018 Nontrivial Studio
	updated by Aaron BocANEGRA
	tested in Windows 10 x64
	Visual Studio 2017
	openFrameworks 0.98
	<https://github.com/abocanegra/ofxWinMenu>
	=========================================================================
	==== Original ====
	Copyright (C) 2016-2017 Lynn Jarvis.
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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("ofxWinMenu basic example"); // Set the app name on the title bar

	// Get the window size for image loading
	window = ofGetWindowRect();
	screen.set(ofPoint(0, 0), ofGetScreenWidth(), ofGetScreenHeight());
	window.alignTo(screen);
	bTopmost = false;
	// Centre on the screen
	ofSetWindowPosition(window.x, window.y);
	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);
	// Load an image for the example
	myImage.loadImage("lighthouse.jpg");
	
	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);
	setupMenu();
} // end Setup
//--------------------------------------------------------------
void ofApp::update() {

}// End Update
//--------------------------------------------------------------
void ofApp::draw() {
	char str[256];
	ofBackground(0, 0, 0, 255);
	ofSetColor(255);

	myImage.draw(0, 0, ofGetWidth(), ofGetHeight());

	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " ' ' show/hide info : 'f' toggle full screen");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}
} // end Draw
//-------------------------------------------------------------
void ofApp::setupMenu() {
#ifdef TARGET_WIN32
	hWnd = WindowFromDC(wglGetCurrentDC());
	//
	// Create a menu using ofxWinMenu
	//
	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);
	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);
	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();
	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");
	//
	// Add popup items to the File menu
	//
	// Open an image file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	// Save an image file
	menu->AddPopupItem(hPopup, "Save As", false, false); // Not checked and not auto-checked
	// Example submenu off the File menu
	HMENU hSubMenu = menu->AddPopupMenu(hPopup, "Submenu");
	menu->AddPopupItem(hSubMenu, "Item 1", true); // Checked and auto-check
	menu->AddPopupItem(hSubMenu, "Item 2"); // Not checked and auto-check (default)
	menu->AddPopupItem(hSubMenu, "Item 3", false, false); // Not checked and not auto-checked
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);
	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");
	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show info", true); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show on top"); // Not checked (default)
	bFullscreen = ofGetWindowMode(); // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check
															 //
															 // Help popup menu
															 //
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check
													   // Set the menu to the window
	menu->SetWindowMenu();
#endif
}
//End SetupMenu
//--------------------------------------------------------------
//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
#ifdef TARGET_WIN32
void ofApp::appMenuFunction(string title, bool bChecked) {
	ofFileDialogResult result;
	string filePath;
	size_t pos;
	// File menu
	if (title == "Open") {
		result = ofSystemLoadDialog("Select an image file", false);
		if (result.bSuccess) {
			filePath = result.getPath();
			printf("Open\n");
			pos = filePath.find_last_of(".");
			if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "jpg") {
				// found the right extension
				printf("  Loading [%s]\n", result.getName().c_str());
				myImage.loadImage(filePath);
				// Adjust window height to match image aspect ratio
				ofSetWindowShape(window.width, window.height);
			}
			else
				printf("  Needs a '.jpg' extension\n");
		}
	}
	if (title == "Save As") {
		result = ofSystemSaveDialog(filePath, "Save an image file");
		if (result.bSuccess) {
			printf("Save As\n");
			filePath = result.getPath();
			pos = filePath.find_last_of(".");
			if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "jpg") {
				printf("  Saving [%s]\n", result.getName().c_str());
				myImage.saveImage(filePath, OF_IMAGE_QUALITY_BEST);
			}
			else
				printf("  Needs a '.jpg' extension\n");
		}
	}
	// Exit
	if (title == "Exit") {
		ofExit(); // Quit the application
	}
	// Window menu
	if (title == "Show info") {
		bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
	}
	if (title == "Show on top") {
		bTopmost = bChecked; // Use the checked value directly
		menu->DoTopMost(bChecked);
	}
	if (title == "Full screen") {
		ofToggleFullscreen();
		menu->ToggleWindowMenu(bTopmost);
	}
	// Help menu
	if (title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}
} // end appMenuFunction
#endif

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			ofSetFullscreen(false);
			#ifdef TARGET_WIN32
				menu->SetWindowMenu();
			#endif
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		#ifdef TARGET_WIN32
			menu->SetPopupItem("Show info", bShowInfo);
		#endif
	}

	if(key == 'f') {
		ofToggleFullscreen();
        #ifdef TARGET_WIN32
			menu->ToggleWindowMenu(bTopmost);
         #endif
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	bFullscreen = ofGetWindowMode();
	window.set(ofGetWindowRect());
	if (!ofGetWindowMode()) {
		window.alignTo(screen);
		// Centre on the screen
		ofSetWindowPosition(window.x, window.y);
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}