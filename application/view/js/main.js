$(document).ready(function(){
    setHourglass(true);
    //DEBUG
    data = "<data><response>list</response><airports><airport><name>Sydney</name><iata>SYD</iata></airport><airport><name>Warszawa</name><iata>WAW</iata></airport><airport><name>Gdańsk</name><iata>GDA</iata></airport></airports></data>";
    parseResult(data);
    //DEBUG
    $.post("controller", {data : "<data><command>list</command></data>"}, function(data)
    {
        alert("Odebrano: " + data);
        //TODO tymczasowo
        data = "<data><response>list</response><airports><airport><name>Sydney</name><iata>SYD</iata></airport><airport><name>Warszawa</name><iata>WAW</iata></airport><airport><name>Gdańsk</name><iata>GDA</iata></airport></airports></data>";
        //TODO
        parseResult(data);
    });
    setHourglass(false);

    $("#mainForm").submit(function(event)
    {
        event.preventDefault();
        setHourglass(true);
    });
});

///aktualiazcja wyboru miast
function updateCitySelections($xml)
{
    $xml.find("airports").find("airport").each(function(index)
    {
        var name = $(this).find("name").html();
        var iata = $(this).find("iata").html();
        var text = "<option>" + name + " (" + iata + ")" + "</option>";
        $(".citySelect").append(text);
    });
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
