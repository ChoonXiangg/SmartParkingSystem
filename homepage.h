const char homepagePart1[] PROGMEM = R"rawliteral(
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
    h1{
        font-size:50px;
    }
    p{
        font-size:38px;
    }
    a{
        font-size:25px;
        margin:10px;
        color:white;
        text-decoration:none;
        display:block;
    }
    #error{
        font-size:25px;
        color:red;
    }
    </style>
</head>
<body>
    <h1>Smart Parking System<i class="fa-solid fa-square-parking"></i></h1>
    <p>Please select a parking lot</p>
    <a href="/reserve" class="parking-lot">Hynes Yard 
)rawliteral";
const char homepagePart2[] PROGMEM = R"rawliteral(
    </a>
    <a href="/reserve" class="parking-lot">City Centre Car Park Galway 0</a>
    <a href="/reserve" class="parking-lot">Aeventess Parking 0</a>
    <a href="/reserve" class="parking-lot">Cathedral 0</a>
    <a href="/reserve" class="parking-lot">Headford Road 0</a>
    <p id="error"></p>
    <script>
      document.addEventListener("DOMContentLoaded",function(){
          const parkingLots=document.querySelectorAll('.parking-lot');
          parkingLots.forEach(parkingLot=>{
              parkingLot.addEventListener('click',function(event){
                  const availableSpaces=parseInt(parkingLot.textContent.match(/\d+/)[0]);
                  if(availableSpaces===0){
                      event.preventDefault();
                      document.getElementById('error').textContent="Please select a parking lot with available parking spaces";
                  }
              });
          });
      });
    </script>
</body>
</html>
)rawliteral";