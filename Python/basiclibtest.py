# ctypes_test.py
import ctypes
import pathlib
import numpy as np

import ctypes
from ctypes import *

from scipy.io import wavfile

import sys

import os
import pyaudio
# import wave
import wavfile
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

c_short_p = POINTER(c_short)

audiobookWav = '/home/marvin/Media/Audiobooks/Snapshot.wav'

sonicLib = ctypes.CDLL(DIR + '/libsonic.so.0.3.0')
sonicStream = POINTER(sonicStreamStruct)


sonicCreateStream = sonicLib.sonicCreateStream
sonicCreateStream.restype = sonicStream
sonicCreateStream.argtypes = [c_int, c_int]

sonicSetSpeed = sonicLib.sonicSetSpeed
sonicSetSpeed.argtypes = [sonicStream, c_float]

sonicGetSpeed = sonicLib.sonicSetSpeed
sonicGetSpeed.restype = c_float
sonicGetSpeed.argtypes = [sonicStream]


sonicChangeFloatSpeed = sonicLib.sonicChangeShortSpeed
sonicChangeFloatSpeed.restype = c_int
sonicChangeFloatSpeed.argtypes = [POINTER(c_float), c_int, c_float, c_float, c_float, c_float, c_int, c_int, c_int]

# int sonicChangeShortSpeed(short* samples, int numSamples, float speed,
#                           float pitch, float rate, float volume,
#                           int useChordPitch, int sampleRate, int numChannels);


CHUNK = 1024

# if len(sys.argv) < 2:
#     print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
#     sys.exit(-1)

# wf = wave.open(audiobookWav, 'rb')
wf = wavfile.open(audiobookWav, 'r')

# instantiate PyAudio (1)
p = pyaudio.PyAudio()



def audioCallback(in_data, framesNeeded, time_info, status):
    global wf
    data = getFrames(wf, framesNeeded)
    return (data, pyaudio.paContinue)



# read data
def getFrames(wf, amt):
    data = wf.read_float(amt)

    # newData = []
    # for i in data:
    #     newData.append(i[0])
    #     newData.append(i[1])
    # shortData = (ctypes.c_float * len(newData))(*newData)
    # # sonicChangeFloatSpeed(shortData, c_int(len(newData) * 2), c_float(2.0), c_float(1.0), c_float(1.0), c_float(1.0), c_int(1), c_int(wf.sample_rate), c_int(wf.num_channels))

    print(np.array(data, dtype=c_float))
    exit(0)
    # return np.array(shortData, dtype=c_float)
    return np.array(data, dtype=c_float)
    # return None




# open stream (2)
stream = p.open(format=pyaudio.paFloat32,
                channels=wf.num_channels,
                rate=wf.sample_rate,
                output=True,
                stream_callback=audioCallback)


stream.start_stream()

while stream.is_active():
    time.sleep(0.1)

# data = getFrames(wf, CHUNK)

# # play stream (3)
# while len(data) > 0:
#     stream.write(data)
#     data = getFrames(wf, CHUNK)
#     # data = wf.readframes(CHUNK)

# stop stream (4)
stream.stop_stream()
stream.close()

# close PyAudio (5)
p.terminate()



# sStream = sonicCreateStream(22050, 2)
# sonicSetSpeed(sStream, c_float(2.0))
# print(sonicGetSpeed(sStream))




# struct sonicStreamStruct;
# typedef struct sonicStreamStruct* sonicStream;

# /* For all of the following functions, numChannels is multiplied by numSamples
#    to determine the actual number of values read or returned. */

