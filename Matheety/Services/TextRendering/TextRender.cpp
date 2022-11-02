#include "TextRender.h"


TextObject::TextObject(const std::string& str, GlyphLoader* glyphLoader, float x, float y, float z, float scale,uint32_t indInArray, bool* changesRequested)
{
    m_indInArray = indInArray;
    m_glyphLoader = glyphLoader;
    m_changesRequested = changesRequested;
	UpdateText(str,x,y,z,scale);
}

void TextObject::UpdateText(const std::string& str, float x, float y, float z, float scale)
{
	m_glyphVertices = std::vector<std::vector<Vertex>>(256);
	m_glyphInds.clear();

    float tempx = 0;
	for (auto it = str.begin(); it != str.end(); it++)
	{
	   char glyphNum = (uint32_t)( * it);


       Character ch = m_glyphLoader->GetGlyphArray()[glyphNum];
       float xpos = tempx + ch.Bearing.x * scale;
       float ypos = -(ch.Size.y - ch.Bearing.y) * scale;
       
       float w = ch.Size.x * scale;
       float h = ch.Size.y * scale;


		m_glyphVertices[glyphNum].push_back({ glm::vec4(x,y,z,0),glm::vec4(xpos,ypos,w,h) });
		if (m_glyphVertices[glyphNum].size() == 1)
		{
			m_glyphInds.push_back(glyphNum);
		}

        tempx += (ch.Advance >> 6) * scale;
	}
    *m_changesRequested = true;
}

TextRender::TextRender(GLBP_wrap&& subbuf, GlyphLoader* glyphLoader)
{
    m_glyphLoader = glyphLoader;
    m_subbuf = std::move(subbuf);
    std::vector<Shader::ShaderData> shData;
    shData.push_back(Shader::ShaderData(Shader::Type::VERTEX, "Shaders\\textShad.vs"));
    shData.push_back(Shader::ShaderData(Shader::Type::GEOMETRY, "Shaders\\textShad.gs"));
    shData.push_back(Shader::ShaderData(Shader::Type::FRAGMENT, "Shaders\\textShad.fs"));

    m_shader.reset(new Shader(shData));
}

TextObject* TextRender::AddText(const std::string& str, float x, float y, float z, float scale)
{
    auto txt = new TextObject(str,m_glyphLoader, x, y, z, scale, m_textObjs.size(), &m_changesRequested);
	m_textObjs.push_back(std::unique_ptr<TextObject>(txt));
    return txt;
}

void TextRender::DeleteText(TextObject** txt)
{
    uint32_t id = (*txt)->m_indInArray;//Get pos of frame view in the array of framevies
    *txt = nullptr; // assign null to pointer
    if (id == m_textObjs.size() - 1) //if id is the last lement then just pop
    {
        m_textObjs.pop_back();
    }
    else
    {
        TextObject* lastEl = m_textObjs.back().get();//else get last fv
        lastEl->m_indInArray = id; //set its id to that of fv to delete
        std::iter_swap(m_textObjs.begin() + id, m_textObjs.end() - 1);//swap
        m_textObjs.pop_back();//pop 
    }
    m_changesRequested = true;
}

void TextRender::Clear()
{
    m_textObjs.clear();
    m_glyphInds.clear();
}

void TextRender::Update()
{
    if (m_changesRequested)
    {
        m_glyphVertices = std::vector<VertVec_UpdId_pair>(256); //clear Glyph/vertex array
        m_glyphInds.clear();//clear Used glyphs ind array

        for (auto& txtObj : m_textObjs)
        {
            for (uint32_t ind : txtObj->m_glyphInds)
            {
                //append vertices of particular glyph to a common array of this glyph
                m_glyphVertices[ind].glyphVertices.insert(m_glyphVertices[ind].glyphVertices.end(), txtObj->m_glyphVertices[ind].begin(), txtObj->m_glyphVertices[ind].end());

                //add index of this glyph to common ind array to mark that iy is used
                if (m_glyphVertices[ind].isUpdated == false)
                {
                    m_glyphInds.push_back(ind);
                    m_glyphVertices[ind].isUpdated = true;
                }


            }
        }

        m_countToDraw = 0;
        for (uint32_t ind : m_glyphInds)
        {
            m_subbuf->UpdateVertices(m_countToDraw, m_glyphVertices[ind].glyphVertices);
            m_countToDraw += m_glyphVertices[ind].glyphVertices.size();
        }
    }
    m_changesRequested = false;

}

void TextRender::Render(Camera* camera, GlyphLoader* glyphLoader)
{
    if (!m_glyphInds.empty())
    {


        glm::mat4 projectionOrth = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
        m_shader->use();
        m_shader->setMat4("projectionOrth", projectionOrth);

        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.5f, 50.0f);
        glm::mat4 view = camera->GetViewMatrix();

        m_shader->setMat4("projection", projection);
        m_shader->setMat4("view", view);

        int offset = 0;
        for (uint32_t ind : m_glyphInds)
        {
        
            glBindTexture(GL_TEXTURE_2D, glyphLoader->GetGlyphArray()[ind].TextureID);
            glDrawArrays(GL_POINTS, m_subbuf->GetVOffset()+ offset, m_glyphVertices[ind].glyphVertices.size());
        
            offset += m_glyphVertices[ind].glyphVertices.size();
        }
        glBindTexture(GL_TEXTURE_2D, 0);

    }
}

GlyphLoader::GlyphLoader()
{
    m_characters.resize(128);
    // FreeType
     // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // find path to font
    std::string font_name = "C:\\Windows\\Fonts\\Arial.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            m_characters[c] = character;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
const std::vector<Character>& GlyphLoader::GetGlyphArray()
{
    return m_characters;
}

GlyphLoader::~GlyphLoader()
{
    for (auto& el : m_characters)
    {
        glDeleteTextures(1, &el.TextureID);
    }
}

