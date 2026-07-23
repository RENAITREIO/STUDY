#include "numc.h"
#include <structmember.h>

PyTypeObject Matrix61cType;

/* Helper functions for initalization of matrices and vectors */

/*
 * Return a tuple given rows and cols
 */
PyObject *get_shape(int rows, int cols) {
  if (rows == 1 || cols == 1) {
    return PyTuple_Pack(1, PyLong_FromLong(rows * cols));
  } else {
    return PyTuple_Pack(2, PyLong_FromLong(rows), PyLong_FromLong(cols));
  }
}
/*
 * Matrix(rows, cols, low, high). Fill a matrix random double values
 */
int init_rand(PyObject *self, int rows, int cols, unsigned int seed, double low,
              double high) {
    matrix *new_mat;
    int alloc_failed = allocate_matrix(&new_mat, rows, cols);
    if (alloc_failed) return alloc_failed;
    rand_matrix(new_mat, seed, low, high);
    ((Matrix61c *)self)->mat = new_mat;
    ((Matrix61c *)self)->shape = get_shape(new_mat->rows, new_mat->cols);
    return 0;
}

/*
 * Matrix(rows, cols, val). Fill a matrix of dimension rows * cols with val
 */
int init_fill(PyObject *self, int rows, int cols, double val) {
    matrix *new_mat;
    int alloc_failed = allocate_matrix(&new_mat, rows, cols);
    if (alloc_failed)
        return alloc_failed;
    else {
        fill_matrix(new_mat, val);
        ((Matrix61c *)self)->mat = new_mat;
        ((Matrix61c *)self)->shape = get_shape(new_mat->rows, new_mat->cols);
    }
    return 0;
}

/*
 * Matrix(rows, cols, 1d_list). Fill a matrix with dimension rows * cols with 1d_list values
 */
int init_1d(PyObject *self, int rows, int cols, PyObject *lst) {
    if (rows * cols != PyList_Size(lst)) {
        PyErr_SetString(PyExc_ValueError, "Incorrect number of elements in list");
        return -1;
    }
    matrix *new_mat;
    int alloc_failed = allocate_matrix(&new_mat, rows, cols);
    if (alloc_failed) return alloc_failed;
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            set(new_mat, i, j, PyFloat_AsDouble(PyList_GetItem(lst, count)));
            count++;
        }
    }
    ((Matrix61c *)self)->mat = new_mat;
    ((Matrix61c *)self)->shape = get_shape(new_mat->rows, new_mat->cols);
    return 0;
}

/*
 * Matrix(2d_list). Fill a matrix with dimension len(2d_list) * len(2d_list[0])
 */
int init_2d(PyObject *self, PyObject *lst) {
    int rows = PyList_Size(lst);
    if (rows == 0) {
        PyErr_SetString(PyExc_ValueError,
                        "Cannot initialize numc.Matrix with an empty list");
        return -1;
    }
    int cols;
    if (!PyList_Check(PyList_GetItem(lst, 0))) {
        PyErr_SetString(PyExc_ValueError, "List values not valid");
        return -1;
    } else {
        cols = PyList_Size(PyList_GetItem(lst, 0));
    }
    for (int i = 0; i < rows; i++) {
        if (!PyList_Check(PyList_GetItem(lst, i)) ||
                PyList_Size(PyList_GetItem(lst, i)) != cols) {
            PyErr_SetString(PyExc_ValueError, "List values not valid");
            return -1;
        }
    }
    matrix *new_mat;
    int alloc_failed = allocate_matrix(&new_mat, rows, cols);
    if (alloc_failed) return alloc_failed;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            set(new_mat, i, j,
                PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(lst, i), j)));
        }
    }
    ((Matrix61c *)self)->mat = new_mat;
    ((Matrix61c *)self)->shape = get_shape(new_mat->rows, new_mat->cols);
    return 0;
}

/*
 * This deallocation function is called when reference count is 0
 */
void Matrix61c_dealloc(Matrix61c *self) {
    deallocate_matrix(self->mat);
    Py_TYPE(self)->tp_free(self);
}

/* For immutable types all initializations should take place in tp_new */
PyObject *Matrix61c_new(PyTypeObject *type, PyObject *args,
                        PyObject *kwds) {
    /* size of allocated memory is tp_basicsize + nitems*tp_itemsize*/
    Matrix61c *self = (Matrix61c *)type->tp_alloc(type, 0);
    return (PyObject *)self;
}

