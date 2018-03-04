"use strict"

window.onload = window.onresize = function() {
    let c = document.getElementById("myCanvas");
    c.width = window.innerWidth;
    c.height = window.innerHeight;

    let ctx = c.getContext("2d");
    ctx.font = "10px Arial";

    c.addEventListener('click', function(event) {
        let x = event.pageX;
        let y = event.pageY;
        drawItem("Hello World", x, y);
    }, false);
}

function drawItem(text, x, y) {
    let c = document.getElementById("myCanvas");
    let ctx = c.getContext("2d");
    let textDimensions = ctx.measureText(text)
    console.log(textDimensions)
    const offset = 10
    drawRectangle(x - offset, y, textDimensions.width + 2*offset, 10+2*offset);
    drawString(text, x, y + 10 + offset);
}

function drawRectangle(x,y,width,height) {
    let c = document.getElementById("myCanvas");
    let ctx = c.getContext("2d");
//FIXME hardcoded positions
    ctx.strokeRect(x, y, width, height);
}

function drawString(text, x, y) {
    let c = document.getElementById("myCanvas");
    let ctx = c.getContext("2d");
//FIXME hardcoded positions
    ctx.fillText(text,x,y); 
}
