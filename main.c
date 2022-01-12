
#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>

#define PY_SSIZE_T_CLEAN  /* Make "s#" use Py_ssize_t rather than int. */
#include <Python.h>

/*
https://docs.python.org/3/extending/extending.html


TO DO:
DOT product:


MAX:
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

MIN:
#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

Clamp:
float Clamp01(float v) {
  return Min(Max(v, 0.0f), 1.0f);
}

AngleInRadians
loat AngleRad(Vector v1, Vector v2) {
  float cosAngle = DotProduct(v1, v2) / (v1.magnitude * v2.magnitude);
  return ArcCos(cosAngle);
}

LERP:
float Lerp(float a, float b, float t) {
  t = Clamp01(t); // Clamp01 makes sure t is between [0, 1]
  return (1.0f - t) * a + t * b;
}


Pendulum maths:

T = 2π√(I/mgD)
where:

m is the mass of the pendulum;
I is the moment of inertia of the mass; and
D is the distance from the center of mass to the point of suspension.



More on the Pendulum
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



static PyObject * anglecoords(PyObject *self, PyObject *args)
{
    double angle;
    double distance;

    if ( !PyArg_ParseTuple(args, "(dd)", &angle, &distance) )
        return NULL;

    double x = distance * cos(angle * M_PI / 180.0);
    double y = distance * sin(angle * M_PI / 180.0);

    return Py_BuildValue("(dd)", x, y);
}


static PyMethodDef methods[] = {
    {"distangle", (PyCFunction)distangle, METH_VARARGS, 
        "Calculate distance and angle from two points (tuples).\n Returns tuple with distance and angle."},
    {"anglecoords", (PyCFunction)anglecoords, METH_VARARGS, 
        "Calculate x and y coords from angle and distance tuple."},
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
