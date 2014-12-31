/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "LightingScene.h"
#include "XMLScene.h"
#include "TPInterface.h"
#include "sceneGraph.h"
#include "connectProlog.h"
#include "GameBoard.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {
	
	sceneGraph graph;
	sceneGraph * pgraph = new sceneGraph();
	pgraph = &graph;
	char* filename = "myScene.anf";
	if (argc >1)
		filename = argv[1];
	CGFapplication app = CGFapplication();
	LightingScene * scene = new LightingScene();
	try {
		app.init(&argc, argv);
		XMLScene n = XMLScene(filename,pgraph);
		scene->setGraph(graph);
		app.setScene(scene);
		app.setInterface(new TPinterface(pgraph));
		app.setInterface(new PickInterface());
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