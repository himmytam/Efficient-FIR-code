#include <Python.h>
#include <Windows.h>
#include <cmath>    
#include <stdio.h>

const double pi = 3.141592653589793;
long taps, type;
float f1, f2, fs;
int x = 1;
double *buffer = new double[x]();
double *h = new double[x]();
int *n = new int[x]();
int val = 0;
int m;

PyObject* filter_design(PyObject*, PyObject* args) {                          // function will be seen by python
	if (!PyArg_ParseTuple(args, "llfff", &taps, &type, &fs, &f1, &f2));       // This function take 5 parameter
	buffer = new double[taps]();
	h = new double[taps]();

	//bandstop filter
	if (type == 1) {                    
		for (int g = 0; g < taps; g++) {
			m = g - (taps - 1)/2;
			h[g] = (1 /(m* pi)) *(sin((f1 * 2 * pi*m) / fs) - sin((f2 * 2 * pi*m) / fs));
			//printf("%d. %.50f\n", g, h[g]);
		}
		h[(taps-1)/2] =1- ((f2*2*pi)/fs - (f1 * 2 * pi) / fs) / pi;
		printf("bandstop_filter");
	}
	//low pass filte
	else if (type == 2) {                    
		for (int g = 0; g < taps; g++) {
			m = g - (taps - 1) / 2;
			h[g] = (1 / (m* pi)) *sin((f1 * 2 * pi*m) /fs);
		}
		h[(taps - 1) / 2] = (2 * pi*f1) / (fs*pi);
		printf("low_pass_filter");
	}
	//high pass filter
	else if (type == 3) {        
		for (int g = 0; g < taps; g++) {
			m = g - (taps - 1) / 2;
			h[g] = (1/(m* pi)) *- sin((f1 * 2 * pi *m)/fs);
		}
		h[(taps - 1) / 2] = 1-((f1*2*pi)/(fs*pi));
		printf("high_pass_filter");
	}
	//bandpass pass filter
	else if (type == 4) {                    
		for (int g = 0; g < taps; g++) {
			m = g - (taps - 1) / 2;
			h[g] = (1 / (m* pi)) *(sin((f2 * 2 * pi*m) /fs) - sin((f1 * 2 * pi*m) /fs));
			//printf("%d. %.50f\n", g, h[g]);
		}
		h[(taps - 1) / 2] = ((f2 * 2 * pi)/fs - (f1 * 2 * pi)/fs) / pi;
		printf("bandpass_filter");
	}
	else {
		printf("\nThis is not a proper Filter type input to the function! Please read the function description in the python part");
	}
		return PyLong_FromLong(type);
	}

PyObject* convolution(PyObject*, PyObject*o) {                           //function to do convolution
	double new_data_input = PyFloat_AsDouble(o);
	buffer[0] = new_data_input;
	double out_put_value = 0;
	for (int z = 0; z < taps; z++) {                                    //convolution
		out_put_value += buffer[z] * h[z];
	}
	for (int y = taps- 1; y> 0; y--) {                                  //shift the buffer, make it seem like the real convolution
		buffer[y] = buffer[y-1];
	}
	return PyFloat_FromDouble(out_put_value);
}

static PyMethodDef superfastcode_methods[] = {                          
	// The first property is the name exposed to python, the second is the C++ function name        
	{ "fir_convolution", (PyCFunction)convolution,METH_O, nullptr},                //fir_convolution will be the function name seen by python
	{ "filter_design", (PyCFunction)filter_design, METH_O, nullptr },
	// Terminate the array with an object containing nulls.
	{ nullptr, nullptr, 0, nullptr }
};


static PyModuleDef superfastcode_module = {
	PyModuleDef_HEAD_INIT,
	"superfastcode",                        // Module name
	"speed up the process for convolution", // Module description
	0,
	superfastcode_methods                   // Structure that defines the methods
};

PyMODINIT_FUNC PyInit_superfastcode() {
	return PyModule_Create(&superfastcode_module);
}