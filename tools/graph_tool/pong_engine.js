"use strict"

class PongEngine {
	constructor() {
		
		this.ball_pos_y = 0.0
		this.ball_pos_x = 0.0
		this.ball_diameter = 0.15
		this.ball_speed = 0.1
		this.ball_speed_angle = 2 * Math.PI * Math.random()
        this.ball_dy = Math.sin(this.ball_speed_angle)*this.ball_speed
        this.ball_dx = Math.cos(this.ball_speed_angle)*this.ball_speed

		this.paddle_pos_x = 0
		this.paddle_pos_y = 0.05
		this.paddle_width = 0.4
		this.paddle_height = 0.05
	}

	step() {
		this.ball_pos_y += this.ball_dy
		this.ball_pos_x += this.ball_dx

		if(this.ball_pos_y > 1) {
            this.ball_dy = -this.ball_dy
        }
		if(this.ball_pos_y < -1) {
            this.ball_dy = -this.ball_dy
        }
		if(this.ball_pos_x > 1) {
            this.ball_dx = -this.ball_dx
        }
		if(this.ball_pos_x < -1) {
            this.ball_dx = -this.ball_dx
        }

        
// TODO add inputs : Move right, move left.

	// TODO increase speed as it goes
	// TODO Calculate bounce angle
	// TODO different angle for paddle hit?

		//console.log("this.ball_pos_y", this.ball_pos_y)
		//console.log("this.ball_pos_x", this.ball_pos_x)
		//console.log("this.paddle_pos_x", this.paddle_pos_x)
	}
}

