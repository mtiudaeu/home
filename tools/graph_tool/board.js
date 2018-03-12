"use strict"

class BoardEngine {
constructor(canva) {
    this.canva = canva
    this.context2d = canva.getContext("2d");
    this.context2d.font = "10px Arial";
    this.cards = []
    this.currentText = ""
}

getCardBounds(card) {
    const TEXT_BORDER = 10; //FIXME

    let textDimensions = this.context2d.measureText(card.title);
    let cardWidth = textDimensions.width + 2*TEXT_BORDER;
    let cardHeight = 3*TEXT_BORDER;
    let cardX = card.x - cardWidth/2;
    let cardY = card.y - cardHeight/2;

    let textX = cardX + TEXT_BORDER;
    let textY = cardY + 10 + TEXT_BORDER;

    let bounds = {
        x:cardX,
        y:cardY,
        width:cardWidth,
        height:cardHeight,
        textX:textX,
        textY:textY
    }
    return bounds;
}

isColliding(card, x,y) {
    let bounds = this.getCardBounds(card);
    if(x < bounds.x) {
        return false;
    }
    else if(y < bounds.y) {
        return false;
    }
    else if(x > (bounds.x + bounds.width)) {
        return false;
    }
    else if(y > (bounds.y + bounds.height)) {
        return false;
    }

    return true;
}


unSelectAll() {
    for (let i = 0; i < this.cards.length; i++) {
        this.cards[i].isSelected = false;
    }
    this.clearAndDrawAll(); //FIXME should be optional
}

beginDrag(x, y) {
    for (let i = 0; i < this.cards.length; i++) {
        if(this.isColliding(this.cards[i], x, y)) {
            this.cards[i].isSelected = true;
            this.cards[i].isDragged = true;
        }
        else {
            this.cards[i].isSelected = false;
            this.cards[i].isDragged = false;
        }
    }
    this.clearAndDrawAll(); //FIXME should be optional

}

stopDrag() {
    for (let i = 0; i < this.cards.length; i++) {
        this.cards[i].isDragged = false;
    }
}

drag(x,y) {
    for (let i = 0; i < this.cards.length; i++) {
        if(this.cards[i].isDragged) {
            this.cards[i].x = x;
            this.cards[i].y = y;
        }
    }
    this.clearAndDrawAll(); //FIXME should be optional
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
    if(card.isSelected) {
        this.context2d.fillStyle = 'blue'; //FIXME should not change often I assume...
        this.context2d.strokeStyle = 'blue'; //FIXME should not change often I assume...
    }
    else {
        this.context2d.fillStyle = 'black'; //FIXME should not change often I assume...
        this.context2d.strokeStyle = 'black'; //FIXME should not change often I assume...
    }

    let bounds = this.getCardBounds(card);
    this.drawRectangle(bounds.x, bounds.y, bounds.width, bounds.height);
    this.drawString(card.title, bounds.textX, bounds.textY);
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