/*
 * This matrix61c type is mutable, so needs init function. Return 0 on success otherwise -1
 */
int Matrix61c_init(PyObject *self, PyObject *args, PyObject *kwds) {
    /* Generate random matrices */
    if (kwds != NULL) {
        PyObject *rand = PyDict_GetItemString(kwds, "rand");
        if (!rand) {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }
        if (!PyBool_Check(rand)) {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }
        if (rand != Py_True) {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }

        PyObject *low = PyDict_GetItemString(kwds, "low");
        PyObject *high = PyDict_GetItemString(kwds, "high");
        PyObject *seed = PyDict_GetItemString(kwds, "seed");
        double double_low = 0;
        double double_high = 1;
        unsigned int unsigned_seed = 0;

        if (low) {
            if (PyFloat_Check(low)) {
                double_low = PyFloat_AsDouble(low);
            } else if (PyLong_Check(low)) {
                double_low = PyLong_AsLong(low);
            }
        }

        if (high) {
            if (PyFloat_Check(high)) {
                double_high = PyFloat_AsDouble(high);
            } else if (PyLong_Check(high)) {
                double_high = PyLong_AsLong(high);
            }
        }

        if (double_low >= double_high) {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }

        // Set seed if argument exists
        if (seed) {
            if (PyLong_Check(seed)) {
                unsigned_seed = PyLong_AsUnsignedLong(seed);
            }
        }

        PyObject *rows = NULL;
        PyObject *cols = NULL;
        if (PyArg_UnpackTuple(args, "args", 2, 2, &rows, &cols)) {
            if (rows && cols && PyLong_Check(rows) && PyLong_Check(cols)) {
                return init_rand(self, PyLong_AsLong(rows), PyLong_AsLong(cols), unsigned_seed, double_low,
                                 double_high);
            }
        } else {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }
    }
    PyObject *arg1 = NULL;
    PyObject *arg2 = NULL;
    PyObject *arg3 = NULL;
    if (PyArg_UnpackTuple(args, "args", 1, 3, &arg1, &arg2, &arg3)) {
        /* arguments are (rows, cols, val) */
        if (arg1 && arg2 && arg3 && PyLong_Check(arg1) && PyLong_Check(arg2) && (PyLong_Check(arg3)
                || PyFloat_Check(arg3))) {
            if (PyLong_Check(arg3)) {
                return init_fill(self, PyLong_AsLong(arg1), PyLong_AsLong(arg2), PyLong_AsLong(arg3));
            } else
                return init_fill(self, PyLong_AsLong(arg1), PyLong_AsLong(arg2), PyFloat_AsDouble(arg3));
        } else if (arg1 && arg2 && arg3 && PyLong_Check(arg1) && PyLong_Check(arg2) && PyList_Check(arg3)) {
            /* Matrix(rows, cols, 1D list) */
            return init_1d(self, PyLong_AsLong(arg1), PyLong_AsLong(arg2), arg3);
        } else if (arg1 && PyList_Check(arg1) && arg2 == NULL && arg3 == NULL) {
            /* Matrix(rows, cols, 1D list) */
            return init_2d(self, arg1);
        } else if (arg1 && arg2 && PyLong_Check(arg1) && PyLong_Check(arg2) && arg3 == NULL) {
            /* Matrix(rows, cols, 1D list) */
            return init_fill(self, PyLong_AsLong(arg1), PyLong_AsLong(arg2), 0);
        } else {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments");
            return -1;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments");
        return -1;
    }
}

/*
 * List of lists representations for matrices
 */
PyObject *Matrix61c_to_list(Matrix61c *self) {
    int rows = self->mat->rows;
    int cols = self->mat->cols;
    PyObject *py_lst = NULL;
    if (self->mat->is_1d) {  // If 1D matrix, print as a single list
        py_lst = PyList_New(rows * cols);
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                PyList_SetItem(py_lst, count, PyFloat_FromDouble(get(self->mat, i, j)));
                count++;
            }
        }
    } else {  // if 2D, print as nested list
        py_lst = PyList_New(rows);
        for (int i = 0; i < rows; i++) {
            PyList_SetItem(py_lst, i, PyList_New(cols));
            PyObject *curr_row = PyList_GetItem(py_lst, i);
            for (int j = 0; j < cols; j++) {
                PyList_SetItem(curr_row, j, PyFloat_FromDouble(get(self->mat, i, j)));
            }
        }
    }
    return py_lst;
}

