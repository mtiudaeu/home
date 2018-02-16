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

let game_engine = new GameEngine()
const PADDLE_WIDTH = game_engine.unit_width
const PADDLE_HEIGHT = game_engine.unit_height
const SCENE_OFFSET = 0.8

let geometry = new THREE.PlaneBufferGeometry( PADDLE_WIDTH, PADDLE_HEIGHT, 32 );
let material = new THREE.MeshBasicMaterial( {color: 0xffff00, side: THREE.DoubleSide} );
let plane = new THREE.Mesh( geometry, material );

let animate = function () {
    for (let line = 0; line < game_engine.grid_height; line++) {
        for (let column = 0; column < game_engine.grid_width; column++) {
            if(game_engine.grid[game_engine.grid_width*line+column] === 1) {
                let unit = new THREE.Mesh( geometry, material );
                unit.position.x = column*game_engine.unit_width - SCENE_OFFSET
                unit.position.y = line*-game_engine.unit_height + SCENE_OFFSET
                scene.add( unit );
            }
        }
    }
	game_engine.step()

    setTimeout( function() {

        requestAnimationFrame( animate );

    }, 1000 );
	renderer.render(scene, camera);
    while(scene.children.length > 0){ 
        scene.remove(scene.children[0]); 
    }
};

animate();
