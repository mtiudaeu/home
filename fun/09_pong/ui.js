"use strict"

//let WIDTH = window.innerWidth
//let HEIGHT = window.innerHeight
const WIDTH = 400
const HEIGHT = 400
const CAMERA_DISTANCE = 2

let scene = new THREE.Scene();
let camera = new THREE.PerspectiveCamera( 75, WIDTH/HEIGHT, 0.1, 1000 );
camera.position.z = CAMERA_DISTANCE;

let renderer = new THREE.WebGLRenderer();
renderer.setSize( WIDTH, HEIGHT );
document.body.appendChild( renderer.domElement );

let pong_engine = new PongEngine()
const CIRCLE_RADIUS = pong_engine.ball_diameter/2
const PADDLE_WIDTH = pong_engine.paddle_width
const PADDLE_HEIGHT = pong_engine.paddle_height

let geometry = new THREE.CircleGeometry( CIRCLE_RADIUS, 32 );
let material = new THREE.MeshBasicMaterial( { color: 0xffff00 } );
let circle = new THREE.Mesh( geometry, material );
scene.add( circle );

geometry = new THREE.PlaneBufferGeometry( PADDLE_WIDTH, PADDLE_HEIGHT, 32 );
material = new THREE.MeshBasicMaterial( {color: 0xffff00, side: THREE.DoubleSide} );
let plane = new THREE.Mesh( geometry, material );
scene.add( plane );

let animate = function () {
	requestAnimationFrame( animate );

//TODO var d = new Date();
//TODO var n = d.getTime();

/*
	if(up) {
		circle.position.y += 0.1;
	}
	else {
		circle.position.y -= 0.1;
	}
*/
	pong_engine.step()

	circle.position.y = pong_engine.ball_pos_y;
	circle.position.x = pong_engine.ball_pos_x;

	renderer.render(scene, camera);
};

animate();
