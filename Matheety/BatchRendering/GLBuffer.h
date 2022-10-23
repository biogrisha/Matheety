#pragma once
#include <glad/glad.h>
#include <GraphicStructs/GraphicStructs.h>
#include "InputBuffer.h"

class GLSubBufferProfile //Each drawer must have a profile to use the buffer in its own private region of buffer
{
public:
	void UpdateVertices(unsigned int offset, const std::vector<Vertex>& vertices);
	void UpdateIndices(unsigned int offset, const std::vector<int>& indices);
	unsigned int GetIndexOffset();
	unsigned int GetVOffset();
	bool NeedRewriteData();
	void NeedRewriteData(bool value); //signal for the Render Unit to update the image
	uint32_t GetIndexCount(); // Count of indices to draw
	void SetIndexCount(uint32_t indCountToDraw);// Count of indices to draw

private:
	friend class GLBuffer;
	GLSubBufferProfile(unsigned int vBufId
		, unsigned int indBufId
		, unsigned int vBufSize
		, unsigned int indBufSize
		, InputBuffer<Vertex>* vBuff
		, InputBuffer<int>* indBuff
		, int subBufferId
	);
	GLSubBufferProfile(const GLSubBufferProfile&) = delete;

	bool m_needRewriteData = true;
	unsigned int m_vBufId; //Designates offset in buffer(can be changed by ObjectBuffer in case some subbuffer will be deleted and reorganization of the buffer is needed)
	unsigned int m_indBufId; //Same as above but for the index buffer
	unsigned int m_vBufSize;
	unsigned int m_indBufSize;
	uint32_t m_indCountToDraw;
	int m_subBufferId;
	InputBuffer<Vertex>* m_vBuff = nullptr;
	InputBuffer<int>* m_indBuff = nullptr;
};

class GLBuffer;
class GLBP_wrap
{
public:
	~GLBP_wrap();
	GLBP_wrap() {};
	GLBP_wrap(GLSubBufferProfile* subBuff, GLBuffer*  owner);
	GLBP_wrap(const GLBP_wrap&) = delete;
	GLBP_wrap(GLBP_wrap&& obj);
	GLSubBufferProfile* get();
	GLSubBufferProfile* operator->();
	GLBP_wrap& operator= (GLBP_wrap&& other);
private:
	GLBuffer* m_owner = nullptr;
	GLSubBufferProfile* m_subBuff = nullptr;
};

class GLBuffer
{
public:
	~GLBuffer();
	GLBuffer(uint32_t vBuffsize, uint32_t indBuffsize);
	GLBP_wrap NewSubBuffer(uint32_t vSubBufSize, uint32_t indSubBufSize);
	void DeleteSubBuffer(GLSubBufferProfile** subBuffer);
	unsigned int  GetVAO();
	void Bind();
private:
	unsigned int VAO;
	std::vector<std::unique_ptr<GLSubBufferProfile>> m_subBuffers;
	std::unique_ptr<InputBuffer<Vertex>> m_vBuff{ nullptr };
	std::unique_ptr <InputBuffer<int>> m_indBuff{ nullptr };
};
