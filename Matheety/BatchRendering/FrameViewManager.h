#pragma once
#include<vector>
#include<list>
#include<map>
#include <memory>
#include <Shader/shader_s.h>
#include "RenderUnit.h"
#include "GLBuffer.h"

class FrameViewBase
{
private:
	static uint32_t GenId()
	{
		static uint32_t id = 0;
		return ++id;
	}
public:
	virtual~FrameViewBase();
	FrameViewBase(GLsizei width,GLsizei height);

	void SetIdInArray(uint32_t id); //used by FrameViewManager to delete fast
	uint32_t GetIdInArray(); //used by FrameViewManager to delete fast

	uint32_t GetId(); //used by ObjectTracingAttributes to identify which attributes

	void SetSize(GLsizei width, GLsizei height);
	GLuint GetRenderTarget();
	void UpdateFrame();//traverse through ru and calls update
	void AddRenderUnit(std::unique_ptr<RenderUnit>&& renderUnit);
private:
	uint32_t m_idInArray;

protected:
	uint32_t m_id = GenId();
	std::vector<std::unique_ptr<RenderUnit>> m_renderUnits;
	//FrameBuffer related
	GLsizei m_fb_width = 0;
	GLsizei m_fb_height = 0;
	GLuint m_fb_renderedTexture;
	unsigned int m_fb_framebuffer = 0;
	unsigned int m_fb_rbo;
}; 




class FrameViewManager 
{
public:
	~FrameViewManager();
	FrameViewManager();
	FrameViewBase* AddFrameView(std::unique_ptr<FrameViewBase>&& frameViewPtr);
	void DeleteFrameView(FrameViewBase** frameViewPtr);
	void ProcessAll(GLBuffer* glBuffer);
	bool IsActive();

	void RequestUpdate()
	{
		m_updateRequested = true;
	}
private:
	std::vector< std::unique_ptr<FrameViewBase>> m_frameViews;
	bool m_isActive = true;
	bool m_updateRequested = true;
};
