package main

import (
	"golang.org/x/net/websocket"
	"log"
	"net/http"
)

func Echo(ws *websocket.Conn) {
	var err error

	for {
		var reply string

		if err = websocket.Message.Receive(ws, &reply); err != nil {
			log.Print("Terminating socket : ", err)
			break
		}

		log.Print("Received back from client: " + reply)
		msg := "Received:  " + reply
		log.Print("Sending to client: " + msg)

		if err = websocket.Message.Send(ws, msg); err != nil {
			log.Print("Terminating socket : ", err)
			break
		}
	}
}

func main() {
	log.SetFlags(log.Lshortfile)

	http.Handle("/", websocket.Handler(Echo))

	if err := http.ListenAndServe(":1234", nil); err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}
