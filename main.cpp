/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "TPinterface.h"
#include "LightingScene.h"
#include "XMLScene.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	XMLScene n = XMLScene("demograph.anf");

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new LightingScene());
		app.setInterface(new CGFinterface());
		app.setInterface(new TPinterface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
}