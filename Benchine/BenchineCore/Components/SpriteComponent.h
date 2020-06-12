#pragma once
#include "Components/BaseComponent.h"
#include "Resources/Texture2D.h"
#include "Graphics/GLTextureWrapper.h"
class SpriteComponent final : public BaseComponent
{
public:
    /**
     * Constructor
     * @param pSpriteSheet Texture for the spritesheet
     * @param nrCols Number of collums
     * @param nrRows Number of rows
     * @param nrZones Amount of different zones in the spritesheet, to use for different sprites in spritesheets
     * @param fps Framerate of the animation
     * */
    SpriteComponent(Texture2D* pSpriteSheet, uint32_t nrCols, uint32_t nrRows, uint32_t nrZones, float fps);
    virtual ~SpriteComponent() override = default;
    DEL_ROF(SpriteComponent)

    void Update(float dT) override;


    [[nodiscard]] constexpr auto GetFrameWidth() const noexcept-> float { return m_pSpriteSheet->GetTextureWrapper()->GetWidth() / static_cast<float>(m_Cols); }

    [[nodiscard]] constexpr auto GetFrameHeight() const noexcept-> float { return m_pSpriteSheet->GetTextureWrapper()->GetHeight() / static_cast<float>(m_Rows); }

    [[nodiscard]] constexpr auto GetTextureWrapper() const noexcept-> GLTextureWrapper* { return m_pSpriteSheet->GetTextureWrapper(); }

protected:
    void Initialize() override;

private:
    Texture2D* m_pSpriteSheet;
    uint32_t m_Cols;
    uint32_t m_Rows;
    uint32_t m_Zones;
    float m_Fps;
    float m_CurrentElapsed;
    uint32_t m_CurrentFrame;
};

