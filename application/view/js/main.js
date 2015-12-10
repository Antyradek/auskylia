$(document).ready(function(){
    //TODO polecenie AJAX i ściągnięcie listy miast, rozpakowanie XML i aktualizacja pól HTML. Puki co, twardo wpisana tablica:
    var cities = ["Gdańsk", "Warszawa", "Kraków", "Radom", "Poznań", "Sydney", "Melbourne", "Brisbane", "Perth", "Adelaide"];
    updateCitySelections(cities);

});

///aktualiazcja wyboru miast
function updateCitySelections(cities)
{
    for(var i = 0; i < cities.length; i++)
    {
        var text = "<option>" + cities[i] + "</option>";
        $(".citySelect").append(text);
    }
}
