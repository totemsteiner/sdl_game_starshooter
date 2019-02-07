#ifndef GAME_HPP
#define GAME_HPP
#include "pch.h"
#include "Player.hpp"
#include "Asteroid.hpp"

class CGame
{
public:
	CGame();

	void Init();
	void Run();
	void Quit();

private:
	void ProcessEvents();
	void SpawnAsteroids();
	void RenderAsteroids();
	void CheckCollisions();

	CPlayer *m_pPlayer;             // Spieler-Instanz
	CSprite *m_pSpriteBackground;   // Sprite für den Hintergrund
	CSprite *m_pSpriteAsteroid;     // Sprite für die Asteroiden
	float    m_fAsteroidTimer;      // Zeitgeber für nächsten Asteroiden
	bool     m_bGameRun;            // Läuft das Spiel noch?
	list<CAsteroid> m_AsteroidList; // Liste der Asteroiden

};

#endif
