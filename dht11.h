const char dht11[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Parking System</title>
    <link href="https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap" rel="stylesheet">
    <script src="https://kit.fontawesome.com/ca435ff6ff.js" crossorigin="anonymous"></script>
    <style>
    body{
        background-color:darkblue;
        color:white;
        font-family:"Press Start 2P";
        text-align:center;
    }
    #flex-container{
        width:450px;
        display:flex;
        flex-direction:column;
        justify-content:center;
        align-items:center;
        margin:auto;
    }
    a{
        font-size:25px;
        color:white;
        text-decoration:none;
        align-self:flex-end;
    }
    @media(max-width:480px){
        #flex-container{
            width:300px;
            display:flex;
            flex-direction:column;
            justify-content:center;
            align-items:center;
            margin:auto;
        }
        .thingspeak{
          width:300px;
          height:173px;
        }
    }
    </style>
</head>
<body>
    <h1>Temperature and Humidity Graph</h1>
    <div id="flex-container">
        <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2499268/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" class="thingspeak"></iframe>
        <br>
        <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2499268/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15" class="thingspeak"></iframe>
        <br>
        <a href="/reserve2">Back</a>
    </div>
</body>
</html>
)rawliteral";