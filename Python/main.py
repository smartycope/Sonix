# ctypes_test.py
import ctypes
import pathlib
import numpy as np

import ctypes
from ctypes import *

from scipy.io import wavfile

import os
import pyaudio
import wave
import time

DIR = os.path.dirname(__file__)

'''
# Defining the python type that represents the C SmartString
# It must extend the 'Structure' class
# Structure, c_uint, c_char_p, etc. were imported from ctypes
class SmartString(Structure):
    _fields_=[("string_len",c_uint),
              ("alloc_len",c_uint),
              ("str",c_char_p),
              ("str_terminator", c_char_p)]



# Defining pointer to the SmartString_new() function
SmartString_new = smartstring_lib.SmartString_new

# Declaring the function return type - a pointer to a SmartString object - just like in the C code
SmartString_new.restype = POINTER(SmartString)

# Declaring list of parameter types. In this case, the list contains only one item,
# as the function has only one parameter
SmartString_new.argtypes = [c_char_p]

# Calling the SmartString_new() function. Expecting to get a pointer to SmartString object into 'my_str'
# The API requires a MUTABLE string, so create_string_buffer() is used here
# The reference to this string is not saved, as I don't care if it is modified by the C code
my_str = SmartString_new(create_string_buffer('my nice string'))

# Printing fields of the dereferenced returned value (dereferencing is done using '.contents')
print my_str.contents.string_len
print my_str.contents.alloc_len
print my_str.contents.str
print my_str.contents.str_terminator
'''


class sonicStreamStruct(Structure):
    _feilds_ = [("inputBuffer", POINTER(c_short)), # *short
                ("outputBuffer", POINTER(c_short)), # *short
                ("pitchBuffer", POINTER(c_short)), # *short
                ("downSampleBuffer", POINTER(c_short)), # *short
                ("speed", c_float),
                ("volume", c_float),
                ("pitch", c_float),
                ("rate", c_float),
                ("oldRatePosition", c_int),
                ("newRatePosition", c_int),
                ("useChordPitch", c_int),
                ("quality", c_int),
                ("numChannels", c_int),
                ("inputBufferSize", c_int),
                ("pitchBufferSize", c_int),
                ("outputBufferSize", c_int),
                ("numInputSamples", c_int),
                ("numOutputSamples", c_int),
                ("numPitchSamples", c_int),
                ("minPeriod", c_int),
                ("maxPeriod", c_int),
                ("maxRequired", c_int),
                ("remainingInputToCopy", c_int),
                ("sampleRate", c_int),
                ("prevPeriod", c_int),
                ("prevMinDiff", c_int),
                ("avePower", c_float)]


sonicLib = ctypes.CDLL(DIR + '/libsonic.so.0.3.0')
sonicStream = POINTER(sonicStreamStruct)

BUFFER_SIZE = 2048
audiobookWav = '/home/marvin/Media/Audiobooks/Snapshot.wav'
audiobookOut = '/home/marvin/Media/Audiobooks/Snapshot_test.wav'


sonicCreateStream = sonicLib.sonicCreateStream
sonicCreateStream.restype = sonicStream
sonicCreateStream.argtypes = [c_int, c_int]

sonicSetSpeed = sonicLib.sonicSetSpeed
sonicSetSpeed.argtypes = [sonicStream, c_float]

sonicSetPitch = sonicLib.sonicSetPitch
sonicSetPitch.argtypes = [sonicStream, c_float]

sonicSetRate = sonicLib.sonicSetRate
sonicSetRate.argtypes = [sonicStream, c_float]

sonicSetVolume = sonicLib.sonicSetVolume
sonicSetVolume.argtypes = [sonicStream, c_float]

sonicSetChordPitch = sonicLib.sonicSetChordPitch
sonicSetChordPitch.argtypes = [sonicStream, c_int]

sonicSetQuality = sonicLib.sonicSetQuality
sonicSetQuality.argtypes = [sonicStream, c_int]

sonicFlushStream = sonicLib.sonicFlushStream
sonicFlushStream.argtypes = [sonicStream]

