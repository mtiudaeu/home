"use strict"

class DrawEngine {
constructor(context2d) {
    this.context2d = context2d;
    this.items = []
}

drawItems() {
    for (let i = 0; i < this.items.length; i++) {
        //MDTMP
        this.drawItem("Hello World",this.items[i].x, this.items[i].y)
    }
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

}