PyObject *Matrix61c_class_to_list(Matrix61c *self, PyObject *args) {
    PyObject *mat = NULL;
    if (PyArg_UnpackTuple(args, "args", 1, 1, &mat)) {
        if (!PyObject_TypeCheck(mat, &Matrix61cType)) {
            PyErr_SetString(PyExc_TypeError, "Argument must of type numc.Matrix!");
            return NULL;
        }
        Matrix61c* mat61c = (Matrix61c*)mat;
        return Matrix61c_to_list(mat61c);
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments");
        return NULL;
    }
}

/*
 * Add class methods
 */
PyMethodDef Matrix61c_class_methods[] = {
    {"to_list", (PyCFunction)Matrix61c_class_to_list, METH_VARARGS, "Returns a list representation of numc.Matrix"},
    {NULL, NULL, 0, NULL}
};

/*
 * Matrix61c string representation. For printing purposes.
 */
PyObject *Matrix61c_repr(PyObject *self) {
    PyObject *py_lst = Matrix61c_to_list((Matrix61c *)self);
    return PyObject_Repr(py_lst);
}

/* NUMBER METHODS */

/*
 * Add the second numc.Matrix (Matrix61c) object to the first one. The first operand is
 * self, and the second operand can be obtained by casting `args`.
 */
