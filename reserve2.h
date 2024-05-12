const char reserve2Part1[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Parking System</title>
    <link href="https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap" rel="stylesheet">
    <style>
    body{
        background-color:darkblue;
        color:white;
        font-family:"Press Start 2P";
        text-align:center;
    }
    h1{
        font-size:50px;
    }
    p{
        font-size:25px;
    }
    table{
        height:600px;
        width:1000px;
        margin:auto;
    }
    tr{
        height:300px;
        background:linear-gradient(to bottom,lightgrey,grey);
    }
    th{
        width:200px;
        color:black;
    }
    #circleParkingSpace{
        height:50px;
        width:50px;
        border-radius:50px;
        background-color:blue;
        margin:auto;
    }
    .circle{
        height:50px;
        width:50px;
        border-radius:50px;
        background-color:red;
        margin:auto;
    }
    a{
        font-size:25px;
        color:white;
        text-decoration:none;
    }
    @media(max-width:480px){
        table{
            height:180px;
            width:300px;
            margin:auto;
        }
        tr{
            height:90px;
            background:linear-gradient(to bottom,lightgrey,grey);
        }
        th{
            width:60px;
            color:black;
        }
        #circleParkingSpace{
            height:50px;
            width:50px;
            border-radius:50px;
            background-color:blue;
            margin:auto;
        }
        .circle{
            height:50px;
            width:50px;
            border-radius:50px;
            background-color:red;
            margin:auto;
        }
    }
    </style>
</head>
<body>
    <h1>Hello 
)rawliteral";
const char reserve2Part2[] PROGMEM = R"rawliteral(
    </h1>
    <p>Please arrive within 1 hour or reservation will be automatically cancelled</p>
    <p id="timer">Time remaining: <span id="countdown">01:00:00</span></p>
    <p>Your parking space is here</p>
    <table>
        <tr>
            <th>1<div id="circleParkingSpace"></div></th>
            <th>2<div class="circle"></div></th>
            <th>3<div class="circle"></div></th>
            <th>4<div class="circle"></div></th>
            <th>5<div class="circle"></div></th>
        </tr>
        <tr>
            <th>6<div class="circle"></div></th>
            <th>7<div class="circle"></div></th>
            <th>8<div class="circle"></div></th>
            <th>9<div class="circle"></div></th>
            <th>10<div class="circle"></div></th>
        </tr>
    </table>
    <br>
    <a href="/dht11">View temperature and humidity graph</a>
    <br>
    <a href="/" id="back"></a>
    <script>
    var endTime=new Date();
    endTime.setMinutes(endTime.getMinutes()+1);
    var timerInterval=setInterval(updateCountdown,1000);
    function updateCountdown(){
        var currentTime=new Date();
        var timeDifference=endTime-currentTime;
        var hours=Math.floor((timeDifference%(1000*60*60*24))/(1000*60*60));
        var minutes=Math.floor((timeDifference%(1000*60*60))/(1000*60));
        var seconds=Math.floor((timeDifference%(1000*60))/1000);
        hours=(hours<10)?"0"+hours:hours;
        minutes=(minutes<10)?"0"+minutes:minutes;
        seconds=(seconds<10)?"0"+seconds:seconds;
        document.getElementById("countdown").innerText=hours+":"+minutes+":"+seconds;
        if(timeDifference<=0){
            clearInterval(timerInterval);
            document.getElementById("countdown").innerText="00:00:00";
            document.getElementById("timer").innerText="Reservation cancelled";
            document.getElementById("back").innerText="Back";
            var xhttp=new XMLHttpRequest();
            xhttp.open("GET","/timerEnd",true);
            xhttp.send();
        }
    }
    updateCountdown();
    </script>
    </body>
</html>
)rawliteral";