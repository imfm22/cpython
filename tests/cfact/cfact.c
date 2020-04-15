#include <Python.h>

// C 函数
int cfactorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * cfactorial(n - 1);
    }
}

// 使用模板进行包装
static PyObject * factorial(PyObject *self, PyObject *args) {
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    int result = cfactorial(n);
    return Py_BuildValue("i", result);
}

static PyMethodDef mainMethods[] = {
    {"factorial", factorial, METH_VARARGS, "Calculate the factorial of n"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef cfact = {
    PyModuleDef_HEAD_INIT,
    "cfact", "Factorial Calculation",
    -1,
    mainMethods
};

// 此处初始化函数名称必须遵从 PyInit_<module-name> 的格式
PyMODINIT_FUNC PyInit_cfact(void) {
    return PyModule_Create(&cfact);
}
