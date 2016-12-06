#!/usr/bin/env python
#
# This is a modified version of a demo socket server provide
# in vim 8.0.
#
# Server that will accept connections from a Vim channel.
# Run this server and then in Vim you can open the channel:
#  :let handle = ch_open('localhost:8765')
#
# Then Vim can send requests to the server:
#  :let response = ch_sendexpr(handle, 'hello!')
#
# And you can control Vim by typing a JSON message here, e.g.:
#   ["ex","echo 'hi there'"]
#
# There is no prompt, just type a line and press Enter.
# To exit cleanly type "quit<Enter>".
#
# See ":help channel-demo" in Vim.
#
# This requires Python 2.6 or later.

from __future__ import print_function
import json
import socket
import sys
import threading
import getopt
import time

try:
    # Python 3
    import socketserver
except ImportError:
    # Python 2
    import SocketServer as socketserver

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

SEND_TO_VIM = "send_to_vim"
HOST, PORT = "localhost", 8765
socket_array = [];
DEBUG = False

def LOG_DEBUG(msg):
    if DEBUG:
        print(msg)

class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):

    def handle(self):
        LOG_DEBUG("=== socket opened ===")
        global socket_array
        socket_array.append(self.request)
        while True:
            try:
                data = self.request.recv(4096).decode('utf-8')
            except socket.error:
                LOG_DEBUG("=== socket error ===")
                break
            except IOError:
                LOG_DEBUG("=== socket closed ===")
                break
            if data == '':
                LOG_DEBUG("=== socket closed ===")
                break
            LOG_DEBUG("received: {0}".format(data))
            try:
                decoded = json.loads(data)
            except ValueError:
                LOG_DEBUG("json decoding failed")
                decoded = [-1, '']

            if decoded[0] == SEND_TO_VIM:
                # Sending to vim
                encoded = json.dumps([decoded[1],decoded[2]])
                LOG_DEBUG("sending {0}".format(encoded))
                for s in socket_array:
                    s.sendall(encoded.encode('utf-8'))
            elif decoded[0] >= 0:
                # Sent from vim
                # Send a response if the sequence number is positive.
                # Negative numbers are used for "eval" responses.
                if decoded[1] == 'hello!':
                    response = "got it"
                else:
                    response = "what?"
                encoded = json.dumps([decoded[0], response])
                LOG_DEBUG("sending {0}".format(encoded))
                self.request.sendall(encoded.encode('utf-8'))

        socket_array.remove(self.request)

def run_vim_server():
    server = ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler)
    ip, port = server.server_address

    # Start a thread with the server -- that thread will then start one
    # more thread for each request
    server_thread = threading.Thread(target=server.serve_forever)

    # Exit the server thread when the main thread terminates
    server_thread.daemon = True
    server_thread.start()
    LOG_DEBUG("Server loop running in thread: " +  server_thread.name)

    LOG_DEBUG("Listening on port {0}".format(PORT))
    while True:
        if DEBUG is True:
            typed = sys.stdin.readline()
            if "quit" in typed:
                LOG_DEBUG("Goodbye!")
                break
            LOG_DEBUG("sending {0}".format(typed))
            for s in socket_array:
                s.sendall(typed.encode('utf-8'))
        else:
            time.sleep(10)

    server.shutdown()
    server.server_close()

def args_print_usage():
    print("Usage : python vim-server.py")
    print("-h : help")
    print("--debug : Enable debugging and manually send command to vim")

def args_read(argv):
   try:
      opts, args = getopt.getopt(argv,"h",["debug"])
   except getopt.GetoptError:
      args_print_usage()
      sys.exit(1)
   for opt, arg in opts:
      if opt == '-h':
         args_print_usage()
         sys.exit()
      elif opt in ("--debug"):
         DEBUG = True

if __name__ == "__main__":
   args_read(sys.argv[1:]) 
   run_vim_server() 

# TODO List
# -In args_read : Add -p option to chose port.
# -Change print for log into file.



