import numpy as np
import wave
import struct
from matplotlib import pylab as plt


list_file = ['1_c3.wav', '2_d3.wav', '3_e3.wav', '4_f3.wav', '5_g3.wav', '6_a3.wav', '7_b3.wav', '8_c4.wav']
list_hz = [262, 294, 330, 349, 392, 440, 494, 523]

fs  = 44100
sec = 1
A   = 32767
samples = sec * fs

for i in range(len(list_hz)):
	# Wav用
	t = np.linspace(0, sec, samples)
	s = A * np.sin(2 * np.pi * list_hz[i] * t)
	s = s.astype(np.int16)

	data = struct.pack("h" * samples , *s)

	wf = wave.open(list_file[i], 'w')
	wf.setnchannels(1)
	wf.setsampwidth(2)
	wf.setframerate(fs)
	wf.writeframes(data)
	wf.close()

	plt.plot(s[0:441])
	plt.show()


	# GBA用
	fs_gba = 16384
	samples_gba = sec * fs_gba

	t = np.linspace(0, sec, fs_gba)
	s = A * np.sin(2 * np.pi * list_hz[i] * t)
	s = s.astype(np.int16)

	for j in range(len(s)):
		s[j] = s[j] >> 8

	data = struct.pack("b" * samples_gba , *s)

	wf = open(list_file[i][:-4]+'.bin', 'wb')
	wf.write(data)
	wf.close()

	plt.plot(s[0:163])
	plt.show()
