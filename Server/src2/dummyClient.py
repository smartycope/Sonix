import requests, os, re, json, music_tag, pydub
from pydub.playback import play
import io

buffer = io.BytesIO()

file = '/home/marvin/Media/Audiobooks/Dragons Egg-Cheela, Book 1.m4b'
metadata = requests.post(f"http://localhost:8080{file}")



for i in range(10):
    resp = requests.get(f"http://localhost:8080")
    buffer.write(resp.content)


play(pydub.AudioSegment(data=buffer.getvalue(), sample_width=2, frame_rate=44100, channels=2))
