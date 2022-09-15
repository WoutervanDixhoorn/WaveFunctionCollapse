#pragma once
#include "ILayer.h"
#include "ImGuiLayer.h"

class WaveLayer : public Douter::ILayer
{
public:

	virtual void OnAttach()
	{
	}

	virtual void OnDettach()
	{
	}

	virtual void Update(double deltaTime)
	{
	}

	virtual void OnImGuiDraw()
	{
		Douter::ImGuiLayer::Begin();

		Douter::ImGuiLayer::End();
	}

	virtual void Draw()
	{
	}
};