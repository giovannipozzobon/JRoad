#include <stdint.h>

// Funzione per verificare se un bit specifico è impostato in una variabile
uint8_t bit_check(uint8_t var, uint8_t pos)
{
	// Crea una maschera con un bit impostato nella posizione specificata
	uint8_t mask = 1 << pos;

	// Utilizza l'operatore AND bitwise per controllare il bit nella variabile
	if (var & mask)
	{
		return 1; // Il bit è impostato
	}
	else
	{
		return 0; // Il bit non è impostato
	}
}
