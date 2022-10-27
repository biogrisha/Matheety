#include "GLBuffer.h"

GLSubBufferProfile::GLSubBufferProfile(unsigned int vBufId, unsigned int indBufId, unsigned int vBufSize, unsigned int indBufSize, InputBuffer<Vertex>* vBuff, InputBuffer<int>* indBuff, int subBufferId) :
	m_vBufId(vBufId), m_indBufId(indBufId), m_vBufSize(vBufSize), m_indBufSize(indBufSize), m_vBuff(vBuff), m_indBuff(indBuff), m_subBufferId(subBufferId)
{
}
void GLSubBufferProfile::UpdateVertices(unsigned int offset, const std::vector<Vertex>& vertices)
{
	if (offset + vertices.size() < m_vBufSize)
	{
		m_vBuff->Update(vertices, GLintptr(offset + m_vBufId));
	}
}

void GLSubBufferProfile::UpdateIndices(unsigned int offset, const std::vector<int>& indices)
{
	if (offset + indices.size() < m_indBufSize)
	{
		m_indBuff->Update(indices, GLintptr(offset + m_indBufId));
	}
}

unsigned int GLSubBufferProfile::GetIndexOffset()
{
	return m_indBufId;
}

unsigned int GLSubBufferProfile::GetVOffset()
{
	return m_vBufId;
}

bool GLSubBufferProfile::NeedRewriteData()
{
	return m_needRewriteData;
}

void GLSubBufferProfile::NeedRewriteData(bool value)
{
	m_needRewriteData = value;
}

uint32_t GLSubBufferProfile::GetIndexCount()
{
	return m_indCountToDraw;
}

void GLSubBufferProfile::SetIndexCount(uint32_t indCountToDraw)
{
	m_indCountToDraw = indCountToDraw;
}

GLBuffer::GLBuffer(uint32_t vBuffsize, uint32_t indBuffsize)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	m_indBuff.reset(new InputBuffer<int>(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(indBuffsize), GL_DYNAMIC_DRAW));
	m_vBuff.reset(new InputBuffer<Vertex>(GL_ARRAY_BUFFER, GLsizeiptr(vBuffsize), GL_DYNAMIC_DRAW));

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

GLBuffer::~GLBuffer()
{
	glDeleteVertexArrays(1, &VAO);
	m_vBuff.reset();
	m_indBuff.reset();
}

GLBP_wrap GLBuffer::NewSubBuffer(uint32_t vSubBufSize, uint32_t indSubBufSize)
{
	GLSubBufferProfile* ret = nullptr;
	if (m_subBuffers.empty())
	{
		auto subbuf = ret = new GLSubBufferProfile(0, 0, vSubBufSize, indSubBufSize, m_vBuff.get(), m_indBuff.get(), 0);
		m_subBuffers.push_back(std::unique_ptr<GLSubBufferProfile>(subbuf));
	}
	else
	{
		auto subbufLast = m_subBuffers.back().get();
		auto subbuf = ret = new GLSubBufferProfile(subbufLast->m_vBufSize + subbufLast->m_vBufId
			, subbufLast->m_indBufSize + subbufLast->m_indBufId
			, vSubBufSize
			, indSubBufSize
			, m_vBuff.get()
			, m_indBuff.get()
			, m_subBuffers.size()
		);
		m_subBuffers.push_back(std::unique_ptr<GLSubBufferProfile>(subbuf));
	}
	return GLBP_wrap(ret,this);
}

void GLBuffer::DeleteSubBuffer(GLSubBufferProfile** subBuffer)
{
	if ((*subBuffer)->m_subBufferId < m_subBuffers.size() - 1)//if it is not a last subbuffer in the array
	{
		auto lastEl = m_subBuffers.back().get();//get last sub buffer
		int indSizeDif = (int)lastEl->m_indBufSize - (int)(*subBuffer)->m_indBufSize;//get the difference in the size of the indexes to adjust subsequent objects after the swap
		int vSizeDif = (int)lastEl->m_vBufSize - (int)(*subBuffer)->m_vBufSize;//same but for vertices
		lastEl->m_indBufId = (*subBuffer)->m_indBufId;//exchange index offset of subbuf in main buffer
		lastEl->m_vBufId = (*subBuffer)->m_vBufId;//exchange vert offset of subbuf in main buffer
		lastEl->m_subBufferId = (*subBuffer)->m_subBufferId;//exchange ids
		std::iter_swap(m_subBuffers.begin() + (*subBuffer)->m_subBufferId, m_subBuffers.end() - 1);//swap itself
		*subBuffer = nullptr;//null old pointer
		m_subBuffers.pop_back();//pop

		if (lastEl->m_subBufferId < m_subBuffers.size() - 1)//if it is not the last element now after pop
		{
			for (auto it = m_subBuffers.begin() + lastEl->m_subBufferId + 1; it != m_subBuffers.end(); it++)//updaate all next subbuffers in vector to preserve consistency of indices
			{
				it->get()->m_indBufId += indSizeDif;//add corresponding difference in offsets
				it->get()->m_vBufId += vSizeDif;
				it->get()->NeedRewriteData(true);

			}
		}
	}
	else
	{
		m_subBuffers.pop_back();
	}
}

unsigned int GLBuffer::GetVAO()
{
	return VAO;
}

void GLBuffer::Bind()
{
	m_indBuff->ForceBindBuffer();
	m_vBuff->ForceBindBuffer();
}

GLBP_wrap::~GLBP_wrap()
{
	if(m_owner && m_subBuff)
		m_owner->DeleteSubBuffer(&m_subBuff);
}

GLBP_wrap::GLBP_wrap(GLSubBufferProfile* subBuff, GLBuffer* owner)
{
	m_owner = owner;
	m_subBuff = subBuff;
}

GLBP_wrap::GLBP_wrap(GLBP_wrap&& obj):m_owner{obj.m_owner},m_subBuff{obj.m_subBuff}
{
	obj.m_owner = nullptr;
	obj.m_subBuff = nullptr;
}

GLSubBufferProfile* GLBP_wrap::get()
{
	return m_subBuff;
}

GLSubBufferProfile* GLBP_wrap::operator->()
{
	return m_subBuff;
}

GLBP_wrap& GLBP_wrap::operator=(GLBP_wrap&& obj)
{
	if (m_owner && m_subBuff)
		m_owner->DeleteSubBuffer(&m_subBuff);
	m_owner = obj.m_owner;
	m_subBuff = obj.m_subBuff;
	obj.m_owner = nullptr;
	obj.m_subBuff = nullptr;
	return *this;
}
