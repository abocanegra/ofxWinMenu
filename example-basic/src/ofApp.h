/*

	ofxWinMenu basic example - ofApp.h

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
	This program has been updated for use as an example for ofxWin Minu
	<https://github.com/abocanegra/ofxWinMenu> by Aaron Bocanegra of Nontrivial Studio
	cc 2018
*/

#pragma once

#include "ofMain.h"

#include "ofxWinMenu.h" // Menu addon

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// then the the platform specific includes:
		#ifdef TARGET_WIN32
			// Menu
			ofxWinMenu * menu; // Menu object
			void appMenuFunction(string title, bool bChecked); // Menu return function
			HWND hWnd; // Application window
			HWND hWndForeground; // current foreground window
        #endif
		void	setupMenu();
		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		ofRectangle window;
		ofRectangle screen;

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;

		// Example functions
		//void doTopmost(bool bTop);
};
