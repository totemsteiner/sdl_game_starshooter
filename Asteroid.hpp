
#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Sprite.hpp"

class CAsteroid {
public:
	void Init(CSprite *pSpriteAsteroid, float fXPos, float fYPos);
	void Update();
	void Render();
	bool IsAlive() { return m_bIsAlive; }
	void SetAlive(bool bIsAlive) { m_bIsAlive = bIsAlive; }
	SDL_Rect GetRect() { return m_Rect; }

private:
	CSprite *m_pSpriteAsteroid;
	float m_fXPos;
	float m_fYPos;
	float m_fAnimPhase;
	bool m_bIsAlive;
	SDL_Rect m_Rect;
};
#endif