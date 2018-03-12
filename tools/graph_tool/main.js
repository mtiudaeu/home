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
canva.addEventListener('mousedown', function(event) {
    let x = event.offsetX;
    let y = event.offsetY;
    drawEngine.beginDrag(x, y);
}, false);
canva.addEventListener('mouseup', function(event) {
    drawEngine.stopDrag();
}, false);
canva.addEventListener('mousemove', function(event) {
    let x = event.offsetX;
    let y = event.offsetY;
    drawEngine.drag(x,y);
}, false);
