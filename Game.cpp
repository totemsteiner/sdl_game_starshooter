#include "pch.h"
#include "Game.hpp"

// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CGame::CGame()
{
	m_pPlayer = NULL;
	m_pSpriteBackground = NULL;
	m_pSpriteAsteroid = NULL;
} // Konstruktor

// Init
//
// Aufgabe: Spieler, Hintergrund und Asteroid initialisieren
//
void CGame::Init()
{
	// Neuen Spieler initialisieren
	m_pPlayer = new CPlayer;
	m_pPlayer->Init();
	m_pPlayer->Reset();

	// Hintergrundbild (Sprite) laden
	m_pSpriteBackground = new CSprite;
	m_pSpriteBackground->Load("Data/Background.bmp");

	// Sprite für Asteroiden laden
	m_pSpriteAsteroid = new CSprite;
	m_pSpriteAsteroid->Load("Data/Asteroid.bmp", 10, 
												64, 64);
	m_pSpriteAsteroid->SetColorKey(255, 0, 255);

	// Timer für Asteroiden zurücksetzen
	m_fAsteroidTimer = 0.0f;

	// Spiel läuft
	m_bGameRun = true;
} // Init

// Quit
//
// Aufgabe: Instanzen freigeben
//
void CGame::Quit()
{
	// Spieler freigeben
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Quit();
		delete (m_pPlayer);
		m_pPlayer = NULL;
	}

	// Hintergrundsprite freigeben
	if (m_pSpriteBackground != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}

	// Asteroidensprite freigeben
	if (m_pSpriteAsteroid != NULL)
	{
		delete (m_pSpriteBackground);
		m_pSpriteBackground = NULL;
	}

} // Quit

// Run
//
// Aufgabe: Hauptschleife des Spiels
//
void CGame::Run()
{
	// Hauptschleife des Spiels durchlaufen
	//
	while (m_bGameRun == true)
	{
		// Events bearbeiten
		ProcessEvents();

		// Framework updaten und Buffer löschen
		g_pFramework->Update();
		g_pFramework->Clear();

		// Hintergrundbild rendern
		m_pSpriteBackground->Render();

		// Spieler updaten und rendern
		m_pPlayer->Update();
		m_pPlayer->Render();

		// Neue Asteroiden hinzufügen
		SpawnAsteroids();

		// Kollisionen prüfen
		CheckCollisions();

		// Asteroiden rendern
		RenderAsteroids();

		// Buffer flippen
		g_pFramework->Flip();

	}

} // Run

// ProcessEvents
//
// Aufgabe: Events bearbeiten
//
void CGame::ProcessEvents()
{
	SDL_Event Event;

	// Gab es ein Event?
	if (SDL_PollEvent(&Event))
	{
		// Ja, also schauen welches
		switch (Event.type)
		{
			// Beenden?
		case (SDL_QUIT):
		{
			m_bGameRun = false;

		} break;


		// Wurde eine Taste gedrückt?
		case (SDL_KEYDOWN):
		{
			switch (Event.key.keysym.sym)
			{
			case (SDLK_ESCAPE):
			{
				// Ja, also Spiel beenden
				m_bGameRun = false;

			} break;
			}
		} break;
		}
	}

} // ProcessEvents

// SpawnAsteroids
//
// Aufgabe: Nach Ablauf einer bestimmten Zeit neuen Asteroiden erzeugen
//
void CGame::SpawnAsteroids()
{
	// Timer für nächsten Asteroiden erhöhen
	m_fAsteroidTimer += g_pTimer->GetElapsed();

	// Wenn eine halbe Sekunde vergangen ist,
	// dann einen neuen Asteroiden erzeugen
	if (m_fAsteroidTimer >= 0.5f)
	{
		// Neuer Asteroid
		CAsteroid Asteroid;

		// Zufällige X-Position
		int XPos = rand() % 736;

		// Asteroid initialisieren
		Asteroid.Init(m_pSpriteAsteroid, static_cast<float>(XPos), -60.0f);

		// Asteroid in Liste einfügen
		m_AsteroidList.push_back(Asteroid);

		// Zeitgeber wieder zurücksetzen
		m_fAsteroidTimer = 0.0f;

	}

} // SpawnAsteroids

// CheckCollisions
//
// Aufgabe: Kollisionen zwischen Asteroiden und Schüssen prüfen
//
void CGame::CheckCollisions()
{
	// Schussliste des Spielers holen
	list<CShot> *ShotList = m_pPlayer->GetShotList();

	// Iteratoren für Asteroiden- und Schussliste
	list<CAsteroid>::iterator ItAsteroid = m_AsteroidList.begin();
	list<CShot>::iterator ItShot;

	// Rects für Asteroiden und Schüsse
	SDL_Rect RectAsteroid;
	SDL_Rect RectShot;

	// Alle Asteroiden durchlaufen
	while (ItAsteroid != m_AsteroidList.end())
	{
		// Rect des Asteroiden holen
		RectAsteroid = ItAsteroid->GetRect();

		// Alle Schüsse durchlaufen
		for (ItShot = ShotList->begin();
			ItShot != ShotList->end();
			++ItShot)
		{
			// Rect des Schusses holen
			RectShot = ItShot->GetRect();
			// Überschneiden sich die Rects?
			if (RectShot.y < RectAsteroid.y + RectAsteroid.h &&
				RectShot.y + RectShot.h > RectAsteroid.y &&
				RectShot.x < RectAsteroid.x + RectAsteroid.w &&
				RectShot.x + RectShot.w > RectAsteroid.x)
			
			{
				// Ja, also gab es eine Kollision. Somit Schuss und
				// Asteroid deaktivieren
				cout << "kollision" << endl;
				ItAsteroid->SetAlive(false);
				ItShot->SetAlive(false);
			}
		}

		// Asteroid löschen, falls deaktiviert
		if (ItAsteroid->IsAlive()) {
			ItAsteroid++;
		}
		else {
			ItAsteroid = m_AsteroidList.erase(ItAsteroid);
		}
			

	}

} // CheckCollision

// RenderAsteroids
//
// Aufgabe: Alle Asteroiden rendern und updaten
//
void CGame::RenderAsteroids()
{
	// Iterator für die Asteroiden-Liste
	std::list<CAsteroid>::iterator It;

	// Asteroiden-Liste durchlaufen
	for (It = m_AsteroidList.begin(); It != m_AsteroidList.end(); ++It)
	{
		// Asteroid rendern
		It->Render();

		// Asteroid updaten
		It->Update();

	}

} // RenderAsteroids

