const artyom = new Artyom();

var inputText;

var micBtn = document.getElementById("mic");

micBtn.addEventListener("mousedown", getCommand);
micBtn.addEventListener("mouseup", setCommand);

function getCommand(){
  console.log("getting command");

  var UserDictation = artyom.newDictation({
      continuous:true, // Enable continuous if HTTPS connection
      onResult:function(text){
          inputText = text;

          // setCommand(inputText);

      },
      onStart:function(){
          console.log("Dictation started by the user");
      },
      onEnd:function(){
          alert("Dictation stopped by the user");
      }
  });

  UserDictation.start();
}

function setCommand(){
  console.log("in set");
  console.log("Text: " + inputText);
  var submit = document.getElementById('textInput');
  submit.value = inputText;

}
