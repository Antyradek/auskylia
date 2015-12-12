///Punkt startowy
$(document).ready(function()
{
    //załaduj lotniska
    loadAirports();

    //event wysłania formularza
    $("#mainForm").submit(function(event)
    {
        event.preventDefault();
        calculate();
    });

    //event zamknięcia okienka błędu
    $("#errorClose").click(function()
    {
        $("#errorWindow").slideUp();
    });
});

///ładuje listę lotnisk
function loadAirports()
{
    setHourglass(true);
    //DEBUG
    data = "<data><response>list</response><airports><airport><name>Sydney</name><iata>SYD</iata></airport><airport><name>Warszawa</name><iata>WAW</iata></airport><airport><name>Gdańsk</name><iata>GDA</iata></airport></airports></data>";
    parseResult(data);
    //DEBUG
    sendData("<data><command>list</command></data>", "Nie udało się pobrać listy lotnisk");
    setHourglass(false);
}

///aktualiazcja wyboru miast
function updateCitySelections($xml)
{
    $xml.find("airports").find("airport").each(function(index)
    {
        var name = $(this).find("name").html();
        var iata = $(this).find("iata").html();
        var text = "<option value='" + iata + "'>" + name + " (" + iata + ")" + "</option>";
        $(".citySelect").append(text);
    });
}

///pokazuje, lub ukrywa klepsydrę
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

///wczytaj początek rezultatu i wykonaj odpowiednią dla niego akcję
function parseResult(data)
{
    var $xml = $($.parseXML(data));
    var $data = $xml.find("data");
    var $command = $data.find("response");
    switch($command.html())
    {
        case "list":
            updateCitySelections($data);
            break;
        //...
        default:
            //TODO informacja o błędnej komendzie
            alert("Błędna komenda: " + $command.html());
    }
}

///pobierz dane z formularza i wyślij
function calculate()
{
    setHourglass(true);
    var start = $("#startCity").val();
    var end = $("#endCity").val();
    var price = $("#priceRange").val();
    var safety = $("#safetyRange").val();
    var comfort = $("#comfortRange").val();
    var time = $("#timeRange").val();
    var xml = "<data><command>calculate</command><start>" + start + "</start><end>" + end + "</end><price>" + price + "</price><safety>" + safety + "</safety><comfort>" + comfort + "</comfort><time>" + time + "</time></data>";
    sendData(xml, "Nie udało się wysłać formularza.");
    setHourglass(false);
}

///wywal oczojebny błąd na ekran
function showError(text)
{
    $("#errorText").text(text);
    $("#errorWindow").slideDown();
}

///wysyła rządanie i przetwarza wynik, lub pokazuje błąd
function sendData(data, errorText)
{
    $.post("controller", {data : data})
    .done(function(data)
    {
        alert("Odebrano: " + data);
        parseResult(data);
    })
    .fail(function()
    {
        showError(errorText);
    });
}
