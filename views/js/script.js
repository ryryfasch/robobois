const artyom = new Artyom();

function startArtyom(){
    console.log("initializing Artyom");
    artyom.initialize({
       lang: "en-GB",
       continuous: false,
       debug: true,
       listen: true
    });
}

artyom.on(['forward']).then(function(i){
    console.log("forward");
        $("#textInput").val("forward");
        $('#button1').trigger('click');
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
artyom.on(['back']).then(function(){
    console.log("back");
    $("#textInput").val("back");
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
artyom.on(['dance']).then(function(){
    console.log("exit");
    $("#textInput").val("dance");
    $('#button1').trigger('click');
});
artyom.on(['reset']).then(function(){
    console.log("reset");
    $("#textInput").val("reset");
    $('#button1').trigger('click');
});


$("#micButton").mousedown(function(){
    startArtyom();
});
$("#micButton").mouseup(function(){

});

$("#forward").click(function(){
    $("#textInput").val("forward");
    $('#button1').trigger('click');
});
$("#left").click(function(){
    $("#textInput").val("left");
    $('#button1').trigger('click');
});
$("#right").click(function(){
    $("#textInput").val("right");
    $('#button1').trigger('click');
});
$("#back").click(function(){
    $("#textInput").val("back");
    $('#button1').trigger('click');
});
$("#grab").click(function(){
    $("#textInput").val("grab");
    $('#button1').trigger('click');
});
$("#dance").click(function(){
    $("#textInput").val("dance");
    $('#button1').trigger('click');
});
$("#reset").click(function(){
    $("#textInput").val("reset");
    $('#button1').trigger('click');
});
