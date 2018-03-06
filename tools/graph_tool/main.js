"use strict"

window.onload = window.onresize = function() {
    let c = document.getElementById("myCanvas");
    c.width = window.innerWidth;
    c.height = window.innerHeight;

    let ctx = c.getContext("2d");
    ctx.font = "10px Arial";

    c.addEventListener('click', function(event) {
        let drawEngine = new DrawEngine(ctx);
        let x = event.pageX;
        let y = event.pageY;
        drawEngine.addItem(x,y);
        drawEngine.drawItems();
    }, false);
}

