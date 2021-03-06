var url = "server";
var isWorking = false;
var progressInterval;
var airportsMap = {};

///Punkt startowy
$(document).ready(function()
{
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

    $("#stopButton").click(function()
    {
        stopCalc();
    });

    //załaduj lotniska
    loadAirports();

});

///ładuje listę lotnisk
function loadAirports()
{
    sendData("<data><command>list</command></data>", "Nie można pobrać listy lotnisk");
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
        airportsMap[iata] = name;
    });
}


///pokazuje, lub ukrywa klepsydrę
function setHourglass(setOn)
{
    if(setOn)
    {
        return $("#waitWindow").slideDown().promise();
    }
    else
    {
        return $("#waitWindow").slideUp().promise();
    }
}

///wczytaj początek rezultatu i wykonaj odpowiednią dla niego akcję
function parseResult(data)
{
	//alert("Odebrano: \n" + data);
    try
    {
        var $xml = $($.parseXML(data));
    }
    catch(e)
    {
        showError("Błąd odczytu XML", e.message);
        setHourglass(false);
        return;
    }
    var $data = $xml.find("data");
    var $command = $data.find("response");
    switch($command.html())
    {
        case "list":
            updateCitySelections($data);
            break;
        case "failture":
            showServerError($data);
            break;
        case "progress":
            updateProgress($data);
            break;
        case "success":
            showSolution($data);
            break;
        //...
        default:
            showError("Błędna komenda", $command.html());
    }
}

///aktualizacja stanu wykonywania obliczeń
function updateProgress($xml)
{
    if(isWorking)
    {
        var prog = $xml.find("progress").html();
        $("#progressBar").val(prog);
    }
    else
    {
        isWorking = true;
        $("#progressWindow").slideDown();
        $("#submitForm").slideUp();
        setHourglass(true);
        progressInterval = setInterval(function()
        {
            $.ajax({
                type: "POST",
                url: url,
                data: "<data><command>status</command></data>"
            })
            .done(function(resp)
            {
                parseResult(resp);
            })
            .fail(function()
            {
                showError("Błąd wysyłania", "Błąd sprawdzania stanu obliczeń");
            });
        }, 2000);
    }

}

///pobierz dane z formularza i wyślij
function calculate()
{
    $("#solutionWindow").slideUp();
    var start = $("#startCity").val();
    var end = $("#endCity").val();
    var price = $("#priceRange").val();
    var safety = $("#safetyRange").val();
    var comfort = $("#comfortRange").val();
    var time = $("#timeRange").val();
    var xml = "<data><command>calculate</command><start>" + start + "</start><end>" + end + "</end><price>" + price + "</price><safety>" + safety + "</safety><comfort>" + comfort + "</comfort><time>" + time + "</time></data>";
    sendData(xml, "Nie udało się wysłać formularza z danymi do obliczeń");
}

///wywal oczojebny błąd na ekran
function showError(title, text)
{
    $("#errorTitle").html(title);
    $("#errorText").html(text);
    $("#errorWindow").slideDown();
}

///wysyła rządanie i przetwarza wynik, lub pokazuje błąd
function sendData(data, error)
{
    setHourglass(true)
    .done(function()
    {
        return $.ajax({
            type: "POST",
            url: url,
            data: data
        })
        .done(function(resp)
        {
            parseResult(resp);
            setHourglass(false);
        })
        .fail(function()
        {
            showError("Błąd wysyłania",error);
            setHourglass(false);
        });
    });

}

//pokazuje błąd serwera
function showServerError($xml)
{
    stopRefresh();
    setHourglass(false);
    showError("Błąd serwera" ,$xml.find("cause").html());
}

//zatrzymaj odświeżanie statusu
function stopRefresh()
{
    isWorking = false;
    clearInterval(progressInterval);
    $("#progressWindow").slideUp();
    $("#submitForm").slideDown();
}

//zatrzymaj obliczenia
function stopCalc()
{
    sendData("<data><command>stop</command></data>", "Nie można zaktualizować stanu obliczeń");
}

//pokaż wynik
function showSolution($xml)
{
    stopRefresh();
	$("#solution").html("");
    $xml.find("airports").find("airport").each(function(index)
    {
        var iata = $(this).find("iata").html();
        var name = airportsMap[iata];
        var inner = $("#solution").html();
        inner += "<p class='solutionAirport'>" + name + " (" + iata + ")</p>";
        $("#solution").html(inner);
    });
    var price = $xml.find("price").html();
    var safety = $xml.find("safety").html();
    var comfort = $xml.find("comfort").html();
    var time = $xml.find("time").html();
    $("#solutionPrice").html(price);
    $("#safetyMeter").val(safety);
    $("#comfortMeter").val(comfort);
    $("#solutionTime").html(time);
    $("#solutionWindow").slideDown();
}
