$(document).ready(function(){
    setHourglass(true);
    $.post("controller", {command : "get_cities"}, function(data)
    {
        alert("Odebrano: " + data);
    });
    var cities = ["Gdańsk", "Warszawa", "Kraków", "Radom", "Poznań", "Sydney", "Melbourne", "Brisbane", "Perth", "Adelaide"];
    updateCitySelections(cities);
    setHourglass(false);

    $("#mainForm").submit(function(event)
    {
        event.preventDefault();
        setHourglass(true);
    });
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

function setHourglass(setOn)
{
    if(setOn)
    {
        $("#waitWindow").slideDown();
    }
    else
    {
        $("#waitWindow").slideUp();
    }
}
