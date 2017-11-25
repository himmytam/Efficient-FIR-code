# Efficient-FIR-code : Read the following statement first!

**Create c++ extension for python
This is the program about filter the unwanted noise from the ecg signal
With the help of c++ doing datas convolution, the filter process can be significantly speeded up, resulting a higher performance.
The main program will be written in python and the data crunching will be achieved in c++ in order to speed up the process
**
**Requirement to run the program**

1. Visual studio 2017 with both the Desktop Development with C++ and Python Development. 
  -link to down from Microsoft: https://docs.microsoft.com/en-us/visualstudio/python/installation

2. 32-bits version Anaconda 4.40 with Python 3.6.3 :

3. Click the file above, python extension > python extension.sln > open it in Vsual studio 2017
you should able to see the soulution Explorer on the right hand site 

4. Make sure that your python environments are sat to 32-bits python

5. Left click the c++ solution > Property> Set configuration to all configurations

6. C/C++>Additional Include Diretories>Edit...>add folder (include) which is contained in your Python or Anaconda directory

7. Linker>Additional Library Directories >Edit...>add folder (libs) which is contained in your Python or Anaconda directory 

6 & 7 simply mean open the directory where you download the Python or Anacoda, 
the directory maybe in C drive>User ....


To Check more datails of the presedure discribed above  (In section *Creating the core c++ Project*):
https://docs.microsoft.com/en-us/visualstudio/python/cpp-and-python

A vedio version discribing the set up above:
https://docs.microsoft.com/en-us/visualstudio/python/debugging-mixed-mode

The Python code are compiled by (32-bits Anaconda 4.40 : python 3.6.3) and the soulution is created in Visual Studio 2017
ps: the version of the python is extremely important!!!!!!!!!!!!!!

@author : Himmy Tam
