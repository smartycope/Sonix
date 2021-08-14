from http.server import BaseHTTPRequestHandler, HTTPServer
import time, json, threading
# from Cope import debug
# from easyOption import Option, createOptionMenu
from enum import Enum, auto
import os, re
from os import path
import pydub
import music_tag as tag

# How many seconds of data to load at a time
LOAD_SEC = 5

hostname = None
port = None
filepath = None
audioData = bytes()
filePos = 0


class Server(BaseHTTPRequestHandler):
    class Status(Enum):
        INACTIVE = 0
        HALTED   = -1
        ACTIVE   = 1
        SERVING  = 2

    def __init__(self, *args, **kwargs):
        if not len(args) and not len(kwargs):
            # print(f'socket = {socket}, adress={address}, otherthing={otherThing}')
            self.status = Server.Status.INACTIVE
            self.readableStatus = "Inactive"
        else:
            super().__init__(*args, **kwargs)


    def start(self, _hostname, _port):
        global hostname, port
        hostname = _hostname
        port = _port
        self.updateStatus(Server.Status.ACTIVE, f'Starting on http://{hostname}:{port}')
        return HTTPServer((hostname, port), Server)


    def updateStatus(self, status, message):
        self.status = status
        self.readableStatus = message
        print(self.readableStatus)


    def do_GET(self):
        global audioData, filePos, filepath

        if filepath:
            # .set_sample_width(1) mangles the data bad for some reason
            response = pydub.AudioSegment.from_file(filepath, start_second=filePos, duration=LOAD_SEC).set_frame_rate(44100).set_channels(2).raw_data
            filePos += LOAD_SEC

        self.send_response(200 if filepath else 204)
        # self.send_header("Content-type", "text/plain") # "audio/wav")
        self.send_header("Content-type", "audio/wav")
        self.end_headers()
        if filepath:
            self.wfile.write(response)


    def do_POST(self):
        global port, audioData, filepath, filepath

        # print("rfile:", '"', self.rfile.read(), '"')

        #* Discern the path they gave
        if str(self.server.server_port) in self.path:
            filepath = self.path[re.search(str(self.server.server_port), self.path).span()[1]:]
        else:
            filepath = self.path

        filepath = re.sub(r'[%][2][0]', ' ', filepath)
        filepath = re.sub(r'[%][2][C]', ",", filepath)

        #* See if that path actually exists
        foundFile = True
        if not path.exists(filepath):
            foundFile = False
            raise FileNotFoundError(f'"{filepath}" isn\'t a valid filepath.\n')

        #* Get the data out of that path
        # self.audioData = pydub.AudioSegment.from_file(filepath)
        self.updateStatus(Server.Status.SERVING, f"Audio file set to {filepath}, serving data...")

        #* Actually respond
        self.send_response(200 if foundFile else 404)
        self.send_header("Content-type", "application/json")
        self.end_headers()

        def chk(val, replace):
            return val if val else replace
        #* Get metadata from the path
        md = tag.load_file(filepath)
        response = json.dumps({ "album":             chk(md['album'].first,          "[Album]"),
                                "albumartist":       chk(md['albumartist'].first,    "[Album Artist]"),
                                "artist":            chk(md['artist'].first,         "[Artist]"),
                                "description":       chk(md['comment'].first,        '[No Description]'),
                                "compilation":       chk(md['compilation'].first,    False),
                                "composer":          chk(md['composer'].first,       '[Composer]'),
                                "discnumber":        chk(md['discnumber'].first,     -1),
                                "genre":             chk(md['genre'].first,          'Audiobook'),
                                "totaldiscs":        chk(md['totaldiscs'].first,     -1),
                                "totaltracks":       chk(md['totaltracks'].first,    -1),
                                "tracknumber":       chk(md['tracknumber'].first,    -1),
                                "title":             chk(md['tracktitle'].first,     '[Title]'),
                                "year":              chk(md['year'].first,           0000),
                                "isrc":              chk(md['isrc'].first,           '[isrc]'),
                                "bitrate":           chk(md['#bitrate'].first,       -1),
                                "length":            chk(md['#length'].first,        -1),
                                "channels":          chk(md['#channels'].first,      -1),
                                "bitspersample":     chk(md['#bitspersample'].first, -1),
                                "samplerate":        chk(md['#samplerate'].first,    -1)
        }, ensure_ascii=False)
        response = re.sub('[n][u][l][l]', '"NULL"', response).encode('raw_unicode_escape')
        self.wfile.write(response)
        # "artwork": {md['artwork'].first.data}
        # "codec": {md['#codec']},


if __name__ == "__main__":
    Server().start('localhost', 8080).serve_forever()

    #* Because why not?
    if self.webServer:
        self.webServer.server_close()

    #* Uncomment this for a non-blocking start
    # self.serveThread = threading.Thread(target=self.webServer.serve_forever)
    # self.serveThread.start()