#pragma once
#include "Camera.h"

namespace Douter
{

	class OrthoCamera : public Camera
	{
	public:
		OrthoCamera();
		~OrthoCamera();

		virtual void SetPosition(float x, float y, float z) override;
		virtual void Translate(float x, float y, float z) override;
		virtual void Rotate(float x, float y, float z) override;

	private:
		virtual void UpdateViewProjection() override;
	};

}