#pragma once
#include <memory>
#include <glad/glad.h>
#include <vector>
#include <algorithm>
#include <stdexcept>

class InputBufferBinding
{
public:
	enum class EBindTarg
	{
		CONTENT_ARRAY=0,
		ELEMENT_ARRAY=1
	};
	static uint32_t s_bindIDs[];//EBindTarg designates the array elements in which the bound buffer ids are written
	static unsigned int GetCurrentlyBound(EBindTarg targ)
	{
		return s_bindIDs[(int)targ];
	}
};


template<typename T>
class InputBuffer
{
public:

private:

public:

	InputBuffer(GLenum target, GLsizeiptr size, const std::vector<T>& data, GLenum usage);
	InputBuffer(GLenum target, GLsizeiptr size, GLenum usage);
	InputBuffer(const InputBuffer& other) = delete;
	InputBuffer(InputBuffer&& other) = delete;

	InputBuffer& operator=(const InputBuffer& other) = delete;
	InputBuffer& operator=(const InputBuffer&& other)noexcept = delete;

	~InputBuffer();

	void BindBuffer();
	void ForceBindBuffer();
	void UnbindBuffer();

	void Resize(GLsizeiptr size);
	void Resize(GLsizeiptr size, const T* data);
	void Update(const std::vector<T>& data, GLintptr offset);
	void Update(const T* data, GLintptr offset, GLsizeiptr size);
	void Clear();

	void DeleteBuffer();
private:
	bool m_isAlive = false;
	unsigned int m_ID;
	GLenum m_target;
	GLenum m_usage;
	GLsizeiptr m_size;
	InputBufferBinding::EBindTarg m_target_enum;


	//Debug
#ifdef GRAPHICS_DEBUG
	std::vector<T> deb_data;
	GLBufferTracker* deb_buffTrack;
#endif // GRAPHICS_DEBUG
};


//Member functions
template<typename T>
inline InputBuffer<T>::InputBuffer(GLenum target, GLsizeiptr size, const std::vector<T>& data, GLenum usage)
{
	m_size = size;
	m_target = target;
	switch (m_target)
	{
	case GL_ELEMENT_ARRAY_BUFFER:
		m_target_enum = InputBufferBinding::EBindTarg::ELEMENT_ARRAY;
		break;
	case GL_ARRAY_BUFFER:
		m_target_enum = InputBufferBinding::EBindTarg::CONTENT_ARRAY;
		break;
	default:
		break;
	}
	m_usage = usage;
	glGenBuffers(1, &m_ID);
	m_isAlive = true;
	BindBuffer();
	glBufferData(target, sizeof(T) * size, *data[0], usage);
	

#ifdef GRAPHICS_DEBUG
	deb_buffTrack = GLBufferTracker::getInstance();
	deb_data.assign(data.begin(), data.begin() + size);
	deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG
}

template<typename T>
inline InputBuffer<T>::InputBuffer(GLenum target, GLsizeiptr size, GLenum usage)
{
	m_size = size;
	m_target = target;
	switch (m_target)
	{
	case GL_ELEMENT_ARRAY_BUFFER:
		m_target_enum = InputBufferBinding::EBindTarg::ELEMENT_ARRAY;
		break;
	case GL_ARRAY_BUFFER:
		m_target_enum = InputBufferBinding::EBindTarg::CONTENT_ARRAY;
		break;
	default:
		break;
	}
	m_usage = usage;
	glGenBuffers(1, &m_ID);
	m_isAlive = true;
	BindBuffer();
	glBufferData(target, sizeof(T) * size, NULL, usage);
#ifdef GRAPHICS_DEBUG
	deb_buffTrack = GLBufferTracker::getInstance();
	deb_data.resize(size);
	deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG
}

template<typename T>
inline InputBuffer<T>::~InputBuffer()
{
	if (m_isAlive == true)
	{
		UnbindBuffer();
		glDeleteBuffers(1, &m_ID);
	}
}

template<typename T>
inline void InputBuffer<T>::BindBuffer()
{
	if (m_isAlive == true)
	{
		if (InputBufferBinding::s_bindIDs[(int)m_target_enum] != m_ID)
		{
			glBindBuffer(m_target, m_ID);
			InputBufferBinding::s_bindIDs[(int)m_target_enum] = m_ID;
		}
	}
}

template<typename T>
inline void InputBuffer<T>::ForceBindBuffer()
{
	if (m_isAlive == true)
	{
		
		glBindBuffer(m_target, m_ID);
		InputBufferBinding::s_bindIDs[(int)m_target_enum] = m_ID;
		
	}
}

template<typename T>
inline void InputBuffer<T>::UnbindBuffer()
{
	if (m_isAlive == true)
	{
		if (InputBufferBinding::s_bindIDs[(int)m_target_enum] == m_ID)
		{
			glBindBuffer(m_target, 0);
			InputBufferBinding::s_bindIDs[(int)m_target_enum] = 0;
		}
	}
}

template<typename T>
inline void InputBuffer<T>::Resize(GLsizeiptr size)
{
	if (m_isAlive == true)
	{
		BindBuffer();
		glBufferData(m_target, sizeof(T) * size, NULL, m_usage);

#ifdef GRAPHICS_DEBUG
		deb_data.clear();
		deb_data.resize(size);
		deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG

		m_size = size;
	}
}

template<typename T>
inline void InputBuffer<T>::Resize(GLsizeiptr size, const T* data)
{
	if (m_isAlive == true)
	{
		BindBuffer();
		glBufferData(m_target, sizeof(T) * size, data, m_usage);

#ifdef GRAPHICS_DEBUG
		deb_data.clear();
		deb_data.resize(size);
		deb_data.assign(data, data + size);
		deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG

		m_size = size;
	}
}

template<typename T>
inline void InputBuffer<T>::Update(const std::vector<T>& data, GLintptr offset)
{
	if (m_isAlive == true)
	{
		if (offset + data.size() > m_size)
		{
			throw std::invalid_argument("Not enough buffer space");
		}
		BindBuffer();
		glBufferSubData(m_target, sizeof(T) * offset, sizeof(T) * data.size(), &data[0]);

#ifdef GRAPHICS_DEBUG
		std::copy(data.begin(), data.end(), deb_data.begin() + offset);
		deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG
	}
}

template<typename T>
inline void InputBuffer<T>::Update(const T* data, GLintptr offset, GLsizeiptr size)
{
	if (m_isAlive == true)
	{
		if (offset + size > m_size)
		{
			throw std::invalid_argument("Not enough buffer space");
		}
		BindBuffer();
		glBufferSubData(m_target, sizeof(T) * offset, sizeof(T) * size, data);
#ifdef GRAPHICS_DEBUG
		std::copy(data, data+ size, deb_data.begin() + offset);
		deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG
	}
}

template<typename T>
inline void InputBuffer<T>::Clear()
{
	if (m_isAlive == true)
	{
		BindBuffer();
		glBufferData(m_target, 0, NULL, m_usage);

#ifdef GRAPHICS_DEBUG
		deb_data.clear();
		deb_buffTrack->UpdateBufferDisplay(deb_data);
#endif // GRAPHICS_DEBUG
	}
}

template<typename T>
inline void InputBuffer<T>::DeleteBuffer()
{
	if (m_isAlive == true)
	{
		UnbindBuffer();
		glDeleteBuffers(1, &m_ID);
		m_isAlive = false;
	}

}
