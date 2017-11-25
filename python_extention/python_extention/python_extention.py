"""
read me

c++ extension for Python
Welcome to my programming world: This is the program about filter the unwanted noise from the ecg signal
With the help of c++ doing datas convolution, the filter process can be significantly speeded up, make the FIR filter more real time

The main program will be written in python and the data crunching will be achieved in c++ in order to speed up the process

The Python code are compiled by (32-bits Anaconda 4.40 : python 3.6.3) and the soulution is created in Visual Studio 2017
ps: the version of the python is extremely important!!!!!!!!!!!!!! be careful your python compiled are 32-bits or 64-bits!

The way to set up the links between the python and c++ are the same procedure taken by the link below: 
https://docs.microsoft.com/en-us/visualstudio/python/cpp-and-python
To install the Visual studio with can creating c++ extensions for python, please check the following link:
https://docs.microsoft.com/en-us/visualstudio/python/installation

@author : Himmy Tam
"""
import numpy as np
import pylab as pl

data=np.loadtxt('C:\ctest.dat')                            #read the ecg from the dat file 
ecg_signal = data[:,1]                                     #column 1 of this file is the ecg value
time = data[:,0]                                           #column 0 is the sampling time
ecg_signal = ((ecg_signal*0.002)-4.096)/500                #gain of 500
ecg_signal = ecg_signal*1000                               #put the voltage into micro scale

if __name__ == "__main__":                                   
    from superfastcode import fir_convolution,filter_design   #import the function from the c++ extension module - superfastcode

    design_parameters=(1001,1,1000,45,55) #must be python tuple type
    """
    design_parameters = (taps,filter_type,fs,f1,f2) 
    1. taps = number of taps of the filter
    2. filter_type = 1 - 4
       1 ---->Bandstop Filter
       2 ---->Lowpass Filter
       3 ---->Highpass Filter
       4 ---->Bandpass Filter
       5 ---->Think again!!!
    3. fs = sampling rate of the signal, used for normalized the frequence
    4. f1 = First important frequency, if you know how filter works, you should know what should put inside there
    5. f2 = Second importrant frequency (can put any arbitary value only for low pass and high pass filter design)
    ps: the first and second frequecny are decided seen from 0 to +pi
    """
    x= filter_design(design_parameters)                             #call the c++ function 
    out_put_array= np.zeros(len(ecg_signal))

    for i in range(len(ecg_signal)):                                #keep inserting input value
        next_input_value = ecg_signal[i]
        filtered_signal = fir_convolution(next_input_value)         #call c++ function to do convolution
        out_put_array[i] = filtered_signal                          #get the filtered signal

    pl.figure(1)
    pl.title('Time domain plot of filtered ECG signal')
    pl.ylabel('Voltage (mV)')
    pl.xlabel('Time (ms)')
    pl.plot(out_put_array)
    pl.show()
    
    f_axis=np.linspace(0,1000,len(out_put_array))
    filted_signal = np.fft.fft(out_put_array);

    pl.figure(figsize=(20,10))
    x_tick =np.linspace(0,1000,20)
    pl.xticks(x_tick)
    pl.title('Frequency domain plot of the filtered ECG signal')
    pl.ylabel('Amplitude')
    pl.xlabel('Frequency (Hz)')
    pl.plot(f_axis,abs(filted_signal))
    pl.show()