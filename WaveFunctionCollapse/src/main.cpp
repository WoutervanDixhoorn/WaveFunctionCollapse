#include <stdio.h>
#include <iostream>

#include "Application.h"

#include "WaveLayer.h"

class WaveFunctionCollapse : public Douter::Application
{
private:
	WaveLayer* m_WaveLayer = NULL;

public:

	virtual void Init()
	{
		std::cout << "Init!\n";

		//Attach main application layer!
		m_WaveLayer = new WaveLayer();
		AttachLayer(m_WaveLayer);
	}
};

int main() {

	Douter::Application* wfc = new WaveFunctionCollapse();
	wfc->Run();
	delete wfc;

	return 0;
}

