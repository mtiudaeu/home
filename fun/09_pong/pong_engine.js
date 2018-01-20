"use strict"

class PongEngine {
	constructor() {
		
		this.ball_pos_y = 0.5
		this.ball_pos_x = 0.5
		this.ball_diameter = 0.15
		this.ball_speed = 0.1
		this.ball_speed_direction = Math.PI * Math.random()

		this.paddle_pos_x = 0.5
		this.paddle_pos_y = 0.05
		this.paddle_width = 0.4
		this.paddle_height = 0.05
	}

	update(time_delta) {
// TODO add params : Move right, move left.
		//console.log("this.ball_pos_y", this.ball_pos_y)
		//console.log("this.ball_pos_x", this.ball_pos_x)
		//console.log("this.paddle_pos_x", this.paddle_pos_x)
	}
}

