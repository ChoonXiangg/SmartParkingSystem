const char reserve[] PROGMEM = R"rawliteral(
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
    #flex-container{
        width:1000px;
        display:flex;
        flex-direction:column;
        justify-content:center;
        align-items:center;
        margin:auto;
    }
    input[type="text"]{
        height:100px;
        width:1000px;
        font-size:50px;
        font-family:"Press Start 2P";
    }
    #flex-container2{
        flex-direction:row;
        align-self:flex-end;
    }
    input[type="submit"]{
        font-size:25px;
        color:white;
        font-family:"Press Start 2P";
        border:none;
        background:none;
    }
    input[type="submit"]:hover{
        cursor:pointer;
    }
    a{
        font-size:25px;
        color:white;
        text-decoration:none;
    }
    #error{
        font-size:25px;
        color:red;
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
        input[type="text"]{
            height:30px;
            width:300px;
            font-size:15px;
            font-family:"Press Start 2P";
        }
    }
    </style>
</head>
<body>
    <h1>Please enter your number plate</h1>
    <form action="/get">
        <div id="flex-container">
            <input type="text" name="numberPlate">
            <br>
            <div id="flex-container2">
                <input type="submit" value="Confirm">
                <a href="/">Back</a>
            </div>
        </div>
    </form>
    <p id="error"></p>
    <script>
    document.addEventListener("DOMContentLoaded",function(){
        const form=document.querySelector('form');
        form.addEventListener('submit',function(event){
            const numberPlateInput=document.querySelector('input[name="numberPlate"]');
            const numberPlateValue=numberPlateInput.value.trim();
            if(numberPlateValue===''){
                event.preventDefault();
                document.getElementById('error').textContent="Please enter a number plate";
            }
        });
    });
    </script>
</body>
</html>
)rawliteral";