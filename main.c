#define PY_SSIZE_T_CLEAN  /* Make "s#" use Py_ssize_t rather than int. */
#include <Python.h>
#include <math.h>
#include <stdio.h>


/*
https://docs.python.org/3/extending/extending.html
*/
static PyObject * distangle(PyObject *self, PyObject *args)
{
    double x1,y1;
    double x2,y2;

    if ( !PyArg_ParseTuple(args, "(dd)(dd)", &x1, &y1, &x2, &y2) )
        return NULL;

    double deltaX = (y2-y1)*(y2-y1);
    double deltaY = (x2-x1)*(x2-x1);

    double distance = sqrt(deltaY + deltaX);

    double radians = atan2(deltaY, deltaX);
    double angle = radians * (180 / M_PI);

    return Py_BuildValue("(dd)", distance, angle);
}






/*
const float gravity = 9.8;     // units of metres/sec/sec
const float deltaT  = 0.001;   // equals 0.001 sec or 1 millisecond

var xVelocity = 0.010;         // units metres/sec equals 10 cm/sec 
var x = 0.0;                   // units metres
var y = 0.0;                   // units metres

while (true) {
  var xAcceleration = -gravity * (x/L) * (L-y)/L;

  x += (xVelocity + (xAcceleration/2 * deltaT)) * deltaT;
  y  = Math.SQRT(L*L - x*x) - L; 

  xVelocity += xAcceleration * deltaT;
}
*/




static PyMethodDef methods[] = {
    {"distangle", (PyCFunction)distangle, METH_VARARGS, 
        "Calculate distance and angle from two points (tuples).\n Returns tuple with distance and angle."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "simplephys",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC
PyInit_simplephys(void)
{
    return PyModule_Create(&module);
}
