/* 使用 C 或 C++ 扩展 Python: 一个简单的例子
[spam](https://docs.python.org/zh-cn/3/extending/extending.html)
*/
#define PY_SSIZE_t_CLEAN
#include <Python.h>

static PyObject *SpamError;

// 提供 Python spam.system 函数
static PyObject *
spam_system(PyObject *self, PyObject *args) {
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(SpamError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyMethodDef SpamMethods[] = {
    {
        "system",
        spam_system,
        METH_VARARGS,   // 可选值有 METH_VARARGS,
                        // METH_VARARGS | METH_KEYWORDS
                        // 前者使用 tuple 格式的参数
                        // 后者接受关键字参数并使用
                        // PyArg_ParseTupleAndKeywords() 来解析参数
        "Execute a shell command."
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef spammoudle = {
    PyModuleDef_HEAD_INIT,
    "spam",
    "Spam Module Functions",
    -1,
    SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void) {
    PyObject *m;
    m = PyModule_Create(&spammoudle);
    if (m == NULL)
        return NULL;
    
    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_XINCREF(SpamError);
    if (PyModule_AddObject(m, "error", SpamError) < 0) {
        Py_XDECREF(SpamError);
        Py_CLEAR(SpamError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
