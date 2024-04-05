"""
setup.py
"""
 
from distutils.core import setup, Extension
import os
import numpy

neuware_home = os.environ.get('NEUWARE_HOME')
 
example_module = Extension('_pycnnl',
                            sources=['./swig/pycnnl_wrap.cxx',
                            './src/net.cc',
                            './src/layers.cc',
                            './src/public.cc',
                            './src/tool.cc'], 
                            include_dirs=[neuware_home + '/include', './include',numpy.get_include()],
                            libraries=['cnnl', 'cnrt'],
                            library_dirs=[neuware_home + '/lib64'],
                            swig_opts=['c++'],
                            extra_compile_args=['-std=c++11'],
                            extra_link_args=['-std=c++11'],
                           )
 
setup (name = 'pycnnl',
       version = '0.1',
       author      = "ict-zkg",
       description = """cnnl op for python""",
       ext_modules = [example_module],
       py_modules = ["pycnnl"],
       )
