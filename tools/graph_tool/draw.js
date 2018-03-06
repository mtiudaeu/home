"use strict"

class DrawEngine {
constructor(canva) {
    this.canva = canva
    this.context2d = canva.getContext("2d");
    this.context2d.font = "10px Arial";
    this.items = []
    this.currentText = ""
}

clearAndDrawAll() {
    this.context2d.clearRect(0, 0, this.canva.width, this.canva.height);
    for (let i = 0; i < this.items.length; i++) {
        //MDTMP
        this.drawItem("Hello World",this.items[i].x, this.items[i].y)
    }
//FIXME
    this.drawString(this.currentText, 150, 150)
}

drawItem(text, x, y) {
    let textDimensions = this.context2d.measureText(text)
    const offset = 10
    this.drawRectangle(x - offset, y, textDimensions.width + 2*offset, 10+2*offset);
    this.drawString(text, x, y + 10 + offset);
}

drawRectangle(x,y,width,height) {
//FIXME hardcoded positions
    this.context2d.strokeRect(x, y, width, height);
}

drawString(text, x, y) {
//FIXME hardcoded positions
    this.context2d.fillText(text,x,y); 
}

addItem(x, y) {
    this.items.push({x:x,y:y})
}

keyPressed(keyCode) {
    console.log(keyCode)
    if(keyCode === 27) {
        // Esc key
        this.currentText = ""
        this.clearAndDrawAll()
    }
    if(keyCode >= 65 && keyCode <= 90) {
        // A to Z key
        this.currentText += String.fromCharCode(keyCode)
        this.clearAndDrawAll()
    }
}

}

