#include "pch.h"
#include "Framework.hpp"
#include "Game.hpp"
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
int main(int argc, char *argv[])
{
	// Framework initialisieren
	if (g_pFramework->Init(800, 600, 16, true) == false)
		return (0);

	// Neue Instanz des Spiels
	CGame Game;

	// Spiel initialisieren
	Game.Init();

	// Spiel laufen lassen. Diese Funktion läuft so lange,
	// bis das Spiel geschlossen oder die Escape-Taste
	// gedrückt wird
	Game.Run();

	// Spiel beenden
	Game.Quit();

	// Framework beenden
	g_pFramework->Quit();
	g_pFramework->Del();

	return (0);

}
