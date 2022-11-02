#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <Services/GraphicStructs/GraphicStructs.h>
#include <Services/BatchRendering/GLBuffer.h>
#include <Services/Shader/shader_s.h>
#include <Services/3DAuxiliaryFunctions/Camera.h>
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class GlyphLoader
{
public:
	GlyphLoader();
	~GlyphLoader();

	const std::vector<Character>& GetGlyphArray();
private:
	std::vector<Character> m_characters;

};

class TextObject
{
public:
	void UpdateText(const std::string& str, float x, float y, float z, float scale);
private:
	TextObject(const std::string& str, GlyphLoader* glyphLoader, float x, float y,float z, float scale,uint32_t indInArray, bool* changesRequested);
	friend class TextRender;
	std::vector<std::vector<Vertex>> m_glyphVertices;
	std::vector<uint32_t> m_glyphInds;
	GlyphLoader* m_glyphLoader;
	uint32_t m_indInArray = 0;
	bool* m_changesRequested = nullptr;
};

class TextRender
{
public:
	TextRender(GLBP_wrap&& subbuf, GlyphLoader* glyphLoader);
	TextObject* AddText(const std::string& str, float x, float y, float z, float scale);
	void DeleteText(TextObject** txt);
	void Clear();
	void Update();
	void Render(Camera* camera, GlyphLoader* glyphLoader);

private:

	struct VertVec_UpdId_pair
	{
		std::vector<Vertex> glyphVertices;
		uint32_t isUpdated = false;
	};
	std::vector<VertVec_UpdId_pair> m_glyphVertices;
	std::vector<uint32_t> m_glyphInds;
	std::vector<std::unique_ptr<TextObject>> m_textObjs;
	GLBP_wrap m_subbuf;
	std::unique_ptr<Shader> m_shader;

	GlyphLoader* m_glyphLoader;
	int m_countToDraw = 0;
	bool m_changesRequested = true;
};