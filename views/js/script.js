const artyom = new Artyom();

var inputText;

var micBtn = document.getElementById("mic");
var UserDictation;

micBtn.addEventListener("mousedown", getCommand);
micBtn.addEventListener("mouseup", setCommand);

function getCommand(){
  console.log("getting command");

  UserDictation = artyom.newDictation({
      continuous:true, // Enable continuous if HTTPS connection
      onResult:function(text){
          inputText = text;
          // console.log(inputText);

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

function setCommand(text){
  console.log(UserDictation);
  // console.log("in set");
  // console.log("Text: " + inputText);
  // var submit = document.getElementById('textInput');
  // submit.value = text;

}
