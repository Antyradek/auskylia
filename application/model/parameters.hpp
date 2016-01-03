#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

/**
 * \brief  Lista parametrów trasy 
 */
enum class Parameters 
{
	// nazwa        // indeks tablicy 
	COST,           // 0
	TIME,           // 1
	SAFETY,         // 2
	COMFORT,        // 3

	// liczba parametrów (rozmiar tablicy)
	Count,          // 4 (proszę pamiętać o tym, jak kompilator numeruje wartości;
	                //    jeśli ostatni parametr ma inną wartość niż indeks,
	                //    trzeba podać liczbę wprost)
};

enum class Limits
{
	NODES_MAX      = 10000,

	MAP_SIZE       = 10000,

	COMFORT_MIN    = 1,
	COMFORT_MAX    = 10,
	COMFORT_RANGE  = COMFORT_MAX - COMFORT_MIN,

	SAFETY_MIN     = 1,
	SAFETY_MAX     = 10,
	SAFETY_RANGE   = SAFETY_MAX - SAFETY_MIN,

	SPEED_MIN      = 1,
	SPEED_MAX      = 10,
	SPEED_RANGE    = SPEED_MAX - SPEED_MIN,
};

#endif // PARAMETERS_HPP
