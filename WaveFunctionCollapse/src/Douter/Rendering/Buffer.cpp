#include "Buffer.h"

#include <glad/glad.h>

namespace Douter {

	//Helpers
	int AttributeTypeToSize(AttributeType type)
	{
		switch (type) {
		case AttributeType::FLOAT:
		case AttributeType::INT:
		case AttributeType::UINT:
			return 4;
		default:
			std::cout << "ERROR: This type is not implemented yet!\n";
			return 0;
		}
	}

	int AttributeToGlType(AttributeType type)
	{
		switch (type) {
		case AttributeType::FLOAT:
			return GL_FLOAT;
		case AttributeType::INT:
			return GL_INT;
		case AttributeType::UINT:
			return GL_UNSIGNED_INT;
		default:
			std::cout << "ERROR: This type is not implemented yet!\n";
			return 0;
		}
	}

	//VertexArray
	
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_Id);
		m_VertexSize = 0;
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_Id);
	}

	void VertexArray::AddBuffer(VertexBuffer* buffer)
	{
		m_VertexBuffer = buffer;
	}

	void VertexArray::AddBuffer(IndexBuffer* buffer)
	{
		m_IndexBuffer = buffer;
	}

	void VertexArray::Bind() const
	{
		if (m_VertexBuffer != nullptr)
			m_VertexBuffer->Bind();
		if (m_IndexBuffer != nullptr)
			m_IndexBuffer->Bind();

		glBindVertexArray(m_Id);
	}

	void VertexArray::Unbind() const
	{
		if (m_VertexBuffer != nullptr)
			m_VertexBuffer->Unbind();
		if (m_IndexBuffer != nullptr)
			m_IndexBuffer->Unbind();

		glBindVertexArray(0);
	}
	
	template<>
	void VertexArray::Add<float>(int count)
	{
		Bind();

		VertexAttribute attrib{
			m_Attributes.size(), //Location
			count,
			AttributeType::FLOAT
		};
		m_Attributes.push_back(attrib);

		m_VertexSize += count * AttributeTypeToSize(AttributeType::FLOAT);

		UpdateAttributes();
	}

	template<>
	void VertexArray::Add<int>(int count)
	{

	}

	template<>
	void VertexArray::Add<unsigned int>(int count)
	{

	}

	void VertexArray::UpdateAttributes()
	{
		int offset = 0;
		for (int i = 0; i < m_Attributes.size(); i++)
		{
			VertexAttribute attrib = m_Attributes.at(i);
			glVertexAttribPointer(attrib.location, attrib.count, AttributeToGlType(attrib.type), GL_FALSE, m_VertexSize, (void*)offset);
			glEnableVertexAttribArray(attrib.location);
			offset += (attrib.count * AttributeTypeToSize(attrib.type));
		}
	}

	//VertexBuffer
	VertexBuffer::VertexBuffer()
	{
		glCreateBuffers(1, &m_Id);
	}

	VertexBuffer::VertexBuffer(size_t size)
	{
		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(size_t size, void* data)
	{
		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::Data(size_t size, void* data)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); //TODO: Make dynamic draw changable
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//Index Buffer
	IndexBuffer::IndexBuffer(size_t size)
	{
		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::IndexBuffer(size_t size, int count, uint32_t* data)
	{
		glCreateBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void IndexBuffer::Data(size_t size, int count, uint32_t* data)
	{
		Bind();
		m_Count = count;
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data); //TODO: Make dynamic draw changable
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}