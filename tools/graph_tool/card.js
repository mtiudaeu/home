"use strict"

class Card {
constructor(
    canva,
    title,
    x,
    y )
{
    this.canva = canva;
    this.context2d = canva.getContext("2d");

    let textDimensions = this.context2d.measureText(title);
    //FIXME
    const offset = 10;
    this.width = textDimensions.width + 2*offset; //FIXME
    this.height = 10+2*offset; //FIXME
    this.title = title;
    this.x = x;
    this.y = y;
}
}

