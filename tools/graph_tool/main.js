"use strict"

let c = document.getElementById("myCanvas");
let ctx = c.getContext("2d");
ctx.font = "10px Arial";

let drawEngine = new DrawEngine(ctx);

window.onload = window.onresize = function() {
    c.width = window.innerWidth;
    c.height = window.innerHeight;
    drawEngine.drawItems();
}

document.onkeydown = function(event) {
    console.log(event.keyCode)
};
