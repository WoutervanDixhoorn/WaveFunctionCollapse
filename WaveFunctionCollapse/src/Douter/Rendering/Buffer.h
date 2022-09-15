#pragma once
#include <vector>
#include <iostream>

#include <glad/glad.h>

namespace Douter {

	class VertexBuffer
	{
	private:
		unsigned int m_Id;
	public:
		VertexBuffer();
		VertexBuffer(size_t size, void* data);

		~VertexBuffer();

		void Data(size_t size, void* data);

		void Bind() const;
		void Unbind() const;
	};

	///  Vertex Array
	enum class AttributeType
	{
		NONE,
		FLOAT,
		INT,
		UINT
	};

	struct VertexAttribute
	{
		int location;
		int count;
		AttributeType type;
	};

	class VertexArray
	{
	private:
		unsigned int m_Id;
		VertexBuffer* m_VertexBuffer;
		int m_VertexSize;
		std::vector<VertexAttribute> m_Attributes;

	public:
		VertexArray();
		~VertexArray();
		
		template<typename T>
		void Add(int count);
		void UpdateAttributes();

		void AddBuffer(VertexBuffer* buffer);

		void Bind() const;
		void Unbind() const;
	};




}