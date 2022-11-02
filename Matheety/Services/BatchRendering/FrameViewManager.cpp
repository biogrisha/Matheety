#include "FrameViewManager.h"

FrameViewManager::~FrameViewManager()
{
	m_isActive = false;
}

FrameViewManager::FrameViewManager()
{

}

FrameViewBase* FrameViewManager::AddFrameView(std::unique_ptr<FrameViewBase>&& frameViewPtr)
{
	frameViewPtr->SetIdInArray(m_frameViews.size());
	m_frameViews.push_back(std::move(frameViewPtr));
	return m_frameViews.back().get();
}

void FrameViewManager::DeleteFrameView(FrameViewBase** frameViewPtr)
{

	uint32_t id = (*frameViewPtr)->GetIdInArray();//Get pos of frame view in the array of framevies
	*frameViewPtr = nullptr; // assign null to pointer
	if (id == m_frameViews.size() - 1) //if id is the last lement then just pop
	{
		m_frameViews.pop_back();
	}
	else 
	{
		FrameViewBase* lastEl = m_frameViews.back().get();//else get last fv
		lastEl->SetIdInArray(id); //set its id to that of fv to delete
		std::iter_swap(m_frameViews.begin() + id, m_frameViews.end() - 1);//swap
		m_frameViews.pop_back();//pop 
	}
	
}

void FrameViewManager::ProcessAll(GLBuffer* glBuffer)
{

	if(!m_frameViews.empty() && m_isActive && m_updateRequested)
	{
		glBindVertexArray(glBuffer->GetVAO());
		glBuffer->Bind();
		for (auto& frame : m_frameViews)
		{
			frame->UpdateFrame();
		}
		glBindVertexArray(0);
		m_updateRequested = false;
	}
}

bool FrameViewManager::IsActive()
{
	return m_isActive;
}

FrameViewBase::~FrameViewBase()
{
	glDeleteFramebuffers(1, &m_fb_framebuffer);
	glDeleteTextures(1, &m_fb_renderedTexture);
}

FrameViewBase::FrameViewBase(GLsizei width, GLsizei height)
{
	m_fb_width = width;
	m_fb_height = height;
	glGenFramebuffers(1, &m_fb_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fb_framebuffer);
	glGenTextures(1, &m_fb_renderedTexture);
	glBindTexture(GL_TEXTURE_2D, m_fb_renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fb_renderedTexture, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_fb_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_fb_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fb_width, m_fb_height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_fb_rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameViewBase::SetIdInArray(uint32_t id)
{
	m_idInArray = id;
}

uint32_t FrameViewBase::GetIdInArray()
{
	return m_idInArray;
}

uint32_t FrameViewBase::GetId()
{
	return m_id;
}

void FrameViewBase::SetSize(GLsizei width, GLsizei height)
{
	m_fb_width = width;
	m_fb_height = height;
	glBindTexture(GL_TEXTURE_2D, m_fb_renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint FrameViewBase::GetRenderTarget()
{
	return m_fb_renderedTexture;
}

void FrameViewBase::UpdateFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fb_framebuffer);
	GLint aiViewport[4];
	glGetIntegerv(GL_VIEWPORT, aiViewport);
	glViewport(0, 0, m_fb_width, m_fb_height);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& ru : m_renderUnits)
	{
		ru->Update(m_fb_renderedTexture);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	glViewport(aiViewport[0], aiViewport[1], (GLsizei)aiViewport[2], (GLsizei)aiViewport[3]);
}

void FrameViewBase::AddRenderUnit(std::unique_ptr<RenderUnit>&& renderUnit)
{
	m_renderUnits.push_back(std::move(renderUnit));
}



