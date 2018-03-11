"use strict"

let canva = document.getElementById("myCanvas");

let drawEngine = new BoardEngine(canva);

window.onload = window.onresize = function() {
    canva.width = window.innerWidth;
    canva.height = window.innerHeight;
    drawEngine.clearAndDrawAll();
}

document.onkeydown = function(event) {
    drawEngine.keyPressed(event.keyCode)
};
canva.addEventListener('click', function(event) {
    let x = event.pageX;
    let y = event.pageY;
    drawEngine.addItem("Hello World", x,y);
    drawEngine.clearAndDrawAll();
}, false);