PyObject *Matrix61c_add(Matrix61c* self, PyObject* args) {
    if (!PyObject_TypeCheck(args, &Matrix61cType)) {
        PyErr_SetString(PyExc_TypeError, "Operands must be numc.Matrix");
        return NULL;
    }
    Matrix61c *other = (Matrix61c *)args;
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    if (allocate_matrix(&m, self->mat->rows, self->mat->cols)) {
        Py_DECREF(result);
        return NULL;
    }
    if (add_matrix(m, self->mat, other->mat)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * Substract the second numc.Matrix (Matrix61c) object from the first one. The first operand is
 * self, and the second operand can be obtained by casting `args`.
 */
PyObject *Matrix61c_sub(Matrix61c* self, PyObject* args) {
    if (!PyObject_TypeCheck(args, &Matrix61cType)) {
        PyErr_SetString(PyExc_TypeError, "Operands must be numc.Matrix");
        return NULL;
    }
    Matrix61c *other = (Matrix61c *)args;
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    if (allocate_matrix(&m, self->mat->rows, self->mat->cols)) {
        Py_DECREF(result);
        return NULL;
    }
    if (sub_matrix(m, self->mat, other->mat)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * NOT element-wise multiplication. The first operand is self, and the second operand
 * can be obtained by casting `args`.
 */
PyObject *Matrix61c_multiply(Matrix61c* self, PyObject *args) {
    if (!PyObject_TypeCheck(args, &Matrix61cType)) {
        PyErr_SetString(PyExc_TypeError, "Operands must be numc.Matrix");
        return NULL;
    }
    Matrix61c *other = (Matrix61c *)args;
    int rows = self->mat->rows;
    int cols = other->mat->cols;
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    if (allocate_matrix(&m, rows, cols)) {
        Py_DECREF(result);
        return NULL;
    }
    if (mul_matrix(m, self->mat, other->mat)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * Negates the given numc.Matrix.
 */
PyObject *Matrix61c_neg(Matrix61c* self) {
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    if (allocate_matrix(&m, self->mat->rows, self->mat->cols)) {
        Py_DECREF(result);
        return NULL;
    }
    if (neg_matrix(m, self->mat)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * Take the element-wise absolute value of this numc.Matrix.
 */
PyObject *Matrix61c_abs(Matrix61c *self) {
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    if (allocate_matrix(&m, self->mat->rows, self->mat->cols)) {
        Py_DECREF(result);
        return NULL;
    }
    if (abs_matrix(m, self->mat)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * Raise numc.Matrix (Matrix61c) to the `pow`th power. You can ignore the argument `optional`.
 */
PyObject *Matrix61c_pow(Matrix61c *self, PyObject *pow, PyObject *optional) {
    (void)optional;
    int exponent = (int)PyLong_AsLong(pow);
    if (exponent < 0) {
        PyErr_SetString(PyExc_ValueError, "Exponent must be non-negative");
        return NULL;
    }
    Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
    if (!result) return NULL;
    matrix *m;
    int n = self->mat->rows;
    if (allocate_matrix(&m, n, n)) {
        Py_DECREF(result);
        return NULL;
    }
    if (pow_matrix(m, self->mat, exponent)) {
        deallocate_matrix(m);
        Py_DECREF(result);
        return NULL;
    }
    result->mat = m;
    result->shape = get_shape(m->rows, m->cols);
    return (PyObject *)result;
}

/*
 * Create a PyNumberMethods struct for overloading operators with all the number methods you have
 * define. You might find this link helpful: https://docs.python.org/3.6/c-api/typeobj.html
 */
PyNumberMethods Matrix61c_as_number = {
    .nb_add = (binaryfunc)Matrix61c_add,
    .nb_subtract = (binaryfunc)Matrix61c_sub,
    .nb_multiply = (binaryfunc)Matrix61c_multiply,
    .nb_negative = (unaryfunc)Matrix61c_neg,
    .nb_absolute = (unaryfunc)Matrix61c_abs,
    .nb_power = (ternaryfunc)Matrix61c_pow,
};


/* INSTANCE METHODS */

/*
 * Given a numc.Matrix self, parse `args` to (int) row, (int) col, and (double/int) val.
 * Return None in Python (this is different from returning null).
 */
PyObject *Matrix61c_set_value(Matrix61c *self, PyObject* args) {
    int row, col;
    double val;
    if (!PyArg_ParseTuple(args, "iid", &row, &col, &val)) {
        return NULL;
    }
    set(self->mat, row, col, val);
    Py_RETURN_NONE;
}

/*
 * Given a numc.Matrix `self`, parse `args` to (int) row and (int) col.
 * Return the value at the `row`th row and `col`th column, which is a Python
 * float/int.
 */
PyObject *Matrix61c_get_value(Matrix61c *self, PyObject* args) {
    int row, col;
    if (!PyArg_ParseTuple(args, "ii", &row, &col)) {
        return NULL;
    }
    double val = get(self->mat, row, col);
    return PyFloat_FromDouble(val);
}

/*
 * Create an array of PyMethodDef structs to hold the instance methods.
 * Name the python function corresponding to Matrix61c_get_value as "get" and Matrix61c_set_value
 * as "set"
 * You might find this link helpful: https://docs.python.org/3.6/c-api/structures.html
 */
PyMethodDef Matrix61c_methods[] = {
    {"get", (PyCFunction)Matrix61c_get_value, METH_VARARGS, "Get value at (row, col)"},
    {"set", (PyCFunction)Matrix61c_set_value, METH_VARARGS, "Set value at (row, col) to val"},
    {NULL, NULL, 0, NULL}
};

/* INDEXING */

/*
 * Given a numc.Matrix `self`, index into it with `key`. Return the indexed result.
 */
PyObject *Matrix61c_subscript(Matrix61c* self, PyObject* key) {
    /* int key: for 1D, flat index -> value; for 2D, row index -> row slice */
    if (PyLong_Check(key)) {
        long idx = PyLong_AsLong(key);
        if (self->mat->is_1d) {
            int total = self->mat->rows * self->mat->cols;
            if (idx < 0 || idx >= total) {
                PyErr_SetString(PyExc_IndexError, "Index out of range");
                return NULL;
            }
            int row = idx / self->mat->cols;
            int col = idx % self->mat->cols;
            return PyFloat_FromDouble(get(self->mat, row, col));
        }
        /* 2D: return row slice */
        if (idx < 0 || idx >= self->mat->rows) {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            return NULL;
        }
        Matrix61c *result = (Matrix61c *)Matrix61c_new(&Matrix61cType, NULL, NULL);
        if (!result) return NULL;
        matrix *m;
        if (allocate_matrix_ref(&m, self->mat, idx, 0, 1, self->mat->cols)) {
            Py_DECREF(result);
            return NULL;
        }
        result->mat = m;
        result->shape = get_shape(m->rows, m->cols);
        return (PyObject *)result;
    }
    /* (row, col) tuple -> element value */
    if (PyTuple_Check(key) && PyTuple_Size(key) == 2) {
        PyObject *r_obj = PyTuple_GetItem(key, 0);
        PyObject *c_obj = PyTuple_GetItem(key, 1);
        if (!PyLong_Check(r_obj) || !PyLong_Check(c_obj)) {
            PyErr_SetString(PyExc_TypeError, "Indices must be integers");
            return NULL;
        }
        long row = PyLong_AsLong(r_obj);
        long col = PyLong_AsLong(c_obj);
        if (row < 0 || row >= self->mat->rows || col < 0 || col >= self->mat->cols) {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            return NULL;
        }
        return PyFloat_FromDouble(get(self->mat, row, col));
    }
    PyErr_SetString(PyExc_TypeError, "Invalid index type");
    return NULL;
}

/*
 * Given a numc.Matrix `self`, index into it with `key`, and set the indexed result to `v`.
 */
int Matrix61c_set_subscript(Matrix61c* self, PyObject *key, PyObject *v) {
    /* (row, col) tuple -> set element */
    if (PyTuple_Check(key) && PyTuple_Size(key) == 2) {
        PyObject *r_obj = PyTuple_GetItem(key, 0);
        PyObject *c_obj = PyTuple_GetItem(key, 1);
        if (!PyLong_Check(r_obj) || !PyLong_Check(c_obj)) {
            PyErr_SetString(PyExc_TypeError, "Indices must be integers");
            return -1;
        }
        long row = PyLong_AsLong(r_obj);
        long col = PyLong_AsLong(c_obj);
        if (row < 0 || row >= self->mat->rows || col < 0 || col >= self->mat->cols) {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            return -1;
        }
        double val = PyFloat_AsDouble(v);
        if (PyErr_Occurred()) return -1;
        set(self->mat, row, col, val);
        return 0;
    }
    /* int key on 1D: flat index -> set element */
    if (PyLong_Check(key) && self->mat->is_1d) {
        long idx = PyLong_AsLong(key);
        int total = self->mat->rows * self->mat->cols;
        if (idx < 0 || idx >= total) {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            return -1;
        }
        int row = idx / self->mat->cols;
        int col = idx % self->mat->cols;
        double val = PyFloat_AsDouble(v);
        if (PyErr_Occurred()) return -1;
        set(self->mat, row, col, val);
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "Invalid index or unsupported assignment");
    return -1;
}

PyMappingMethods Matrix61c_mapping = {
    NULL,
    (binaryfunc) Matrix61c_subscript,
    (objobjargproc) Matrix61c_set_subscript,
};

/* INSTANCE ATTRIBUTES*/
PyMemberDef Matrix61c_members[] = {
    {
        "shape", T_OBJECT_EX, offsetof(Matrix61c, shape), 0,
        "(rows, cols)"
    },
    {NULL}  /* Sentinel */
};

PyTypeObject Matrix61cType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "numc.Matrix",
    .tp_basicsize = sizeof(Matrix61c),
    .tp_dealloc = (destructor)Matrix61c_dealloc,
    .tp_repr = (reprfunc)Matrix61c_repr,
    .tp_as_number = &Matrix61c_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,
    .tp_doc = "numc.Matrix objects",
    .tp_methods = Matrix61c_methods,
    .tp_members = Matrix61c_members,
    .tp_as_mapping = &Matrix61c_mapping,
    .tp_init = (initproc)Matrix61c_init,
    .tp_new = Matrix61c_new
};


struct PyModuleDef numcmodule = {
    PyModuleDef_HEAD_INIT,
    "numc",
    "Numc matrix operations",
    -1,
    Matrix61c_class_methods
};

/* Initialize the numc module */
PyMODINIT_FUNC PyInit_numc(void) {
    PyObject* m;

    if (PyType_Ready(&Matrix61cType) < 0)
        return NULL;

    m = PyModule_Create(&numcmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&Matrix61cType);
    PyModule_AddObject(m, "Matrix", (PyObject *)&Matrix61cType);
    printf("CS61C Fall 2020 Project 4: numc imported!\n");
    fflush(stdout);
    return m;
}
