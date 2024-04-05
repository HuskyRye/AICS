%module pycnnlmlp
%{
    #define SWIG_FILE_WITH_INIT
    #include "layers.hpp"
    #include "tool.h"
%}

%include "std_vector.i"

%include "std_string.i"

%include "numpy.i"

%init %{
    import_array();
%}


namespace std {
    %template(FloatVector) vector<float>;
    %template(IntVector) vector<int>;
    %template(DoubleVector) vector<double>;
    %template(FloatVector2) vector<vector<float>>;
    %template(IntVector2) vector<vector<int>>;
    %template(DoubleVector2) vector<vector<double>>;
}

%include "layers.hpp"
%include "tool.h"
