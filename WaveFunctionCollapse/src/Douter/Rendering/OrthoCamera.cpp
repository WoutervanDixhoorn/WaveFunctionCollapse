#include "OrthoCamera.h"

#include <glm.hpp>
#include <glm/gtx/transform.hpp>

namespace Douter
{
	OrthoCamera::OrthoCamera()
	{
		m_Projection = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, 0.0f, 1.0f); //TODO: Correct this with viewport size
		m_View = glm::lookAt(
			glm::vec3(0, 0, 0), 
			glm::vec3(0, 0, -1), 
			glm::vec3(0, 1, 0)  
		);

		UpdateViewProjection();
	}

	void OrthoCamera::SetPosition(float x, float y, float z)
	{
		m_Transform->SetPosition(x, y, z);
		UpdateViewProjection();
	}

	void OrthoCamera::Translate(float x, float y, float z)
	{
		m_Transform->Translate(x, y, z);
		UpdateViewProjection();
	}

	void OrthoCamera::Rotate(float x, float y, float z)
	{

	}

	void OrthoCamera::UpdateViewProjection()
	{
		glm::mat4 view = glm::translate(m_View, -m_Transform->GetPosition());;

		m_ViewProjection = m_Projection * view;
	}

}