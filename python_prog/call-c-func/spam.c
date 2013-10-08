#include <Python.h>

// The self argument points to the module object for module-level functions; 
// for a method it would point to the object instance.
//
// The args argument will be a pointer to a Python tuple object containing the arguments. 
// Each item of the tuple corresponds to an argument in the call’s argument list.
static PyObject * spam_system(PyObject *self, PyObject *args) {
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);
	return PyLong_FromLong(sts);
}

static PyMethodDef SpamMethods[] = {
		{"system",  spam_system, METH_VARARGS,
			"Execute a shell command."},
		{NULL, NULL, 0, NULL}        /* Sentinel */
};