# /* Create a sonic stream.  Return NULL only if we are out of memory and cannot
#   allocate the stream. Set numChannels to 1 for mono, and 2 for stereo. */
# sonicStream sonicCreateStream(int sampleRate, int numChannels);
# /* Destroy the sonic stream. */
# void sonicDestroyStream(sonicStream stream);
# /* Use this to write floating point data to be speed up or down into the stream.
#    Values must be between -1 and 1.  Return 0 if memory realloc failed,
#    otherwise 1 */
# int sonicWriteFloatToStream(sonicStream stream, float* samples, int numSamples);
# /* Use this to write 16-bit data to be speed up or down into the stream.
#    Return 0 if memory realloc failed, otherwise 1 */
# int sonicWriteShortToStream(sonicStream stream, short* samples, int numSamples);
# /* Use this to write 8-bit unsigned data to be speed up or down into the stream.
#    Return 0 if memory realloc failed, otherwise 1 */
# int sonicWriteUnsignedCharToStream(sonicStream stream, unsigned char* samples,
#                                    int numSamples);
# /* Use this to read floating point data out of the stream.  Sometimes no data
#    will be available, and zero is returned, which is not an error condition. */
# int sonicReadFloatFromStream(sonicStream stream, float* samples,
#                              int maxSamples);
# /* Use this to read 16-bit data out of the stream.  Sometimes no data will
#    be available, and zero is returned, which is not an error condition. */
# int sonicReadShortFromStream(sonicStream stream, short* samples,
#                              int maxSamples);
# /* Use this to read 8-bit unsigned data out of the stream.  Sometimes no data
#    will be available, and zero is returned, which is not an error condition. */
# int sonicReadUnsignedCharFromStream(sonicStream stream, unsigned char* samples,
#                                     int maxSamples);
# /* Force the sonic stream to generate output using whatever data it currently
#    has.  No extra delay will be added to the output, but flushing in the middle
#    of words could introduce distortion. */
# int sonicFlushStream(sonicStream stream);
# /* Return the number of samples in the output buffer */
# int sonicSamplesAvailable(sonicStream stream);
# /* Get the speed of the stream. */
# float sonicGetSpeed(sonicStream stream);
# /* Set the speed of the stream. */
# void sonicSetSpeed(sonicStream stream, float speed);
# /* Get the pitch of the stream. */
# float sonicGetPitch(sonicStream stream);
# /* Set the pitch of the stream. */
# void sonicSetPitch(sonicStream stream, float pitch);
# /* Get the rate of the stream. */
# float sonicGetRate(sonicStream stream);
# /* Set the rate of the stream. */
# void sonicSetRate(sonicStream stream, float rate);
# /* Get the scaling factor of the stream. */
# float sonicGetVolume(sonicStream stream);
# /* Set the scaling factor of the stream. */
# void sonicSetVolume(sonicStream stream, float volume);
# /* Get the chord pitch setting. */
# int sonicGetChordPitch(sonicStream stream);
# /* Set chord pitch mode on or off.  Default is off.  See the documentation
#    page for a description of this feature. */
# void sonicSetChordPitch(sonicStream stream, int useChordPitch);
# /* Get the quality setting. */
# int sonicGetQuality(sonicStream stream);
# /* Set the "quality".  Default 0 is virtually as good as 1, but very much
#  * faster. */
# void sonicSetQuality(sonicStream stream, int quality);
# /* Get the sample rate of the stream. */
# int sonicGetSampleRate(sonicStream stream);
# /* Set the sample rate of the stream.  This will drop any samples that have not
#  * been read. */
# void sonicSetSampleRate(sonicStream stream, int sampleRate);
# /* Get the number of channels. */
# int sonicGetNumChannels(sonicStream stream);
# /* Set the number of channels.  This will drop any samples that have not been
#  * read. */
# void sonicSetNumChannels(sonicStream stream, int numChannels);
# /* This is a non-stream oriented interface to just change the speed of a sound
#    sample.  It works in-place on the sample array, so there must be at least
#    speed*numSamples available space in the array. Returns the new number of
#    samples. */
# int sonicChangeFloatSpeed(float* samples, int numSamples, float speed,
#                           float pitch, float rate, float volume,
#                           int useChordPitch, int sampleRate, int numChannels);
# /* This is a non-stream oriented interface to just change the speed of a sound
#    sample.  It works in-place on the sample array, so there must be at least
#    speed*numSamples available space in the array. Returns the new number of
#    samples. */
# int sonicChangeShortSpeed(short* samples, int numSamples, float speed,
#                           float pitch, float rate, float volume,
#                           int useChordPitch, int sampleRate, int numChannels);


# sonicSetPitch = sonicLib.sonicSetPitch
# sonicSetPitch.argtypes = [sonicStream, c_float]

# sonicSetRate = sonicLib.sonicSetRate
# sonicSetRate.argtypes = [sonicStream, c_float]

# sonicSetVolume = sonicLib.sonicSetVolume
# sonicSetVolume.argtypes = [sonicStream, c_float]

# sonicSetChordPitch = sonicLib.sonicSetChordPitch
# sonicSetChordPitch.argtypes = [sonicStream, c_int]

# sonicSetQuality = sonicLib.sonicSetQuality
# sonicSetQuality.argtypes = [sonicStream, c_int]

# sonicFlushStream = sonicLib.sonicFlushStream
# sonicFlushStream.argtypes = [sonicStream]

# sonicWriteShortToStream = sonicLib.sonicWriteShortToStream
# sonicWriteShortToStream.restype = c_int
# sonicWriteShortToStream.argtypes = [sonicStream, POINTER(c_short), c_int]
# # sonicWriteShortToStream.argtypes = [sonicStream, ctypes.ARRAY(c_short, BUFFER_SIZE), c_int]

# sonicReadShortFromStream = sonicLib.sonicReadShortFromStream
# sonicReadShortFromStream.restype = c_int
# sonicReadShortFromStream.argtypes = [sonicStream, POINTER(c_short), c_int]
# # sonicReadShortFromStream.argtypes = [sonicStream, ctypes.ARRAY(c_short, BUFFER_SIZE), c_int]

# sonicDestroyStream = sonicLib.sonicDestroyStream
# sonicDestroyStream.argtypes = [sonicStream]
