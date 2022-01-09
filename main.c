#define PY_SSIZE_T_CLEAN  /* Make "s#" use Py_ssize_t rather than int. */
#include <Python.h>
#include <math.h>
#include <stdio.h>

/*
https://docs.python.org/3/extending/extending.html
*/
static PyObject * distance(PyObject *self, PyObject *args)
{
    double x1,y1;
    double x2,y2;

    if ( !PyArg_ParseTuple(args, "(dd)(dd)", &x1, &y1, &x2, &y2) )
        return NULL;

    double distance = sqrt( ((y2-y1)*(y2-y1)) + ((x2-x1)*(x2-x1)) );

    printf("%f, %f, %f, %f\n",x1,y1,x2,y2);

    return PyFloat_FromDouble(distance);
}

static PyMethodDef methods[] = {
    {"distance", (PyCFunction)distance, METH_VARARGS, "Calculate distance between two points."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "pysimplephys",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC
PyInit_pysimplephys(void)
{
    return PyModule_Create(&module);
}
