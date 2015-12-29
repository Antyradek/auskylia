#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP


// proszę bez skrępowania dodawać/usuwać/modyfikować 
// dla modelu liczy się tylko liczba parametrów, nie ma on tak naprawdę pojęcia co konkretnie liczy
// lista jest po to, by wiedzieć, co kontroler przekazuje do modelu

/**
 * \brief  Lista parametrów trasy 
 */
enum class Parameters 
{
        // nazwa        // indeks tablicy 
        COST,           // 0
        TIME,           // 1
        SECURITY,       // 2

        // liczba parametrów (rozmiar tablicy)
        Count           // 3 (proszę pamiętać o tym, jak kompilator numeruje wartości;
                        //    jeśli ostatni parametr ma inną wartość niż indeks,
                        //    trzeba podać liczbę wprost)
};

#endif // PARAMETERS_HPP
