#include "BenchinePCH.h"
#include "Resources/Texture2D.h"

Texture2D::Texture2D(SDL_Texture* pTexture)
	: m_pTexture{ pTexture }
{

}

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}