sonicWriteShortToStream = sonicLib.sonicWriteShortToStream
sonicWriteShortToStream.restype = c_int
sonicWriteShortToStream.argtypes = [sonicStream, POINTER(c_short), c_int]
# sonicWriteShortToStream.argtypes = [sonicStream, ctypes.ARRAY(c_short, BUFFER_SIZE), c_int]

sonicReadShortFromStream = sonicLib.sonicReadShortFromStream
sonicReadShortFromStream.restype = c_int
sonicReadShortFromStream.argtypes = [sonicStream, POINTER(c_short), c_int]
# sonicReadShortFromStream.argtypes = [sonicStream, ctypes.ARRAY(c_short, BUFFER_SIZE), c_int]

sonicDestroyStream = sonicLib.sonicDestroyStream
sonicDestroyStream.argtypes = [sonicStream]

#open a wav format music
f = wave.open(audiobookWav, "rb")
#instantiate PyAudio
p = pyaudio.PyAudio()

stream = None
channels = 1
sStream = None

def audioCallback(in_data, framesNeeded, time_info, status):
    global channels, sStream
    # data = wf.readframes(framesNeeded)
    transportBuffer = ctypes.pointer(c_short)
    fileData = f.readframes(framesNeeded)

    # print(type(fileData))
    # print(type(fileData[0]))

    data = bytes()

    #play stream
    while fileData:
        samplesWritten = sonicWriteShortToStream( sStream, cast(fileData,  POINTER(c_short)), framesNeeded)
        samplesRead    = sonicReadShortFromStream(sStream, transportBuffer, c_int(framesNeeded))
        # wavStream.write(np.frombuffer(transportBuffer, c_short, BUFFER_SIZE))
        data += transportBuffer # f.readframes(framesNeeded)

    return (data, pyaudio.paContinue)


def initStream(p, wf):
    global channels, stream

    # open stream using callback (3)
    stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                    channels=wf.getnchannels(),
                    rate=wf.getframerate(),
                    output=True,
                    stream_callback=audioCallback)

    channels = wf.getnchannels()

    # start the stream (4)
    stream.start_stream()



def done(stream, p, f):
    sonicDestroyStream(stream)

    # stop stream (6)
    stream.stop_stream()
    stream.close()
    f.close()

    # close PyAudio (7)
    p.terminate()


