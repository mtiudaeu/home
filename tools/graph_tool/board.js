"use strict"

class BoardEngine {
constructor(canva) {
    this.canva = canva
    this.context2d = canva.getContext("2d");
    this.context2d.font = "10px Arial";
    this.cards = []
    this.currentText = ""
}

getCardWidth(card) {
    let textDimensions = this.context2d.measureText(card.title);
    //FIXME
    const offset = 10;
    return textDimensions.width + 2*offset; //FIXME
}

getCardHeight() {
//FIXME
    const offset = 10
    return 10+2*offset; //FIXME
}

clearAndDrawAll() {
    this.context2d.clearRect(0, 0, this.canva.width, this.canva.height);
    for (let i = 0; i < this.cards.length; i++) {
        this.drawItem(this.cards[i]);
    }
//FIXME
    this.drawString(this.currentText, 150, 150)
}

drawItem(card) {
    let cardWidth = this.getCardWidth(card);
    let cardHeight = this.getCardHeight();
    //FIXME
    const offset = 10
    this.drawRectangle(card.x - cardWidth/2, card.y - cardHeight/2, cardWidth, cardHeight);
    this.drawString(card.title, card.x- cardWidth/2 + offset, card.y  - cardHeight/2 + 10 + offset);
}

drawRectangle(x,y,width,height) {
    this.context2d.strokeRect(x, y, width, height);
}

drawString(text, x, y) {
    this.context2d.fillText(text,x,y); 
}

addItem(title, x, y) {
    let card = new Card(
        title,
        x,
        y
    )
    this.cards.push(card)
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

