"use strict"

window.onload = window.onresize = function() {
    let c = document.getElementById("myCanvas");
    c.width = window.innerWidth;
    c.height = window.innerHeight;

    let ctx = c.getContext("2d");
    ctx.font = "10px Arial";

    drawRectangle()
    drawString()
}

function drawRectangle() {
    let c = document.getElementById("myCanvas");
    let ctx = c.getContext("2d");
//FIXME hardcoded positions
    ctx.strokeRect(100, 100, 100, 100);
}

function drawString() {
    let c = document.getElementById("myCanvas");
    let ctx = c.getContext("2d");
//FIXME hardcoded positions
    ctx.fillText("Hello World",100,100); 
}
