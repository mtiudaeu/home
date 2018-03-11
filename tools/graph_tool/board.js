"use strict"

class BoardEngine {
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
        this.drawItem(this.items[i]);
    }
//FIXME
    this.drawString(this.currentText, 150, 150)
}

drawItem(item) {
    //FIXME
    const offset = 10
    this.drawRectangle(item.x - offset, item.y, item.width, item.height);
    this.drawString(item.title, item.x, item.y + 10 + offset);
}

drawRectangle(x,y,width,height) {
    this.context2d.strokeRect(x, y, width, height);
}

drawString(text, x, y) {
    this.context2d.fillText(text,x,y); 
}

addItem(title, x, y) {
    let item = new Card(
        this.canva,
        title,
        x,
        y
    )
    this.items.push(item)
}

keyPressed(keyCode) {
    console.log(keyCode)
    if(keyCode === 27) {
        // Esc key
        this.currentText = ""
        this.clearAndDrawAll()
    }
    if(keyCode === 13) {
        // Enter key
        //FIXME
        this.addItem(this.currentText, 100, 100)
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

