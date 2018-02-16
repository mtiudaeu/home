"use strict"

class GameEngine {
	constructor() {
		this.unit_width = 0.4
		this.unit_height = 0.4

		this.grid_width = 5
		this.grid_height = 5
        this.grid = new Array(this.grid_width*this.grid_height)

        for (let line = 0; line < this.grid_height; line++) {
            for (let column = 0; column < this.grid_width; column++) {
                this.grid[this.grid_width*line+column] = 0
            }
            let seed = Math.random() * 4
            let idx = Math.floor(seed)
            this.grid[this.grid_width*line+idx] = 1
        }
	}

	step() {
        //FIXME
        if(this.grid_height<2) {
            alert("AAAH!")
        }
        for (let line = this.grid_height-2; line >= 0; line--) {
            for (let column = 0; column < this.grid_width; column++) {
                this.grid[this.grid_width*(line+1)+column] = this.grid[this.grid_width*line+column]
            }
        }
        for (let column = 0; column < this.grid_width; column++) {
                this.grid[column] = 0
        }
        let seed = Math.random() * 4
        let idx = Math.floor(seed)
        this.grid[+idx] = 1
	}
}

