#include <stdio.h>
#include <iostream>

#include "Douter/Application.h"
#include "Douter/Rendering/Renderer.h"


#include "WaveLayer.h"

class WaveFunctionCollapse : public Douter::Application
{
private:
	WaveLayer* m_WaveLayer = nullptr;

public:

	virtual void Init()
	{
		//Init 2D Renderer
		Douter::Renderer2D::Init();

		std::cout << "Init!\n";

		//Attach main application layer!
		m_WaveLayer = new WaveLayer();
		AttachLayer(m_WaveLayer);
	}

	~WaveFunctionCollapse()
	{
		delete m_WaveLayer;
	}
};

int main() {
	Douter::Application* wfc = new WaveFunctionCollapse();
	wfc->Run();
	delete wfc;

	return 0;
}