def initSonic(f, speed, pitch, rate, volume, quality, emulateChordPitch):
    global sStream
    # def runSonic(inFileName: str, outFileName: str, speed: c_float, pitch: c_float, rate: c_float, volume: c_float,
            #  outputSampleRate: c_int, emulateChordPitch: c_int, quality: c_int, enableNonlinearSpeedup: c_int,
            #  computeSpectrogram: c_int, numRows: c_int, numCols: c_int):

    # samplerate, data = wavfile.read(audiobookWav)
    #open stream
    # wavStream = p.open(format = p.get_format_from_width(f.getsampwidth()),
    #                 channels = f.getnchannels(),
    #                 rate = f.getframerate(),
    #                 output = True)


    # sStream = sonicStream()

    '''
    # samplerate = c_int(samplerate)
    #define stream chunk
    chunk = 4096

    # inBuffer = c_short() * BUFFER_SIZE
    # inBuffer  = ctypes.cast(_inBuffer, POINTER(c_short))
    arr = c_short * BUFFER_SIZE
    inBuffer  = arr(*((0,) * BUFFER_SIZE))
    # inBuffer  = POINTER(c_short) # short[]
    # outBuffer = c_short() * BUFFER_SIZE
    # outBuffer = ctypes.cast(_outBuffer, POINTER(c_short))

    outBuffer = arr(*((0,) * BUFFER_SIZE))
    # outBuffer = POINTER(c_short) # short[]
    # numpy.frombuffer(cast(in_data.pDataBuffer, POINTER(ArrayType)).contents, dtype=c_int16)

    # sampleRate = c_int()
    numChannels = c_int(2)
    samplesRead = c_int(1)
    samplesWritten = c_int(0)

    # inFile = openInputWaveFile(inFileName, &sampleRate, &numChannels);
    if outputSampleRate != 0:
        sampleRate = outputSampleRate

    # outFile = openOutputWaveFile(outFileName, sampleRate, numChannels);
    print('setting up')
    '''

    # samplerate = c_int(f.getframerate())
    # numChannels = c_int(f.getnchannels())

    sStream = sonicCreateStream(22050, 2) # samplerate, channels
    sonicSetSpeed(sStream, speed)
    sonicSetPitch(sStream, pitch)
    sonicSetRate(sStream, rate)
    sonicSetVolume(sStream, volume)
    sonicSetChordPitch(sStream, emulateChordPitch)
    sonicSetQuality(sStream, quality)
    # sonicFlushStream(sStream)

    print('done setting up')
    '''
    while (samplesRead.value > 0):
        # samplesRead = readFromWaveFile(inFile, inBuffer, BUFFER_SIZE / numChannels);
        if (samplesRead.value == 0):
            sonic.sonicFlushStream(stream)
        else:
            sonic.sonicWriteShortToStream(stream, cast(inBuffer, POINTER(c_short)), samplesRead)
            while (samplesWritten.value > 0):
                samplesWritten = sonic.sonicReadShortFromStream(stream, cast(outBuffer, POINTER(c_short)), BUFFER_SIZE / numChannels)
                if samplesWritten.value > 0:
                    wavfile.write(audiobookOut, samplerate, np.frombuffer(cast(cast(outBuffer, POINTER(c_short)).pDataBuffer, POINTER(Array)).contents, dtype=c_int16))
                    # writeToWaveFile(outFile, outBuffer, samplesWritten)
    '''
    # flatData = []
    # print(type(data))
    # print(type(data[0]))
    # for i in data:
        # flatData.append(i[0])
        # flatData.append(i[1])

    # buff = []
    # samplesRead = 1

    #read data


    # for sample in flatData:
        # inBuffer =
        # sonic.sonicWriteShortToStream(stream, cast(inBuffer, POINTER(c_short)), samplesRead)

        # samplesWritten = sonic.sonicReadShortFromStream(stream, cast(outBuffer, POINTER(c_short)), BUFFER_SIZE / numChannels)
        # outBuffer += np.frombuffer(outBuffer, c_short, samplesWritten)

    # wavfile.write(audiobookOut, samplerate, buff)




    print('done with the hard part, closing streams...')


# Print the usage.
def usage():
    print(
      "Usage: sonic [OPTION]... infile outfile\n"
      "    -c         -- Modify pitch by emulating vocal chords vibrating\n"
      "                  faster or slower.\n"
      "    -n         -- Enable nonlinear speedup\n"
      "    -o         -- Override the sample rate of the output.  -o 44200\n"
      "                  on an input file at 22100 KHz will paly twice as fast\n"
      "                  and have twice the pitch.\n"
      "    -p pitch   -- Set pitch scaling factor.  1.3 means 30%% higher.\n"
      "    -q         -- Disable speed-up heuristics.  May increase quality.\n"
      "    -r rate    -- Set playback rate.  2.0 means 2X faster, and 2X "
      "pitch.\n"
      "    -s speed   -- Set speed up factor.  2.0 means 2X faster.\n"
      "    -v volume  -- Scale volume by a constant factor.\n")
    exit(1)


if __name__ == "__main__":
    inFileName = c_char_p()
    outFileName = c_char_p()
    speed = c_float(1.0)
    pitch = c_float(1)
    rate = c_float(1.0)
    volume = c_float(1.0)
    outputSampleRate = c_int(0)    # Means use the input file sample rate.
    emulateChordPitch = c_int(0)
    quality = c_int(0)
    xArg = c_int(1)
    enableNonlinearSpeedup = c_int(0)
    computeSpectrogram = c_int(0)
    numRows = c_int(0)
    numCols = c_int(0)

    speed = c_float(2.0)


    # runSonic(inFileName, outFileName, speed, pitch, rate, volume, outputSampleRate, emulateChordPitch, quality, enableNonlinearSpeedup, computeSpectrogram, numRows, numCols)

    initStream(p, f)
    initSonic(f, speed, pitch, rate, volume, quality, emulateChordPitch)

    # wait for stream to finish (5)
    while stream.is_active():
        time.sleep(0.1)

    done(stream, p, f)