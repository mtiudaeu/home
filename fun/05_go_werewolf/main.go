package main

import (
	"golang.org/x/net/websocket"
	"log"
	"net/http"
)

func websocketHandler(ws *websocket.Conn) {
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

 http.Handle("/", http.FileServer(http.Dir("public")))
 http.Handle("/room/", http.FileServer(http.Dir("public")))
	http.Handle("/ws", websocket.Handler(websocketHandler))

	if err := http.ListenAndServe(":1234", nil); err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}

/*

func api_handle(w http.ResponseWriter, r *http.Request) {
  filename := r.URL.Path[5:]
  api_send_file_content(w, "api_" + filename + ".data")
}
func api_send_file_content(w http.ResponseWriter, filename string) {
  if ( w == nil ) {
    return
  }
  w.Header().Set("Access-Control-Allow-Origin", "*")
  DataFile, err := os.Open(filename)
  defer DataFile.Close()
  if err != nil {
    // File not found, send 404
    http.Error(w, "Invalid Request", 404)
    return
  }
  io.Copy(w, DataFile)
}

func main() {
 http.Handle("/", http.FileServer(http.Dir("public")))

 http.HandleFunc("/api/components", api_handle)
 http.HandleFunc("/api/expand", api_handle)

 http.ListenAndServe(":8000", nil)
}
*/

/*
http.HandleFunc("/static/", func(w http.ResponseWriter, r *http.Request) {
    http.ServeFile(w, r, r.URL.Path[1:])
})
*/
