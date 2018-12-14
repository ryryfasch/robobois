const artyom = new Artyom();

var inputText = '';
var commands = [];

function startArtyom(){
    console.log("initializing Artyom");
    artyom.initialize({
       lang: "en-GB",
       continuous: false,
       debug: true,
       listen: true
    });
}

artyom.on(['forward','for']).then(function(i){
    switch (i) {
        case 0:
            console.log("forward");
            $("#textInput").val("forward");
        break;
        case 1:
            console.log("foward");
        break;
    }
});
artyom.on(['left']).then(function(){
    console.log("left");
    $("#textInput").val("left");
    $('#button1').trigger('click');
});
artyom.on(['right']).then(function(){
    console.log("right");
    $("#textInput").val("right");
    $('#button1').trigger('click');
});
artyom.on(['stop']).then(function(){
    console.log("stop");
    $("#textInput").val("stop");
    $('#button1').trigger('click');
});
artyom.on(['grab']).then(function(){
    console.log("grab");
    $("#textInput").val("grab");
    $('#button1').trigger('click');
});
artyom.on(['exit']).then(function(){
    console.log("exit");
    $("#textInput").val("exit");
    $('#button1').trigger('click');
});


$("#micButton").mousedown(function(){
    startArtyom();
});
$("#micButton").mouseup(function(){

});

// function updateForm(command){
//     console.log("in update form: ");
//     console.log(command);
//     $("textInput").val(command);
// }
