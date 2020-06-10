#include "BenchinePCH.h"
#include "Components/SpriteComponent.h"
#include "Components/RenderComponent.h"
SpriteComponent::SpriteComponent(Texture2D* pSpriteSheet, uint32_t nrCols, uint32_t nrRows, uint32_t nrZones, float fps)
    : m_pSpriteSheet(pSpriteSheet)
    , m_Cols(nrCols)
    , m_Rows(nrRows)
    , m_Zones(nrZones)
    , m_Fps(fps)
    , m_CurrentElapsed()
    , m_CurrentFrame()
{

}

void SpriteComponent::Initialize()
{
    FRect src{};
    src.Width = GetFrameWidth();
    src.Height = GetFrameHeight();

    src.X = 0; 
    src.Y = src.Height * (m_pSpriteSheet->GetTexture()->GetHeight() / GetFrameHeight()/*Nr of cells in the sheet*/) / m_Zones ;

    m_pSpriteSheet->GetTexture()->SetSource(src);
    GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTexture());
}

void SpriteComponent::Update(float dT)
{
    m_CurrentElapsed += dT;
    if (m_CurrentElapsed >= 1.f / m_Fps)
    {
        ++m_CurrentFrame %= (m_Cols * m_Rows);
        m_CurrentElapsed -= 1.f / m_Fps;


        FRect src{};
        src.Width = GetFrameWidth();
        src.Height = GetFrameHeight();

        src.X = src.Width * (m_CurrentFrame % m_Cols);
        src.Y = src.Height * ((m_CurrentFrame / m_Cols) - 1.f);

        m_pSpriteSheet->GetTexture()->SetSource(src);
        

    }
    GetGameObject()->GetRenderComponent()->AddTexture(m_pSpriteSheet->GetTexture());
}