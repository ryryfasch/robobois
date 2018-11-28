const artyom = new Artyom();

var xhr = new XMLHttpRequest();

console.log(artyom);

var inputText;


var UserDictation = artyom.newDictation({
    continuous:true, // Enable continuous if HTTPS connection
    onResult:function(text){
        // Do something with the text
        console.log(text);
        inputText = text;

        updateForm(inputText);
        // let data = {command: text};
        // fetch("http://localhost:3000/", {
        //   method: "POST",
        //   body: JSON.stringify(text)
        // }).then(res => {
        //   console.log("Request complete! response:", res);
        // });

    },
    onStart:function(){
        console.log("Dictation started by the user");
    },
    onEnd:function(){
        alert("Dictation stopped by the user");
    }
});

UserDictation.start();

function updateForm(text){
  var submit = document.getElementById('script');

  submit.value = text
}
