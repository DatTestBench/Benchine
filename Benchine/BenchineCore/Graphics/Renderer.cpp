#include "BenchinePCH.h"

#include "Resources/Texture2D.h"
#include "glm/geometric.hpp"
#include "Debugging/DebugRenderer.h"

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize(const WindowSettings& windowSettings)
{
	// Why does this function throw errors, and not use the logger, you may ask?
	// As the ImGui logger can't be created if the window creation fails, having the errors logged in the logger would be useless

	// OpenGL versions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Window creation
	m_pWindow = SDL_CreateWindow(
		windowSettings.name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSettings.width,
		windowSettings.height,
		SDL_WINDOW_OPENGL);

	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		throw std::runtime_error(std::string("SDL_GL_CreateContext Error: ") + SDL_GetError());
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_WindowSettings.enableVSync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			throw std::runtime_error(std::string("SDL_GL_SetSwapInterval Error: ") + SDL_GetError());
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowSettings.width, 0, m_WindowSettings.height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, static_cast<int>(m_WindowSettings.width), static_cast<int>(m_WindowSettings.height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_MakeCurrent(m_pWindow, m_pContext);

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_pContext);
	ImGui_ImplOpenGL2_Init();

}

void Renderer::SetupRender() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
}

void Renderer::PresentRender() const
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(m_pWindow);
}

void Renderer::Cleanup()
{	
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_pContext);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}

void Renderer::RenderTexture(GLTextureWrapper* pTexture, const FRect& dest, const FRect& src) const
{
	if (!pTexture->IsCreationOk())
	{
		return;
	}
	
	const auto textureWidth = pTexture->GetWidth();
	const auto textureHeight = pTexture->GetHeight();

	// Determine texture coordinates using srcRect and default destination width and height
	float uvLeft{}, uvRight{}, uvTop{}, uvBottom{};
	float defaultDestWidth{}, defaultDestHeight{};

	if (!(src.width > 0.0f && src.height > 0.0f)) // No src specified
	{
		// Use complete texture
		uvLeft = 0.0f;
		uvRight = 1.0f;
		uvTop = 0.0f;
		uvBottom = 1.0f;

		defaultDestWidth = textureWidth;
		defaultDestHeight = textureHeight;
	}
	else // src specified
	{
		// Convert to the range [0.0, 1.0]
		uvLeft = src.x / textureWidth;
		uvRight = (src.x + src.width) / textureWidth;
		uvTop = (src.y - src.height) / textureHeight;
		uvBottom = src.y / textureHeight;

		defaultDestHeight = src.height;
		defaultDestWidth = src.width;
	}

	// Determine vertex coordinates




	float vertexLeft{}, vertexBottom{}, vertexRight{}, vertexTop{};
	if (!(dest.width > 0.0f && dest.height > 0.0f)) // If no size specified use default size
	{
		vertexLeft = dest.x - defaultDestWidth / 2.f;
		vertexRight = dest.x + defaultDestWidth / 2.f;
		vertexTop = dest.y + defaultDestHeight / 2.f;
		vertexBottom = dest.y - defaultDestHeight / 2.f;
	}
	else
	{
		vertexLeft = dest.x - dest.width / 2.f;
		vertexRight = dest.x + dest.width / 2.f;
		vertexTop = dest.y + dest.height / 2.f;
		vertexBottom = dest.y - dest.height / 2.f;

	}

	// Tell opengl which texture we will use
	glBindTexture(GL_TEXTURE_2D, pTexture->GetId());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(uvLeft, uvBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(uvLeft, uvTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(uvRight, uvTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(uvRight, uvBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}

void Renderer::RenderTexture(GLTextureWrapper* pTexture, const glm::vec2& center, const FRect& src) const
{
	RenderTexture(pTexture, FRect(center.x, center.y, src.width, src.height), src);
}

